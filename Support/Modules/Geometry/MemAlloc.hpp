// *********************************************************************************************************************
// Description:		MemAlloc.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef MEMALLOC_HPP
#define MEMALLOC_HPP

#pragma once

#include "Array.hpp"
#include "ThreadLocal.hpp"
#include "GeometricDefinitions.h"


namespace QXTools {

class GEOMETRY_DLL_EXPORT MemAllocBase
{
	friend class MemAllocBaseInitializer;
	struct AllocationUnit
	{
		char* mem;
		ULong size;
		ULong nextFree;
	};

	GS::ArrayFB<AllocationUnit, 16> allocationUnits;

	void GetNewAllocationUnit ();

	static void Initialize ();
	static void Exit ();
public:
	~MemAllocBase ();

	char* Allocate (ULong nBytes);

};

template<int maxAllocBytes>
class MemAlloc : MemAllocBase
{
	static const ULong Alignment = (sizeof (void*) + 7) & ~7;		// = 8
	void* firstFreePointers[(maxAllocBytes + Alignment - 1) / Alignment + 1];

	MemAlloc (const MemAlloc&);
	MemAlloc& operator= (const MemAlloc&);

public:
	MemAlloc ();

	char* Allocate (ULong nBytes);
	void Free (char* mem, ULong nBytes);

	template<typename T>
	T* Allocate ();

	template<typename T>
	void Free (T* tp);
};

typedef MemAlloc<8 * 1024> MemAlloc8K;

class GEOMETRY_DLL_EXPORT MemAlloc8KThreadLocal : public GS::ThreadLocal<MemAlloc8K*, GS::ThreadLocal<MemAlloc8K*>::NullInitializator>
{
public:
	virtual	~MemAlloc8KThreadLocal ();
};

extern GEOMETRY_DLL_EXPORT MemAlloc8KThreadLocal memAlloc8KThreadLocal;


#include "MemAllocImp.hpp"

}	// namespace QXTools

#endif
