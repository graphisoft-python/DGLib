
// *****************************************************************************
//
//                               Class PagedArray
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined PAGEDARRAY_HPP
#define PAGEDARRAY_HPP

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
#include "BM.hpp"

#include "InitializerRefList.hpp"

#include <new>
#include <utility>
#include <functional>


// ============================= Class PagedArray ==============================

namespace GS {

class GSROOT_DLL_EXPORT PagedArrayPrivate {
public:
	static GS::ClassInfo	classInfo;	// PagedArray's private classInfo
};


template <UInt32 value>
struct Check2;

template <>
struct Check2<0> {
	enum { Check = 0 };
};

template <UInt32 value>
struct Log2 {
	enum { Result = 1 + Log2<value / 2>::Result + Check2<value % 2>::Check };
};

template <>
struct Log2<1> {
	enum { Result = 0 };
};

template <>
struct Log2<8> {
	enum { Result = 3 };
};


template <class Type, UInt32 PageSize = 8>
class PagedArray: public RandomContainer<Type> {
private:
	enum { FixPageTableCapacity = 1 };

	Type**	pageTable = nullptr;					// table of pointers to pages of items
	Type*	fixPageTable[FixPageTableCapacity];		// built in page table for small sizes
	USize	capacity = 0;							// capacity of the PagedArray (in items)
	USize	deallocationCapacity = 0;				// lower capacity of the PagedArray below (or equal) which allocation units should be deleted
	USize	size = 0;								// number of items in the PagedArray

	enum {
		Log2PageSize = Log2<PageSize>::Result,	// log2 of the page size
		OffsetMask	 = PageSize - 1				// mask for the indices inside a page
	};

	inline Type&		Cell (UIndex idx);
	inline const Type&	Cell (UIndex idx) const;

	inline USize	GetPageNumber (void) const;

	USize			GetPageTableCapacity (void) const;
	static USize	GetNextPageTableCapacity (USize minCapacity);

	inline void		IncreaseCapacity (USize minCapacity);
	void			AddNewPages		 (USize minCapacity);

	inline void		DecreaseCapacity  (USize minCapacity);
	void			DeleteUnusedPages (USize minCapacity);

	inline ULong	GetCurrentAllocationUnit (void) const;
	inline ULong	GetNextAllocationUnit (ULong currentAllocationUnit) const;
	inline ULong	GetPrevAllocationUnit (ULong currentAllocationUnit) const;

	static char*	AllocateBuffer (USize bufferCapacity);
	static void		DeleteBuffer   (char* buffer);

	static ULong	ComputeLog2 (ULong n);

public:
		// Types

	typedef RandomContainerIterator<PagedArray>				Iterator;
	typedef ConstRandomContainerIterator<PagedArray>		ConstIterator;

	typedef GeneralRandomContainerIterator<PagedArray>		GeneralIterator;
	typedef ConstGeneralRandomContainerIterator<PagedArray>	ConstGeneralIterator;

	typedef RandomContainerReverseIterator<PagedArray>		ReverseIterator;
	typedef ConstRandomContainerReverseIterator<PagedArray>	ConstReverseIterator;

	typedef RandomContainerRange<PagedArray>				Range;
	typedef RandomContainerConstRange<PagedArray>			ConstRange;

	class ConstEnumerator;
	class ConversionEnumerator;

		// Constructors

	PagedArray ();
	explicit PagedArray (ConstIterator begin);
	explicit PagedArray (ConstForwardIterator<Type> begin);
	explicit PagedArray (const GS::ConstEnumerator<Type>& enumerator);
	PagedArray (const GS::ConversionEnumerator<Type>& enumerator);
	PagedArray (std::initializer_list<Type> items);
	PagedArray (ByRefSelector, InitializerRefList<Type> items);
	PagedArray (const PagedArray& source);
	PagedArray (PagedArray&& source);

	template <class SourceType, UInt32 SourcePageSize>
	explicit PagedArray (const PagedArray<SourceType, SourcePageSize>& source);

	PagedArray&	operator= (const PagedArray& source);
	PagedArray&	operator= (PagedArray&& source);
	PagedArray&	operator= (const GS::ConstEnumerator<Type>& enumerator);

	template <class SourceType, UInt32 SourcePageSize>
	PagedArray&	operator= (const PagedArray<SourceType, SourcePageSize>& source);

   ~PagedArray ();

	inline	void	Move (PagedArray& source);
	void			Move (const std::function<void (Type&&)>& processor);

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
	
	void	Append (const PagedArray& items);
	void	Append (PagedArray&& items);

	void	Delete		(UIndex idx);
	void	Delete		(UIndex from, USize range);
	void	DeleteLast	(void);

	UIndex	DeleteFirst	(const Type& item);
	UIndex	DeleteLast	(const Type& item);
	void	DeleteAll	(const Type& item);

	void	Clear (bool keepCapacity = false);

	void	Swap (PagedArray& rightOp);

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
	void			IncreaseSize (USize sizeIncrement);
	void			EnsureSize	 (USize requiredSize);

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

	Range         operator() (UIndex from, USize to);
	ConstRange    operator() (UIndex from, USize to) const;

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

	USize	Count	 (const Type& item, UIndex from = 0, USize range = MaxUSize) const;
	USize	Count	 (const std::function<bool (const Type&)>& condition, UIndex from = 0, USize range = MaxUSize) const;

	bool	operator== (const PagedArray& rightOp) const;
	bool	operator!= (const PagedArray& rightOp) const;

		// I/O

	GSErrCode	Read  (IChannel& ic);
	GSErrCode	Read  (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader);
	GSErrCode	Write (OChannel& oc) const;
	GSErrCode	Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const;

		// Debug

	void	Print	   (OChannel& oc) const;
	void	Dump	   (OChannel& oc) const;
	bool	CheckState (void) const;

		// Types

	class ConstEnumerator: public GS::ConstEnumerator<Type> {
	private:
		const PagedArray* source;

	public:
		inline ConstEnumerator (const PagedArray& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;
	};

	class ConversionEnumerator: public GS::ConversionEnumerator<Type> {
	private:
		const PagedArray* source;

	public:
		inline ConversionEnumerator (const PagedArray& source);

		virtual void	Enumerate (const std::function<void (const Type&)>& processor) const override;
	};
};

// === class DefaultPagedArray =========================================================================================

template <class Type>
class DefaultPagedArray: public GS::PagedArray<Type> {};


// === PagedArray methods ==============================================================================================

template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray ()
	//lint -esym(1401, GS::PagedArray<*>::fixPageTable)
{
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (ConstIterator begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (ConstForwardIterator<Type> begin)
{
	while (begin != nullptr) {
		Push (*begin);
		++begin;
	}
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (const GS::ConstEnumerator<Type>& enumerator)
{
	enumerator.Enumerate (GetInserter (*this));
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (const GS::ConversionEnumerator<Type>& enumerator)
{
	enumerator.Enumerate (GetInserter (*this));
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (const PagedArray& source)
{
	IncreaseCapacity (source.size);

	for (UIndex i = 0; i < source.size; i++)
		new (&Cell (i)) Type (source[i]);

	size = source.size;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (std::initializer_list<Type> items)
{
	IncreaseCapacity (USize (items.size ()));

	UIndex i = 0;
	for (const auto& item : items)
		new (&Cell (i++)) Type (item);

	size = USize (items.size ());
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (ByRefSelector, InitializerRefList<Type> items)
{
	IncreaseCapacity (USize (items.size ()));

	UIndex i = 0;
	for (const auto& item : items)
		new (&Cell (i++)) Type (*item);

	size = USize (items.size ());
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::PagedArray (PagedArray&& source)
{
	Move (source);
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (const PagedArray& source)
{
	PagedArray copy = source;
	Swap (copy);

	return *this;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (PagedArray&& source)
{
	Move (source);

	return *this;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (const GS::ConstEnumerator<Type>& enumerator)
{
	Clear ();

	enumerator.Enumerate (GetInserter (*this));

	return *this;
}


template <class Type, UInt32 PageSize>
PagedArray<Type, PageSize>::~PagedArray ()
{
	Clear ();
}


template <class Type, UInt32 PageSize>
template <class SourceType, UInt32 SourcePageSize>
PagedArray<Type, PageSize>::PagedArray (const PagedArray<SourceType, SourcePageSize>& items) :
	pageTable (nullptr),
	capacity (0),
	deallocationCapacity (0),
	size (0)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	IncreaseCapacity (items.GetSize ());

	for (const SourceType& item : items)
		Push (item);

	size = items.GetSize ();
}


template <class Type, UInt32 PageSize>
template <class SourceType, UInt32 SourcePageSize>
PagedArray<Type, PageSize>&		PagedArray<Type, PageSize>::operator= (const PagedArray<SourceType, SourcePageSize>& items)
{
	static_assert (IsConvertible<SourceType, Type>, "'SourceType' is not convertible to 'Type'.");

	PagedArray<Type, PageSize> copy (items);
	Swap (copy);

	return *this;
}


template <class Type, UInt32 PageSize>
inline	void	PagedArray<Type, PageSize>::Move (PagedArray& source)
{
	if (DBERROR (&source == this))
		return;

	Swap (source);
	source.Clear ();
}


template <class Type, UInt32 PageSize>
void			PagedArray<Type, PageSize>::Move (const std::function<void (Type&&)>& processor)
{
	for (UIndex i = 0; i < size; ++i)
		processor (std::move (Cell (i)));

	Clear ();
}


template <class Type, UInt32 PageSize>
inline Type&	PagedArray<Type, PageSize>::operator[] (UIndex idx)
{
	REF_CHECK (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
inline const Type&	PagedArray<Type, PageSize>::operator[] (UIndex idx) const
{
	REF_CHECK (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
inline Type&	PagedArray<Type, PageSize>::Get (UIndex idx)
{
	REF_CHECK_R (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
inline const Type&	PagedArray<Type, PageSize>::Get (UIndex idx) const
{
	REF_CHECK_R (idx < size);

	return Cell (idx);
}


template <class Type, UInt32 PageSize>
inline Type&	PagedArray<Type, PageSize>::GetFirst (void)
{
	PRECOND (size != 0);

	return pageTable[0][0];
}


template <class Type, UInt32 PageSize>
inline const Type&	PagedArray<Type, PageSize>::GetFirst (void) const
{
	PRECOND (size != 0);

	return pageTable[0][0];
}


template <class Type, UInt32 PageSize>
inline Type&	PagedArray<Type, PageSize>::GetLast (void)
{
	PRECOND (size != 0);

	return Cell (size - 1);
}


template <class Type, UInt32 PageSize>
inline const Type&	PagedArray<Type, PageSize>::GetLast (void) const
{
	PRECOND (size != 0);

	return Cell (size - 1);
}


template <class Type, UInt32 PageSize>
inline UIndex	PagedArray<Type, PageSize>::GetLastIndex (void) const
{
	PRECOND (size != 0);

	return size - 1;
}


template <class Type, UInt32 PageSize>
inline void		PagedArray<Type, PageSize>::Set (UIndex idx, const Type& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	Cell (idx) = item;
}


template <class Type, UInt32 PageSize>
inline void		PagedArray<Type, PageSize>::Set (UIndex idx, Type&& item)
{
	REF_CHECK (idx < size);
	NULL_REF_CHECK (item);

	Cell (idx) = std::move (item);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Fill (const Type& item, UIndex from, USize range)
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	GS::Fill (Begin () + from, Begin () + from + range, item);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::Replace (const Type& oldItem, const Type& newItem, UIndex from, USize range)
{
	NULL_REF_CHECK (oldItem);
	NULL_REF_CHECK (newItem);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Replace (Begin () + from, Begin () + from + range, oldItem, newItem);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, const Type& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	new (&Cell (size)) Type ();
	for (UIndex i = size; i > to; i--)
		Cell (i) = std::move (Cell (i - 1));
	Cell (to) = item;

	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, Type&& item)
{
	REF_CHECK (to <= size);
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	new (&Cell (size)) Type ();
	for (UIndex i = size; i > to; i--)
		Cell (i) = std::move (Cell (i - 1));
	Cell (to) = std::move (item);

	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstIterator begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstIterator begin, ConstIterator end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstForwardIterator<Type> begin)
{
	REF_CHECK (to <= size);

	while (begin != nullptr) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Insert (UIndex to, ConstForwardIterator<Type> begin, ConstForwardIterator<Type> end)
{
	REF_CHECK (to <= size);

	while (begin != end) {
		Insert (to, *begin);
		to++;
		++begin;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Append (const PagedArray& items)
{
	NULL_REF_CHECK (items);

	if (&items == this) {
		PagedArray temp = items;
		Append (std::move (temp));
		return;
	}

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		new (&Cell (size + i)) Type (items[i]);

	size += items.GetSize ();
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Append (PagedArray&& items)
{
	NULL_REF_CHECK (items);

	IncreaseCapacity (size + items.GetSize ());

	for (UIndex i = 0; i < items.GetSize (); i++)
		new (&Cell (size + i)) Type (std::move (items[i]));

	size += items.GetSize ();
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Delete (UIndex idx)
{
	REF_CHECK (idx < size);

	for (UIndex i = idx + 1; i < size; i++)
		Cell (i - 1) = std::move (Cell (i));

	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Delete (UIndex from, USize range)
{
	REF_CHECK (from + range <= size);

	if (range == 0)
		return;

	for (UIndex i = from + range; i < size; i++)
		Cell (i - range) = std::move (Cell (i));

	for (UIndex j = size - range; j < size; j++)
		Cell (j).~Type ();
	size -= range;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteLast (void)
{
	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::DeleteFirst (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex first = FindFirst (item);
	if (first != MaxUIndex)
		Delete (first);

	return first;
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::DeleteLast (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex last = FindLast (item);
	if (last != MaxUIndex)
		Delete (last);

	return last;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteAll (const Type& item)
{
	NULL_REF_CHECK (item);

	UIndex last = 0;
	while (last != MaxUIndex)
		last = DeleteLast (item);	// deleting from the end is faster
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Clear (bool keepCapacity)
{
	for (UIndex i = 0; i < size; i++)
		Cell (i).~Type ();

	if (!keepCapacity) {
		USize growth = GetCurrentAllocationUnit ();
		UIndex j = GetPageNumber ();
		while (j > 0) {
			j -= growth;	// start index of the allocation unit
			DeleteBuffer (reinterpret_cast<char*> (pageTable[j]));	//lint !e796: Conceivable access of out-of-bounds pointer (1 beyond end of data) by operator '['
			growth = GetPrevAllocationUnit (growth);
		}

		if (pageTable != fixPageTable)
			DeleteBuffer (reinterpret_cast<char*> (pageTable));

		pageTable = nullptr;
		capacity = 0;
		deallocationCapacity = 0;
	}

	size = 0;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Swap (PagedArray& rightOp)
{
	NULL_REF_CHECK (rightOp);

	if (this == &rightOp)
		return;

	GS::Swap (pageTable, rightOp.pageTable);
	if (pageTable == rightOp.fixPageTable)
		pageTable = fixPageTable;
	if (rightOp.pageTable == fixPageTable)
		rightOp.pageTable = rightOp.fixPageTable;

	for (UIndex i = 0; i < FixPageTableCapacity; i++)
		GS::Swap (fixPageTable[i], rightOp.fixPageTable[i]);

	GS::Swap (capacity,				rightOp.capacity);
	GS::Swap (deallocationCapacity,	rightOp.deallocationCapacity);
	GS::Swap (size,					rightOp.size);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Push (const Type& item)
{
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	new (&Cell (size)) Type (item);
	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Push (Type&& item)
{
	NULL_REF_CHECK (item);

	IncreaseCapacity (size + 1);

	new (&Cell (size)) Type (std::move (item));
	size++;
}


template <class Type, UInt32 PageSize>
template <class... ItemParameters>
void	PagedArray<Type, PageSize>::PushNew (ItemParameters&&... itemParameters)
{
	IncreaseCapacity (size + 1);

	new (&Cell (size)) Type (std::forward<ItemParameters> (itemParameters)...);
	size++;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Pop (Type* item)
{
	PRECOND (size != 0);
	NULL_PTR_CHECK (item);

	*item = std::move (Cell (size - 1));

	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);
}


template <class Type, UInt32 PageSize>
Type	PagedArray<Type, PageSize>::Pop (void)
{
	PRECOND (size != 0);

	Type result = std::move (Cell (size - 1));

	Cell (size - 1).~Type ();
	size--;

	DecreaseCapacity (size);

	return result;
}


template <class Type, UInt32 PageSize>
inline USize	PagedArray<Type, PageSize>::GetSize (void) const
{
	return size;
}


template <class Type, UInt32 PageSize>
inline bool		PagedArray<Type, PageSize>::IsEmpty (void) const
{
	return (size == 0);
}


template <class Type, UInt32 PageSize>
inline bool		PagedArray<Type, PageSize>::IsLast (UIndex idx) const
{
	return (size > 0 && idx == size - 1);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::SetSize (USize newSize)
{
	if (newSize < size) {
		for (UIndex i = newSize; i < size; i++)
			Cell (i).~Type ();
		size = newSize;
		DecreaseCapacity (size);
	} else if (newSize > size) {
		IncreaseCapacity (newSize);
		for (UIndex i = size; i < newSize; i++)
			new (&Cell (i)) Type ();
		size = newSize;
	}
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::IncreaseSize (USize sizeIncrement)
{
	SetSize (size + sizeIncrement);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::EnsureSize (USize requiredSize)
{
	if (size < requiredSize)
		SetSize (requiredSize);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::Iterator	PagedArray<Type, PageSize>::Enumerate (void)
{
	return Iterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstIterator	PagedArray<Type, PageSize>::Enumerate (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
template <class Function>
inline void	PagedArray<Type, PageSize>::Enumerate (Function&& processor)
{
	for (UIndex i = 0; i < size; i++)
		processor (Cell (i));
}


template <class Type, UInt32 PageSize>
template <class Function>
inline void	PagedArray<Type, PageSize>::Enumerate (Function&& processor) const
{
	for (UIndex i = 0; i < size; i++)
		processor (Cell (i));
}


template <class Type, UInt32 PageSize>
template <class Function>
inline void	PagedArray<Type, PageSize>::EnumerateConst (Function&& processor) const
{
	Enumerate (processor);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::Iterator	PagedArray<Type, PageSize>::Begin (void)
{
	return Iterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstIterator	PagedArray<Type, PageSize>::Begin (void) const
{
	return ConstIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::Iterator	PagedArray<Type, PageSize>::End (void)
{
	return Iterator (*this, size);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstIterator	PagedArray<Type, PageSize>::End (void) const
{
	return ConstIterator (*this, size);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::GeneralIterator		PagedArray<Type, PageSize>::EnumerateGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstGeneralIterator	PagedArray<Type, PageSize>::EnumerateGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::GeneralIterator		PagedArray<Type, PageSize>::BeginGeneral (void)
{
	return GeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstGeneralIterator	PagedArray<Type, PageSize>::BeginGeneral (void) const
{
	return ConstGeneralIterator (*this, 0);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::GeneralIterator		PagedArray<Type, PageSize>::EndGeneral (void)
{
	return GeneralIterator (*this, size);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstGeneralIterator	PagedArray<Type, PageSize>::EndGeneral (void) const
{
	return ConstGeneralIterator (*this, size);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ReverseIterator	PagedArray<Type, PageSize>::ReverseEnumerate (void)
{
	return ReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstReverseIterator	PagedArray<Type, PageSize>::ReverseEnumerate (void) const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
template <class Function>
inline void	PagedArray<Type, PageSize>::ReverseEnumerate (Function&& processor)
{
	for (UIndex i = size; i > 0; i--)
		processor (Cell (i - 1));
}


template <class Type, UInt32 PageSize>
template <class Function>
inline void	PagedArray<Type, PageSize>::ReverseEnumerate (Function&& processor) const
{
	for (UIndex i = size; i > 0; i--)
		processor (Cell (i - 1));
}


template <class Type, UInt32 PageSize>
template <class Function>
inline void	PagedArray<Type, PageSize>::ReverseEnumerateConst (Function&& processor) const
{
	ReverseEnumerate (processor);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ReverseIterator	PagedArray<Type, PageSize>::ReverseBegin (void)
{
	return ReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstReverseIterator	PagedArray<Type, PageSize>::ReverseBegin (void) const
{
	return ConstReverseIterator (*this, size - 1);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ReverseIterator	PagedArray<Type, PageSize>::ReverseEnd (void)
{
	return ReverseIterator (*this, -1);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConstReverseIterator	PagedArray<Type, PageSize>::ReverseEnd (void) const
{
	return ConstReverseIterator (*this, -1);
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::Range         PagedArray<Type, PageSize>::operator() (UIndex from, USize to)
{
	return { *this, from, to };
}


template <class Type, UInt32 PageSize>
typename PagedArray<Type, PageSize>::ConstRange    PagedArray<Type, PageSize>::operator() (UIndex from, USize to) const
{
	return { *this, from, to };
}


template <class Type, UInt32 PageSize>
inline PagedArray<Type, PageSize>::operator typename PagedArray<Type, PageSize>::ConstEnumerator () const
{
	return ConstEnumerator (*this);
}


template <class Type, UInt32 PageSize>
inline typename PagedArray<Type, PageSize>::ConversionEnumerator	PagedArray<Type, PageSize>::Convert (void) const
{
	return ConversionEnumerator (*this);
}


template <class Type, UInt32 PageSize>
inline auto&	PagedArray<Type, PageSize>::AsConst (void) const
{
	return reinterpret_cast<const PagedArray<typename Container<Type>::template MakeConstPtr<Type>::ConstType, PageSize>&> (*this);
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindFirst (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	ConstIterator it = GS::Find (Begin () + from, Begin () + from + range, item);

	if (it.GetIndex () == from + range)
		return MaxUIndex;

	return it.GetIndex ();
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindFirst (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	ConstIterator it = GS::Find (Begin () + from, Begin () + from + range, condition);

	if (it.GetIndex () == from + range)
		return MaxUIndex;

	return it.GetIndex ();
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindLast (const Type& item) const
{
	NULL_REF_CHECK (item);

	for (UIndex i = size; i > 0; i--) {
		if (Cell (i - 1) == item)
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, UInt32 PageSize>
UIndex	PagedArray<Type, PageSize>::FindLast (const std::function<bool (const Type&)>& condition) const
{
	for (UIndex i = size; i > 0; i--) {
		if (condition (Cell (i - 1)))
			return i - 1;
	}

	return MaxUIndex;
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::Contains (const Type& item) const
{
	NULL_REF_CHECK (item);

	return (GS::Find (Begin (), End (), item) != nullptr);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::Contains (const std::function<bool (const Type&)>& condition) const
{
	return (GS::Find (Begin (), End (), condition) != nullptr);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::Contains (std::initializer_list<Type> items) const
{
	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::ContainsOnly (std::initializer_list<Type> items) const
{
	if (size != items.size ())
		return false;

	for (const auto& item : items) {
		if (!Contains (item))
			return false;
	}

	return true;
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::Count (const Type& item, UIndex from, USize range) const
{
	NULL_REF_CHECK (item);
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (Begin () + from, Begin () + from + range, item);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::Count (const std::function<bool (const Type&)>& condition, UIndex from, USize range) const
{
	REF_CHECK ((range == MaxUSize && from <= size) || (range != MaxUSize && from + range <= size));

	if (range == MaxUSize)
		range = size - from;

	return GS::Count (Begin () + from, Begin () + from + range, condition);
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::operator== (const PagedArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	if (size != rightOp.size)
		return false;

	return (GS::IsEqual (Begin (), End (), rightOp.Begin ()));
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::operator!= (const PagedArray& rightOp) const
{
	NULL_REF_CHECK (rightOp);

	return !operator== (rightOp);
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Read (IChannel& ic)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, PagedArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = GS::ReadType (ic, Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Write (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, PagedArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = GS::WriteType (oc, Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Read (IChannel& ic, const std::function<GSErrCode (IChannel&, Type&)>& reader)
{
	NULL_REF_CHECK (ic);

	Clear ();

	GS::InputFrame frame (ic, PagedArrayPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = reader (ic, Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
GSErrCode	PagedArray<Type, PageSize>::Write (OChannel& oc, const std::function<GSErrCode (OChannel&, const Type&)>& writer) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, PagedArrayPrivate::classInfo);

	GSErrCode errorCode = oc.Write (size);

	for (UIndex i = 0; i < size && errorCode == NoError; i++)
		errorCode = writer (oc, Cell (i));

	return errorCode;
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Print (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "PagedArray" << '\n';
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::Dump (OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	oc << "pageTable:            " << pageTable << '\n';
	oc << "capacity:             " << capacity << '\n';
	oc << "deallocationCapacity: " << deallocationCapacity << '\n';
	oc << "size:                 " << size << '\n';
}


template <class Type, UInt32 PageSize>
bool	PagedArray<Type, PageSize>::CheckState (void) const
{
	if ((pageTable == nullptr && (capacity != 0 || deallocationCapacity != 0 || size != 0)) ||
		(pageTable != nullptr && (capacity == 0 || size == 0)) ||
		capacity < size || size < deallocationCapacity)
		return false;

	USize currentAllocationUnit = GetCurrentAllocationUnit ();
	USize prevAllocationUnit = GetPrevAllocationUnit (currentAllocationUnit);
	USize reserve = (currentAllocationUnit + prevAllocationUnit) * PageSize;
	if ((reserve <= capacity && capacity - deallocationCapacity != reserve) ||
		(reserve > capacity && deallocationCapacity != 0))
		return false;

	USize pageNumber = GetPageNumber ();
	for (UIndex i = 0; i < pageNumber; i++) {
		if (pageTable[i] == nullptr)
			return false;
	}

	USize pageTableCapacity = GetPageTableCapacity ();
	for (UIndex j = pageNumber; j < pageTableCapacity; j++) {
		if (pageTable[j] != nullptr)
			return false;
	}

	return true;
}


template <class Type, UInt32 PageSize>
inline Type&	PagedArray<Type, PageSize>::Cell (UIndex idx)
{
	return *(pageTable[idx >> Log2PageSize] + (idx & OffsetMask));
}


template <class Type, UInt32 PageSize>
inline const Type&	PagedArray<Type, PageSize>::Cell (UIndex idx) const
{
	return *(pageTable[idx >> Log2PageSize] + (idx & OffsetMask));
}


template <class Type, UInt32 PageSize>
inline USize	PagedArray<Type, PageSize>::GetPageNumber (void) const
{
	return (capacity / PageSize);
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::GetPageTableCapacity (void) const
{
	if (capacity == 0)
		return 0;
	else
		return (1u << ComputeLog2 (GetPageNumber ()));
}


template <class Type, UInt32 PageSize>
USize	PagedArray<Type, PageSize>::GetNextPageTableCapacity (USize minCapacity)
{
	if (minCapacity == 0)
		return 0;
	else
		return (1u << ComputeLog2 (minCapacity));
}


template <class Type, UInt32 PageSize>
inline void		PagedArray<Type, PageSize>::IncreaseCapacity (USize minCapacity)
{
	if (minCapacity > capacity)
		AddNewPages (minCapacity);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::AddNewPages (USize minCapacity)
{
	if (minCapacity <= capacity)
		return;		// there is no need to add new pages

	USize pageNumber = GetPageNumber ();

	USize minPageNumber = (minCapacity + PageSize - 1) >> Log2PageSize;
	USize growth = GetCurrentAllocationUnit ();
	USize newPageNumber = pageNumber;
	while (newPageNumber < minPageNumber) {
		growth = GetNextAllocationUnit (growth);
		newPageNumber += growth;
	}
	USize lastAU     = growth;
	USize prevLastAU = GetPrevAllocationUnit (lastAU);

	USize newCapacity = newPageNumber * PageSize;

	USize pageTableCapacity = GetPageTableCapacity ();

	if (newPageNumber > pageTableCapacity) {
		USize newPageTableCapacity = GetNextPageTableCapacity (newPageNumber);

		Type** newPageTable;
		if (newPageTableCapacity <= FixPageTableCapacity && pageTable != fixPageTable)
			newPageTable = fixPageTable;
		else
			newPageTable = reinterpret_cast<Type**> (AllocateBuffer (newPageTableCapacity * sizeof (Type*)));

		if (pageNumber > 0)
			::BNCopyMemory (newPageTable, pageTable, static_cast<GSSize>(pageNumber * sizeof (Type*)));
		if (pageTable != fixPageTable)
			DeleteBuffer (reinterpret_cast<char*> (pageTable));
		pageTable = newPageTable;

		for (UIndex k = newPageNumber; k < newPageTableCapacity; k++)
			pageTable[k] = nullptr;
	}

	growth = GetCurrentAllocationUnit ();
	UIndex i = pageNumber;
	while (i < newPageNumber) {
		growth = GetNextAllocationUnit (growth);
		Type* buffer = reinterpret_cast<Type*> (AllocateBuffer (growth * PageSize * sizeof (Type)));
		for (UIndex j = 0; j < growth; j++)
			pageTable[i + j] = buffer + j * PageSize;
		i += growth;
	}

	capacity = newCapacity;

	USize reserve = (lastAU + prevLastAU) * PageSize;
	if (capacity >= reserve)
		deallocationCapacity = capacity - reserve;
	else
		deallocationCapacity = 0;
}


template <class Type, UInt32 PageSize>
inline void		PagedArray<Type, PageSize>::DecreaseCapacity (USize minCapacity)
{
	if (minCapacity <= deallocationCapacity)
		DeleteUnusedPages (minCapacity);
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteUnusedPages (USize minCapacity)
{
	if (minCapacity > deallocationCapacity)
		return;		// it is not possible or worth to delete unused allocation units

	USize pageNumber = GetPageNumber ();

	USize minPageNumber = (minCapacity + PageSize - 1) >> Log2PageSize;
	USize growth = GetCurrentAllocationUnit ();
	USize newPageNumber = pageNumber;
	while (newPageNumber - growth >= minPageNumber && newPageNumber != 0) {
		newPageNumber -= growth;
		DeleteBuffer (reinterpret_cast<char*> (pageTable[newPageNumber]));
		for (UIndex i = 0; i < growth; i++)
			pageTable[newPageNumber + i] = nullptr;
		growth = GetPrevAllocationUnit (growth);
	}
	USize lastAU     = growth;
	USize prevLastAU = GetPrevAllocationUnit (lastAU);

	USize newCapacity = newPageNumber * PageSize;

	USize pageTableCapacity = GetPageTableCapacity ();

	USize newPageTableCapacity = GetNextPageTableCapacity (newPageNumber);

	if (newPageTableCapacity < pageTableCapacity) {
		Type** newPageTable = nullptr;
		if (newPageTableCapacity != 0) {
			if (newPageTableCapacity <= FixPageTableCapacity && pageTable != fixPageTable)
				newPageTable = fixPageTable;
			else
				newPageTable = reinterpret_cast<Type**> (AllocateBuffer (newPageTableCapacity * sizeof (Type*)));

			::BNCopyMemory (newPageTable, pageTable, newPageNumber * sizeof (Type*));
			for (UIndex j = newPageNumber; j < newPageTableCapacity; j++)
				newPageTable[j] = nullptr;
		}
		if (pageTable != fixPageTable)
			DeleteBuffer (reinterpret_cast<char*> (pageTable));
		pageTable = newPageTable;
	}

	capacity = newCapacity;

	USize reserve = (lastAU + prevLastAU) * PageSize;
	if (capacity >= reserve)
		deallocationCapacity = capacity - reserve;
	else
		deallocationCapacity = 0;
}


template <class Type, UInt32 PageSize>
inline ULong	PagedArray<Type, PageSize>::GetCurrentAllocationUnit (void) const
{
	return ((((capacity - deallocationCapacity) >> Log2PageSize) + 1) >> 1);
}


template <class Type, UInt32 PageSize>
inline ULong	PagedArray<Type, PageSize>::GetNextAllocationUnit (ULong currentAllocationUnit) const
{
	return currentAllocationUnit + 1;
}


template <class Type, UInt32 PageSize>
inline ULong	PagedArray<Type, PageSize>::GetPrevAllocationUnit (ULong currentAllocationUnit) const
{
	return (currentAllocationUnit == 0 ? 0 : currentAllocationUnit - 1);
}


template <class Type, UInt32 PageSize>
char*	PagedArray<Type, PageSize>::AllocateBuffer (USize bufferCapacity)
{
	return new char[bufferCapacity];	// buffer_overrun_reviewed_0
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::DeleteBuffer (char* buffer)
{
	delete [] buffer;
}


template <class Type, UInt32 PageSize>
ULong	PagedArray<Type, PageSize>::ComputeLog2 (ULong n)
{
	PRECOND (n > 0);

	n += n - 1;	// to reach the next power of 2 (if it isn't power of 2)

	ULong log2 = 0;
	while (n > 1) {
		n = n >> 1;
		log2++;
	}

	return log2;
}


template <class Type, UInt32 PageSize>
inline PagedArray<Type, PageSize>::ConstEnumerator::ConstEnumerator (const PagedArray& source):
	source (&source)
{
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::ConstEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


template <class Type, UInt32 PageSize>
inline PagedArray<Type, PageSize>::ConversionEnumerator::ConversionEnumerator (const PagedArray& source):
	source (&source)
{
}


template <class Type, UInt32 PageSize>
void	PagedArray<Type, PageSize>::ConversionEnumerator::Enumerate (const std::function<void (const Type&)>& processor) const
{
	source->Enumerate (processor);
}


// === PagedArrayInserter===============================================================================================

template <class Type>
class PagedArrayInserter {
	PagedArray<Type>* array;

public:
	explicit PagedArrayInserter (PagedArray<Type>* array) :
		array (array)
	{
	}

	void operator() (const Type& item) const { array->Push (item); }
	void operator() (Type&& item)	   const { array->Push (std::move (item)); }

	typedef Type DecayedFirstArgumentType;
};


// === Global functions ================================================================================================

template <class Type, UInt32 PageSize>
inline auto		begin (PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.Begin ();
}


template <class Type, UInt32 PageSize>
inline auto		end (PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.End ();
}


template <class Type, UInt32 PageSize>
inline auto		begin (const PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.Begin ();
}


template <class Type, UInt32 PageSize>
inline auto		end (const PagedArray<Type, PageSize>& pagedArray)
{
	return pagedArray.End ();
}


template <class Type>
inline PagedArrayInserter<Type>	GetInserter (PagedArray<Type>& destination)
{
	return PagedArrayInserter<Type> (&destination);
}


template <class Type, UInt32 PageSize>
inline GSErrCode	Read (IChannel& ic, PagedArray<Type, PageSize>& obj)
{
	return obj.Read (ic);
}


template <class Type, UInt32 PageSize>
inline GSErrCode	Write (OChannel& oc, const PagedArray<Type, PageSize>& obj)
{
	return obj.Write (oc);
}


template <class Type, UInt32 PageSize>
inline GSErrCode	Print (OChannel& oc, const PagedArray<Type, PageSize>& obj)
{
	obj.Print (oc);

	return NoError;
}

}	// namespace GS
// _____________________________ Class PagedArray ______________________________


#endif
