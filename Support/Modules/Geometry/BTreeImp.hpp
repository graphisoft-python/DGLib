// *********************************************************************************************************************
// Description:		BTreeImp.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTree<Type,SortType, AllocType>::BTreeElem::BTreeElem ()
{
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTree<Type,SortType, AllocType>::BTreeElem::BTreeElem (const Type& elem) :
	elem (elem)
{
}

template<typename Type, typename SortType, typename AllocType>
inline BTree<Type,SortType, AllocType>::BTree (CompareElementsFnc cmpElements, CompareWithSortkeyFnc cmpSortkey, ULong bMin, AllocType& memAlloc) :
	BTreeBase<AllocType> (bMin, memAlloc),
	compareElements (cmpElements),
	compareWithSortkey (cmpSortkey)
{
}

template<typename Type, typename SortType, typename AllocType>
BTree<Type,SortType, AllocType>::BTree (const BTree& source) :
	BTreeBase<AllocType> (source.bMin, source.memAlloc),
	compareElements (source.compareElements),
	compareWithSortkey (source.compareWithSortkey)
{
	try {
		for (BTreePos<Type> ps = source.NextPos (BTreeNullPos); ps; ps = source.NextPos (ps))
			InsertBefore (BTreeNullPos, source[ps]);
	}
	catch (...) {
		RemoveAll ();
		throw;
	}
}

template<typename Type, typename SortType, typename AllocType>
BTree<Type,SortType, AllocType>::BTree (BTree&& source) :
	BTreeBase<AllocType> (std::move (source)),
	compareElements (source.compareElements),
	compareWithSortkey (source.compareWithSortkey)
{
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTree<Type,SortType, AllocType>::~BTree ()
{
	RemoveAll ();
}

template<typename Type, typename SortType, typename AllocType>
const BTree<Type,SortType, AllocType>& BTree<Type,SortType, AllocType>::operator= (const BTree& source)
{
	if (this != &source) {
		RemoveAll ();
		for (BTreePos<Type> ps = source.NextPos (BTreeNullPos); ps; ps = source.NextPos (ps))
			InsertBefore (BTreeNullPos, source[ps]);
	}
	return *this;
}

template<typename Type, typename SortType, typename AllocType>
const BTree<Type,SortType, AllocType>& BTree<Type,SortType, AllocType>::operator= (BTree&& source)
{
	if (this != &source) {
		*this = std::move (static_cast<BTreeBase<AllocType>&&> (source));
	}
	return *this;
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE void BTree<Type,SortType, AllocType>::SetCompareFunctions (CompareElementsFnc cmpElements, CompareWithSortkeyFnc cmpSortkey)
{
	compareElements = cmpElements;
	compareWithSortkey = cmpSortkey;
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE void BTree<Type,SortType, AllocType>::GetCompareFunctions (CompareElementsFnc** cmpElements, CompareWithSortkeyFnc** cmpSortkey) const
{
	if (cmpElements != nullptr) {
		*cmpElements = compareElements;
	}
	if (cmpSortkey != nullptr) {
		*cmpSortkey = compareWithSortkey;
	}
}

// Insert the given new item into the array that is assumed to be sorted. The array remains sorted.
// The returned value is the position of the new item.
template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::Insert (const Type& data)
{
	BTreeElem* el = NewElem (data);
	try { BTreeBase<AllocType>::InsertBefore (el, (LeafType*) FindNextPos (data).pos); } // look-up insert position and insert the item into the B-tree
	catch (...) { DeleteElem (el); throw; }

	return LeafToBTreePos (el);
}

// Insert the given new item into the array before the item whose position is passed to the function. If pos is BTreeNullPos,
//  the new item will be the last item in the array.
// The returned value is the position of the new item.
template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::InsertBefore (BTreePos<Type> pos, const Type& data)
{
	BTreeElem* el = NewElem (data);
	try { BTreeBase<AllocType>::InsertBefore (el, (LeafType*) pos.pos); }
	catch (...) { DeleteElem (el); throw; }

	return LeafToBTreePos (el);
}

// Insert a default new item in the array before the item whose position is passed to the function.
// If pos is BTreeNullPos, the new item will be the last item in the array.
// The returned value is the position of the new item.
template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::InsertBefore (BTreePos<Type> pos)
{
	BTreeElem* el = NewElem ();
	try { BTreeBase<AllocType>::InsertBefore (el, (LeafType*) pos.pos); }
	catch (...) { DeleteElem (el); throw; }

	return LeafToBTreePos (el);
}

// This function inserts the given new element after the given position.
// If pos is BTreeNullPos, the new element will be the first in the array.
// The returned value is the position of the new item.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTreePos<Type> BTree<Type,SortType, AllocType>::InsertAfter (BTreePos<Type> pos, const Type& data)
{
	return InsertBefore (NextPos (pos), &data);
}

// This function inserts a default new element after the given position.
// If pos is BTreeNullPos, the new element will be the first in the array.
// The returned value is the position of the new item.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTreePos<Type> BTree<Type,SortType, AllocType>::InsertAfter (BTreePos<Type> pos)
{
	return InsertBefore (NextPos (pos));
}

// This function finds the right position of the given item in the ordered array.
// It assumes that the array is already ordered with the exception of the given element.
//  posItem: position of the element whose new place is to be found
template<typename Type, typename SortType, typename AllocType>
void BTree<Type,SortType, AllocType>::Reinsert (BTreePos<Type> posItem)
{
	BTreeElem* el = (BTreeElem*) posItem.pos;
	BTreeBase<AllocType>::RemovePos (el); // take it out, but don't destroy
	try { BTreeBase<AllocType>::InsertBefore (el, (LeafType*) FindNextPos (*GD (posItem)).pos); } // insert it back to the right position
	catch (...) { DeleteElem (el); throw; }
}

// This function replaces the given item in the array before the given position
//  pos: position of item before which the other item is repositioned
//  posItem: position of the element whose new place is to be found
//	if pos is BTreeNullPos, the element will be the last in the array
template<typename Type, typename SortType, typename AllocType>
void BTree<Type,SortType, AllocType>::ReinsertBefore (BTreePos<Type> pos, BTreePos<Type> posItem)
{
	// if pos was the same as posItem, the call below to 'BTreeBase::InsertBefore' would be desasterous
	if (pos != posItem && NextPos (posItem) != pos) {
		BTreeElem* el = (BTreeElem*) posItem.pos;
		BTreeBase<AllocType>::RemovePos (el); // take it out but don't destroy
		try { BTreeBase<AllocType>::InsertBefore (el, (LeafType*) pos.pos); } // insert it back before the given position
		catch (...) { DeleteElem (el); throw; }
	}
}

// This function replaces the given item in the array after the given position
//  pos: position of item after which the other item is repositioned
//  posItem: position of the element whose new place is to be found
//  if pos is BTreeNullPos, the element will be the first in the array
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE void BTree<Type,SortType, AllocType>::ReinsertAfter (BTreePos<Type> pos, BTreePos<Type> posItem)
{
	ReinsertBefore (NextPos (pos), posItem);
}

template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::Add (const Type& data)
{
	BTreePos<Type> ps = FindNextPos (data);
	if (ps != BTreeNullPos && data == *GD (ps))
		return ps;
	else
		return InsertBefore (ps, data);
}

// This function removes the item of the given position.
template<typename Type, typename SortType, typename AllocType>
inline void BTree<Type,SortType, AllocType>::RemovePos (BTreePos<Type> pos)
{
	BTreeBase<AllocType>::RemovePos ((LeafType*) pos.pos); // it takes item out but doesn't destroy it
	DeleteElem ((BTreeElem*) pos.pos);
}

// This function removes all elements of the array.
template<typename Type, typename SortType, typename AllocType>
void BTree<Type,SortType, AllocType>::RemoveAll ()
{
	if (BTreeElem* leaf = (BTreeElem*) BTreeBase<AllocType>::RemoveAllBNodes ()) {
		do {
			BTreeElem* lf2 = (BTreeElem*) leaf->pNext;
			DeleteElem (leaf);
			leaf = lf2;
		} while (leaf);
	}
}

template<typename Type, typename SortType, typename AllocType>
void BTree<Type,SortType, AllocType>::SortArray ()
{
	if (BTreeElem* leaf = (BTreeElem*) BTreeBase<AllocType>::RemoveAllBNodes ()) {
		try {
			do {
				BTreeElem* lf2 = (BTreeElem*) leaf->pNext;
				BTreeBase<AllocType>::InsertBefore (leaf, (LeafType*) FindNextPos (*GD (leaf)).pos);
				leaf = lf2;
			} while (leaf);
		}
		catch (...) {
			if (BTreeBase<AllocType>::pLast) {
				this->pLast->pNext = leaf;
				leaf->pPrev = this->pLast;
				leaf = (BTreeElem*) this->pFirst;
			}

			BTreeBase<AllocType>::RemoveAllBNodes ();

			this->root.pFirst = this->root.pEdge = this->pFirst = leaf;
			while (leaf) {
				this->root.pLast = this->pLast = leaf;
				leaf->pAbove = &this->root;
				this->root.ulChildren++;
				leaf = (BTreeElem*) leaf->pNext;
			}

			throw;
		}
	}
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE bool BTree<Type,SortType, AllocType>::Contains (const Type& data) const
{
	return Find (data) != BTreeNullPos;
}

template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::Find (const Type& data) const
{
	BTreePos<Type> ps = FindNextPos (data);
	return ps != BTreeNullPos && data == *GD (ps) ? ps : BTreeNullPos;
}

// This function finds the position of the item after which a given new item should be inserted.
// It assumes that the array is currently sorted.
// If the returned value is BTreeNullPos, a new such item should be inserted as the first in the array.
// In case of equality, the first possible position is returned.
template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::FindPrevPos (const Type& data) const
{
	const NodeType* p;

	if (this->pFirst == nullptr || compareElements (*GD (this->root.pEdge), data) >= 0)
		return BTreeNullPos;
	else {
		p = &this->root;
		do {
			p = p->pLast;
			while (compareElements (*GD (p->pEdge), data) >= 0)
				p = p->pPrev;
		} while (p->pFirst);

		return LeafToBTreePos ((const LeafType *) p);
	}
}

// This function finds the position in the ordered array before which the given new item should be inserted.
//   BTreeNullPos is returned if the item should be the last in the array.
// In case of equality, the first possible position is returned.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTreePos<Type> BTree<Type,SortType, AllocType>::FindNextPos (const Type& data) const
{
	return NextPos (FindPrevPos (data));
}

// This function finds the position of the item after which any item whose sort key is given by ord should be
//  inserted. It assumes that the array is currently sorted.
// The sort key is normally a part of an item, but can be the item itself, too.
// If the returned value is BTreeNullPos, a new such item should be inserted as the first in the array.
// In case of equality, the first possible position is returned.
template<typename Type, typename SortType, typename AllocType>
BTreePos<Type> BTree<Type,SortType, AllocType>::FindPrevPosBySortkey (const SortType& ord) const
{
	const NodeType* p;

	// the following algorithm relies on the pEdge field of a node. This field points to the left-most item
	// that belongs to the given node, so if the array is sorted, this field gives the smallest
	// element under a node.
	if (BTreeBase <AllocType>::pFirst == nullptr || compareWithSortkey (*GD (BTreeBase <AllocType>::root.pEdge), ord) >= 0)
		return BTreeNullPos;
	else {
		p = &this->root;
		do {
			p = p->pLast; // go one level down, take right-most child node.
			// find the insert position on the current level
			while (compareWithSortkey (*GD (p->pEdge), ord) >= 0)
				p = p->pPrev;
		} while (p->pFirst); // if leaf level is reached, we are done

		return LeafToBTreePos ((const LeafType *) p);
	}
}

// This function finds the position in the ordered array before which a new item should be inserted whose sort key is
// pointed to by the given pointer.
// The sort key is normally a part of an item, but can be the item itself, too.
//   BTreeNullPos is returned if the item should be the last in the array
// In case of equality, the first possible position is returned.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTreePos<Type> BTree<Type,SortType, AllocType>::FindNextPosBySortkey (const SortType& ord) const
{
	return NextPos (FindPrevPosBySortkey (ord));
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE Type& BTree<Type,SortType, AllocType>::operator[] (BTreePos<Type> pos)
{
	return *GD (pos);
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE const Type& BTree<Type,SortType, AllocType>::operator[] (BTreePos<Type> pos) const
{
	return *GD (pos);
}

template<typename Type, typename SortType, typename AllocType>
inline Type& BTree<Type,SortType, AllocType>::Get (BTreePos<Type> pos)
{
	return *GD (pos);
}

template<typename Type, typename SortType, typename AllocType>
inline const Type& BTree<Type,SortType, AllocType>::Get (BTreePos<Type> pos) const
{
	return *GD (pos);
}

// This function finds the position of the next item in the array after the item given by the passed position.
// If pos is BTreeNullPos, the position of the first item is returned.
// BTreeNullPos is returned if pos is the position of the last item of the array.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTreePos<Type> BTree<Type,SortType, AllocType>::NextPos (BTreePos<Type> pos) const
{
	return LeafToBTreePos ((LeafType *) (pos.pos ? ((LeafType *) pos.pos)->pNext : this->pFirst));
}

// This function finds the position of the previous item in the array before the item given by the passed position.
// If pos is BTreeNullPos, the position of the last item is returned.
// BTreeNullPos is returned if pos is the position of the first item of the array.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE BTreePos<Type> BTree<Type,SortType, AllocType>::PrevPos (BTreePos<Type> pos) const
{
	return LeafToBTreePos ((LeafType *) (pos.pos ? ((LeafType *) pos.pos)->pPrev : BTreeBase <AllocType>::pLast));
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE ULong BTree<Type,SortType, AllocType>::GetSize () const
{
	return BTreeBase <AllocType>::elementsNum;
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE bool BTree<Type,SortType, AllocType>::IsEmpty () const
{
	return BTreeBase <AllocType>::pFirst == nullptr;
}

template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE const Type* BTree<Type,SortType, AllocType>::GetConstElemFromPos (BTreePos<Type> pos)
{
	return GD (pos);
}

// This private helper function returns the pointer to the item data given the pointer of a leaf.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE Type* BTree<Type,SortType, AllocType>::GD (LeafType* pLf)
{
	return &((BTreeElem*) pLf)->elem;
}

// This private helper function returns the pointer to the item data given its position.
template<typename Type, typename SortType, typename AllocType>
GS_FORCE_INLINE Type* BTree<Type,SortType, AllocType>::GD (BTreePos<Type> pos)
{
	return GD ((LeafType *) pos.pos);
}

template<typename Type, typename SortType, typename AllocType>
inline BTreePos<Type> BTree<Type,SortType, AllocType>::LeafToBTreePos (const LeafType* leaf)
{
	BTreePos<Type> pos;
	pos.pos = (void*) leaf;
	return pos;
}

template<typename Type, typename SortType, typename AllocType>
inline typename BTree<Type,SortType, AllocType>::BTreeElem* BTree<Type,SortType, AllocType>::NewElem ()
{
	BTreeElem* newElem = (BTreeElem*) BTreeBase <AllocType>::memAlloc.Alloc (sizeof (BTreeElem));
	try { new (newElem) BTreeElem; }
	catch (...) { BTreeBase <AllocType>::memAlloc.Free (newElem, sizeof (BTreeElem)); throw; }

	return newElem;
}

template<typename Type, typename SortType, typename AllocType>
inline typename BTree<Type,SortType, AllocType>::BTreeElem* BTree<Type,SortType, AllocType>::NewElem (const Type& data)
{
	BTreeElem* newElem = (BTreeElem*) BTreeBase <AllocType>::memAlloc.Alloc (sizeof (BTreeElem));
	try { new (newElem) BTreeElem (data); }
	catch (...) { BTreeBase <AllocType>::memAlloc.Free (newElem, sizeof (BTreeElem)); throw; }

	return newElem;
}

template<typename Type, typename SortType, typename AllocType>
inline void BTree<Type,SortType, AllocType>::DeleteElem (BTreeElem* pLf)
{
	pLf->~BTreeElem ();
	BTreeBase <AllocType>::memAlloc.Free (pLf, sizeof (BTreeElem));
}


// class BTreeBase
template<typename AllocType>
BTreeBase<AllocType>::BTreeBase (ULong bMin, AllocType& memAlloc) :
	bMin (bMin),
	bMax (bMin * 2 - 1),
	memAlloc (memAlloc)
{
	InitBTree(); // clear out B-tree
}

template<typename AllocType>
BTreeBase<AllocType>::BTreeBase (BTreeBase&& source) :
	bMin (source.bMin),
	bMax (source.bMax),
	root (source.root),
	pFirst (source.pFirst),
	pLast (source.pLast),
	elementsNum (source.elementsNum),
	memAlloc (source.memAlloc)
{
	source.InitBTree ();
}

// This private function initializes the B-tree structure to an empty tree.
template<typename AllocType>
void BTreeBase<AllocType>::InitBTree ()
{
	memset (&root, 0, sizeof (root));
	pFirst = pLast = nullptr;
	elementsNum = 0;
}

template<typename AllocType>
inline typename BTreeBase<AllocType>::BNode* BTreeBase<AllocType>::NewBNode ()
{
	BNode* bn = (BNode*)memAlloc.Alloc (sizeof (BNode));
	new (bn) BNode;
	return bn;
}

template<typename AllocType>
inline void BTreeBase<AllocType>::DeleteBNode (BNode* p)
{
	p->~BNode ();
	memAlloc.Free (p, sizeof (BNode));
}

template<typename AllocType>
typename BTreeBase<AllocType>::Leaf* BTreeBase<AllocType>::RemoveAllBNodes ()
{
	if (pFirst == nullptr)
		return nullptr;

	BNode* rowFirst = root.pFirst;
	while (rowFirst->pEdge != rowFirst) {
		BNode* delNode = rowFirst;
		rowFirst = rowFirst->pFirst;
		while (delNode) {
			BNode* n = delNode->pNext;
			DeleteBNode (delNode);
			delNode = n;
		}
	}

	Leaf* firstLeaf = pFirst;
	InitBTree ();

	return firstLeaf;
}

// This private function inserts a new element into the B-tree.
// The datafield part of pLf (containing the item itself and placed in the memory just after the Leaf structure)
//  must already be initialized, but the Leaf structure is filled out correctly by the function.
//  The new item is inserted before the element given by the 'pos' position, or inserted as last item if pos is nullptr.
template<typename AllocType>
void BTreeBase<AllocType>::InsertBefore (Leaf* pLf, Leaf* pos)
{
	elementsNum++;

	BNode *p, *pN, *pP, *pA;

	pLf->pFirst = pLf->pLast = nullptr; // a leaf cannot have children
	pLf->pEdge = pLf; // the pEdge of a leaf always points back to itself
	pLf->ulChildren=0;
	// now initialize the three important variables before entering the main loop
	p = pLf; // p: the node that is to be inserted into the B-tree
	pN = pos; // pN: the node already in the B-tree that will be the next node of the new node
	pP = pN ? pN->pPrev : pLast; // pP: the node already in the B-tree that will be the previous node of the new node
	// the two member pointers that refer to leaves may need be changed
	if (!pP)
		pFirst = pLf;
	if (!pN)
		pLast = pLf;

	// At each execution of the following loop a new node is inserted into the B-tree. We start out from the leaf
	// level and by each execution of the loop we move upward. Actually, it takes one execution of the loop to insert
	// a new node and the next execution is necessary only if we cannot avoid node-splitting and we have to add a new
	// node at the above level, as well.
	// The state of the variables must be the following before
	// each entry to the loop: p points to the new node to be inserted, pN points to the node that will follow p,
	// pP points to the node that will precede p. (pN and pP can be nullptr). The following fields of p must be already
	// correctly filled out: ulChildren, pFirst, pLast, pEdge; while the following are filled out by the
	// next execution of the loop: pPrev, pNext, pAbove.
	for (;;) {
		// put p into the doubly linked list of nodes of the same level:
		p->pPrev = pP;
		p->pNext = pN;
		if (pP)
			pP->pNext = p, pP = pP->pAbove;
		if (pN)
			pN->pPrev = p, pN = pN->pAbove;

		// now we have changed pP and pN, too and they point to the parents of p's neighbors.
		// next we have to choose the parent of p, and this will obviously be one of the parents of its neighbors, so
		//  now either pP or pN.(There is a great chance that pP==pN, but it is okay).

		// we put the future parent of p into pA:
		if (!pP && !pN)
			pA = &root; // this can only be if the tree is empty and p will be the first element
			// otherwise we look for a parent who can still have an extra child
		else if (pP && pP->ulChildren < bMax)
			pA = pP;
		else if (pN && pN->ulChildren < bMax)
			pA = pN;
			// otherwise just choose one of them
		else if (pN)
			pA = pN;
		else
			pA=pP;

		pA->ulChildren++;
		p->pAbove = pA;

		// see if p becomes the first child of pA. In that case even pA's pEdge pointer must be changed and maybe
		//  its ancestors' too.
		if (!pA->pFirst || pA->pFirst->pPrev == p)
			pA->pFirst = p, ChangeEdge (pA, p->pEdge);
		if (!pA->pLast || pA->pLast->pNext == p)
			pA->pLast = p;

		// now the insertion of the node is complete, so if pA does not have too many children, we can leave
		if (pA->ulChildren <= bMax)
			break;

		// pA has too many children (one more than it should have). Let's first try to give one child node to a
		// neighbor to avoid node-splitting.
		// Change pP and pN so that they point to the neighbors of pA.
		pP = pA->pPrev;
		pN = pA->pNext;

		// check if we can pass a child to the node before pA (pP)
		if(pP && pP->ulChildren < bMax) {
			// the left-most (first) child of pA becomes the right-most (last) child of pP:
			pP->pLast = pA->pFirst;
			pA->pFirst = pP->pLast->pNext;
			pP->pLast->pAbove = pP;
			// pA has a new first child node, so its pEdge must be changed
			ChangeEdge (pA, pA->pFirst->pEdge);
			pA->ulChildren--;
			pP->ulChildren++;
			break;
		}
		// check if we can pass a child to the node after pA (pN)
		else if (pN && pN->ulChildren<bMax) {
			// the right-most (last) child of pA becomes the left-most (first) child of pN:
			pN->pFirst = pA->pLast;
			pA->pLast = pN->pFirst->pPrev;
			pN->pFirst->pAbove = pN;
			// pN has a new first child node so its pEdge field must be changed
			ChangeEdge (pN, pN->pFirst->pEdge);
			pA->ulChildren--;
			pN->ulChildren++;
			break;
		}

		// now we have to split the node pA into two and pass half of its children to a new node
		// p is the new node
		p = NewBNode ();
		if (pA->pAbove)
			pP = pA; // no special case. p will later be put after pA (so pP is already changed to pA)
		// special case: pA is root and it cannot be split. Instead we add two new nodes under the root and thus
		//  a new level is added to the tree. (the BMin rule does not hold for the children of the root.)
		else {
			try { pP = NewBNode (); }
			catch (...) { DeleteBNode (p); throw; }
		}

		// so let's pass the right-side child nodes of pA to p (both of them will have BMin children at the end)
		p->ulChildren = 0;
		p->pFirst = p->pLast = pA->pLast;
		for (;;) {
			// we have just added the child p->pFirst to p, so change everything accordingly
			p->pFirst->pAbove = p;
			p->ulChildren++;
			if (p->ulChildren >= bMin)   // ==
				break;
			p->pFirst = p->pFirst->pPrev; // add one more child to p
		}
		pA->ulChildren -= p->ulChildren; // pA lost the same number of children than p received
		pA->pLast = p->pFirst->pPrev;
		p->pEdge = p->pFirst->pEdge;
		if (!pA->pAbove) { // now treat special case: pA is root
			*pP = *pA;  // copy all pA structure into the other new node, pP.
			pA->ulChildren = 1; // p is not yet really in the B-tree, so pA (the root) has only pP as child
			pA->pFirst = pA->pLast = pP;
			pP->pAbove = pA;
			// now pA becomes a simple running variable used to changing the pAbove pointers of all children of pP.
			pA = pP->pFirst;
			while (pA != pP->pLast) {
				pA->pAbove = pP;
				pA = pA->pNext;
			}
			pA->pAbove = pP;
			pN = nullptr;
		} else
			pN = pP->pNext;
		// now we can reenter the loop to insert the new node p into the tree.
		// the state of the variables (p,pP,pN) satisfies the requirements described at the start of the loop.
	}
}

// This private function removes the item given by pos from the B-tree.
// The item itself and its Leaf structure is not destroyed.
template<typename AllocType>
void BTreeBase<AllocType>::RemovePos (Leaf* pos)
{
	elementsNum--;

	Leaf* pLf;
	BNode *p, *pP, *pN, *pA;

	pLf = pos;
	// If necessary, change the pFirst and pLast pointers which are used for the leaf level only.
	if (pFirst == pLf)
		pFirst = (Leaf*) pLf->pNext;
	if (pLast == pLf)
		pLast = (Leaf*) pLf->pPrev;

	// set the three loop-variables to the correct initial values.
	p = pLf;
	pP = p->pPrev;
	pN = p->pNext;

	// At each execution of the following loop a node is taken out from the B-tree. The first execution takes out the
	// node that belongs to the item that we want to remove, so it is on the leaf level. Each consecutive execution
	// takes out and destroys a node that is on one level above to the previous. We pass to a next execution of the loop
	// only if we cannot avoid assembling nodes in the current execution, otherwise we break out from the loop.
	// Before each execution, the variable p must point to the node to be taken out, pN to its next node on the same
	// level (can be nullptr), pP to its previous node on the same level (can be nullptr).
	for (;;) {
		// first, remove the node from the doubly-linked list of the current level of nodes.
		if (pP)
			pP->pNext = pN;
		if (pN)
			pN->pPrev = pP;

		pA = p->pAbove;  // pA: parent node of p
		// p is no longer a child of pA, so make changes accordingly
		if (pA->pFirst == p) {
			pA->pFirst = pN; // the new first child of pA is the next node of p
			// Now pA has a new first child, so its pEdge pointer must be updated (and maybe some of its ancestors')
			if (pN)
				ChangeEdge (pA, pN->pEdge);
			else
				pA->pEdge = nullptr;
		}

		// if p was the last child of pA, the new last child of pA becomes the previous node of p
		if (pA->pLast == p)
			pA->pLast = pP;
		pA->ulChildren--;

		if (p->pFirst)
			DeleteBNode (p); // if p is not on the leaf level (not an item), deallocate this node
		// now p is removed from the list, so if the number of child nodes of pA is correct, we are done.
		if (pA->ulChildren >= bMin || !pA->pAbove)
			break;

		// pA has bMin-1 child nodes. First, let's try to solve this problem by adding one child from its
		// right or left neighbor.
		pP = pA->pPrev;
		pN = pA->pNext;

		// see if next node can pass its first child to pA
		if (pN && pN->ulChildren > bMin) {
			// there are three pointers to change
			pA->pLast = pN->pFirst;
			pN->pFirst = pN->pFirst->pNext;
			pA->pLast->pAbove = pA;

			// now pN has a new first child, so ChangeEdge must be called to update the pEdge field(s).
			ChangeEdge (pN, pN->pFirst->pEdge);
			pA->ulChildren++;
			pN->ulChildren--;
			// we are done
			break;
		}
		// otherwise, see if the previous node can pass its last child to pA
		else if (pP && pP->ulChildren > bMin) {
			// change the three pointers
			pA->pFirst = pP->pLast;
			pP->pLast = pP->pLast->pPrev;
			pA->pFirst->pAbove = pA;

			// now pA has a new first child, so ChangeEdge must be called to update the pEdge field(s).
			ChangeEdge (pA, pA->pFirst->pEdge);
			pA->ulChildren++;
			pP->ulChildren--;
			// we are done
			break;
		}

		// We could not avoid assembling nodes. The previous or the next node of pA must exist (pA is not the root),
		// and we know that they have exactly bMin child nodes (the two if-conditions above have failed).
		// As pA has bMin-1 child nodes, the new node, which
		// we will create by joining pA to one of its neighbors, will contain bMin+bMin-1, that is exactly bMax
		// child nodes. This is really cool.

		// Change pointers so that p point to the right-side of the two nodes that we will join, pN to the left side,
		// and pP to the previous node of p.
		if (pP)
			p = pP, pN = pA;
		else
			p = pA;
		pP = p->pPrev;

		//As we will pass all children of p to pN and remove p from the tree in the
		// next execution of the loop, these values of the three pointers fulfill the initial loop-condition which is
		// described above.(so p, pP and pN are no longer changed before the next execution of the loop).

		// now pass all children of p to pN. pA is used as a running variable.
		pA = pN->pFirst;
		do {
			pA = pA->pPrev;
			pA->pAbove = pN; // the new parent of these nodes is pN
		} while (pA != p->pFirst);
		pN->pFirst = p->pFirst;
		pN->ulChildren += p->ulChildren;
		// pN has a new first child, so call ChangeEdge to change the pEdge field(s)
		ChangeEdge (pN, pN->pFirst->pEdge);

		// now p is still in the tree with no child. It is removed from the tree by the next execution
		// of the loop.

		// in the rest of the function we check the special case, when the root has two child nodes, and
		// one of them is removed (p). Then instead of keeping one child of the root, this node is removed, too, and the
		// root will have all its children. That is the way we delete a level in the tree.
		pA = p->pAbove;
		if (!pA->pAbove && pA->ulChildren == 2) { // pA is root and has two children (p and pN)
			*pA = *pN; // pA now has all children of pN
			pA->pAbove = pA->pPrev = nullptr; // pA->pNext is already nullptr as pN->pNext was nullptr, too
			// pP is now a running variable
			pP = pA->pFirst;
			while (pP != pA->pLast) {
				pP->pAbove = pA; // the new parent of these nodes is pA
				pP = pP->pNext;
			}
			pP->pAbove = pA;
			// by destroying the two nodes p and pN, we in fact decrease the number of levels in the tree.
			DeleteBNode (p);
			DeleteBNode (pN);
			break; // no need for the next execution of the loop
		}
	}
}

// This private helper function updates the pEdge field of the given node and of all its ancestors whose left-most
// descendant node on this level is the given node. The pEdge parameter contains the new value for the pEdge fields.
// (the pEdge field of a node points always to the left-most item (leaf) that belongs to that node).
template<typename AllocType>
void BTreeBase<AllocType>::ChangeEdge (BNode* p, Leaf* pEdge)
{
	BNode* prev;

	do {
		p->pEdge = pEdge;
		prev = p;
		p = p->pAbove; // move one level up
	} while (p && p->pFirst == prev); // go on only if the previous node is the first child of the current node
}
