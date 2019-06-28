// *****************************************************************************
//
// GDL / Text Style Table definition
//
// Contact person: FE
//
// *****************************************************************************

#ifndef _TS_H_
#define _TS_H_

#pragma once

#include	"GSRoot.hpp"
#include	"TSProcs.h"
#include	"VectorImageExport.h"
#include	"Coord.h"
#include	"GSUserData.hpp"
#include	"GDLProc.h"

#if defined (__cplusplus)
extern "C" {
#endif

// -----------------------------------------------------------------------------

struct TSFontEnvir {
	CheckFontNameProc			*checkfontname;
	ProcessGDLCntlCharsProc		*processcntlchars;
	GetDefaultFontNameProc		*getdefaultfontname;
	GetTextLenProc				*gettextlen;
	GetStyleInfoProc			*getstyleinfo;
	GetWordInfoProc				*getwordinfo;
};

VI_DLL_EXPORT
GSErr	VI_CALL	TSInit (const TSFontEnvir& fontenvir);

#if defined(TARGET_RT_MAC_MACHO) && TARGET_RT_MAC_MACHO
#define TSExit TSExit_GS
#endif

VI_DLL_EXPORT
void	VI_CALL	TSExit (void);

VI_DLL_EXPORT StyleGenProc		TSStyleGen;
VI_DLL_EXPORT StyleDefCheckProc TSCheckStyleDef;
VI_DLL_EXPORT TextLenProc		TSTextLen;

VI_DLL_EXPORT
Int32	VI_CALL	TSPutDownStyle (short			familytype,
									const GS::UniString& fontname,
									unsigned char	face,
									char			centre,
									short			just,
									double			slant,
									double			size);


VI_DLL_EXPORT
GSErr	VI_CALL	TSPickUpStyle  (Int32			styleind,
									short			*familytype,
									GS::UniString*	fontname,
									unsigned char	*face,
									char			*centre,
									short			*just,
									double			*slant,
									double			*size);

VI_DLL_EXPORT
bool	VI_CALL	TSSearchStyle (short			familytype,
								   const GS::UniString& fontname,
								   unsigned char	face,
								   char				centre,
								   short			just,
								   double			slant,
								   double			size,
								   Int32				*styleind);


VI_DLL_EXPORT
GSErrCode	VI_CALL	TSWriteStyle  (GS::OChannel& oc, Int32 styleind);

VI_DLL_EXPORT
GSErrCode	VI_CALL	TSReadStyle  (GS::IChannel& ic, Int32 *styleind);

VI_DLL_EXPORT
short	VI_CALL	TSGetStyleNum (void);




VI_DLL_EXPORT
bool	VI_CALL	TSCheckFontName (const GS::UniString& fontname);

VI_DLL_EXPORT
GSErr	VI_CALL	TSProcessCntlChars (const GS::UniString &instring, GS::UniString &outstring);

VI_DLL_EXPORT
void	VI_CALL	TSGetDefaultFontName (GS::UniString& fontName, size_t size);

VI_DLL_EXPORT
double	VI_CALL	TSGetTextLen (Int32			styleind,
							  const GS::UniString& lineStr);

VI_DLL_EXPORT
void	VI_CALL	TSGetStyleInfo (const GS::UniString& fontname,
								short		familytype,
								double		face,
								double		slant,
								double		size,
								double		*height,
								double		*descent,
								double		*leading);
VI_DLL_EXPORT
GSErr	VI_CALL	TSGetWordInfo (Int32 styleind,
							   const char *text, short nChar,
							   short *nLine, short **lstPtr, Int32 *lenLst,
							   double *wordHeight, double *wordWidth);


#if defined (__cplusplus)
}
#endif

#endif
