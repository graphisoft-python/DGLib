/*==========================================================================**
**								GSModelerExport.h							**
**																			**
**			DEFINITIONS FOR EXPORTATION FROM THE GSMODELER MODULE			**
**==========================================================================*/

#ifndef	GSMODELEREXPORT_H
#define	GSMODELEREXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(GSMODELER_NOT_DLL)
	#define GSMODELER_DLL_EXPORT
	#define	GSM_CALL
#else
	#if defined (GSMODELER_DLL_COMPILE)
		#define GSMODELER_DLL_EXPORT	PLATFORM_DLL_EXPORT
	#else
		#define GSMODELER_DLL_EXPORT	PLATFORM_DLL_IMPORT
	#endif
	#if defined (_MSC_VER)
		#define	GSM_CALL	__fastcall
	#else
		#define	GSM_CALL
	#endif
#endif

#define GSModelerModulID 1000

#endif
