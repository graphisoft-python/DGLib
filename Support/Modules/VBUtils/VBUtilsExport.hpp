// *********************************************************************************************************************
// VBUtils compiler environment
//
// Module:			VBUtils
// Namespace:		-
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (VBUTILSEXPORT_H)
#define VBUTILSEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp" // from GSRoot


// --- Export/Import directives ----------------------------------------------------------------------------------------


#if defined (VBUTILS_NOT_DLL)
	#define VBUTILS_DLL_EXPORT
#else
	#if defined (VBUTILS_DLL_COMPILE)
		#define VBUTILS_DLL_EXPORT	PLATFORM_DLL_EXPORT
	#else
		#define VBUTILS_DLL_EXPORT	PLATFORM_DLL_IMPORT
	#endif
#endif


#endif
