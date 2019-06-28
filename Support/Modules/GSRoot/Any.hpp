// *********************************************************************************************************************
// Description:		The classes GS::Any, GS::HashableAny, etc. are containers for single values of any type.
//					The contained type must adhere to specific compile time restrictions in each Any variant.
//					The class GS::GenericAny can be parametrized with the capabilities that are expected from the
//					contained type.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef ANY_HPP
#define ANY_HPP

#pragma once


#include <typeinfo>
#include "GSDebug.hpp"
#include "HashCommon.hpp"


namespace GS {


// === Capabilities of the Type in GenericAny ==========================================================================

namespace AnyCapabilities {

using Flags = UInt64;

constexpr Flags HasGenerateHashValue = 0b00000001;			// 'GenerateHashValue (t)' is required, where t is a value of the contained Type
constexpr Flags HasOperatorEquals    = 0b00000010;			// 't1 == t2'              is required, where t1 and t2 is a value of the contained Type
constexpr Flags HasOperatorNotEquals = 0b00000100;			// 't1 != t2'              is required, where t1 and t2 is a value of the contained Type

constexpr Flags Hashable             = HasGenerateHashValue | HasOperatorEquals;
constexpr Flags Comparable           = HasOperatorEquals | HasOperatorNotEquals;

}


// === Implementation details for GenericAny ===========================================================================

namespace ImpAny {


constexpr USize BufferSize	= sizeof  (void*);				// size in bytes of the in-place storage in GenericAny
constexpr USize BufferAlign	= alignof (void*);				// alignment provided by the in-place storage in GenericAny


template <class Type>
constexpr bool	FitsInBuffer = sizeof  (Type) <= BufferSize &&
							   alignof (Type) <= BufferAlign;


union Storage {
	alignas (BufferAlign) char	buffer[BufferSize];
	void*						ptr;
};


struct VTable {
	const std::type_info& (*getTypeInfo)   ();
	void				  (*destroy)       (Storage& storage);
	void				  (*copyConstruct) (Storage& destination, const Storage& source);
	void				  (*copyAssign)    (Storage& destination, const Storage& source);
	void				  (*moveConstruct) (Storage& destination, Storage& source);
	void				  (*moveAssign)    (Storage& destination, Storage& source);
	ULong				  (*getHashValue)  (const Storage& storage);
	bool				  (*isEqual)       (const Storage& leftOp, const Storage& rightOp);
	bool				  (*isNotEqual)    (const Storage& leftOp, const Storage& rightOp);
};


template <class Type>
struct VTableForBuffer
{
		// type query

	static const std::type_info&	GetTypeInfo ()
	{
		return typeid (Type);
	}

		// default capabilities

	static void		Destroy (Storage& storage)
	{
		UNUSED_PARAMETER (storage);		// VS 2015 bug: reports unused parameter if 'Type' is a class
		reinterpret_cast<Type&> (storage.buffer).~Type ();
	}

	static void		CopyConstruct (Storage& destination, const Storage& source)
	{
		new (destination.buffer) Type (reinterpret_cast<const Type&> (source.buffer));
	}

	static void		CopyAssign (Storage& destination, const Storage& source)
	{
		reinterpret_cast<Type&> (destination.buffer) = reinterpret_cast<const Type&> (source.buffer);
	}

	static void		MoveConstruct (Storage& destination, Storage& source)
	{
		new (destination.buffer) Type (reinterpret_cast<Type&&> (source.buffer));
		reinterpret_cast<Type&> (source.buffer).~Type ();
	}

	static void		MoveAssign (Storage& destination, Storage& source)
	{
		reinterpret_cast<Type&> (destination.buffer) = reinterpret_cast<Type&&> (source.buffer);
		reinterpret_cast<Type&> (source.buffer).~Type ();
	}

		// GetHashValue ()

	template <bool isEnabled, EnableIf<isEnabled>* = nullptr>
	static ULong	GetHashValue (const Storage& storage)
	{
		return GenerateHashValue (reinterpret_cast<const Type&> (storage.buffer));
	}

	template <bool isEnabled, EnableIf<!isEnabled>* = nullptr>
	static ULong	GetHashValue (const Storage& /*storage*/)
	{
		DBBREAK ();
		return 0;
	}

		// IsEqual ()

	template <bool isEnabled, EnableIf<isEnabled>* = nullptr>
	static bool		IsEqual (const Storage& leftOp, const Storage& rightOp)
	{
		return reinterpret_cast<const Type&> (leftOp.buffer) == reinterpret_cast<const Type&> (rightOp.buffer);
	}

	template <bool isEnabled, EnableIf<!isEnabled>* = nullptr>
	static bool		IsEqual (const Storage& /*leftOp*/, const Storage& /*rightOp*/)
	{
		DBBREAK ();
		return false;
	}

		// IsNotEqual ()

	template <bool isEnabled, EnableIf<isEnabled>* = nullptr>
	static bool		IsNotEqual (const Storage& leftOp, const Storage& rightOp)
	{
		return reinterpret_cast<const Type&> (leftOp.buffer) != reinterpret_cast<const Type&> (rightOp.buffer);
	}

	template <bool isEnabled, EnableIf<!isEnabled>* = nullptr>
	static bool		IsNotEqual (const Storage& /*leftOp*/, const Storage& /*rightOp*/)
	{
		DBBREAK ();
		return false;
	}
};


template <class Type>
struct VTableForPtr
{
		// type query

	static const std::type_info&	GetTypeInfo ()
	{
		return typeid (Type);
	}

		// default capabilities

	static void		Destroy (Storage& storage)
	{
		delete reinterpret_cast<Type*> (storage.ptr);
	}

	static void		CopyConstruct (Storage& destination, const Storage& source)
	{
		destination.ptr = new Type (*reinterpret_cast<const Type*> (source.ptr));
	}

	static void		CopyAssign (Storage& destination, const Storage& source)
	{
		*reinterpret_cast<Type*> (destination.ptr) = *reinterpret_cast<const Type*> (source.ptr);
	}

	static void		MoveConstruct (Storage& destination, Storage& source)
	{
		destination.ptr = source.ptr;
	}

	static void		MoveAssign (Storage& destination, Storage& source)
	{
		delete reinterpret_cast<Type*> (destination.ptr);
		destination.ptr = source.ptr;
	}

		// GetHashValue ()

	template <bool isEnabled, EnableIf<isEnabled>* = nullptr>
	static ULong	GetHashValue (const Storage& storage)
	{
		return GenerateHashValue (*reinterpret_cast<const Type*> (storage.ptr));
	}

	template <bool isEnabled, EnableIf<!isEnabled>* = nullptr>
	static ULong	GetHashValue (const Storage& /*storage*/)
	{
		DBBREAK ();
		return 0;
	}

		// IsEqual ()

	template <bool isEnabled, EnableIf<isEnabled>* = nullptr>
	static bool		IsEqual (const Storage& leftOp, const Storage& rightOp)
	{
		return *reinterpret_cast<const Type*> (leftOp.ptr) == *reinterpret_cast<const Type*> (rightOp.ptr);
	}

	template <bool isEnabled, EnableIf<!isEnabled>* = nullptr>
	static bool		IsEqual (const Storage& /*leftOp*/, const Storage& /*rightOp*/)
	{
		DBBREAK ();
		return false;
	}

		// IsNotEqual ()

	template <bool isEnabled, EnableIf<isEnabled>* = nullptr>
	static bool		IsNotEqual (const Storage& leftOp, const Storage& rightOp)
	{
		return *reinterpret_cast<const Type*> (leftOp.ptr) != *reinterpret_cast<const Type*> (rightOp.ptr);
	}

	template <bool isEnabled, EnableIf<!isEnabled>* = nullptr>
	static bool		IsNotEqual (const Storage& /*leftOp*/, const Storage& /*rightOp*/)
	{
		DBBREAK ();
		return false;
	}
};


template <AnyCapabilities::Flags Cap, class Type>
VTable*		GetVTableForType ()
{
	static_assert ((Cap & AnyCapabilities::HasGenerateHashValue) == 0 || HasGenerateHashValue<Type>, "'Type' has no GenerateHashValue ().");
	static_assert ((Cap & AnyCapabilities::HasOperatorEquals) == 0    || HasOperatorEquals<Type>,    "'Type' has no operator== ().");
	static_assert ((Cap & AnyCapabilities::HasOperatorNotEquals) == 0 || HasOperatorNotEquals<Type>, "'Type' has no operator!= ().");

	using VT = Conditional<FitsInBuffer<Type>, VTableForBuffer<Type>, VTableForPtr<Type>>;

	static VTable table = { VT::GetTypeInfo, VT::Destroy, VT::CopyConstruct, VT::CopyAssign, VT::MoveConstruct, VT::MoveAssign,
							VT::template GetHashValue<(Cap & AnyCapabilities::HasGenerateHashValue) != 0>,
							VT::template IsEqual<(Cap & AnyCapabilities::HasOperatorEquals) != 0>,
							VT::template IsNotEqual<(Cap & AnyCapabilities::HasOperatorNotEquals) != 0> };

	return &table;
}


}	// namespace ImpAny


// === class GenericAny ================================================================================================

template <AnyCapabilities::Flags Cap = 0>
class GenericAny final {
private:
	ImpAny::VTable*		vTable;
	ImpAny::Storage		storage;

	template <class Type>
	using IsEnabledType = EnableIf<!IsSame<Decay<Type>, GenericAny>>;

	void	Destroy ();

	template <class Type>
	void	ConstructFromValue (Type&& value);

	template <class Type, class... Args>
	void	ConstructFromArguments (Args&&... args);

	template <class Type>
	void	AssignSameType (Type&& value);

public:
	GenericAny ();
	GenericAny (const GenericAny& source);
	GenericAny (GenericAny&& source);

	template <class Type, class = IsEnabledType<Type>>
	GenericAny (Type&& value);

	~GenericAny ();

	GenericAny&		operator= (const GenericAny& source);
	GenericAny&		operator= (GenericAny&& source);

	template <class Type, class = IsEnabledType<Type>>
	GenericAny&		operator= (Type&& value);

	template <class Type, class... Args>
	void	New (Args&&... args);

	void	Clear ();
	bool	HasValue () const;

	template <class Type>
	bool	Is () const;

	template <class Type>	Type&		Get () &;
	template <class Type>	const Type&	Get () const&;
	template <class Type>	Type&&		Get () &&;

	operator HashValue () const;
	bool	operator== (const GenericAny& rightOp) const;
	bool	operator!= (const GenericAny& rightOp) const;
};


// === GenericAny methods ==============================================================================================

template <AnyCapabilities::Flags Cap>
GenericAny<Cap>::GenericAny ()
{
	vTable = nullptr;
}


template <AnyCapabilities::Flags Cap>
GenericAny<Cap>::GenericAny (const GenericAny& source)
{
	vTable = source.vTable;

	if (vTable != nullptr)
		vTable->copyConstruct (storage, source.storage);
}


template <AnyCapabilities::Flags Cap>
GenericAny<Cap>::GenericAny (GenericAny&& source)
{
	vTable = source.vTable;

	if (vTable != nullptr) {
		vTable->moveConstruct (storage, source.storage);
		source.vTable = nullptr;
	}
}


template <AnyCapabilities::Flags Cap>
template <class Type, class /*= IsEnabledType<Type>*/>
GenericAny<Cap>::GenericAny (Type&& value)
{
	ConstructFromValue (std::forward<Type> (value));
}


template <AnyCapabilities::Flags Cap>
GenericAny<Cap>::~GenericAny ()
{
	Destroy ();
}


template <AnyCapabilities::Flags Cap>
GenericAny<Cap>&	GenericAny<Cap>::operator= (const GenericAny& source)
{
	if (vTable == source.vTable) {
		if (vTable != nullptr)
			vTable->copyAssign (storage, source.storage);
	} else {
		Destroy ();

		if (source.vTable != nullptr) {
			vTable = source.vTable;
			vTable->copyConstruct (storage, source.storage);
		} else {
			vTable = nullptr;
		}
	}

	return *this;
}


template <AnyCapabilities::Flags Cap>
GenericAny<Cap>&	GenericAny<Cap>::operator= (GenericAny&& source)
{
	if (vTable == source.vTable) {
		if (vTable != nullptr) {
			vTable->moveAssign (storage, source.storage);
			source.vTable = nullptr;
		}
	} else {
		Destroy ();

		if (source.vTable != nullptr) {
			vTable = source.vTable;
			vTable->moveConstruct (storage, source.storage);
			source.vTable = nullptr;
		} else {
			vTable = nullptr;
		}
	}

	return *this;
}


template <AnyCapabilities::Flags Cap>
template <class Type, class /*= IsEnabledType<Type>*/>
GenericAny<Cap>&	GenericAny<Cap>::operator= (Type&& value)
{
	if (Is<Decay<Type>> ()) {
		AssignSameType (std::forward<Type> (value));
	} else {
		Destroy ();
		ConstructFromValue (std::forward<Type> (value));
	}

	return *this;
}


template <AnyCapabilities::Flags Cap>
template <class Type, class... Args>
void	GenericAny<Cap>::New (Args&&... args)
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	Destroy ();
	ConstructFromArguments<Type> (std::forward<Args> (args)...);
}


template <AnyCapabilities::Flags Cap>
void	GenericAny<Cap>::Clear ()
{
	if (vTable != nullptr) {
		vTable->destroy (storage);
		vTable = nullptr;
	}
}


template <AnyCapabilities::Flags Cap>
bool	GenericAny<Cap>::HasValue () const
{
	return vTable != nullptr;
}


template <AnyCapabilities::Flags Cap>
template <class Type>
bool	GenericAny<Cap>::Is () const
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	return vTable != nullptr && vTable->getTypeInfo () == typeid (Type);
}


template <AnyCapabilities::Flags Cap>
template <class Type>
Type&	GenericAny<Cap>::Get () &
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	DBASSERT (Is<Type> ());

	if (ImpAny::FitsInBuffer<Type>)
		return reinterpret_cast<Type&> (storage.buffer);
	else
		return *reinterpret_cast<Type*> (storage.ptr);
}


template <AnyCapabilities::Flags Cap>
template <class Type>
const Type&		GenericAny<Cap>::Get () const&
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	DBASSERT (Is<Type> ());

	if (ImpAny::FitsInBuffer<Type>)
		return reinterpret_cast<const Type&> (storage.buffer);
	else
		return *reinterpret_cast<const Type*> (storage.ptr);
}


template <AnyCapabilities::Flags Cap>
template <class Type>
Type&&	GenericAny<Cap>::Get () &&
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	DBASSERT (Is<Type> ());

	if (ImpAny::FitsInBuffer<Type>)
		return std::move (reinterpret_cast<Type&> (storage.buffer));
	else
		return std::move (*reinterpret_cast<Type*> (storage.ptr));
}


template <AnyCapabilities::Flags Cap>
GenericAny<Cap>::operator HashValue () const
{
	static_assert ((Cap & AnyCapabilities::HasGenerateHashValue) != 0, "This GS::GenericAny can hold values that do not provide GenerateHashValue ().");

	return (vTable == nullptr) ? 0 : vTable->getHashValue (storage);
}


template <AnyCapabilities::Flags Cap>
bool	GenericAny<Cap>::operator== (const GenericAny& rightOp) const
{
	static_assert ((Cap & AnyCapabilities::HasOperatorEquals) != 0, "This GS::GenericAny can hold values that do not provide operator== ().");

	return (vTable == nullptr && rightOp.vTable == nullptr) ||
		   (vTable != nullptr && rightOp.vTable != nullptr && DBVERIFY (vTable == rightOp.vTable) && vTable->isEqual (storage, rightOp.storage));
}


template <AnyCapabilities::Flags Cap>
bool	GenericAny<Cap>::operator!= (const GenericAny& rightOp) const
{
	static_assert ((Cap & AnyCapabilities::HasOperatorNotEquals) != 0, "This GS::GenericAny can hold values that do not provide operator!= ().");

	return (vTable != nullptr || rightOp.vTable != nullptr) &&
		   (vTable == nullptr || rightOp.vTable == nullptr || DBERROR (vTable != rightOp.vTable) || vTable->isNotEqual (storage, rightOp.storage));
}


template <AnyCapabilities::Flags Cap>
void	GenericAny<Cap>::Destroy ()
{
	if (vTable != nullptr)
		vTable->destroy (storage);
}


template <AnyCapabilities::Flags Cap>
template <class Type>
void	GenericAny<Cap>::ConstructFromValue (Type&& value)
{
	vTable = ImpAny::GetVTableForType<Cap, Decay<Type>> ();

	if (ImpAny::FitsInBuffer<Decay<Type>>)
		new (storage.buffer) Decay<Type> (std::forward<Type> (value));
	else
		storage.ptr = new Decay<Type> (std::forward<Type> (value));
}


template <AnyCapabilities::Flags Cap>
template <class Type, class... Args>
void	GenericAny<Cap>::ConstructFromArguments (Args&&... args)
{
	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

	vTable = ImpAny::GetVTableForType<Cap, Type> ();

	if (ImpAny::FitsInBuffer<Type>)
		new (storage.buffer) Type (std::forward<Args> (args)...);
	else
		storage.ptr = new Type (std::forward<Args> (args)...);
}


template <AnyCapabilities::Flags Cap>
template <class Type>
void	GenericAny<Cap>::AssignSameType (Type&& value)
{
	if (ImpAny::FitsInBuffer<Decay<Type>>)
		reinterpret_cast<Decay<Type>&> (storage.buffer) = std::forward<Type> (value);
	else
		*reinterpret_cast<Decay<Type>*> (storage.ptr) = std::forward<Type> (value);
}


// === Specialized Any classes =========================================================================================

using Any                   = GenericAny<>;
using HashableAny           = GenericAny<AnyCapabilities::Hashable>;
using ComparableAny         = GenericAny<AnyCapabilities::Comparable>;
using HashableComparableAny = GenericAny<AnyCapabilities::Hashable | AnyCapabilities::Comparable>;


}	// namespace GS


#endif
