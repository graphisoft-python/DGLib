// *********************************************************************************************************************
// Description:		MemAllocImp.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef	MEMALLOCIMP_HPP
#define	MEMALLOCIMP_HPP

template<int maxAllocBytes>
GS_FORCE_INLINE MemAlloc<maxAllocBytes>::MemAlloc ()
{
	memset (firstFreePointers, 0, sizeof (firstFreePointers));
}

template<int maxAllocBytes>
GS_FORCE_INLINE char* MemAlloc<maxAllocBytes>::Allocate (ULong nBytes)
{
	DBASSERT (nBytes <= maxAllocBytes);

	ULong index = (nBytes + Alignment - 1) / Alignment;
	void* ret = firstFreePointers[index];
	if (ret == nullptr)
		return MemAllocBase::Allocate (index * Alignment);

	firstFreePointers[index] = *(void**)ret;
	return (char*) ret;
}

template<int maxAllocBytes>
GS_FORCE_INLINE void MemAlloc<maxAllocBytes>::Free (char* mem, ULong nBytes)
{
	if (nBytes == 0)
		return;

#ifdef DEBUVERS
	memset (mem, 0xaf, nBytes);
#endif

	ULong index = (nBytes + Alignment - 1) / Alignment;
	*(void**)mem = firstFreePointers[index];
	firstFreePointers[index] = mem;
}

template<int maxAllocBytes>
template<typename T>
GS_FORCE_INLINE T* MemAlloc<maxAllocBytes>::Allocate ()
{
	return (T*) Allocate (sizeof (T));
}

template<int maxAllocBytes>
template<typename T>
GS_FORCE_INLINE void MemAlloc<maxAllocBytes>::Free (T* tp)
{
	Free ((char*) tp, sizeof (T));
}


#endif	// MEMALLOCIMP_HPP
