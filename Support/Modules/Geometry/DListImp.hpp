// *********************************************************************************************************************
// Description:		DListImp.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

template<typename Type>
GS_FORCE_INLINE DList<Type>::DListElem::DListElem ()
{
}

template<typename Type>
GS_FORCE_INLINE DList<Type>::DListElem::DListElem (const Type& t) :
	elem (t)
{
}

template<typename Type>
GS_FORCE_INLINE DList<Type>::DList (MemAlloc8K* memAlloc) :
	memAlloc (memAlloc),
	first (nullptr),
	last (nullptr)
{
}

template<typename Type>
DList<Type>::DList (const DList& source) :
	memAlloc (source.memAlloc),
	first (nullptr),
	last (nullptr)
{
	try {
		for (const DListElem* el = source.last; el != nullptr; el = el->prev)
			InsertAfter (DListNullPos, el->elem);
	}
	catch (...) {
		Clear ();
		throw;
	}
}

template<typename Type>
DList<Type>::DList (DList&& source) :
	memAlloc (source.memAlloc),
	first (source.first),
	last (source.last)
{
	source.memAlloc = nullptr;
	source.first = nullptr;
	source.last = nullptr;
}

template<typename Type>
GS_FORCE_INLINE DList<Type>::~DList ()
{
	Clear ();
}

template<typename Type>
const DList<Type>& DList<Type>::operator= (const DList& source)
{
	if (this == &source)
		return *this;

	if (source.memAlloc != nullptr)
		memAlloc = source.memAlloc;

	DListElem* de = last;
	const DListElem* se = source.last;
	for (; se != nullptr && de != nullptr; se = se->prev, de = de->prev)
		de->elem = se->elem;

	if (de == nullptr) {
		for (; se != nullptr; se = se->prev)
			InsertAfter (DListNullPos, se->elem);
	} else {
		do {
			DListPos<Type> delPs;
			delPs.pos = de;
			de = de->prev;
			Delete (delPs);
		} while (de != nullptr);
	}

	return *this;
}

template<typename Type>
const DList<Type>& DList<Type>::operator= (DList&& source)
{
	if (this == &source)
		return *this;

	if (source.memAlloc != nullptr)
		memAlloc = source.memAlloc;
	first = source.first;
	last = source.last;

	source.memAlloc = nullptr;
	source.first = nullptr;
	source.last = nullptr;

	return *this;
}

template<typename Type>
DListPos<Type> DList<Type>::InsertAfter (DListPos<Type> ps, DListElem* se)
{
	DListElem* after = (DListElem*) ps.pos;
	if (after != nullptr) {
		se->next = after->next;
		se->prev = after;
		(after->next == nullptr ? last : after->next->prev) = se;
		after->next = se;
	} else {
		se->prev = nullptr;
		se->next = first;
		(first == nullptr ? last : first->prev) = se;
		first = se;
	}

	DListPos<Type> retPs;
	retPs.pos = se;
	return retPs;
}

template<typename Type>
DListPos<Type> DList<Type>::InsertAfter (DListPos<Type> ps)
{
	if (memAlloc == nullptr) {
		memAlloc = memAlloc8KThreadLocal.Get ();
		if (memAlloc == nullptr)
			throw GS::Exception (nullptr, __FILE__, __LINE__);
	}
	DListElem* se = memAlloc->Allocate<DListElem> ();
	try { new (se) DListElem; }
	catch (...) { memAlloc->Free (se); throw; }

	return InsertAfter (ps, se);
}

template<typename Type>
DListPos<Type> DList<Type>::InsertAfter (DListPos<Type> ps, const Type& t)
{
	if (memAlloc == nullptr) {
		memAlloc = memAlloc8KThreadLocal.Get ();
		if (memAlloc == nullptr)
			throw GS::Exception (nullptr, __FILE__, __LINE__);
	}
	DListElem* se = memAlloc->Allocate<DListElem> ();
	try { new (se) DListElem (t); }
	catch (...) { memAlloc->Free (se); throw; }

	return InsertAfter (ps, se);
}

template<typename Type>
GS_FORCE_INLINE DListPos<Type> DList<Type>::InsertBefore (DListPos<Type> ps)
{
	return InsertAfter (PrevPos (ps));
}

template<typename Type>
GS_FORCE_INLINE DListPos<Type> DList<Type>::InsertBefore (DListPos<Type> ps, const Type& t)
{
	return InsertAfter (PrevPos (ps), t);
}

template<typename Type>
void DList<Type>::Delete (DListPos<Type> ps)
{
	DListElem* del = (DListElem*) ps.pos;

	(del->next == nullptr ? last : del->next->prev) = del->prev;
	(del->prev == nullptr ? first : del->prev->next) = del->next;

	del->~DListElem ();
	memAlloc->Free (del);
}

template<typename Type>
GS_FORCE_INLINE const Type& DList<Type>::operator[] (DListPos<Type> ps) const
{
	return ((DListElem*) ps.pos)->elem;
}

template<typename Type>
GS_FORCE_INLINE Type& DList<Type>::operator[] (DListPos<Type> ps)
{
	return ((DListElem*) ps.pos)->elem;
}

template<typename Type>
GS_FORCE_INLINE DListPos<Type> DList<Type>::NextPos (DListPos<Type> ps) const
{
	if (ps.pos == nullptr)
		ps.pos = first;
	else
		ps.pos = ((DListElem*) ps.pos)->next;
	return ps;
}

template<typename Type>
GS_FORCE_INLINE DListPos<Type> DList<Type>::PrevPos (DListPos<Type> ps) const
{
	if (ps.pos == nullptr)
		ps.pos = last;
	else
		ps.pos = ((DListElem*) ps.pos)->prev;
	return ps;
}

template<typename Type>
void DList<Type>::Clear ()
{
	while (first) {
		DListElem* p = first->next;
		first->~DListElem ();
		memAlloc->Free (first);
		first = p;
	}
	last = nullptr;
}

template<typename Type>
GS_FORCE_INLINE bool DList<Type>::IsEmpty () const
{
	return first == nullptr;
}

template<typename Type>
UInt32 DList<Type>::GetSize () const
{
	UInt32 size = 0;
	for (DListPos<Type> ps = NextPos (DListNullPos); ps != DListNullPos; ps = NextPos (ps)) {
		size++;
	}
	return size;
}

