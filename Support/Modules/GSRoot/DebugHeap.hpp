// *********************************************************************************************************************
// Description:		C Runtime heap management with built-in debugging support
//
// Module:			GSRoot
// Namespace:		DebugHeap
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#if !defined (DEBUGHEAP_HPP)
#define DEBUGHEAP_HPP

#pragma once


#if defined (HEAP_DEBUG)

// --- Includes	--------------------------------------------------------------------------------------------------------

// from C/C++ Runtime Library
#include	<stddef.h>

// from GSRoot
#include 	"GSRootExport.hpp"
#include 	"Definitions.hpp"

#if defined (WINDOWS)
#include	"Win32Interface.hpp"
#endif

#if defined(_MSC_VER)
#pragma push_macro("calloc")
#pragma push_macro("malloc")
#pragma push_macro("free")
#pragma push_macro("realloc")
#endif
#undef calloc
#undef malloc
#undef free
#undef realloc

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace DebugHeap {

// --- Constant definitions	--------------------------------------------------------------------------------------------

enum {
	Dump_ClientBlocks	= 0x00000001,
	Dump_FreeBlocks		= 0x00000002,
	Dump_CRTBlocks		= 0x00000004,
	Dump_NormalBlocks	= 0x00000008,

	Dump_SmallBlocks	= 0x00000010,
	Dump_Stack			= 0x00000020,

	Dump_Append			= 0x10000000,

	Dump_Default		= Dump_ClientBlocks | Dump_NormalBlocks,
	Dump_Full			= Dump_ClientBlocks | Dump_NormalBlocks | Dump_SmallBlocks | Dump_Stack
};

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

void GSCALL	init (void);
void GSCALL	terminate (void);

GSROOT_DLL_EXPORT	void		GSCALL	addmodule (const void* loadAddress, const char* pathName);
GSROOT_DLL_EXPORT	GS::UIntPtr	GSCALL	GetUsageDebugInfo ();
GSROOT_DLL_EXPORT	void		GSCALL	setuserdata (GS::IntPtr uData, const char* datadescription);
#if defined (WINDOWS)
GSROOT_DLL_EXPORT	void		GSCALL	addmodule (const void* loadAddress, const WCHAR* pathName);
GSROOT_DLL_EXPORT	void		GSCALL	removemodule (const WCHAR* pathName);
GSROOT_DLL_EXPORT	void		GSCALL	setuserdata (GS::IntPtr uData, const WCHAR* datadescription);
#endif

GSROOT_DLL_EXPORT	void*		GSCALL	calloc (size_t num, size_t size);
GSROOT_DLL_EXPORT	void*		GSCALL	malloc (size_t size);
GSROOT_DLL_EXPORT	void		GSCALL	free (void *userData);
GSROOT_DLL_EXPORT	void*		GSCALL	realloc (void *userData, size_t newSize);
GSROOT_DLL_EXPORT	size_t		GSCALL	msize (void *userData);
GSROOT_DLL_EXPORT	int			GSCALL	heapchk (void);

GSROOT_DLL_EXPORT	bool		GSCALL	isValidHeapPointer (const void* userData);
GSROOT_DLL_EXPORT	void		GSCALL	dump (
											const char*		fileName,
											UInt32			dumpFlags = Dump_Default,
											UInt32			minBlockSize = 0,
											Int32			maxBlockSize = -1
										);
#if defined (WINDOWS)
GSROOT_DLL_EXPORT	void		GSCALL	dump (
											const WCHAR*	fileName,
											UInt32			dumpFlags = Dump_Default,
											UInt32			minBlockSize = 0,
											Int32			maxBlockSize = -1
										);
#endif

GSROOT_DLL_EXPORT	void		GSCALL	dumpInfo (void* userData);

GSROOT_DLL_EXPORT	void		GSCALL	SetStackMaxDepth (UInt16 newStackMaxDepth);
GSROOT_DLL_EXPORT	UInt16		GSCALL	GetStackMaxDepth (void);

GSROOT_DLL_EXPORT	void		GSCALL	AddLeakFilterString (const char* filterString);
#if defined (WINDOWS)
GSROOT_DLL_EXPORT	void		GSCALL	AddLeakFilterString (const WCHAR* filterString);
#endif
}	// namespace DebugHeap

#if defined(_MSC_VER)
#pragma pop_macro("calloc")
#pragma pop_macro("malloc")
#pragma pop_macro("free")
#pragma pop_macro("realloc")
#endif

#endif	// HEAP_DEBUG

#endif
