// *********************************************************************************************************************
// Description:		SList.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#pragma once

#ifndef SLIST_HPP
#define SLIST_HPP

#include "MemAlloc.hpp"


namespace QXTools {

struct SListNullPosType
{
	SListNullPosType () {}
};

static const SListNullPosType SListNullPos;

template<typename Type>
struct SListPos
{
	void* pos;

	SListPos () : pos (nullptr) {}
	SListPos (const SListNullPosType&) { pos = nullptr; }
	SListPos operator= (const SListNullPosType&) { pos = nullptr; return *this; }

	bool operator== (const SListPos& tp) const { return pos == tp.pos; }
	bool operator!= (const SListPos& tp) const { return pos != tp.pos; }

	bool operator== (const SListNullPosType&) const { return pos == nullptr; }
	bool operator!= (const SListNullPosType&) const { return pos != nullptr; }

	operator bool () const { return pos != nullptr; }
};

template<typename Type>
class SList
{
	struct SListElem
	{
		SListElem* next;
		Type elem;

		SListElem ();
		SListElem (const Type&);
	};

	MemAlloc8K* memAlloc;
	SListElem* first;
	ULong size;

	SListPos<Type> InsertAfter (SListPos<Type>, SListElem*);

public:
	SList (MemAlloc8K*);
	SList (const SList&);
	SList (SList&&);
	~SList ();

	const SList& operator= (const SList&);
	const SList& operator= (SList&&);

	SListPos<Type> InsertAfter (SListPos<Type>);
	SListPos<Type> InsertAfter (SListPos<Type>, const Type&);
	void DeleteAfter (SListPos<Type>);

	const Type& operator[] (SListPos<Type>) const;
	Type& operator[] (SListPos<Type>);

	SListPos<Type> NextPos (SListPos<Type>) const;

	void Clear ();

	ULong GetSize () const;
	bool IsEmpty () const;
	bool Contains (const Type&) const;
};


#include "SListImp.hpp"

}

#endif
