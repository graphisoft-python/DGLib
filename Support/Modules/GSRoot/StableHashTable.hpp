// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined STABLEHASHTABLE_HPP
#define STABLEHASHTABLE_HPP

#pragma once

// ----------------------------------------------------- Includes ------------------------------------------------------

#include "HashTable.hpp"
#include "SmallObj.hpp"


// =============================================== Class StableHashTable ===============================================

namespace GS
{

template <class IndexType, class ItemType>
class StableHashTable
{
private:
	FixedAllocator						allocator;
	GS::HashTable<IndexType, ItemType*>	index;

public:
		// Constructors

	StableHashTable ();
	~StableHashTable ();

		// Item access

	ItemType&		operator[] (const IndexType& key);
	const ItemType&	operator[] (const IndexType& key) const;

	ItemType*		GetPtr (const IndexType& idx);
	const ItemType*	GetPtr (const IndexType& idx) const;

		// Content management

	void Add (const IndexType& idx, const ItemType& item);

	void Put (const IndexType& idx, const ItemType& item);

	void Delete (const IndexType& key);

	void Clear ();

	USize GetSize (void) const;
	bool IsEmpty (void) const;

		// Content query

	bool ContainsKey (const IndexType& key) const;
};



template <class IndexType, class ItemType>
inline StableHashTable<IndexType, ItemType>::StableHashTable ():
	allocator (sizeof (ItemType))
{
}


template <class IndexType, class ItemType>
inline StableHashTable<IndexType, ItemType>::~StableHashTable ()
{
	Clear ();
}


template <class IndexType, class ItemType>
inline ItemType& StableHashTable<IndexType, ItemType>::operator[] (const IndexType& key)
{
	return *index[key];
}


template <class IndexType, class ItemType>
const ItemType& StableHashTable<IndexType, ItemType>::operator[] (const IndexType& key) const
{
	return *index[key];
}


template <class IndexType, class ItemType>
inline ItemType*	StableHashTable<IndexType, ItemType>::GetPtr (const IndexType& idx)
{
	ItemType** indexPtr = index.GetPtr (idx);
	return indexPtr != nullptr ? *indexPtr : nullptr;
}


template <class IndexType, class ItemType>
inline const ItemType*	StableHashTable<IndexType, ItemType>::GetPtr (const IndexType& idx) const
{
	const ItemType* const* indexPtr = index.GetPtr (idx);
	return indexPtr != nullptr ? *indexPtr : nullptr;
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Add (const IndexType& idx, const ItemType& item)
{
	index.Add (idx, new (allocator.Allocate ()) ItemType (item));
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Put (const IndexType& idx, const ItemType& item)
{
	ItemType* ptr = index.GetPtr (idx);
	if (ptr != nullptr) {
		*index[idx] = item;
	} else {
		Add (idx, item);
	}
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Delete (const IndexType& key)
{
	index[key]->~ItemType ();
	allocator.Deallocate (index[key]);
	index.Delete (key);
}


template <class IndexType, class ItemType>
inline void StableHashTable<IndexType, ItemType>::Clear ()
{
	for (auto it = index.EnumerateValues (); it != nullptr; ++it) {
		(*it)->~ItemType ();
		allocator.Deallocate (*it);
	}
	index.Clear ();
}


template <class IndexType, class ItemType>
inline USize StableHashTable<IndexType, ItemType>::GetSize (void) const
{
	return index.GetSize ();
}


template <class IndexType, class ItemType>
inline bool StableHashTable<IndexType, ItemType>::IsEmpty (void) const
{
	return index.IsEmpty ();
}


template <class IndexType, class ItemType>
inline bool StableHashTable<IndexType, ItemType>::ContainsKey (const IndexType& key) const
{
	return index.ContainsKey (key);
}

}

#endif
