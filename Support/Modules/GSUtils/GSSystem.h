/*==========================================================================**
**									GSUtils.h								**
**																			**
**					CONSTANTS, TYPES AND PROTOTYPES FOR GSUtils				**
**==========================================================================*/

/*
	Copyright � 1995-2018 by GRAPHISOFT
	All rights reserved.
	Any part of the GDL import library kit (including this file) may be used
	for any purpose only under a separate written permission.

	GRAPHISOFT SE manufacturer
	H-1399 Budapest 62, Pf. 660
	Phone: 36.1/437-3000 Fax: 36.1/437-3099
	E-mail: mail@graphisoft.hu

	GRAPHISOFT U.S. Inc. - distributor in the USA
	235 Kansas Street, Suite 200
	San Francisco, CA 94103
	Phone: 415/703 9777 Fax: 415/703 9770
	E-mail: techsupport@graphisoft.com
*/

#ifndef	GSSYSTEM_H
#define	GSSYSTEM_H

#pragma once

#if !defined (COMPROC_H)
#include	"comProc.h"
#endif

#ifndef	GSUTILSEXPORT_H
	#include	"GSUtilsExport.h"
#endif

/*---------------------------------------------------------------------------*/

GSUTILS_DLL_EXPORT
void GSU_CALL GSSysBeep ();
GSUTILS_DLL_EXPORT
void GSU_CALL GSRegisterSound (const GS::UniString& appName, const GS::UniString& soundPath, const GS::UniString& soundName, const GS::UniString& description, bool overWritesoundName);
GSUTILS_DLL_EXPORT
void GSU_CALL GSUnRegisterSound (const GS::UniString& appName, const GS::UniString& soundPath, const GS::UniString& soundName);
GSUTILS_DLL_EXPORT
void GSU_CALL GSPlaySound (const GS::UniString&	soundName);

#endif //GSSYSTEM_H
