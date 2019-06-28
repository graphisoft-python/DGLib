
// *****************************************************************************
//
//                                  Class Array
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ARRAY_HPP
#define ARRAY_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "RandomContainer.hpp"

#include "RandomContainerIterator.hpp"
#include "RandomContainerReverseIterator.hpp"
#include "Enumerator.hpp"
#include "BaseAlgorithms.hpp"

#include "ClassInfo.hpp"
#include "IOFrame.hpp"
#include "Channel.hpp"

#include <new>
#include <utility>
#include <functional>

#include "InitializerRefList.hpp"


// ================================ Class Array ================================

namespace GS {

class GSROOT_DLL_EXPORT ArrayPrivate {
public:
	static GS::ClassInfo	classInfo;	// Array's private classInfo
};


template <class Type>
class Array: public RandomContainer<Type> {
private:
	Type*	array = nullptr;	// array storing items
	USize	capacity = 0;		// capacity of the array (in items)
	USize	size = 0;			// number of items in the array

	inline void		IncreaseCapacity (USize minCapacity);
	inline void		DecreaseCapacity (USize minCapacity);
	void			AdjustCapacity   (USize minCapacity);
	virtual void	Reallocate	     (USize minCapacity);

	void			SetIncreasedSize (USize increasedSize);
	void			SetDecreasedSize (USize decreasedSize);

protected:
	void			SetContent (Type* newArray, USize newSize, USize newCapacity);

	virtual USize	GetMinBufferCapacity (void) const;
	virtual Type*	AllocateNewBuffer	 (USize bufferCapacity, const Type* oldBuffer);
	virtual void	DeleteBuffer		 (Type* buffer);
	virtual bool	IsIndependentBuffer  (const Type* buffer) const;

public:
		// Types

	typedef RandomContainerIterator<Array>				Iterator;
	typedef ConstRandomContainerIterator<Array>			ConstIterator;

	typedef GeneralRandomContainerIterator<Array>		GeneralIterator;
	typedef ConstGeneralRandomContainerIterator<Array>	ConstGeneralIterator;

	typedef RandomContainerReverseIterator<Array>		ReverseIterator;
	typedef ConstRandomContainerReverseIterator<Array>	ConstReverseIterator;

	typedef RandomContainerRange<Array>					Range;
	typedef RandomContainerConstRange<Array>			ConstRange;

	typedef Type*		 FastIterator;
	typedef const Type*	 ConstFastIterator;

	class ConstEnumerator;
	class ConversionEnumerator;

		// Constructors

	Array ();
	explicit Array (USize initialCapacity);
	explicit Array (ConstIterator begin);
	explicit Array (ConstForwardIterator<Type> begin);
	explicit Array (const GS::ConstEnumerator<Type>& enumerator);
	Array (const GS::ConversionEnumerator<Type>& enumerator);
	Array (std::initializer_list<Type> items);
	Array (ByRefSelector, InitializerRefList<Type> items);
	Array (const Array& source);
	Array (Array&& source);

	template <class SourceType>
	explicit Array (const Array<SourceType>& source);

	Array&	operator= (const Array& source);
	Array&	operator= (Array&& source);
	Array&	operator= (const GS::ConstEnumerator<Type>& enumerator);

	template <class SourceType>
	Array&	operator= (const Array<SourceType>& source);

	virtual ~Array ();


		// Type conversion constructors



	inline	void		Move (Array& source);
	void				Move (const std::function<void (Type&&)>& processor);

		// Item access

	inline Type&		operator[] (UIndex idx);
	inline const Type&	operator[] (UIndex idx) const;

	inline Type&		Get (UIndex idx);
	inline const Type&	Get (UIndex idx) const;

	inline Type&		GetFirst (void);
	inline const Type&	GetFirst (void) const;

	inline Type&		GetLast (void);
	inline const Type&	GetLast (void) const;
	inline UIndex		GetLastIndex (void) const;

	inline void			Set (UIndex idx, const Type& item);
	inline void			Set (UIndex idx, Type&& item);

		// Content management

	void	Fill (const Type& item, UIndex from = 0, USize range = MaxUSize);

	USize	Replace (const Type& oldItem, const Type& newItem, UIndex from = 0, USize range = MaxUSize);

	void	Insert (UIndex to, const Type& item);
	void	Insert (UIndex to, Type&& item);
	void	Insert (UIndex to, ConstIterator begin);
	void	Insert (UIndex to, ConstIterator begin, ConstIterator end);
	void	Insert (UIndex to, ConstForwardIterator<Type> begin);
	void	Insert (UIndex to, ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end);

	void	Append (const Array& items);
	void	Append (Array&& items);

	void	Delete		(UIndex idx);
	void	Delete		(UIndex from, USize range);
	void	DeleteLast	(void);

	UIndex	DeleteFirst	(const Type& item);
	UIndex	DeleteLast	(const Type& item);
	void	DeleteAll	(const Type& item);

	void	Clear (bool keepCapacity = false);

	void	Swap (Array& rightOp);

	void	Push (const Type& item);
	void	Push (Type&& item);

	template <class... ItemParameters>
	void	PushNew (ItemParameters&&... itemParameters);
	
	void	Pop	 (Type* item);
	Type	Pop	 (void);

	inline USize	GetSize		 (void) const;
	inline bool		IsEmpty		 (void) const;
	inline bool		IsLast		 (UIndex idx) const;
	void			SetSize		 (USize newSize);
	inline void		IncreaseSize (USize sizeIncrement);
	inline void		EnsureSize	 (USize requiredSize);

		// Content query

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

	inline ReverseIterator		ReverseEnumerate (void);
	inline ConstReverseIterator	ReverseEnumerate (void) const;

	template <class Function>
	inline void					ReverseEnumerate	  (Function&& processor);
	template <class Function>
	inline void					ReverseEnumerate	  (Function&& processor) const;
	template <class Function>
	inline void					ReverseEnumerateConst (Function&& processor) const;

	inline ReverseIterator		ReverseBegin (void);
	inline ConstReverseIterator	ReverseBegin (void) const;

	inline ReverseIterator		ReverseEnd	(void);
	inline ConstReverseIterator	ReverseEnd	(void) const;

	inline FastIterator			BeginFast (void);
	inline ConstFastIterator	BeginFast (void) const;

	inline FastIterator			EndFast	(void);
	inline ConstFastIterator	EndFast	(void) const;

	Range         operator() (UIndex begin, UIndex end);
	ConstRange    operator() (UIndex begin, UIndex end) const;

	inline operator ConstEnumerator	() const;
	inline ConversionEnumerator		Convert (void) const;

	inline auto&				AsConst (void) const;

	UIndex	FindFirst (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindFirst (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;
	UIndex	FindLast  (const Type& item) const;
	UIndex	FindLast  (const std::function<bool (const Type&)>& condition) const;

	bool	Contains	 (const Type& item) const;
	bool	Contains	 (const std::function<bool (const Type&)>& condition) const;
	bool	Contains	 (std::initializer_list<Type> items) const;
	bool	ContainsOnly (std::initializer_list<Type> items) const;

	USize	Count (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	USize	Count (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;

	bool	operator== (const Array& rightOp) const;
	bool	operator!= (const Array& rightOp) const;

		// Performance tuning

	USize	GetCapacity	(void) const;
	void	SetCapacity (USize newCapacity);

	inline void		EnsureCapacity (USize minCapacity);

		// I/O

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Read  (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader);

	GSErrCode	Write (OChannel& oc) const;
	GSErrCode	Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const;

		// Low level access

	inline Type*		GetContent (void);
	inline const Type*	GetContent (void) const;

		// Debug

	void	Print	   (OChannel& oc) const;
	void	Dump	   (OChannel& oc) const;
	bool	CheckState (void) const;

		// Types

	class ConstEnumerator: public GS::ConstEnumerator<Type> {
	private:
		const Array* source;

	public:
		inline ConstEnumerator (const Array& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;
	};

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const Array* source;

	public:
		inline ConversionEnumerator (const Array& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;
	};
};

// === Array methods ===================================================================================================

template <class Type>
Array<Type>::Array ()
{
}


template <class Type>
Array<Type>::Array (USize initialCapacity)
{
	IncreaseCapacity (initialCapacity);
}


template <class Type>
Array<Type>::Array (ConstIterator begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type>
Array<Type>::Array (ConstForwardIterator<Type> begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type>
Array<Type>::Array (const GS::ConstEnumerator<Type>& enumerator)
{
	enumerator.Enumerate (GetInserter (*this));
}


template <class Type>
Array<Type>::Array (const GS::ConversionEnumerator<Type>& enumerator)
{
	enumerator.Enumerate (GetInserter (*this));
}


template <class Type>
template <class SourceType>
Array<Type>::Array (const Array<SourceType>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	IncreaseCapacity (source.GetSize ());

	UIndex i = 0;
	for (const SourceType& item : source)
		new (&array[i++]) Type (item);

	size = source.GetSize ();
}


template <class Type>
template <class SourceType>
Array<Type>&	Array<Type>::operator= (const Array<SourceType>& source)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	Clear ();

	IncreaseCapacity (source.GetSize ());

	UIndex i = 0;
	for (const SourceType& item : source)
		new (&array[i++]) Type (item);
	size = source.GetSize ();

	return *this;
}


template <class Type>
Array<Type>::Array (std::initializer_list<Type> items)
{
	IncreaseCapacity (USize (items.size ()));

	UIndex i = 0;
	for (const Type& item : items)
		new (&array[i++]) Type (item);
	size = USize (items.size ());
}


template <class Type>
Array<Type>::Array (ByRefSelector, InitializerRefList<Type> items)
{
	IncreaseCapacity (USize (items.size ()));

	UIndex i = 0;
	for (const auto& item : items)
		new (&array[i++]) Type (*item);
	size = USize (items.size ());
}


template <class Type>
Array<Type>::Array (const Array& source)
{
	IncreaseCapacity (source.size);

	for (UIndex i = 0; i < source.size; i++)
		new (&array[i]) Type (source.array[i]);
	size = source.size;
}


template <class Type>
Array<Type>::Array (Array&& source)
{
	Move (source);
}


template <class Type>
Array<Type>&	Array<Type>::operator= (const Array& source)
{
	if (&source != this) {
		Clear ();

		IncreaseCapacity (source.size);

		for (UIndex i = 0; i < source.size; i++)
			new (&array[i]) Type (source.array[i]);
		size = source.size;
	}
	
	return *this;
}


template <class Type>
Array<Type>&	Array<Type>::operator= (Array&& source)
{
	Move (source);

	return *this;
}


template <class Type>
Array<Type>&	Array<Type>::operator= (const GS::ConstEnumerator<Type>& enumerator)
{
	Clear ();

	enumerator.Enumerate (GetInserter (*this));

	return *this;
}


template <class Type>
Array<Type>::~Array ()
{
	Clear ();
}


template <class Type>
inline	void	Array<Type>::Move (Array& source)
{
	if (DBERROR (&source == this))
		return;

	if (IsIndependentBuffer (array) && source.IsIndependentBuffer (source.array)) {
		GS::Swap (array,	source.array);
		GS::Swap (capacity, source.capacity);
		GS::Swap (size,		source.size);
	} else {
		Clear ();

		IncreaseCapacity (source.size);

		for (UIndex i = 0; i < source.size; i++)
			new (&array[i]) Type (std::move (source.array[i]));
		size = source.size;
	}

	source.Clear ();
}


template <class Type>
void			Array<Type>::Move (const std::function<void (Type&&)>& processor)
{
	for (UIndex i = 0; i < size; ++i) {
		processor (std::move (array[i]));
	}

	Clear ();
}


template <class Type>
inline Type&	Array<Type>::operator[] (UIndex idx)
{
	REF_CHECK (idx < size);

	return array[idx];
}


template <class Type>
inline const Type&	Array<Type>::operator[] (UIndex idx) const
{
	REF_CHECK (idx < size);

	return array[idx];
}


template <class Type>
inline Type&	Array<Type>::Get (UIndex idx)
{
	REF_CHECK_R (idx < size);

	return array[idx];
}


template <class Type>
inline const Type&	Array<Type>::Get (UIndex idx) const
{
	REF_CHECK_R (idx < size);

	return array[idx];
}


template <class Type>
inline Type&	Array<Type>::GetFirst (void)
{
	PRECOND (size != 0);

	return array[0];
}


template <class Type>
inline const Type&	Array<Type>::GetFirst (void) const
{
	PRECOND (size != 0);

	return array[0];
}


template <class Type>
inline Type&	Array<Type>::GetLast (void)
{
	PRECOND (size != 0);

	return array[size - 1];
}


template <class Type>
inline const Type&	Array<Type>::GetLast (void) const
{
	PRECOND (size != 0);

	return array[size - 1];
}


template <class Type>
inline UIndex	Array<Type>::GetLastIndex (void) const
{
	PRECOND (size != 0);

	return size - 1;
}


template <class Type>
inline void		Array<Type>::Set (UIndex idx, const Type& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	array[idx] = item;
}


template <class Type>
inline void		Array<Type>::Set (UIndex idx, Type&& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	array[idx] = std::move (item);
}


template <class Type>
void	Array<Type>::Fill (const Type& item, UIndex from, USize range)
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	GS::Fill (array + from, array + from + range, item);
}


template <class Type>
USize	Array<Type>::Replace (const Type& oldItem, const Type& newItem, UIndex from, USize range)
{
	NULL_REF_CHECK (oldItem);
	NULL_REF_CHECK (newItem);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Replace (array + from, array + from + range, oldItem, newItem);
}


template <class Type>
void	Array<Type>::Insert (UIndex to, const Type& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);

	if (&item >= array && &item < array + size) {	// is item in the array ?
		Type temp = item;
		Insert (to, std::move (temp));
		return;
	}

	IncreaseCapacity (size + 1);

	if (size == to) {
		new (&array[size]) Type (item);
	} else { // size > 0 for sure
		new (&array[size]) Type (std::move (array[size - 1]));
		for (UIndex i = size - 1; i > to; i--)
			array[i] = std::move (array[i - 1]);
		array[to] = item;
	}

	size++;
}


template <class Type>
void	Array<Type>::Insert (UIndex to, Type&& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);
	DBASSERT (&item < array || &item >= array + size);		// item should not be in the array

	IncreaseCapacity (size + 1);

	if (size == to) {
		new (&array[size]) Type (std::move (item));
	} else { // size > 0 for sure
		new (&array[size]) Type (std::move (array[size - 1]));
		for (UIndex i = size - 1; i > to; i--)
			array[i] = std::move (array[i - 1]);
		array[to] = std::move (item);
	}

	size++;
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstIterator begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstIterator begin, ConstIterator end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstForwardIterator<Type> begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Insert (UIndex to, ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type>
void	Array<Type>::Append (const Array& items)
{
	NULL_REF_CHECK (items);

	if (&items == this) {
		Array temp = items;
		Append (std::move (temp));
		return;
	}

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		new (&array[size + i]) Type (items[i]);

	size += items.GetSize ();
}


template <class Type>
void	Array<Type>::Append (Array&& items)
{
	NULL_REF_CHECK (items);

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		new (&array[size + i]) Type (std::move (items[i]));

	size += items.GetSize ();
}


template <class Type>
void	Array<Type>::Delete (UIndex idx)
{
	REF_CHECK (idx < size);

	for (UIndex i = idx + 1; i < size; i++)
		array[i - 1] = std::move (array[i]);

	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type>
void	Array<Type>::Delete (UIndex from, USize range)
{
	REF_CHECK (from + range <= size);

	if (range == 0)
		return;

	for (UIndex i = from + range; i < size; i++)
		array[i - range] = std::move (array[i]);

	for (UIndex j = size - range; j < size; j++)
		array[j].~Type ();
	size -= range;

	DecreaseCapacity (size);
}


template <class Type>
void	Array<Type>::DeleteLast (void)
{
	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type>
UIndex	Array<Type>::DeleteFirst (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex first = FindFirst (item);
	if (first != MaxUIndex)
		Delete (first);

	return first;
}


template <class Type>
UIndex	Array<Type>::DeleteLast (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex last = FindLast (item);
	if (last != MaxUIndex)
		Delete (last);

	return last;
}


template <class Type>
void	Array<Type>::DeleteAll (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex last = 0;
	while (last != MaxUIndex)
		last = DeleteLast (item);	// deleting from the end is faster
}


template <class Type>
void	Array<Type>::Clear (bool keepCapacity)
{
	for (UIndex i = 0; i < size; i++)
		array[i].~Type ();

	if (!keepCapacity) {
		DeleteBuffer (array);
		array = nullptr;
		capacity = 0;
	}

	size = 0;
}


template <class Type>
void	Array<Type>::Swap (Array& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (IsIndependentBuffer (array) && rightOp.IsIndependentBuffer (rightOp.array)) {
		GS::Swap (array,	rightOp.array);
		GS::Swap (capacity, rightOp.capacity);
		GS::Swap (size,		rightOp.size);
	} else {
		Array* largeArray = this;
		Array* smallArray = &rightOp;
		if (largeArray->GetSize () < smallArray->GetSize ())
			GS::Swap (largeArray, smallArray);

		USize smallArraySize = smallArray->GetSize ();

		for (UIndex i = 0; i < smallArraySize; i++)
			GS::Swap ((*smallArray)[i], (*largeArray)[i]);

		for (UIndex i = smallArraySize; i < largeArray->GetSize (); i++)
			smallArray->Push ((*largeArray)[i]);

		largeArray->SetDecreasedSize (smallArraySize);
	}
}



template <class Type>
void	Array<Type>::Push (const Type& item)
{
	NULL_REF_CHECK (item);

	if (&item >= array && &item < array + size) {	// is item in the array ?
		Type temp = item;
		Push (std::move (temp));
		return;
	}

	IncreaseCapacity (size + 1);

	new (&array[size]) Type (item);
	size++;
}


template <class Type>
void	Array<Type>::Push (Type&& item)
{
	NULL_REF_CHECK (item);
	DBASSERT (&item < array || &item >= array + size);		// item should not be in the array

	IncreaseCapacity (size + 1);

	new (&array[size]) Type (std::move (item));
	size++;
}


template <class Type>
template <class... ItemParameters>
void	Array<Type>::PushNew (ItemParameters&&... itemParameters)
{
	IncreaseCapacity (size + 1);

	new (&array[size]) Type (std::forward<ItemParameters> (itemParameters)...);
	size++;
}


template <class Type>
void	Array<Type>::Pop (Type* item)
{
	PRECOND (size != 0);
	NULL_PTR_CHECK (item);

	*item = std::move (array[size - 1]);

	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type>
Type	Array<Type>::Pop (void)
{
	PRECOND (size != 0);

	Type result = std::move (array[size - 1]);

	array[size - 1].~Type ();
	size--;

	DecreaseCapacity (size);

	return result;
}


template <class Type>
inline USize	Array<Type>::GetSize (void) const
{
	return size;
}


template <class Type>
inline bool		Array<Type>::IsEmpty (void) const
{
	return (size == 0);
}


template <class Type>
inline bool		Array<Type>::IsLast (UIndex idx) const
{
	return (size > 0 && idx == size - 1);
}


template <class Type>
void	Array<Type>::SetSize (USize newSize)
{
	if (newSize < size)
		SetDecreasedSize (newSize);
	else if (newSize > size)
		SetIncreasedSize (newSize);
}


template <class Type>
void	Array<Type>::IncreaseSize (USize sizeIncrement)
{
	SetSize (size + sizeIncrement);
}


template <class Type>
void	Array<Type>::EnsureSize (USize requiredSize)
{
	if (size < requiredSize)
		SetSize (requiredSize);
}


template <class Type>
inline typename Array<Type>::Iterator	Array<Type>::Enumerate (void)
{
	return Iterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::ConstIterator	Array<Type>::Enumerate (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type>
template <class Function>
inline void	Array<Type>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < size; i++)
		processor (array[i]);
}


template <class Type>
template <class Function>
inline void	Array<Type>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < size; i++)
		processor (const_cast<const Type&> (array[i]));
}


template <class Type>
template <class Function>
inline void	Array<Type>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type>
inline typename Array<Type>::Iterator	Array<Type>::Begin (void)
{
	return Iterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::ConstIterator	Array<Type>::Begin (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::Iterator	Array<Type>::End (void)
{
	return Iterator (*this, size);
}


template <class Type>
inline typename Array<Type>::ConstIterator	Array<Type>::End (void) const
{
	return ConstIterator (*this, size);
}


template <class Type>
inline typename Array<Type>::GeneralIterator	Array<Type>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::ConstGeneralIterator	Array<Type>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::GeneralIterator	Array<Type>::BeginGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::ConstGeneralIterator	Array<Type>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type>
inline typename Array<Type>::GeneralIterator	Array<Type>::EndGeneral (void)
{
	return GeneralIterator (*this, size);
}


template <class Type>
inline typename Array<Type>::ConstGeneralIterator	Array<Type>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, size);
}


template <class Type>
inline typename Array<Type>::ReverseIterator	Array<Type>::ReverseEnumerate (void)
{
	return ReverseIterator (*this, size - 1);
}


template <class Type>
inline typename Array<Type>::ConstReverseIterator	Array<Type>::ReverseEnumerate (void) const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type>
template <class Function>
inline void	Array<Type>::ReverseEnumerate (Function&& processor)
{
	for (UIndex i = size; i > 0; i--)
		processor (array[i - 1]);
}


template <class Type>
template <class Function>
inline void	Array<Type>::ReverseEnumerate (Function&& processor) const
{
	for (UIndex i = size; i > 0; i--)
		processor (const_cast<const Type&> (array[i - 1]));
}


template <class Type>
template <class Function>
inline void	Array<Type>::ReverseEnumerateConst (Function&& processor) const
{
	ReverseEnumerate (processor);
}


template <class Type>
inline typename Array<Type>::ReverseIterator	Array<Type>::ReverseBegin (void)
{
	return ReverseIterator (*this, size - 1);
}


template <class Type>
inline typename Array<Type>::ConstReverseIterator	Array<Type>::ReverseBegin (void) const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type>
inline typename Array<Type>::ReverseIterator	Array<Type>::ReverseEnd (void)
{
	return ReverseIterator (*this, -1);
}


template <class Type>
inline typename Array<Type>::ConstReverseIterator	Array<Type>::ReverseEnd (void) const
{
	return ConstReverseIterator (*this, -1);
}


template <class Type>
inline typename Array<Type>::FastIterator	Array<Type>::BeginFast (void)
{
	return array;
}


template <class Type>
inline typename Array<Type>::ConstFastIterator	Array<Type>::BeginFast (void) const
{
	return array;
}


template <class Type>
inline typename Array<Type>::FastIterator	Array<Type>::EndFast (void)
{
	return array + size;
}


template <class Type>
inline typename Array<Type>::ConstFastIterator	Array<Type>::EndFast (void) const
{
	return array + size;
}


template <class Type>
typename Array<Type>::Range        Array<Type>::operator() (UIndex begin, UIndex end)
{
	return { *this, begin, end };
}


template <class Type>
typename Array<Type>::ConstRange    Array<Type>::operator() (UIndex begin, UIndex end) const
{
	return { *this, begin, end };
}


template <class Type>
inline Array<Type>::operator typename Array<Type>::ConstEnumerator () const
{
	return ConstEnumerator (*this);
}


template <class Type>
inline typename Array<Type>::ConversionEnumerator	Array<Type>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type>
inline auto&	Array<Type>::AsConst (void) const
{ 
	return reinterpret_cast<const Array<typename Container<Type>::template MakeConstPtr<Type>::ConstType>&> (*this);
}


template <class Type>
UIndex	Array<Type>::FindFirst (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	Type* it = GS::Find (array + from, array + from + range, item);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type>
UIndex	Array<Type>::FindFirst (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	Type* it = GS::Find (array + from, array + from + range, condition);

	if (it == array + from + range)
		return MaxUIndex;
	else
		return TruncateTo32Bit (it - array);
}


template <class Type>
UIndex	Array<Type>::FindLast (const Type& item) const
{
	NULL_REF_CHECK (item);

	for (UIndex i = size; i > 0; i--) {
		if (array[i - 1] == item)
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type>
UIndex	Array<Type>::FindLast (const std::function<bool (const Type&)>& condition) const
{
	for (UIndex i = size; i > 0; i--) {
		if (condition (array[i - 1]))
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type>
bool	Array<Type>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (array, array + size, item) != array + size);
}


template <class Type>
bool	Array<Type>::Contains (const std::function<bool (const Type&)>& condition) const
{
	return (GS::Find (array, array + size, condition) != array + size);
}


template <class Type>
bool	Array<Type>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type>
bool	Array<Type>::ContainsOnly (std::initializer_list<Type> items) const
{
	if (size != items.size ())
		return false;

	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type>
USize	Array<Type>::Count (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (array + from, array + from + range, item);
}


template <class Type>
USize	Array<Type>::Count (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (array + from, array + from + range, condition);
}


template <class Type>
bool	Array<Type>::operator== (const Array& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (size != rightOp.size)
		return false;

	return (GS::IsEqual (array, array + size, rightOp.array));
}


template <class Type>
bool	Array<Type>::operator!= (const Array& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class Type>
USize	Array<Type>::GetCapacity (void) const
{
	return capacity;
}


template <class Type>
void	Array<Type>::SetCapacity (USize newCapacity)
{
	if (newCapacity < size)
		newCapacity = size;		// can't delete items with this method

	if (newCapacity == capacity)
		return;

	Reallocate (newCapacity);
}


template <class Type>
void	Array<Type>::EnsureCapacity (USize minCapacity)
{
	IncreaseCapacity (minCapacity);
}


template <class Type>
GSErrCode	Array<Type>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, ArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = GS::ReadType (ic, array[i]);

	return errorCode;
}


template <class Type>
GSErrCode	Array<Type>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, ArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = GS::WriteType (oc, array[i]);

	return errorCode;
}


template <class Type>
GSErrCode	Array<Type>::Read (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, ArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = reader (ic, array[i]);

	return errorCode;
}


template <class Type>
GSErrCode	Array<Type>::Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, ArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = writer (oc, array[i]);

	return errorCode;
}


template <class Type>
inline Type*	Array<Type>::GetContent (void)
{
	return array;
}


template <class Type>
inline const Type*	Array<Type>::GetContent (void) const
{
	return array;
}


template <class Type>
void	Array<Type>::Print (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "Array" << '\n';
}


template <class Type>
void	Array<Type>::Dump (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "array:    " << array    << '\n';
	oc << "capacity: " << capacity << '\n';
	oc << "size:     " << size     << '\n';
}


template <class Type>
bool	Array<Type>::CheckState (void) const
{
	if ((array == nullptr && (capacity != 0 || size != 0)) ||
		(array != nullptr && capacity == 0) ||
		capacity < size)
		return false;

	return true;
}


template <class Type>
USize	Array<Type>::GetMinBufferCapacity (void) const
{
	return 0;
}


template <class Type>
Type*	Array<Type>::AllocateNewBuffer (USize bufferCapacity, const Type* /*oldBuffer*/)
{
	return reinterpret_cast<Type*> (new char[bufferCapacity * sizeof (Type)]);	// buffer_overrun_reviewed_0
}


template <class Type>
void	Array<Type>::DeleteBuffer (Type* buffer)
{
	delete [] reinterpret_cast<char*> (buffer);
}


template <class Type>
bool	Array<Type>::IsIndependentBuffer (const Type* /*buffer*/) const
{
	return true;
}


template <class Type>
inline void		Array<Type>::IncreaseCapacity (USize minCapacity)
{
	if (minCapacity > capacity)
		AdjustCapacity (minCapacity);
}


template <class Type>
inline void		Array<Type>::DecreaseCapacity (USize minCapacity)
{
	if (minCapacity <= capacity / 4)
		AdjustCapacity (minCapacity);
}


template <class Type>
void	Array<Type>::AdjustCapacity (USize minCapacity)
{
	if (minCapacity <= capacity && minCapacity > capacity / 4)
		return;		// there is no need to reallocate

	Reallocate (GS::Max (minCapacity, size * 2));
}


template <class Type>
void Array<Type>::SetContent (Type* newArray, USize newSize, USize newCapacity)
{
	// This is used by HandleArray to notify Array about the Handle reallocation.
	ARG_CHECK (newCapacity >= newSize);

	array = newArray;
	size = newSize;
	capacity = newCapacity;
}


template <class Type>
void	Array<Type>::Reallocate (USize minCapacity)
{
	ARG_CHECK (minCapacity >= size);	// can't delete items with this method

	USize newCapacity = minCapacity;

	if (newCapacity < GetMinBufferCapacity ())
		newCapacity = GetMinBufferCapacity ();

	if (newCapacity == capacity)
		return;

	Type* newArray = nullptr;
	if (newCapacity != 0) {
		try {
			newArray = AllocateNewBuffer (newCapacity, array);
		}
		catch (const GS::OutOfMemoryException&) {
			if (capacity >= minCapacity)
				return;
			else
				throw;
		}

		for (UIndex i = 0; i < size; i++) {
			new (&newArray[i]) Type (std::move (array[i]));
			array[i].~Type ();
		}
	}

	DeleteBuffer (array);

	array = newArray;
	capacity = newCapacity;
}


template <class Type>
void	Array<Type>::SetIncreasedSize (USize increasedSize)
{
	IncreaseCapacity (increasedSize);

	for (UIndex i = size; i < increasedSize; i++)
		new (&array[i]) Type ();

	size = increasedSize;
}


template <class Type>
void	Array<Type>::SetDecreasedSize (USize decreasedSize)
{
	for (UIndex i = decreasedSize; i < size; i++)
		array[i].~Type ();

	size = decreasedSize;

	DecreaseCapacity (size);
}


template <class Type>
inline Array<Type>::ConstEnumerator::ConstEnumerator (const Array& source):
	source (&source)
{
}


template <class Type>
void	Array<Type>::ConstEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type>
inline Array<Type>::ConversionEnumerator::ConversionEnumerator (const Array& source):
	source (&source)
{
}


template <class Type>
void	Array<Type>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}

// === class ArrayInserter =============================================================================================

template <class Type>
class ArrayInserter {
	Array<Type>* array;

public:

	explicit ArrayInserter (Array<Type>* array) :
		array (array)
	{
	}

	void     operator() (const Type& value) const { array->Push (value); }
	void     operator() (Type&& value)		const { array->Push (std::move (value)); }

	typedef Type DecayedFirstArgumentType;
};


// === Global functions ================================================================================================

template <class Type>
inline auto		begin (Array<Type>& array)
{
	return array.BeginFast ();
}


template <class Type>
inline auto		end (Array<Type>& array)
{
	return array.EndFast ();
}


template <class Type>
inline auto		begin (const Array<Type>& array)
{
	return array.BeginFast ();
}


template <class Type>
inline auto		end (const Array<Type>& array)
{
	return array.EndFast ();
}


template <class Type>
inline ArrayInserter<Type>	GetInserter (Array<Type>& array)
{
	return ArrayInserter<Type> (&array);
}


template <class Type>
inline GSErrCode	Read (IChannel& ic, Array<Type>& obj)
{
	return obj.Read (ic);
}


template <class Type>
inline GSErrCode	Write (OChannel& oc, const Array<Type>& obj)
{
	return obj.Write (oc);
}


template <class Type>
inline GSErrCode	Print (OChannel& oc, const Array<Type>& obj)
{
	obj.Print (oc);

	return NoError;
}

}	// namespace GS
// ________________________________ Class Array ________________________________



// =============================== Class ArrayFB ===============================

namespace GS {

template <class Type, USize BufferCapacity>
class ArrayFB: public Array<Type> {
private:
	char	fixBuffer[BufferCapacity * sizeof (Type)];	// fix buffer for the Array

protected:
	virtual USize	GetMinBufferCapacity (void) const override;
	virtual Type*	AllocateNewBuffer	 (USize bufferCapacity, const Type* oldBuffer) override;
	virtual void	DeleteBuffer		 (Type* buffer) override;
	virtual bool	IsIndependentBuffer  (const Type* buffer) const override;

public:
	ArrayFB ();
	explicit ArrayFB (ConstForwardIterator<Type> begin);
	explicit ArrayFB (const GS::ConstEnumerator<Type>& enumerator);
	ArrayFB (const GS::ConversionEnumerator<Type>& enumerator);
	ArrayFB (std::initializer_list<Type> items);
	ArrayFB (ByRefSelector, InitializerRefList<Type> items);
	ArrayFB (const ArrayFB& source);
	ArrayFB (ArrayFB&& source);
	ArrayFB (const Array<Type>& source);
	ArrayFB (Array<Type>&& source);
	ArrayFB&	operator= (const ArrayFB& source);
	ArrayFB&	operator= (ArrayFB&& source);
	ArrayFB&	operator= (const Array<Type>& source);
	ArrayFB&	operator= (Array<Type>&& source);
	ArrayFB&	operator= (const GS::ConstEnumerator<Type>& enumerator);
   ~ArrayFB ();
};



template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB ()
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (ConstForwardIterator<Type> begin)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::Insert (0, begin);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const GS::ConstEnumerator<Type>& enumerator)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::operator= (enumerator);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const GS::ConversionEnumerator<Type>& enumerator)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::operator= (enumerator);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (std::initializer_list<Type> items)
{
	Array<Type>::EnsureCapacity (USize (items.size ()));

	for (const Type& item : items)
		Array<Type>::Push (item);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (ByRefSelector, InitializerRefList<Type> items)
{
	Array<Type>::EnsureCapacity (USize (items.size ()));

	for (const auto& item : items)
		Array<Type>::Push (*item);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const ArrayFB& source)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::operator= (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (ArrayFB&& source)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::Move (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (const Array<Type>& source)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::operator= (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::ArrayFB (Array<Type>&& source)
//lint -esym(1401, GS::ArrayFB<*>::fixBuffer)
{
	Array<Type>::Move (source);
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (const ArrayFB& source)
{
	Array<Type>::operator= (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (ArrayFB&& source)
{
	Array<Type>::Move (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (const Array<Type>& source)
{
	Array<Type>::operator= (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (Array<Type>&& source)
{
	Array<Type>::Move (source);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>&	ArrayFB<Type, BufferCapacity>::operator= (const GS::ConstEnumerator<Type>& enumerator)
{
	Array<Type>::operator= (enumerator);

	return *this;
}


template <class Type, USize BufferCapacity>
ArrayFB<Type, BufferCapacity>::~ArrayFB ()
{
	this->Clear ();
}


template <class Type, USize BufferCapacity>
USize	ArrayFB<Type, BufferCapacity>::GetMinBufferCapacity (void) const
{
	return BufferCapacity;
}


template <class Type, USize BufferCapacity>
Type*	ArrayFB<Type, BufferCapacity>::AllocateNewBuffer (USize bufferCapacity, const Type* oldBuffer)
{
	if (IsIndependentBuffer (oldBuffer) && bufferCapacity <= BufferCapacity)
		return reinterpret_cast<Type*> (fixBuffer);
	else
		return Array<Type>::AllocateNewBuffer (bufferCapacity, oldBuffer);
}


template <class Type, USize BufferCapacity>
void	ArrayFB<Type, BufferCapacity>::DeleteBuffer (Type* buffer)
{
	if (IsIndependentBuffer (buffer))
		Array<Type>::DeleteBuffer (buffer);
}


template <class Type, USize BufferCapacity>
bool	ArrayFB<Type, BufferCapacity>::IsIndependentBuffer (const Type* buffer) const
{
	return (buffer != reinterpret_cast<const Type*> (fixBuffer));
}

}	// namespace GS
// _______________________________ Class ArrayFB _______________________________


#endif
