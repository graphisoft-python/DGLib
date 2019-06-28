// *********************************************************************************************************************
// Description:		DList.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#pragma once

#ifndef DLIST_HPP
#define DLIST_HPP

#include "MemAlloc.hpp"


namespace QXTools {

struct DListNullPosType
{
	DListNullPosType () {}
};

static const DListNullPosType DListNullPos;

template<typename Type>
struct DListPos
{
	void* pos;

	DListPos () : pos (nullptr) {}
	DListPos (const DListNullPosType&) { pos = nullptr; }
	DListPos operator= (const DListNullPosType&) { pos = nullptr; return *this; }

	bool operator== (const DListPos& tp) const { return pos == tp.pos; }
	bool operator!= (const DListPos& tp) const { return pos != tp.pos; }

	bool operator== (const DListNullPosType&) const { return pos == nullptr; }
	bool operator!= (const DListNullPosType&) const { return pos != nullptr; }

	operator bool () const { return pos != nullptr; }
};

template<typename Type>
class DList
{
	struct DListElem
	{
		DListElem *next, *prev;
		Type elem;

		DListElem ();
		DListElem (const Type&);
	};

	MemAlloc8K* memAlloc;
	DListElem *first, *last;

	DListPos<Type> InsertAfter (DListPos<Type>, DListElem*);

public:
	DList (MemAlloc8K* = nullptr);
	DList (const DList&);
	DList (DList&&);
	~DList ();

	const DList& operator= (const DList&);
	const DList& operator= (DList&&);

	DListPos<Type> InsertAfter (DListPos<Type>);
	DListPos<Type> InsertAfter (DListPos<Type>, const Type&);
	DListPos<Type> InsertBefore (DListPos<Type>);
	DListPos<Type> InsertBefore (DListPos<Type>, const Type&);
	void Delete (DListPos<Type>);

	const Type& operator[] (DListPos<Type>) const;
	Type& operator[] (DListPos<Type>);

	DListPos<Type> NextPos (DListPos<Type>) const;
	DListPos<Type> PrevPos (DListPos<Type>) const;

	void Clear ();

	bool IsEmpty () const;
	UInt32 GetSize () const;
};


#include "DListImp.hpp"

}

#endif
