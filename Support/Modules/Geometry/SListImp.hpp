// *********************************************************************************************************************
// Description:		SListImp.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

template<typename Type>
GS_FORCE_INLINE SList<Type>::SListElem::SListElem ()
{
}

template<typename Type>
GS_FORCE_INLINE SList<Type>::SListElem::SListElem (const Type& t) :
	elem (t)
{
}

template<typename Type>
GS_FORCE_INLINE SList<Type>::SList (MemAlloc8K* memAlloc) :
	memAlloc (memAlloc),
	first (nullptr),
	size (0)
{
}

template<typename Type>
SList<Type>::SList (const SList& source) :
	memAlloc (source.memAlloc),
	first (nullptr),
	size (0)
{
	try {
		SListPos<Type> lastPos = SListNullPos;
		for (const SListElem* el = source.first; el != nullptr; el = el->next)
			lastPos = InsertAfter (lastPos, el->elem);
	}
	catch (...) {
		Clear ();
		throw;
	}
}

template<typename Type>
SList<Type>::SList (SList&& source) :
	memAlloc (source.memAlloc),
	first (source.first),
	size (source.size)
{
	source.memAlloc = nullptr;
	source.first = nullptr;
	source.size = 0;
}

template<typename Type>
GS_FORCE_INLINE SList<Type>::~SList ()
{
	Clear ();
}

template<typename Type>
const SList<Type>& SList<Type>::operator= (const SList& source)
{
	if (this == &source)
		return *this;

	memAlloc = source.memAlloc;

	SListPos<Type> lastPos = SListNullPos;
	SListElem* de = first;
	const SListElem* se = source.first;
	for (; se != nullptr && de != nullptr; se = se->next, de = de->next) {
		de->elem = se->elem;
		lastPos.pos = de;
	}

	if (de == nullptr) {
		for (; se != nullptr; se = se->next)
			lastPos = InsertAfter (lastPos, se->elem);
	} else {
		do
			DeleteAfter (lastPos);
		while (size > source.size);
	}

	return *this;
}

template<typename Type>
const SList<Type>& SList<Type>::operator= (SList&& source)
{
	if (this == &source)
		return *this;

	memAlloc = source.memAlloc;
	first = source.first;
	size = source.size;

	source.memAlloc = nullptr;
	source.first = nullptr;
	source.size = 0;

	return *this;
}

template<typename Type>
SListPos<Type> SList<Type>::InsertAfter (SListPos<Type> ps, SListElem* se)
{
	SListElem* after = (SListElem*) ps.pos;
	if (after != nullptr) {
		se->next = after->next;
		after->next = se;
	} else {
		se->next = first;
		first = se;
	}

	size++;

	SListPos<Type> retPs;
	retPs.pos = se;
	return retPs;
}

template<typename Type>
SListPos<Type> SList<Type>::InsertAfter (SListPos<Type> ps)
{
	SListElem* se = memAlloc->Allocate<SListElem> ();
	try { new (se) SListElem; }
	catch (...) { memAlloc->Free (se); throw; }

	return InsertAfter (ps, se);
}

template<typename Type>
SListPos<Type> SList<Type>::InsertAfter (SListPos<Type> ps, const Type& t)
{
	SListElem* se = memAlloc->Allocate<SListElem> ();
	try { new (se) SListElem (t); }
	catch (...) { memAlloc->Free (se); throw; }

	return InsertAfter (ps, se);
}

template<typename Type>
void SList<Type>::DeleteAfter (SListPos<Type> ps)
{
	SListElem* del;

	if (ps.pos == nullptr) {
		del = first;
		first = first->next;
	} else {
		del = ((SListElem*) ps.pos)->next;
		((SListElem*) ps.pos)->next = del->next;
	}

	size--;

	del->~SListElem ();
	memAlloc->Free (del);
}

template<typename Type>
GS_FORCE_INLINE const Type& SList<Type>::operator[] (SListPos<Type> ps) const
{
	return ((SListElem*) ps.pos)->elem;
}

template<typename Type>
GS_FORCE_INLINE Type& SList<Type>::operator[] (SListPos<Type> ps)
{
	return ((SListElem*) ps.pos)->elem;
}

template<typename Type>
GS_FORCE_INLINE SListPos<Type> SList<Type>::NextPos (SListPos<Type> ps) const
{
	if (ps.pos == nullptr)
		ps.pos = first;
	else
		ps.pos = ((SListElem*) ps.pos)->next;
	return ps;
}

template<typename Type>
void SList<Type>::Clear ()
{
	while (first) {
		SListElem* p = first->next;
		first->~SListElem ();
		memAlloc->Free (first);
		first = p;
	}

	size = 0;
}

template<typename Type>
GS_FORCE_INLINE ULong SList<Type>::GetSize () const
{
	return size;
}

template<typename Type>
GS_FORCE_INLINE bool SList<Type>::IsEmpty () const
{
	return first == nullptr;
}

template<typename Type>
GS_FORCE_INLINE bool SList<Type>::Contains (const Type& t) const
{
	for (SListElem* currElem = first; currElem != nullptr; currElem = currElem->next) {
		if (currElem->elem == t) {
			return true;
		}
	}
	return false;
}

