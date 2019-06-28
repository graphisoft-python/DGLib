#if !defined (TSPROCS_H)
#define TSPROCS_H

#ifndef	VECTORIMAGEEXPORT_H
	#include	"VectorImageExport.h"
#endif

extern "C" {

/* font/character functions [ */

typedef bool	VI_CALL	CheckFontNameProc (const GS::UniString& fontname);

typedef	GSErr	VI_CALL	ProcessGDLCntlCharsProc (const GS::UniString &instring, GS::UniString &outstring);

typedef void	VI_CALL	GetDefaultFontNameProc (GS::UniString& fontName, size_t size);
typedef double	VI_CALL	GetTextLenProc (Int32		styleind,
										const GS::UniString& lineStr);
typedef void	VI_CALL	GetStyleInfoProc (const GS::UniString& fontname,
										  short		familytype,
										  double	face,
										  double	slant,
										  double	size,
										  double	*height,
										  double	*ascent,
										  double	*descent);

typedef GSErr	VI_CALL	GetWordInfoProc (Int32 styleind,
										 const char *text, short nChar,
										 short *nLine, short **lstPtr, Int32 *lenLst,
										 double *wordHeight, double *wordWidth);

} /* extern "C" */

/* ] */

#endif
