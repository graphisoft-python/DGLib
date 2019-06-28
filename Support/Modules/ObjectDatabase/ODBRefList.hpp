
// *****************************************************************************
//
//                           Classes RefList, ConstRefList
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBREFLIST_HPP
#define ODBREFLIST_HPP


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

#include "ODBReference.hpp"

#include "ODBObject.hpp"

#include "Array.hpp"
#include "BidirectionalContainerIterator.hpp"
#include "Enumerator.hpp"

#include <functional>


// ------------------------------ Predeclarations ------------------------------

namespace ODB { class Query; }


//lint -save -e1521 -e148 -e1520 [multiple copy constructors; member previously declared; multiple assignment operators]

// =============================== Class RefList ===============================

namespace ODB {

template <class T> class RefList;
template <class T> class ConstRefList;
template <class T> class RefListSource;

template <class T> auto begin (RefList<T>& refList);
template <class T> auto end   (RefList<T>& refList);
template <class T> auto begin (const RefList<T>& refList);
template <class T> auto end   (const RefList<T>& refList);


template <class Type>
class RefList {
public:
	typedef Type		ObjectType;
	typedef Ref<Type>	ValueType;

private:
	GS::ArrayFB<Ref<Object>, 4>	objects;	// stores the object list (it is untyped because of the compile time overhead)

		// Iterator support

	struct IteratorState {
		UIndex	current;	// current entry

		explicit IteratorState (UIndex initialIndex): current (initialIndex) {}
	};
	inline ValueType&		GetCurrent (const IteratorState& state) { return *reinterpret_cast<Ref<Type>*> (&objects[state.current]); }
	inline const ValueType&	GetCurrent (const IteratorState& state) const { return *reinterpret_cast<const Ref<Type>*> (&objects[state.current]); }
	inline void				Increment  (IteratorState& state) const { state.current++; }
	inline void				Decrement  (IteratorState& state) const { state.current--; }
	inline bool				IsEqual    (const IteratorState& state1, const IteratorState& state2) const { return (state1.current == state2.current); }
	inline bool				IsBegin    (const IteratorState& state) const { return (state.current == 0); }
	inline bool				IsEnd      (const IteratorState& state) const { return (state.current == objects.GetSize ()); }
	inline void				Print      (GS::OChannel& /*oc*/, const IteratorState& /*state*/) const {}
	inline void				Dump       (GS::OChannel& /*oc*/, const IteratorState& /*state*/) const {}
	inline bool				CheckState (const IteratorState& /*state*/) const { return true; }

	friend class GS::BidirectionalContainerIterator<RefList>;
	friend class GS::ConstBidirectionalContainerIterator<RefList>;
	friend class GS::GeneralBidirectionalContainerIterator<RefList>;
	friend class GS::ConstGeneralBidirectionalContainerIterator<RefList>;

	friend auto begin<Type> (RefList& refList);
	friend auto end<Type>   (RefList& refList);
	friend auto begin<Type> (const RefList& refList);
	friend auto end<Type>   (const RefList& refList);

	template <class T> friend class ConstRefList;	// to allow assigment between ConstRefList and RefList

public:
		// Types

	typedef GS::BidirectionalContainerIterator<RefList> 			Iterator;
	typedef GS::ConstBidirectionalContainerIterator<RefList>		ConstIterator;

	typedef GS::GeneralBidirectionalContainerIterator<RefList> 		GeneralIterator;
	typedef GS::ConstGeneralBidirectionalContainerIterator<RefList>	ConstGeneralIterator;

	class ConstEnumerator;
	class ConversionEnumerator;

		// Constructors

	template <class SourceType> friend class RefList;

	inline RefList ();
	inline RefList (const Ref<Type>& object);
	template <class SourceType>
	inline RefList (const Ref<SourceType>& object);
	inline RefList (std::initializer_list<Ref<Type>> source);
	inline RefList (const RefListSource<Type>& source);
	template <class SourceType>
	inline RefList (const RefListSource<SourceType>& source);
	inline explicit RefList (const GS::ConstEnumerator<Ref<Type>>& enumerator);
	inline RefList (const GS::ConversionEnumerator<Ref<Type>>& enumerator);

	template <class SourceType>
	inline RefList (std::initializer_list<Ref<SourceType>> source);

	inline RefList (const RefList& source);
	inline RefList (RefList&& source);
	template <class SourceType>
	inline RefList (const RefList<SourceType>& source);
	template <class SourceType>
	inline RefList (RefList<SourceType>&& source);

	inline RefList&	operator= (const RefList& source);
	inline RefList&	operator= (RefList&& source);

	template <class SourceType>
	inline RefList&	operator= (const RefList<SourceType>& source);
	template <class SourceType>
	inline RefList&	operator= (RefList<SourceType>&& source);

	inline RefList&	operator= (const RefListSource<Type>& source);
	template <class SourceType>
	inline RefList&	operator= (const RefListSource<SourceType>& source);

	RefList&	operator= (const GS::ConstEnumerator<Ref<Type>>& enumerator);

	inline ~RefList ();

	inline	void	Move (RefList& source);
	void			Move (const std::function<void (Ref<Type>&&)>& processor);
	template <class SourceType>
	inline	void	Move (RefList<SourceType>& source);

		// User interface

	inline void		Append (const Ref<Type>& object);
	inline void		Append (Ref<Type>&& object);

	template <class SourceType>
	inline void		Append (const Ref<SourceType>& object);
	template <class SourceType>
	inline void		Append (Ref<SourceType>&& object);

	inline void		Append (const RefList& objects);
	inline void		Append (RefList&& objects);

	template <class SourceType>
	inline void		Append (const RefList<SourceType>& objects);
	template <class SourceType>
	inline void		Append (RefList<SourceType>&& objects);

	inline void		Append (const RefListSource<Type>& objects);
	template <class SourceType>
	inline void		Append (const RefListSource<SourceType>& objects);

	inline void		Clear  (void);

	inline USize	GetSize (void) const;
	inline bool		IsEmpty (void) const;

	inline bool		Contains	 (const Ref<Type>& object) const;
	bool			Contains	 (std::initializer_list<Ref<Type>> items) const;
	bool			ContainsOnly (std::initializer_list<Ref<Type>> items) const;

	inline bool		operator== (const RefList& rightOp) const;
	template <class RightType>
	inline bool		operator== (const RefList<RightType>& rightOp) const;
	template <class RightType>
	inline bool		operator== (const ConstRefList<RightType>& rightOp) const;
	inline bool		operator!= (const RefList& rightOp) const;
	template <class RightType>
	inline bool		operator!= (const RefList<RightType>& rightOp) const;
	template <class RightType>
	inline bool		operator!= (const ConstRefList<RightType>& rightOp) const;

	inline bool		IsEqualByContent (const RefList& rightOp) const;

	inline Iterator			Enumerate (void);
	inline ConstIterator	Enumerate (void) const;

	template <class Function>
	inline void				Enumerate	   (Function&& processor);
	template <class Function>
	inline void				Enumerate	   (Function&& processor) const;
	template <class Function>
	inline void				EnumerateConst (Function&& processor) const;

	inline Iterator			Begin (void);
	inline ConstIterator	Begin (void) const;

	inline Iterator			End	(void);
	inline ConstIterator	End	(void) const;

	inline GeneralIterator		EnumerateGeneral (void);
	inline ConstGeneralIterator	EnumerateGeneral (void) const;

	inline GeneralIterator		BeginGeneral (void);
	inline ConstGeneralIterator	BeginGeneral (void) const;

	inline GeneralIterator		EndGeneral	(void);
	inline ConstGeneralIterator	EndGeneral	(void) const;

	inline operator ConstEnumerator	() const;
	inline ConversionEnumerator		Convert (void) const;

	inline GSErrCode		Read  (GS::IChannel& ic);
	inline GSErrCode		Write (GS::OChannel& oc) const;
	inline GSErrCode		WriteOriginal (GS::OChannel& oc) const;

	inline void				SetCapacity (USize newCapacity);

		// Casting

	template <class BaseType>
	ODB_FORCE_INLINE const RefList<BaseType>&	As (void) const;

	ODB_FORCE_INLINE const ConstRefList<Type>&	AsConst (void) const;

		// Types

	class ConstEnumerator: public GS::ConstEnumerator<Ref<Type>> {
	private:
		const RefList* source;

	public:
		inline ConstEnumerator (const RefList& source);

		virtual void	Enumerate (const std::function<void (const Ref<Type>&)>& processor) const override;
	};

	class ConversionEnumerator: public GS::ConversionEnumerator<Ref<Type>> {
	private:
		const RefList* source;

	public:
		inline ConversionEnumerator (const RefList& source);

		virtual void	Enumerate (const std::function<void (const Ref<Type>&)>& processor) const override;
	};
};


template <class T>
class RefListInserter {
	RefList<T>* refList;

public:
	explicit RefListInserter (RefList<T>* refList) :
		refList (refList)
	{
	}

	void operator() (const Ref<T>& object) const { refList->Push (object); }
	void operator() (Ref<T>&& object)	   const { refList->Push (std::move (object)); }
};


template <class ToType, class FromType>
inline RefList<ToType>&				UnsafeBaseCast (RefList<FromType>& from);

template <class ToType, class FromType>
inline const RefList<ToType>&		StaticCast (const RefList<FromType>& from);

template <class Type>
inline RefList<Type>				ConstCast (RefList<Type> /*from*/);

template <class Type>
inline const RefList<Type>&			ConstCast (const ConstRefList<Type>& from);

template <class Type>
inline RefList<Type>&				ConstCast (ConstRefList<Type>& from);

template <class Type>
inline RefList<Type>&&				ConstCast (ConstRefList<Type>&& from);

template <class Type>
inline ConstRefList<Type>&			ToConst (RefList<Type>& from);

template <class Type>
inline const ConstRefList<Type>&	ToConst (const RefList<Type>& from);

template <class Type>
inline RefListInserter<Type>		GetInserter (RefList<Type>& destination);

}	// namespace ODB


template <class Type>
inline ODB::RefList<Type>::RefList ()
{
}


template <class Type>
inline ODB::RefList<Type>::RefList (const Ref<Type>& object)
{
	objects.Push (*reinterpret_cast<const Ref<Object>*> (&object));
}


template <class Type>
inline ODB::RefList<Type>::RefList (std::initializer_list<Ref<Type>> objects)
{
	for (const auto& object : objects)
		this->objects.Push (object);
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>::RefList (const Ref<SourceType>& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (*reinterpret_cast<const Ref<Object>*> (&object));
}


template <class Type>
inline ODB::RefList<Type>::RefList (const RefListSource<Type>& source)
{
	source.GetContent (this);
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>::RefList (const RefListSource<SourceType>& source)
{	
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	source.GetContent (reinterpret_cast<RefList<SourceType>*> (this));
}


template <class Type>
inline ODB::RefList<Type>::RefList (const GS::ConstEnumerator<Ref<Type>>& enumerator):
	objects (reinterpret_cast<const GS::ConstEnumerator<Ref<Object>>&> (enumerator))
{
}


template <class Type>
inline ODB::RefList<Type>::RefList (const GS::ConversionEnumerator<Ref<Type>>& enumerator):
	objects (reinterpret_cast<const GS::ConversionEnumerator<Ref<Object>>&> (enumerator))
{
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>::RefList (std::initializer_list<Ref<SourceType>> objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	for (const auto& object : objects)
		this->objects.Push (object);
}


template <class Type>
inline ODB::RefList<Type>::RefList (const RefList& source):
	objects (source.objects)
{
}


template <class Type>
inline ODB::RefList<Type>::RefList (RefList&& source)
{
	Move (source);
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>::RefList (const RefList<SourceType>& source):
	objects (source.objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");
}

template <class Type>
template <class SourceType>
inline ODB::RefList<Type>::RefList (RefList<SourceType>&& source)
{
	Move (source);
}


template <class Type>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (const RefList& source)
{
	if (&source != this)
		objects = source.objects;

	return *this;
}


template <class Type>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (RefList&& source)
{
	Move (source);

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (const RefList<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	if (static_cast<const void*> (&source) != this)
		objects = source.objects;

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (RefList<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	Move (source);

	return *this;
}


template <class Type>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (const RefListSource<Type>& source)
{
	source.GetContent (this);

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (const RefListSource<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	source.GetContent (reinterpret_cast<RefList<SourceType>*> (this));

	return *this;
}


template <class Type>
inline ODB::RefList<Type>&	ODB::RefList<Type>::operator= (const GS::ConstEnumerator<Ref<Type>>& enumerator)
{
	objects.operator= (reinterpret_cast<const GS::ConstEnumerator<Ref<Object>>&> (enumerator));

	return *this;
}


template <class Type>
inline ODB::RefList<Type>::~RefList ()
{
}


template <class Type>
inline	void	ODB::RefList<Type>::Move (RefList& source)
{
	// source-target equality check shall be performed by Move
	objects.Move (source.objects);
	// source is cleared by Move
}


template <class Type>
void			ODB::RefList<Type>::Move (const std::function<void (Ref<Type>&&)>& processor)
{
	objects.Move ([&processor] (Ref<Object>&& item) { processor (std::move (*reinterpret_cast<ODB::Ref<Type>*> (&item))); });
	// source is cleared by Move
}

template <class Type>
template <class SourceType>
inline	void	ODB::RefList<Type>::Move (RefList<SourceType>& source)
{
	// source-target equality check shall be performed by Move
	objects.Move (source.objects);
	// source is cleared by Move
}


template <class Type>
inline void		ODB::RefList<Type>::Append (const Ref<Type>& object)
{
	objects.Push (*reinterpret_cast<const Ref<Object>*> (&object));
}


template <class Type>
inline void		ODB::RefList<Type>::Append (Ref<Type>&& object)
{
	objects.Push (std::move ((*reinterpret_cast<Ref<Object>*> (&object))));
}


template <class Type>
template <class SourceType>
inline void		ODB::RefList<Type>::Append (const Ref<SourceType>& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (*reinterpret_cast<const Ref<Object>*> (&object));
}


template <class Type>
template <class SourceType>
inline void		ODB::RefList<Type>::Append (Ref<SourceType>&& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (std::move ((*reinterpret_cast<Ref<Object>*> (&object))));
}


template <class Type>
inline void		ODB::RefList<Type>::Append (const RefList& objects)
{
	this->objects.Append (objects.objects);
}


template <class Type>
inline void		ODB::RefList<Type>::Append (RefList&& objects)
{
	this->objects.Append (std::move (objects.objects));
}


template <class Type>
template <class SourceType>
inline void		ODB::RefList<Type>::Append (const RefList<SourceType>& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	this->objects.Append (objects.objects);
}


template <class Type>
template <class SourceType>
inline void		ODB::RefList<Type>::Append (RefList<SourceType>&& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	this->objects.Append (std::move (objects.objects));
}


template <class Type>
inline void		ODB::RefList<Type>::Append (const RefListSource<Type>& objects)
{
	objects.AppendContent (this);
}


template <class Type>
template <class SourceType>
inline void		ODB::RefList<Type>::Append (const RefListSource<SourceType>& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.AppendContent (reinterpret_cast<RefList<SourceType>*> (this));
}


template <class Type>
inline void		ODB::RefList<Type>::Clear (void)
{
	objects.Clear ();
}


template <class Type>
inline USize	ODB::RefList<Type>::GetSize (void) const
{
	return objects.GetSize ();
}


template <class Type>
inline bool		ODB::RefList<Type>::IsEmpty (void) const
{
	return objects.IsEmpty ();
}


template <class Type>
inline bool		ODB::RefList<Type>::Contains (const Ref<Type>& object) const
{
	return objects.Contains (*reinterpret_cast<const Ref<Object>*> (&object));
}


template <class Type>
bool	ODB::RefList<Type>::Contains (std::initializer_list<Ref<Type>> objects) const
{
	for (const auto& object : objects) {
		if (!Contains (object))
			return false;
	}

	return true;
}


template <class Type>
bool	ODB::RefList<Type>::ContainsOnly (std::initializer_list<Ref<Type>> objects) const
{
	if (this->objects.GetSize () != objects.size ())
		return false;

	for (const auto& object : objects) {
		if (!Contains (object))
			return false;
	}

	return true;
}


template <class Type>
inline bool		ODB::RefList<Type>::operator== (const RefList& rightOp) const
{
	return (objects == rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::RefList<Type>::operator== (const RefList<RightType>& rightOp) const
{
	return (objects == rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::RefList<Type>::operator== (const ConstRefList<RightType>& rightOp) const
{
	return (objects == rightOp.objects);
}


template <class Type>
inline bool		ODB::RefList<Type>::operator!= (const RefList& rightOp) const
{
	return (objects != rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::RefList<Type>::operator!= (const RefList<RightType>& rightOp) const
{
	return (objects != rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::RefList<Type>::operator!= (const ConstRefList<RightType>& rightOp) const
{
	return (objects != rightOp.objects);
}


template <class Type>
inline bool		ODB::RefList<Type>::IsEqualByContent (const RefList& rightOp) const
{
	if (objects.GetSize () != rightOp.objects.GetSize ())
		return false;

	for (UIndex i = 0; i < rightOp.objects.GetSize (); i++) {
		if (!objects.Contains (rightOp.objects[i]))
			return false;
	}

	return true;
}


template <class Type>
inline typename ODB::RefList<Type>::Iterator	ODB::RefList<Type>::Enumerate (void)
{
	return Iterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::ConstIterator	ODB::RefList<Type>::Enumerate (void) const
{
	return ConstIterator (*this, IteratorState (0));
}


template <class Type>
template <class Function>
inline void	ODB::RefList<Type>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < objects.GetSize (); i++)
		processor (reinterpret_cast<Ref<Type>&> (objects[i]));
}


template <class Type>
template <class Function>
inline void	ODB::RefList<Type>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < objects.GetSize (); i++)
		processor (reinterpret_cast<const Ref<Type>&> (objects[i]));
}


template <class Type>
template <class Function>
inline void	ODB::RefList<Type>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type>
inline typename ODB::RefList<Type>::Iterator	ODB::RefList<Type>::Begin (void)
{
	return Iterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::ConstIterator	ODB::RefList<Type>::Begin (void) const
{
	return ConstIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::Iterator	ODB::RefList<Type>::End (void)
{
	return Iterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline typename ODB::RefList<Type>::ConstIterator	ODB::RefList<Type>::End (void) const
{
	return ConstIterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline typename ODB::RefList<Type>::GeneralIterator		ODB::RefList<Type>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::ConstGeneralIterator	ODB::RefList<Type>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::GeneralIterator	ODB::RefList<Type>::BeginGeneral (void)
{
	return GeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::ConstGeneralIterator	ODB::RefList<Type>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::RefList<Type>::GeneralIterator	ODB::RefList<Type>::EndGeneral (void)
{
	return GeneralIterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline typename ODB::RefList<Type>::ConstGeneralIterator	ODB::RefList<Type>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline ODB::RefList<Type>::operator typename ODB::RefList<Type>::ConstEnumerator () const
{
	return ConstEnumerator (*this);
}


template <class Type>
inline typename ODB::RefList<Type>::ConversionEnumerator	ODB::RefList<Type>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type>
inline GSErrCode	ODB::RefList<Type>::Read (GS::IChannel& ic)
{
	return objects.Read (ic);
}


template <class Type>
inline GSErrCode	ODB::RefList<Type>::Write (GS::OChannel& oc) const
{
	return objects.Write (oc);
}


template <class Type>
inline GSErrCode	ODB::RefList<Type>::WriteOriginal (GS::OChannel& oc) const
{
	return objects.Write (oc, ODB::WriteOriginal);
}


template <class Type>
inline void		ODB::RefList<Type>::SetCapacity (USize newCapacity)
{
	objects.SetCapacity (newCapacity);
}


template <class Type>
template <class BaseType>
ODB_FORCE_INLINE const ODB::RefList<BaseType>&	ODB::RefList<Type>::As (void) const
{
	static_assert (GS::IsCompatible<Type, BaseType>, "Type is not compatible with BaseType.");

	return reinterpret_cast<const RefList<BaseType>&> (*this);
}


template <class Type>
ODB_FORCE_INLINE const ODB::ConstRefList<Type>&		ODB::RefList<Type>::AsConst (void) const
{
	return reinterpret_cast<const ConstRefList<Type>&> (*this);
}


template <class Type>
inline ODB::RefList<Type>::ConstEnumerator::ConstEnumerator (const RefList& source):
	source (&source)
{
}


template <class Type>
void	ODB::RefList<Type>::ConstEnumerator::Enumerate (const std::function<void (const Ref<Type>&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type>
inline ODB::RefList<Type>::ConversionEnumerator::ConversionEnumerator (const RefList& source):
	source (&source)
{
}


template <class Type>
void	ODB::RefList<Type>::ConversionEnumerator::Enumerate (const std::function<void (const Ref<Type>&)>& processor) const
{
	source->Enumerate (processor);
}


template <class ToType, class FromType>
inline ODB::RefList<ToType>&	ODB::UnsafeBaseCast (ODB::RefList<FromType>& from)
{
	static_assert (GS::IsCompatible<FromType, ToType>, "FromType is not compatible with ToType.");

	return reinterpret_cast<RefList<ToType>&> (from);
}


template <class ToType, class FromType>
inline const ODB::RefList<ToType>&	ODB::StaticCast (const ODB::RefList<FromType>& from)
{
	static_assert (GS::IsCompatible<FromType, ToType> || GS::IsCompatible<ToType, FromType>, "FromType and ToType are unrelated.");

	return reinterpret_cast<const RefList<ToType>&> (from);
}


template <class Type>
inline ODB::RefList<Type>	ODB::ConstCast (RefList<Type> /*from*/)
{
	static_assert (GS::AlwaysFalse<Type>, "No need to const cast an ODB::RefList, because it is already not const.");
	return {};
}


template <class Type>
inline const ODB::RefList<Type>&	ODB::ConstCast (const ConstRefList<Type>& from)
{
	return reinterpret_cast<const RefList<Type>&> (from);
}


template <class Type>
inline ODB::RefList<Type>&	ODB::ConstCast (ConstRefList<Type>& from)
{
	return reinterpret_cast<RefList<Type>&> (from);
}


template <class Type>
inline ODB::RefList<Type>&&		ODB::ConstCast (ConstRefList<Type>&& from)
{
	return reinterpret_cast<RefList<Type>&&> (from);
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ToConst (RefList<Type>& from)
{
	return reinterpret_cast<ConstRefList<Type>&> (from);
}


template <class Type>
inline const ODB::ConstRefList<Type>&	ODB::ToConst (const RefList<Type>& from)
{
	return reinterpret_cast<const ConstRefList<Type>&> (from);
}


template <class Type>
auto	ODB::begin (RefList<Type>& refList)
{
	return reinterpret_cast<Ref<Type>*> (refList.objects.BeginFast ());
}


template <class Type>
auto	ODB::end (RefList<Type>& refList)
{
	return reinterpret_cast<Ref<Type>*> (refList.objects.EndFast ());
}


template <class Type>
auto	ODB::begin (const RefList<Type>& refList)
{
	return reinterpret_cast<const Ref<Type>*> (refList.objects.BeginFast ());
}


template <class Type>
auto	ODB::end (const RefList<Type>& refList)
{
	return reinterpret_cast<const Ref<Type>*> (refList.objects.EndFast ());
}


template <class Type>
inline ODB::RefListInserter<Type>	ODB::GetInserter (RefList<Type>& destination)
{
	return ODB::RefListInserter<Type> (&destination);
}
// _______________________________ Class RefList _______________________________



// ============================ Class RefListSource ============================

namespace ODB {

template <class Type>
class RefListSource {
private:
	template <class T> friend class RefList;
	template <class T> friend class ConstRefList;
	inline void		GetContent	  (RefList<Type>* destination) const;
	virtual void	AppendContent (RefList<Type>* destination) const = 0;

public:
	inline bool		operator== (const RefList<Type>& rightOp) const			  { RefList<Type> leftOp; GetContent (&leftOp); return (leftOp == rightOp); }
	template <class RightType>
	inline bool		operator== (const RefList<RightType>& rightOp) const	  { RefList<Type> leftOp; GetContent (&leftOp); return (leftOp == rightOp); }
	template <class RightType>
	inline bool		operator== (const ConstRefList<RightType>& rightOp) const { RefList<Type> leftOp; GetContent (&leftOp); return (leftOp == rightOp); }
	inline bool		operator!= (const RefList<Type>& rightOp) const			  { RefList<Type> leftOp; GetContent (&leftOp); return (leftOp != rightOp); }
	template <class RightType>
	inline bool		operator!= (const RefList<RightType>& rightOp) const	  { RefList<Type> leftOp; GetContent (&leftOp); return (leftOp != rightOp); }
	template <class RightType>
	inline bool		operator!= (const ConstRefList<RightType>& rightOp) const { RefList<Type> leftOp; GetContent (&leftOp); return (leftOp != rightOp); }
	inline RefList<Type> operator* () const									  { RefList<Type> content; GetContent (&content); return content; }
};

}	// namespace ODB



template <class Type>
inline void		ODB::RefListSource<Type>::GetContent (RefList<Type>* destination) const
{
	destination->Clear ();
	AppendContent (destination);
}
// ____________________________ Class RefListSource ____________________________



// ============================ Class ConstRefList =============================

namespace ODB {

template <class T> class ConstRefListSource;

template <class T> auto begin (ConstRefList<T>& constRefList);
template <class T> auto end   (ConstRefList<T>& constRefList);
template <class T> auto begin (const ConstRefList<T>& constRefList);
template <class T> auto end   (const ConstRefList<T>& constRefList);


template <class Type>
class ConstRefList {
public:
	typedef Type			ObjectType;
	typedef ConstRef<Type>	ValueType;

private:
	GS::ArrayFB<ConstRef<Object>, 4>	objects;	// stores the object list (it is untyped because of the compile time overhead)

		// Iterator support

	struct IteratorState {
		UIndex	current;	// current entry

		explicit IteratorState (UIndex initialIndex): current (initialIndex) {}
	};
	inline ValueType&		GetCurrent (const IteratorState& state) { return *reinterpret_cast<ConstRef<Type>*> (&objects[state.current]); }
	inline const ValueType&	GetCurrent (const IteratorState& state) const { return *reinterpret_cast<const ConstRef<Type>*> (&objects[state.current]); }
	inline void				Increment  (IteratorState& state) const { state.current++; }
	inline void				Decrement  (IteratorState& state) const { state.current--; }
	inline bool				IsEqual    (const IteratorState& state1, const IteratorState& state2) const { return (state1.current == state2.current); }
	inline bool				IsBegin    (const IteratorState& state) const { return (state.current == 0); }
	inline bool				IsEnd      (const IteratorState& state) const { return (state.current == objects.GetSize ()); }
	inline void				Print      (GS::OChannel& /*oc*/, const IteratorState& /*state*/) const {}
	inline void				Dump       (GS::OChannel& /*oc*/, const IteratorState& /*state*/) const {}
	inline bool				CheckState (const IteratorState& /*state*/) const { return true; }

	friend class GS::BidirectionalContainerIterator<ConstRefList>;
	friend class GS::ConstBidirectionalContainerIterator<ConstRefList>;
	friend class GS::GeneralBidirectionalContainerIterator<ConstRefList>;
	friend class GS::ConstGeneralBidirectionalContainerIterator<ConstRefList>;

	friend auto begin<Type> (ConstRefList& constRefList);
	friend auto end<Type>   (ConstRefList& constRefList);
	friend auto begin<Type> (const ConstRefList& constRefList);
	friend auto end<Type>   (const ConstRefList& constRefList);

public:
		// Types

	typedef GS::BidirectionalContainerIterator<ConstRefList> 				Iterator;
	typedef GS::ConstBidirectionalContainerIterator<ConstRefList>			ConstIterator;

	typedef GS::GeneralBidirectionalContainerIterator<ConstRefList> 		GeneralIterator;
	typedef GS::ConstGeneralBidirectionalContainerIterator<ConstRefList>	ConstGeneralIterator;

	class ConstEnumerator;
	class ConversionEnumerator;

		// Constructors

	template <class SourceType> friend class ConstRefList;

	inline ConstRefList ();
	inline ConstRefList (const ConstRef<Type>& object);
	template <class SourceType>
	inline ConstRefList (const ConstRef<SourceType>& object);
	inline ConstRefList (std::initializer_list<ConstRef<Type>> source);
	inline ConstRefList (std::initializer_list<Ref<Type>> source);
	inline ConstRefList (const ConstRefListSource<Type>& source);
	template <class SourceType>
	inline ConstRefList (const ConstRefListSource<SourceType>& source);
	inline ConstRefList (const RefListSource<Type>& source);
	template <class SourceType>
	inline ConstRefList (const RefListSource<SourceType>& source);
	inline explicit ConstRefList (const GS::ConstEnumerator<ConstRef<Type>>& enumerator);
	inline ConstRefList (const GS::ConversionEnumerator<ConstRef<Type>>& enumerator);

	template <class SourceType>
	inline ConstRefList (std::initializer_list<ConstRef<SourceType>> source);

	template <class SourceType>
	inline ConstRefList (std::initializer_list<Ref<SourceType>> source);

	inline ConstRefList (const ConstRefList& source);
	inline ConstRefList (ConstRefList&& source);

	inline explicit ConstRefList (const RefList<Type>& source);
	inline ConstRefList (RefList<Type>&& source);

	template <class SourceType>
	inline ConstRefList (const ConstRefList<SourceType>& source);
	template <class SourceType>
	inline ConstRefList (ConstRefList<SourceType>&& source);

	template <class SourceType>
	inline explicit ConstRefList (const RefList<SourceType>& source);
	template <class SourceType>
	inline explicit ConstRefList (RefList<SourceType>&& source);

	inline ConstRefList&	operator= (const ConstRefList& source);
	inline ConstRefList&	operator= (ConstRefList&& source);

	inline ConstRefList&	operator= (const RefList<Type>& source);
	inline ConstRefList&	operator= (RefList<Type>&& source);

	template <class SourceType>
	inline ConstRefList&	operator= (const ConstRefList<SourceType>& source);
	template <class SourceType>
	inline ConstRefList&	operator= (ConstRefList<SourceType>&& source);

	template <class SourceType>
	inline ConstRefList&	operator= (const RefList<SourceType>& source);
	template <class SourceType>
	inline ConstRefList&	operator= (RefList<SourceType>&& source);

	inline ConstRefList&	operator= (const ConstRefListSource<Type>& source);
	template <class SourceType>
	inline ConstRefList&	operator= (const ConstRefListSource<SourceType>& source);
	inline ConstRefList&	operator= (const RefListSource<Type>& source);
	template <class SourceType>
	inline ConstRefList&	operator= (const RefListSource<SourceType>& source);

	ConstRefList&	operator= (const GS::ConstEnumerator<ConstRef<Type>>& enumerator);

	inline ~ConstRefList ();

	inline	void	Move (ConstRefList& source);
	void			Move (const std::function<void (ConstRef<Type>&&)>& processor);
	template <class SourceType>
	inline	void	Move (ConstRefList<SourceType>& source);

		// User interface

	inline void		Append (const ConstRef<Type>& object);
	inline void		Append (ConstRef<Type>&& object);

	template <class SourceType>
	inline void		Append (const ConstRef<SourceType>& object);
	template <class SourceType>
	inline void		Append (ConstRef<SourceType>&& object);

	inline void		Append (const Ref<Type>& object);
	inline void		Append (Ref<Type>&& object);

	template <class SourceType>
	inline void		Append (const Ref<SourceType>& object);
	template <class SourceType>
	inline void		Append (Ref<SourceType>&& object);

	inline void		Append (const ConstRefList& objects);
	inline void		Append (ConstRefList&& objects);

	template <class SourceType>
	inline void		Append (const ConstRefList<SourceType>& objects);
	template <class SourceType>
	inline void		Append (ConstRefList<SourceType>&& objects);

	inline void		Append (const RefList<Type>& objects);
	inline void		Append (RefList<Type>&& objects);

	template <class SourceType>
	inline void		Append (const RefList<SourceType>& objects);
	template <class SourceType>
	inline void		Append (RefList<SourceType>&& objects);

	inline void		Append (const ConstRefListSource<Type>& objects);
	template <class SourceType>
	inline void		Append (const ConstRefListSource<SourceType>& objects);
	inline void		Append (const RefListSource<Type>& objects);
	template <class SourceType>
	inline void		Append (const RefListSource<SourceType>& objects);
	inline void		Clear  (void);

	inline USize	GetSize (void) const;
	inline bool		IsEmpty (void) const;

	inline bool		Contains	 (const ConstRef<Type>& object) const;
	bool			Contains	 (std::initializer_list<ConstRef<Type>> items) const;
	bool			ContainsOnly (std::initializer_list<ConstRef<Type>> items) const;

	inline bool		operator== (const ConstRefList& rightOp) const;
	template <class RightType>
	inline bool		operator== (const ConstRefList<RightType>& rightOp) const;
	template <class RightType>
	inline bool		operator== (const RefList<RightType>& rightOp) const;
	inline bool		operator!= (const ConstRefList& rightOp) const;
	template <class RightType>
	inline bool		operator!= (const ConstRefList<RightType>& rightOp) const;
	template <class RightType>
	inline bool		operator!= (const RefList<RightType>& rightOp) const;

	inline bool		IsEqualByContent (const ConstRefList& rightOp) const;

	inline Iterator				Enumerate (void);
	inline ConstIterator		Enumerate (void) const;

	template <class Function>
	inline void					Enumerate	   (Function&& processor);
	template <class Function>
	inline void					Enumerate	   (Function&& processor) const;
	template <class Function>
	inline void					EnumerateConst (Function&& processor) const;

	inline Iterator				Begin (void);
	inline ConstIterator		Begin (void) const;

	inline Iterator				End	(void);
	inline ConstIterator		End	(void) const;

	inline GeneralIterator		EnumerateGeneral (void);
	inline ConstGeneralIterator	EnumerateGeneral (void) const;

	inline GeneralIterator		BeginGeneral (void);
	inline ConstGeneralIterator	BeginGeneral (void) const;

	inline GeneralIterator		EndGeneral	(void);
	inline ConstGeneralIterator	EndGeneral	(void) const;

	inline operator ConstEnumerator	() const;
	inline ConversionEnumerator		Convert (void) const;

	inline GSErrCode			Read  (GS::IChannel& ic);
	inline GSErrCode			Write (GS::OChannel& oc) const;

	inline void					SetCapacity (USize newCapacity);

		// Casting

	template <class BaseType>
	ODB_FORCE_INLINE const ConstRefList<BaseType>&	As (void) const;

		// Types

	class ConstEnumerator: public GS::ConstEnumerator<ConstRef<Type>> {
	private:
		const ConstRefList* source;

	public:
		inline ConstEnumerator (const ConstRefList& source);

		virtual void	Enumerate (const std::function<void (const ConstRef<Type>&)>& processor) const override;
	};

	class ConversionEnumerator: public GS::ConversionEnumerator<ConstRef<Type>> {
	private:
		const ConstRefList* source;

	public:
		inline ConversionEnumerator (const ConstRefList& source);

		virtual void	Enumerate (const std::function<void (const ConstRef<Type>&)>& processor) const override;
	};
};


template <class T>
class ConstRefListInserter {
	ConstRefList<T>* constRefList;

public:
	ConstRefListInserter (ConstRefList<T>* constrefList) :
		constRefList (constRefList)
	{
	}

	void operator() (const ConstRef<T>& object) const { constRefList->Push (object); }
	void operator() (ConstRef<T>&& object)		const { constRefList->Push (std::move (object)); }
};


template <class ToType, class FromType>
inline ConstRefList<ToType>&		UnsafeBaseCast (ConstRefList<FromType>& from);

template <class ToType, class FromType>
inline const ConstRefList<ToType>&	StaticCast (const ConstRefList<FromType>& from);

template <class Type>
inline ConstRefListInserter<Type>	GetInserter (ConstRefList<Type>& destination);

}	// namespace ODB


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList ()
{
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const ConstRef<Type>& object)
{
	objects.Push (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (const ConstRef<SourceType>& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (std::initializer_list<ConstRef<Type>> objects)
{
	for (const auto& object : objects)
		this->objects.Push (object);
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (std::initializer_list<Ref<Type>> objects)
{
	for (const auto& object : objects)
		this->objects.Push (object.AsConst ());
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const ConstRefListSource<Type>& source)
{
	source.GetContent (this);
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (const ConstRefListSource<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	source.GetContent (reinterpret_cast<ConstRefList<SourceType>*> (this));
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const RefListSource<Type>& source)
{
	source.GetContent (reinterpret_cast<RefList<Type>*> (this));
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (const RefListSource<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	source.GetContent (reinterpret_cast<RefList<SourceType>*> (this));
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const GS::ConstEnumerator<ConstRef<Type>>& enumerator):
	objects (reinterpret_cast<const GS::ConstEnumerator<ConstRef<Object>>&> (enumerator))
{
}

	
template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const GS::ConversionEnumerator<ConstRef<Type>>& enumerator):
	objects (reinterpret_cast<const GS::ConversionEnumerator<ConstRef<Object>>&> (enumerator))
{
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (std::initializer_list<ConstRef<SourceType>> objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	for (const auto& object : objects)
		this->objects.Push (object);
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (std::initializer_list<Ref<SourceType>> objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	for (const auto& object : objects)
		this->objects.Push (object.AsConst ());
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const ConstRefList& source):
	objects (source.objects)
{
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (ConstRefList&& source)
{
	Move (source);
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (const RefList<Type>& source):
	objects (ToConst (source).objects)
{
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstRefList (RefList<Type>&& source)
{
	Move (ToConst (source));
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (const ConstRefList<SourceType>& source):
	objects (source.objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");
}

template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (ConstRefList<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	Move (source);
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (const RefList<SourceType>& source):
	objects (*reinterpret_cast<const GS::ArrayFB<ConstRef<Object>, 4>*> (&source.objects))
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");
}

template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>::ConstRefList (RefList<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Move (*reinterpret_cast<const GS::ArrayFB<ConstRef<Object>, 4>*> (&source.objects));
	// source is cleared by Move
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const ConstRefList& source)
{
	if (&source != this)
		objects = source.objects;

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (ConstRefList&& source)
{	
	Move (source);

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const RefList<Type>& source)
{
	if (static_cast<const void*> (&source) != this)
		objects = *reinterpret_cast<const GS::ArrayFB<ConstRef<Object>, 4>*> (&source.objects);

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (RefList<Type>&& source)
{
	objects.Move (*reinterpret_cast<GS::ArrayFB<ConstRef<Object>, 4>*> (&source.objects));
	// source is cleared by Move

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const ConstRefList<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	if (static_cast<const void*> (&source) != this)
		objects = source.objects;

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (ConstRefList<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	Move (source);

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const RefList<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	if (static_cast<const void*> (&source) != this)
		objects =  *reinterpret_cast<GS::ArrayFB<ConstRef<Object>, 4>*> (&source.objects);

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (RefList<SourceType>&& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Move (*reinterpret_cast<GS::ArrayFB<ConstRef<Object>, 4>*> (&source.objects));
	// source is cleared by Move

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const ConstRefListSource<Type>& source)
{
	source.GetContent (this);

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const ConstRefListSource<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	source.GetContent (reinterpret_cast<ConstRefList<SourceType>*> (this));

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const RefListSource<Type>& source)
{
	source.GetContent (reinterpret_cast<RefList<Type>*> (this));

	return *this;
}


template <class Type>
template <class SourceType>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const RefListSource<SourceType>& source)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	source.GetContent (reinterpret_cast<RefList<SourceType>*> (this));

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>&		ODB::ConstRefList<Type>::operator= (const GS::ConstEnumerator<ConstRef<Type>>& enumerator)
{
	objects.operator= (reinterpret_cast<const GS::ConstEnumerator<ConstRef<Object>>&> (enumerator));

	return *this;
}


template <class Type>
inline ODB::ConstRefList<Type>::~ConstRefList ()
{
}


template <class Type>
inline	void	ODB::ConstRefList<Type>::Move (ConstRefList& source)
{
	// source-target equality check shall be performed by Move
	objects.Move (source.objects);
	// source is cleared by Move
}


template <class Type>
void			ODB::ConstRefList<Type>::Move (const std::function<void (ConstRef<Type>&&)>& processor)
{
	objects.Move ([&processor] (ConstRef<Object>&& item) { processor (std::move (*reinterpret_cast<ConstRef<Type>*> (&item))); });
}


template <class Type>
template <class SourceType>
inline	void	ODB::ConstRefList<Type>::Move (ConstRefList<SourceType>& source)
{
	// source-target equality check shall be performed by Move
	objects.Move (source.objects);
	// source is cleared by Move
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (const ConstRef<Type>& object)
{
	objects.Push (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (ConstRef<Type>&& object)
{
	objects.Push (std::move (*reinterpret_cast<const ConstRef<Object>*> (&object)));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (const ConstRef<SourceType>& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (ConstRef<SourceType>&& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (std::move (*reinterpret_cast<const ConstRef<Object>*> (&object)));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (const Ref<Type>& object)
{
	objects.Push (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (Ref<Type>&& object)
{
	objects.Push (std::move (*reinterpret_cast<const ConstRef<Object>*> (&object)));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (const Ref<SourceType>& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (Ref<SourceType>&& object)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.Push (std::move (*reinterpret_cast<const ConstRef<Object>*> (&object)));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (const ConstRefList& objects)
{
	this->objects.Append (objects.objects);
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (ConstRefList&& objects)
{
	this->objects.Append (std::move (objects.objects));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (const ConstRefList<SourceType>& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	this->objects.Append (objects.objects);
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (ConstRefList<SourceType>&& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	this->objects.Append (std::move (objects.objects));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (const RefList<Type>& objects)
{
	this->objects.Append (objects.objects);
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (RefList<Type>&& objects)
{
	this->objects.Append (std::move (objects.objects));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (const RefList<SourceType>& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	this->objects.Append (objects.objects);
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (RefList<SourceType>&& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	this->objects.Append (std::move (objects.objects));
}



template <class Type>
inline void		ODB::ConstRefList<Type>::Append (const ConstRefListSource<Type>& objects)
{
	objects.AppendContent (this);
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (const ConstRefListSource<SourceType>& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.AppendContent (reinterpret_cast<ConstRefList<SourceType>*> (this));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Append (const RefListSource<Type>& objects)
{
	objects.AppendContent (reinterpret_cast<RefList<Type>*> (this));
}


template <class Type>
template <class SourceType>
inline void		ODB::ConstRefList<Type>::Append (const RefListSource<SourceType>& objects)
{
	static_assert (GS::IsCompatible<SourceType, Type>, "SourceType is not compatible with Type.");

	objects.AppendContent (reinterpret_cast<RefList<SourceType>*> (this));
}


template <class Type>
inline void		ODB::ConstRefList<Type>::Clear (void)
{
	objects.Clear ();
}


template <class Type>
inline USize	ODB::ConstRefList<Type>::GetSize (void) const
{
	return objects.GetSize ();
}


template <class Type>
inline bool		ODB::ConstRefList<Type>::IsEmpty (void) const
{
	return objects.IsEmpty ();
}


template <class Type>
inline bool		ODB::ConstRefList<Type>::Contains (const ConstRef<Type>& object) const
{
	return objects.Contains (*reinterpret_cast<const ConstRef<Object>*> (&object));
}


template <class Type>
bool	ODB::ConstRefList<Type>::Contains (std::initializer_list<ConstRef<Type>> objects) const
{
	for (const auto& object : objects) {
		if (!Contains (object))
			return false;
	}

	return true;
}


template <class Type>
bool	ODB::ConstRefList<Type>::ContainsOnly (std::initializer_list<ConstRef<Type>> objects) const
{
	if (this->objects.GetSize () != objects.size ())
		return false;

	for (const auto& object : objects) {
		if (!Contains (object))
			return false;
	}

	return true;
}


template <class Type>
inline bool		ODB::ConstRefList<Type>::operator== (const ConstRefList& rightOp) const
{
	return (objects == rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::ConstRefList<Type>::operator== (const ConstRefList<RightType>& rightOp) const
{
	return (objects == rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::ConstRefList<Type>::operator== (const RefList<RightType>& rightOp) const
{
	return (objects == rightOp.objects);
}


template <class Type>
inline bool		ODB::ConstRefList<Type>::operator!= (const ConstRefList& rightOp) const
{
	return (objects != rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::ConstRefList<Type>::operator!= (const ConstRefList<RightType>& rightOp) const
{
	return (objects != rightOp.objects);
}


template <class Type>
template <class RightType>
inline bool		ODB::ConstRefList<Type>::operator!= (const RefList<RightType>& rightOp) const
{
	return (objects != rightOp.objects);
}


template <class Type>
inline bool		ODB::ConstRefList<Type>::IsEqualByContent (const ConstRefList& rightOp) const
{
	if (objects.GetSize () != rightOp.objects.GetSize ())
		return false;

	for (UIndex i = 0; i < rightOp.objects.GetSize (); i++) {
		if (!objects.Contains (rightOp.objects[i]))
			return false;
	}

	return true;
}


template <class Type>
inline typename ODB::ConstRefList<Type>::Iterator	ODB::ConstRefList<Type>::Enumerate (void)
{
	return Iterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConstIterator	ODB::ConstRefList<Type>::Enumerate (void) const
{
	return ConstIterator (*this, IteratorState (0));
}


template <class Type>
template <class Function>
inline void	ODB::ConstRefList<Type>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < objects.GetSize (); i++)
		processor (reinterpret_cast<ConstRef<Type>&> (objects[i]));
}


template <class Type>
template <class Function>
inline void	ODB::ConstRefList<Type>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < objects.GetSize (); i++)
		processor (reinterpret_cast<const ConstRef<Type>&> (objects[i]));
}


template <class Type>
template <class Function>
inline void	ODB::ConstRefList<Type>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type>
inline typename ODB::ConstRefList<Type>::Iterator	ODB::ConstRefList<Type>::Begin (void)
{
	return Iterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConstIterator	ODB::ConstRefList<Type>::Begin (void) const
{
	return ConstIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::Iterator	ODB::ConstRefList<Type>::End (void)
{
	return Iterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConstIterator	ODB::ConstRefList<Type>::End (void) const
{
	return ConstIterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::GeneralIterator	ODB::ConstRefList<Type>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConstGeneralIterator	ODB::ConstRefList<Type>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::GeneralIterator	ODB::ConstRefList<Type>::BeginGeneral (void)
{
	return GeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConstGeneralIterator	ODB::ConstRefList<Type>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (0));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::GeneralIterator	ODB::ConstRefList<Type>::EndGeneral (void)
{
	return GeneralIterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConstGeneralIterator	ODB::ConstRefList<Type>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, IteratorState (objects.GetSize ()));
}


template <class Type>
inline ODB::ConstRefList<Type>::operator typename ODB::ConstRefList<Type>::ConstEnumerator () const
{
	return ConstEnumerator (*this);
}


template <class Type>
inline typename ODB::ConstRefList<Type>::ConversionEnumerator	ODB::ConstRefList<Type>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type>
inline GSErrCode	ODB::ConstRefList<Type>::Read (GS::IChannel& ic)
{
	return objects.Read (ic);
}


template <class Type>
inline GSErrCode	ODB::ConstRefList<Type>::Write (GS::OChannel& oc) const
{
	return objects.Write (oc);
}


template <class Type>
inline void		ODB::ConstRefList<Type>::SetCapacity (USize newCapacity)
{
	objects.SetCapacity (newCapacity);
}


template <class Type>
template <class BaseType>
ODB_FORCE_INLINE const ODB::ConstRefList<BaseType>&		ODB::ConstRefList<Type>::As (void) const
{
	static_assert (GS::IsCompatible<Type, BaseType>, "Type is not compatible with BaseType.");

	return *reinterpret_cast<const ConstRefList<BaseType>*> (this);
}


template <class Type>
inline ODB::ConstRefList<Type>::ConstEnumerator::ConstEnumerator (const ConstRefList& source):
	source (&source)
{
}


template <class Type>
void	ODB::ConstRefList<Type>::ConstEnumerator::Enumerate (const std::function<void (const ConstRef<Type>&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type>
inline ODB::ConstRefList<Type>::ConversionEnumerator::ConversionEnumerator (const ConstRefList& source):
	source (&source)
{
}


template <class Type>
void	ODB::ConstRefList<Type>::ConversionEnumerator::Enumerate (const std::function<void (const ConstRef<Type>&)>& processor) const
{
	source->Enumerate (processor);
}


template <class ToType, class FromType>
inline ODB::ConstRefList<ToType>&	ODB::UnsafeBaseCast (ODB::ConstRefList<FromType>& from)
{
	static_assert (GS::IsCompatible<FromType, ToType>, "FromType is not compatible with ToType.");

	return *reinterpret_cast<ConstRefList<ToType>*> (&from);
}


template <class ToType, class FromType>
inline const ODB::ConstRefList<ToType>&		ODB::StaticCast (const ODB::ConstRefList<FromType>& from)
{
	static_assert (GS::IsCompatible<FromType, ToType> || GS::IsCompatible<ToType, FromType>, "FromType and ToType are unrelated.");

	return *reinterpret_cast<const ConstRefList<ToType>*> (&from);
}


template <class Type>
auto	ODB::begin (ConstRefList<Type>& constRefList)
{
	return reinterpret_cast<ConstRef<Type>*> (constRefList.objects.BeginFast ());
}


template <class Type>
auto	ODB::end (ConstRefList<Type>& constRefList)
{
	return reinterpret_cast<ConstRef<Type>*> (constRefList.objects.EndFast ());
}


template <class Type>
auto	ODB::begin (const ConstRefList<Type>& constRefList)
{
	return reinterpret_cast<const ConstRef<Type>*> (constRefList.objects.BeginFast ());
}


template <class Type>
auto	ODB::end (const ConstRefList<Type>& constRefList)
{
	return reinterpret_cast<const ConstRef<Type>*> (constRefList.objects.EndFast ());
}


template <class Type>
inline ODB::ConstRefListInserter<Type>		ODB::GetInserter (ConstRefList<Type>& destination)
{
	return ODB::ConstRefListInserter<Type> (&destination);
}
// ____________________________ Class ConstRefList _____________________________



// ========================= Class ConstRefListSource ==========================

namespace ODB {

template <class Type>
class ConstRefListSource {
private:
	template <class T> friend class ConstRefList;
	inline void		GetContent	  (ConstRefList<Type>* destination) const;
	virtual void	AppendContent (ConstRefList<Type>* destination) const = 0;

public:
	inline bool		operator== (const ConstRefList<Type>& rightOp) const	  { ConstRefList<Type> leftOp; GetContent (&leftOp); return (leftOp == rightOp); }
	template <class RightType>
	inline bool		operator== (const ConstRefList<RightType>& rightOp) const { ConstRefList<Type> leftOp; GetContent (&leftOp); return (leftOp == rightOp); }
	template <class RightType>
	inline bool		operator== (const RefList<RightType>& rightOp) const	  { ConstRefList<Type> leftOp; GetContent (&leftOp); return (leftOp == rightOp); }
	inline bool		operator!= (const ConstRefList<Type>& rightOp) const	  { ConstRefList<Type> leftOp; GetContent (&leftOp); return (leftOp != rightOp); }
	template <class RightType>
	inline bool		operator!= (const ConstRefList<RightType>& rightOp) const { ConstRefList<Type> leftOp; GetContent (&leftOp); return (leftOp != rightOp); }
	template <class RightType>
	inline bool		operator!= (const RefList<RightType>& rightOp) const	  { ConstRefList<Type> leftOp; GetContent (&leftOp); return (leftOp != rightOp); }
	inline ConstRefList<Type> operator* () const							  { ConstRefList<Type> content; GetContent (&content); return content; }
};

}	// namespace ODB



template <class Type>
inline void		ODB::ConstRefListSource<Type>::GetContent (ConstRefList<Type>* destination) const
{
	destination->Clear ();
	AppendContent (destination);
}
// _________________________ Class ConstRefListSource __________________________


namespace ODB {
	typedef ODB::RefList<ODB::Object>		ObjectRefList;
	typedef ODB::ConstRefList<ODB::Object>	ObjectConstRefList;
}

//lint -restore

#endif
