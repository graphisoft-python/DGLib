// *********************************************************************************************************************
// Description:		BTree.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#pragma once

#ifndef BTREE_HPP
#define BTREE_HPP

#include "MemAlloc.hpp"


namespace QXTools {

struct BTreeNullPosType
{
	BTreeNullPosType () {}
};

static const BTreeNullPosType BTreeNullPos;

template<typename Type>
struct BTreePos
{
	void* pos;

	BTreePos () : pos (nullptr) {}
	BTreePos (const BTreeNullPosType&) { pos = nullptr; }
	BTreePos operator= (const BTreeNullPosType&) { pos = nullptr; return *this; }

	bool operator== (const BTreePos& tp) const { return pos == tp.pos; }
	bool operator!= (const BTreePos& tp) const { return pos != tp.pos; }

	bool operator== (const BTreeNullPosType&) const { return pos == nullptr; }
	bool operator!= (const BTreeNullPosType&) const { return pos != nullptr; }

	operator bool () const { return pos != nullptr; }
};


template <typename AllocType>
class BTreeBase
{
protected:
	struct Leaf;
	struct BNode
	{
		// ulChildren: number of child nodes of a node
		ULong ulChildren;

		// pNext, pPrev: next and previous nodes on the same level in the doubly-linked list
		// pFirst, pLast: first and last child nodes of the node
		// pAbove: the parent node
		BNode *pNext, *pPrev, *pFirst, *pLast, *pAbove;

		// pEdge: the left-most descendant (leaf) of the current node
		Leaf *pEdge;
	};

	struct Leaf : BNode
	{
	};

	BTreeBase (ULong bMin, AllocType& memAlloc);
	BTreeBase (BTreeBase&&);

	void InitBTree ();

	Leaf* RemoveAllBNodes ();
	void InsertBefore (Leaf* pLf, Leaf* pos);
	void RemovePos (Leaf* pos);
	static void ChangeEdge (BNode* p, Leaf* pEdge);

	BNode* NewBNode ();
	void DeleteBNode (BNode* p);

	const ULong bMin, bMax; // parameters of the B-tree (bMax=2*bMin-1): min and max number of child nodes of a node (except the root)

	BNode root; // the root node
	Leaf *pFirst, *pLast; // pointers to the doubly-linked list of leaves (nodes of the bottom level)
	ULong elementsNum;

	AllocType& memAlloc;

private:
	BTreeBase (const BTreeBase&);				// forbidden
	BTreeBase& operator= (const BTreeBase&);	// forbidden
};


class MemAlloc8KWrapper {
private:
	MemAlloc8K& memAlloc;
public:
	explicit MemAlloc8KWrapper (MemAlloc8K& memAlloc) : memAlloc (memAlloc) {}
	void*	Alloc (UInt32 size) throw ()					{ return memAlloc.Allocate (size);		}
	void	Free (void* ptr, UInt32 reqSize) throw ()		{ memAlloc.Free ((char*)ptr, reqSize);	}
};


template<typename Type, typename SortType, typename AllocType = MemAlloc8KWrapper>
class BTree : BTreeBase <AllocType>
{
public:
	typedef	typename BTreeBase <AllocType>::Leaf	LeafType;
	typedef	typename BTreeBase <AllocType>::BNode	NodeType;

	struct BTreeElem : LeafType
	{
		Type elem;

		BTreeElem ();
		BTreeElem (const Type&);
	};

	typedef BTreePos<Type>	Pos;

	typedef short CompareElementsFnc (const Type&, const Type&);
	typedef short CompareWithSortkeyFnc (const Type&, const SortType&);

	BTree (CompareElementsFnc cmpElements, CompareWithSortkeyFnc cmpSortkey, ULong bMin, AllocType& memAlloc);
	BTree (const BTree& source);
	BTree (BTree&& source);
	~BTree ();

	const BTree& operator= (const BTree& source);
	const BTree& operator= (BTree&& source);

	void SetCompareFunctions (CompareElementsFnc cmpElements, CompareWithSortkeyFnc cmpSortkey);
	void GetCompareFunctions (CompareElementsFnc** cmpElements, CompareWithSortkeyFnc** cmpSortkey) const;

	BTreePos<Type> Insert (const Type& data);
	BTreePos<Type> InsertBefore (BTreePos<Type> pos, const Type& data);
	BTreePos<Type> InsertBefore(BTreePos<Type> pos);
	BTreePos<Type> InsertAfter (BTreePos<Type> pos, const Type& data);
	BTreePos<Type> InsertAfter (BTreePos<Type> pos);

	void Reinsert (BTreePos<Type> posItem);
	void ReinsertBefore (BTreePos<Type> pos, BTreePos<Type> posItem);
	void ReinsertAfter (BTreePos<Type> pos, BTreePos<Type> posItem);

	BTreePos<Type> Add (const Type& data);

	void RemovePos (BTreePos<Type> pos);
	void RemoveAll ();

	void SortArray ();

	bool Contains (const Type& data) const;
	BTreePos<Type> Find (const Type& data) const;

	BTreePos<Type> FindPrevPos (const Type& data) const;
	BTreePos<Type> FindNextPos (const Type& data) const;
	BTreePos<Type> FindPrevPosBySortkey (const SortType& ord) const;
	BTreePos<Type> FindNextPosBySortkey (const SortType& ord) const;

	Type& operator[] (BTreePos<Type> pos);
	const Type& operator[] (BTreePos<Type> pos) const;

	Type& Get (BTreePos<Type> pos);
	const Type& Get (BTreePos<Type> pos) const;

	BTreePos<Type> NextPos (BTreePos<Type> pos) const;
	BTreePos<Type> PrevPos (BTreePos<Type> pos) const;

	ULong GetSize () const;
	bool IsEmpty () const;

	static constexpr MemSize GetMaxAllocSize ()
	{
		return GS::Max (sizeof (BTreeElem), sizeof (typename BTreeBase <AllocType>::BNode));
	}

	static const Type* GetConstElemFromPos (BTreePos<Type> pos);

private:
	static Type* GD (LeafType* pLf);
	static Type* GD (BTreePos<Type> pos);

	static BTreePos<Type> LeafToBTreePos (const LeafType* leaf);

	BTreeElem* NewElem ();
	BTreeElem* NewElem (const Type& data);
	void DeleteElem (BTreeElem* pLf);

	CompareElementsFnc* compareElements;
	CompareWithSortkeyFnc* compareWithSortkey;
};


#include "BTreeImp.hpp"

}

#endif
