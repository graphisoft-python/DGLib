// *********************************************************************************************************************
// VectorRefComparator compiler environment
//
// Module:			GSATLib
// Namespace:		-
// Contact person:
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (GSATLIB_EXPORT_HPP)
#define GSATLIB_EXPORT_HPP

#pragma once

#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

#include "PlatformDLLExport.hpp"

#if defined (GSATLIB_DLL_COMPILE)
	#define GSATLIB_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#if defined (GSATCONSOLE_COMPILE)
		#define GSATLIB_DLL_EXPORT	PLATFORM_DLL_IMPORT
	#else
		#define GSATLIB_DLL_EXPORT
	#endif
#endif

#endif // GSATLIB_EXPORT_HPP