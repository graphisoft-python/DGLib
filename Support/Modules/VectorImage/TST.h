// *****************************************************************************
//
// GDL / Text Style Table functions
//
// Contact person: FE
//
// *****************************************************************************

#ifndef _TST_H_
#define _TST_H_

#pragma once

#include	"GSRoot.hpp"
#include	"VectorImageExport.h"

#if defined (__cplusplus)
extern "C" {
#endif

// -----------------------------------------------------------------------------

VI_DLL_EXPORT
GSErr	VI_CALL	TSTProcessCntlChars (const GS::UniString &instring, GS::UniString &outstring);

VI_DLL_EXPORT
void	VI_CALL	TSTGetDefaultFontName (GS::UniString& fontName, size_t size);

VI_DLL_EXPORT
double	VI_CALL	TSTGetTextLen (Int32			styleind,
							   const GS::UniString& lineStr);

VI_DLL_EXPORT
void	VI_CALL	TSTGetWordLoc (Coord		*theC,
							   Coord		*wCSquare,
							   short 		wCentre);

VI_DLL_EXPORT
GSErr	VI_CALL	TSTGetWordInfo (Int32 styleind,
								const char *text, short nChar,
								short *nLine, short **lstPtr, Int32 *lenLst,
								double *wordHeight, double *wordWidth);
VI_DLL_EXPORT
void	VI_CALL	TSTGetStyleInfo (const GS::UniString& fontname,
								 short		familytype,
								 double		face,
								 double		slant,
								 double		size,
								 double		*height,
								 double		*ascent,
								 double		*descent);

#if defined (__cplusplus)
}
#endif

#endif
