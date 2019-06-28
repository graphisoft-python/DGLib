
// *****************************************************************************
//
//                              Class FixArray
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined FIXARRAY_HPP
#define FIXARRAY_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "RandomContainer.hpp"

#include "RandomContainerIterator.hpp"
#include "RandomContainerReverseIterator.hpp"
#include "Enumerator.hpp"
#include "BaseAlgorithms.hpp"
#include "InitializerRefList.hpp"

#include "Channel.hpp"

#include <new>
#include <utility>
#include <functional>


// ============================== Class FixArray  ==============================

namespace GS {

template <class Type, USize Size>
class FixArray final: public RandomContainer<Type> {
private:
	Type array[Size];	// array storing items

	static_assert (Size > 0, "Size can't be 0");

public:
		// Types

	typedef RandomContainerIterator<FixArray>				Iterator;
	typedef ConstRandomContainerIterator<FixArray>			ConstIterator;

	typedef GeneralRandomContainerIterator<FixArray>		GeneralIterator;
	typedef ConstGeneralRandomContainerIterator<FixArray>	ConstGeneralIterator;

	typedef RandomContainerReverseIterator<FixArray>		ReverseIterator;
	typedef ConstRandomContainerReverseIterator<FixArray>	ConstReverseIterator;

	typedef Type*		 FastIterator;
	typedef const Type*	 ConstFastIterator;

	class ConstEnumerator;
	class ConversionEnumerator;

		// Constructors

	FixArray ();
	explicit FixArray (const Type& initialValue);
	FixArray (std::initializer_list<Type> items);
	FixArray (ByRefSelector, InitializerRefList<Type> items);
	FixArray (const FixArray& source);
	FixArray (FixArray&& source);

	template <class SourceType>
	explicit FixArray (const FixArray<SourceType, Size>& source);

	FixArray&	operator= (const FixArray& source);
	FixArray&	operator= (FixArray&& source);	

	template <class SourceType>
	FixArray&	operator= (const FixArray<SourceType, Size>& source);

	inline void		Move (FixArray& source);

		// Item access

	inline Type&					operator[] (UIndex idx);
	constexpr inline const Type&	operator[] (UIndex idx) const;

	inline Type&					Get (UIndex idx);
	constexpr inline const Type&	Get (UIndex idx) const;

	inline Type&					GetFirst (void);
	constexpr inline const Type&	GetFirst (void) const;

	inline Type&					GetLast (void);
	constexpr inline const Type&	GetLast (void) const;
	constexpr inline UIndex			GetLastIndex (void) const;

	inline void			Set (UIndex idx, const Type& item);
	inline void			Set (UIndex idx, Type&& item);

		// Content management

	void	Fill (const Type& item, UIndex from = 0, USize range = MaxUSize);

	USize	Replace (const Type& oldItem, const Type& newItem, UIndex from = 0, USize range = MaxUSize);

	void	Swap (FixArray& rightOp);

	constexpr inline USize		GetSize (void) const;
	constexpr inline bool		IsEmpty (void) const;
	constexpr inline bool		IsLast  (UIndex idx) const;

		// Content query

	inline Iterator							Enumerate (void);
	constexpr inline ConstIterator			Enumerate (void) const;

	template <class Function>
	inline void								Enumerate	   (Function&& processor);
	template <class Function>
	inline void								Enumerate	   (Function&& processor) const;
	template <class Function>
	constexpr inline void					EnumerateConst (Function&& processor) const;

	inline Iterator							Begin (void);
	constexpr inline ConstIterator			Begin (void) const;

	inline Iterator							End	(void);
	constexpr inline ConstIterator			End	(void) const;

	inline GeneralIterator					EnumerateGeneral (void);
	constexpr inline ConstGeneralIterator	EnumerateGeneral (void) const;

	inline GeneralIterator					BeginGeneral (void);
	constexpr inline ConstGeneralIterator	BeginGeneral (void) const;

	inline GeneralIterator					EndGeneral	(void);
	constexpr inline ConstGeneralIterator	EndGeneral	(void) const;

	inline ReverseIterator					ReverseEnumerate (void);
	constexpr inline ConstReverseIterator	ReverseEnumerate (void) const;

	template <class Function>
	inline void								ReverseEnumerate	  (Function&& processor);
	template <class Function>
	inline void								ReverseEnumerate	  (Function&& processor) const;
	template <class Function>
	constexpr inline void					ReverseEnumerateConst (Function&& processor) const;

	inline ReverseIterator					ReverseBegin (void);
	constexpr inline ConstReverseIterator	ReverseBegin (void) const;

	inline ReverseIterator					ReverseEnd	(void);
	constexpr inline ConstReverseIterator	ReverseEnd	(void) const;

	inline FastIterator						BeginFast (void);
	constexpr inline ConstFastIterator		BeginFast (void) const;

	inline FastIterator						EndFast	(void);
	constexpr inline ConstFastIterator		EndFast	(void) const;

	constexpr inline operator ConstEnumerator	() const;
	constexpr inline ConversionEnumerator		Convert (void) const;

	constexpr inline auto&				AsConst (void) const;

	UIndex	FindFirst (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirst (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindLast  (const Type& item) const;
	UIndex	FindLast  (const std::function<bool (const Type&)>& condition) const;

	constexpr bool	Contains (const Type& item) const;
	constexpr bool	Contains (const std::function<bool (const Type&)>& condition) const;
	bool			Contains (std::initializer_list<Type> items) const;
	USize	Count	 (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	USize	Count	 (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;

	constexpr bool	operator== (const FixArray& rightOp) const;
	constexpr bool	operator!= (const FixArray& rightOp) const;

		// I/O

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Read  (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader);

	GSErrCode	Write (OChannel& oc) const;
	GSErrCode	Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const;

		// Low level access

	inline Type*					GetContent (void);
	constexpr inline const Type*	GetContent (void) const;

		// Debug

	void	Print (OChannel& oc) const;
	void	Dump  (OChannel& oc) const;

		// Types

	class ConstEnumerator: public GS::ConstEnumerator<Type> {
	private:
		const FixArray* source;

	public:
		inline ConstEnumerator (const FixArray& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;
	};

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const FixArray* source;

	public:
		inline ConversionEnumerator (const FixArray& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;
	};
};

// === FixArray methods ================================================================================================

template <class Type, USize Size>
FixArray<Type, Size>::FixArray ()
{
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (const Type& initialValue)
{
	Fill (initialValue);
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (std::initializer_list<Type> items)
{
	REF_CHECK (Size >= items.size ());

	UIndex i = 0;
	for (const Type& item : items)
		array[i++] = item;
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (ByRefSelector, InitializerRefList<Type> items)
{
	REF_CHECK (Size >= items.size ());

	UIndex i = 0;
	for (const auto& item : items)
		array[i++] = *item;
}



template <class Type, USize Size>
FixArray<Type, Size>::FixArray (const FixArray& source)
{
	for (UIndex i = 0; i < Size; i++)
		array[i] = source.array[i];
}


template <class Type, USize Size>
FixArray<Type, Size>::FixArray (FixArray&& source)
{
	Move (source);
}


template <class Type, USize Size>
FixArray<Type, Size>&	FixArray<Type, Size>::operator= (const FixArray& source)
{
	for (UIndex i = 0; i < Size; i++)
		array[i] = source.array[i];
	
	return *this;
}


template <class Type, USize Size>
FixArray<Type, Size>&	FixArray<Type, Size>::operator= (FixArray&& source)
{
	Move (source);

	return *this;
}


template <class Type, USize Size>
template <class SourceType>
FixArray<Type, Size>::FixArray (const FixArray<SourceType, Size>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	UIndex i = 0;
	for (const SourceType& item : source)
		array[i++] = item;
}


template <class Type, USize Size>
template <class SourceType>
FixArray<Type, Size>&	FixArray<Type, Size>::operator= (const FixArray<SourceType, Size>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	USize i = 0;
	for (const SourceType& item : source)
		array[i++] = item;

	return *this;
}



template <class Type, USize Size>
inline	void	FixArray<Type, Size>::Move (FixArray& source)
{
	if (DBERROR (&source == this))
		return;

	for (UIndex i = 0; i < source.GetSize (); i++)
		array[i] = std::move (source.array[i]);
}


template <class Type, USize Size>
inline Type&	FixArray<Type, Size>::operator[] (UIndex idx)
{
	REF_CHECK (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
constexpr inline const Type&	FixArray<Type, Size>::operator[] (UIndex idx) const
{
	REF_CHECK (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
inline Type&	FixArray<Type, Size>::Get (UIndex idx)
{
	REF_CHECK_R (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
constexpr inline const Type&	FixArray<Type, Size>::Get (UIndex idx) const
{
	REF_CHECK_R (idx < Size);

	return array[idx];
}


template <class Type, USize Size>
inline Type&	FixArray<Type, Size>::GetFirst (void)
{
	return array[0];
}


template <class Type, USize Size>
constexpr inline const Type&	FixArray<Type, Size>::GetFirst (void) const
{
	return array[0];
}


template <class Type, USize Size>
inline Type&	FixArray<Type, Size>::GetLast (void)
{
	return array[Size - 1];
}


template <class Type, USize Size>
constexpr inline const Type&	FixArray<Type, Size>::GetLast (void) const
{
	return array[Size - 1];
}


template <class Type, USize Size>
constexpr inline UIndex	FixArray<Type, Size>::GetLastIndex (void) const
{
	return Size - 1;
}


template <class Type, USize Size>
inline void		FixArray<Type, Size>::Set (UIndex idx, const Type& item)
{
	REF_CHECK (idx < Size);
	NULL_REF_CHECK (item);

	array[idx] = item;
}


template <class Type, USize Size>
inline void		FixArray<Type, Size>::Set (UIndex idx, Type&& item)
{
	REF_CHECK (idx < Size);
	NULL_REF_CHECK (item);

	array[idx] = std::move (item);
}


template <class Type, USize Size>
void	FixArray<Type, Size>::Fill (const Type& item, UIndex from, USize range)
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	GS::Fill (array + from, array + from + range, item);
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::Replace (const Type& oldItem, const Type& newItem, UIndex from, USize range)
{
	NULL_REF_CHECK (oldItem);
	NULL_REF_CHECK (newItem);
	REF_CHECK ((range == Size && from <= Size) || (range != Size && from + range <= Size));

	if (range == Size)
		range = Size - from;

	return GS::Replace (array + from, array + from + range, oldItem, newItem);
}


template <class Type, USize Size>
void	FixArray<Type, Size>::Swap (FixArray& rightOp)
{
	NULL_REF_CHECK (rightOp);
	PRECOND (Size == rightOp.GetSize ());

	for (UIndex i = 0; i < Size; i++)
		GS::Swap (array[i], rightOp[i]);
}


template <class Type, USize Size>
constexpr inline USize	FixArray<Type, Size>::GetSize (void) const
{
	return Size;
}


template <class Type, USize Size>
constexpr inline bool		FixArray<Type, Size>::IsEmpty (void) const
{
	return false;
}


template <class Type, USize Size>
constexpr inline bool		FixArray<Type, Size>::IsLast (UIndex idx) const
{
	return (idx == Size - 1);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::Iterator	FixArray<Type, Size>::Enumerate (void)
{
	return Iterator (*this, 0);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstIterator	FixArray<Type, Size>::Enumerate (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type, USize Size>
template <class Function>
inline void	FixArray<Type, Size>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < Size; i++)
		processor (array[i]);
}


template <class Type, USize Size>
template <class Function>
inline void	FixArray<Type, Size>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < Size; i++)
		processor (const_cast<const Type&> (array[i]));
}


template <class Type, USize Size>
template <class Function>
constexpr inline void	FixArray<Type, Size>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::Iterator	FixArray<Type, Size>::Begin (void)
{
	return Iterator (*this, 0);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstIterator	FixArray<Type, Size>::Begin (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::Iterator	FixArray<Type, Size>::End (void)
{
	return Iterator (*this, Size);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstIterator	FixArray<Type, Size>::End (void) const
{
	return ConstIterator (*this, Size);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::GeneralIterator	FixArray<Type, Size>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstGeneralIterator	FixArray<Type, Size>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::GeneralIterator	FixArray<Type, Size>::BeginGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstGeneralIterator	FixArray<Type, Size>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::GeneralIterator	FixArray<Type, Size>::EndGeneral (void)
{
	return GeneralIterator (*this, Size);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstGeneralIterator	FixArray<Type, Size>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, Size);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::ReverseIterator	FixArray<Type, Size>::ReverseEnumerate (void)
{
	return ReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstReverseIterator	FixArray<Type, Size>::ReverseEnumerate (void) const
{
	return ConstReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
template <class Function>
inline void	FixArray<Type, Size>::ReverseEnumerate (Function&& processor)
{
	for (UIndex i = Size; i > 0; i--)
		processor (array[i - 1]);
}


template <class Type, USize Size>
template <class Function>
inline void	FixArray<Type, Size>::ReverseEnumerate (Function&& processor) const
{
	for (UIndex i = Size; i > 0; i--)
		processor (const_cast<const Type&> (array[i - 1]));
}


template <class Type, USize Size>
template <class Function>
constexpr inline void	FixArray<Type, Size>::ReverseEnumerateConst (Function&& processor) const
{
	ReverseEnumerate (processor);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::ReverseIterator	FixArray<Type, Size>::ReverseBegin (void)
{
	return ReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstReverseIterator	FixArray<Type, Size>::ReverseBegin (void) const
{
	return ConstReverseIterator (*this, Size - 1);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::ReverseIterator	FixArray<Type, Size>::ReverseEnd (void)
{
	return ReverseIterator (*this, -1);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstReverseIterator	FixArray<Type, Size>::ReverseEnd (void) const
{
	return ConstReverseIterator (*this, -1);
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::FastIterator	FixArray<Type, Size>::BeginFast (void)
{
	return array;
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstFastIterator	FixArray<Type, Size>::BeginFast (void) const
{
	return array;
}


template <class Type, USize Size>
inline typename FixArray<Type, Size>::FastIterator	FixArray<Type, Size>::EndFast (void)
{
	return array + Size;
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConstFastIterator	FixArray<Type, Size>::EndFast (void) const
{
	return array + Size;
}


template <class Type, USize Size>
constexpr inline FixArray<Type, Size>::operator typename FixArray<Type, Size>::ConstEnumerator () const
{
	return ConstEnumerator (*this);
}


template <class Type, USize Size>
constexpr inline typename FixArray<Type, Size>::ConversionEnumerator	FixArray<Type, Size>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type, USize Size>
constexpr inline auto&	FixArray<Type, Size>::AsConst (void) const
{
	return reinterpret_cast<const FixArray<typename Container<Type>::template MakeConstPtr<Type>::ConstType, Size>&> (*this);
}

template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindFirst (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	const Type* it = GS::Find (array + from, array + from + range, item);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindFirst (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	const Type* it = GS::Find (array + from, array + from + range, condition);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindLast (const Type& item) const
{
	NULL_REF_CHECK (item);

	for (UIndex i = Size; i > 0; i--) {
		if (array[i - 1] == item)
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, USize Size>
UIndex	FixArray<Type, Size>::FindLast (const std::function<bool (const Type&)>& condition) const
{
	for (UIndex i = Size; i > 0; i--) {
		if (condition (array[i - 1]))
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (array, array + Size, item) != array + Size);
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::Contains (const std::function<bool (const Type&)>& condition) const
{
	return (GS::Find (array, array + Size, condition) != array + Size);
}


template <class Type, USize Size>
bool	FixArray<Type, Size>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::Count (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	return GS::Count (array + from, array + from + range, item);
}


template <class Type, USize Size>
USize	FixArray<Type, Size>::Count (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= Size) || (range != MaxUSize && from + range <= Size));

	if (range == MaxUSize)
		range = Size - from;

	return GS::Count (array + from, array + from + range, condition);
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::operator== (const FixArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return (GS::IsEqual (array, array + Size, rightOp.array));
}


template <class Type, USize Size>
constexpr bool	FixArray<Type, Size>::operator!= (const FixArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	USize sizeOnChannel = 0;

	GSErrCode errorCode = ic.Read (sizeOnChannel);

	if (errorCode != NoError)
		return errorCode;

	if (DBERROR (sizeOnChannel != Size))
		return ErrRead;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = GS::ReadType (ic, array[i]);

	return errorCode;
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Read (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader)
{
	NULL_REF_CHECK (ic);

	USize sizeOnChannel = 0;

	GSErrCode errorCode = ic.Read (sizeOnChannel);

	if (errorCode != NoError)
		return errorCode;

	if (DBERROR (sizeOnChannel != Size))
		return ErrRead;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = reader (ic, array[i]);

	return errorCode;
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GSErrCode errorCode = oc.Write (Size);

	if (errorCode != NoError)
		return errorCode;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = GS::WriteType (oc, array[i]);

	return errorCode;
}


template <class Type, USize Size>
GSErrCode	FixArray<Type, Size>::Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const
{
	NULL_REF_CHECK (oc);

	GSErrCode errorCode = oc.Write (Size);

	if (errorCode != NoError)
		return errorCode;

	for (UIndex i = 0; i < Size && errorCode == NoError; i++)
		errorCode = writer (oc, array[i]);

	return errorCode;
}


template <class Type, USize Size>
inline Type*	FixArray<Type, Size>::GetContent (void)
{
	return array;
}


template <class Type, USize Size>
constexpr inline const Type*	FixArray<Type, Size>::GetContent (void) const
{
	return array;
}


template <class Type, USize Size>
void	FixArray<Type, Size>::Print (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "FixArray" << '\n';
}


template <class Type, USize Size>
void	FixArray<Type, Size>::Dump (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "array: " << array << '\n';
	oc << "size:  " << Size  << '\n';
}


template <class Type, USize Size>
inline FixArray<Type, Size>::ConstEnumerator::ConstEnumerator (const FixArray& source):
	source (&source)
{
}


template <class Type, USize Size>
void	FixArray<Type, Size>::ConstEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type, USize Size>
inline FixArray<Type, Size>::ConversionEnumerator::ConversionEnumerator (const FixArray& source):
	source (&source)
{
}


template <class Type, USize Size>
void	FixArray<Type, Size>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


// === class FixArrayInserter ==========================================================================================

template <class Type, USize Size>
class FixArrayInserter {
private:
	FixArray<Type, Size>* array;
	mutable UInt32 i = 0;

public:

	explicit FixArrayInserter (FixArray<Type, Size>* array) :
		array (array)
	{
	}

	void operator() (const Type& value) const {
		DBASSERT (i < Size);
		array[i] = value;
		++i;
	}

	void operator() (Type&& value)		const {
		DBASSERT (i < Size);
		array[i] = std::move (value);
		++i;
	}

	typedef Type DecayedFirstArgumentType;
};


// === Global functions ================================================================================================

template <class Type, USize Size>
inline auto		begin (FixArray<Type, Size>& array)
{
	return array.BeginFast ();
}


template <class Type, USize Size>
inline auto		end (FixArray<Type, Size>& array)
{
	return array.EndFast ();
}


template <class Type, USize Size>
inline auto		begin (const FixArray<Type, Size>& array)
{
	return array.BeginFast ();
}


template <class Type, USize Size>
inline auto		end (const FixArray<Type, Size>& array)
{
	return array.EndFast ();
}


template <class Type, USize Size>
inline FixArrayInserter<Type, Size> GetInserter (FixArray<Type, Size>& fixArray)
{
	return FixArrayInserter<Type, Size> (&fixArray);
}


template <class Type, USize Size>
inline GSErrCode	Print (OChannel& oc, const FixArray<Type, Size>& obj)
{
	obj.Print (oc);

	return NoError;
}

}	// namespace GS


#endif
