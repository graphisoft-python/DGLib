// *********************************************************************************************************************
// File:			ConvRichText.h
//
// Description:		Converts Sy_RichText to VBUtils::RichText
//
// Namespace:
//
// Contact person:	BA, HK
//
// SG compatible
// *********************************************************************************************************************

#ifndef CONVRICHTEXT_HPP
#define CONVRICHTEXT_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include	"GSModeler2DExport.h"
#include	"GDL.h"

// --- Predeclarations -------------------------------------------------------------------------------------------------

class  Sy_RichTextType;

namespace   VBUtil {
	class   RichText;
}

namespace GS {
	template<class T> class VAArray;
};

GSMODELER2D_DLL_EXPORT
GSErrCode   GSM2D_CALL  CopySyRichText2VBUtilsRichText (
								const Sy_RichTextType*			rt,
								VBUtil::RichText*				vbRichText,
								bool							storePenIndasUserData = false);

GSMODELER2D_DLL_EXPORT
GSErrCode   GSM2D_CALL  CopyVBUtilsRichText2SyRichText (
								VBUtil::RichText&			vbRichText,
								Sy_RichTextType**			pRT,
								char**						pP);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL		GenRichText (
				VBUtil::RichText*						richText,
				bool									b3D,
				double*									plotscale,
				const GdlTextBlockData*					textBlockData,
				const GS::VAArray<GdlParagraphData>*	paragraphs,
				const GSHandle							tabsHdl,		// double
				const GS::VAArray<GdlStringData>*		stringsData,
				const GSHandle							stringsHdl);		// char

GSMODELER2D_DLL_EXPORT
void		GSM2D_CALL CalculateRichTextLocation (short anchor, double tlength, double theight, double* offsx, double* offsy);

#endif
