// -----------------------------------------------------------------------------
// Mac specific (PixMap, Picture) PROTOTYPES for GSPixMap
// -----------------------------------------------------------------------------
#if !defined (GRAPHICS2DMAC_H)
#define GRAPHICS2DMAC_H

#pragma once

#ifndef	GXEXPORT_H
	#include	"GXExport.h"
#endif

#include <ApplicationServices/ApplicationServices.h>

struct Rect;

#include	"GSPix.h"
#include	"Graphics2D.h"


GX_DLL_EXPORT
GSErr GX_CALL GXDrawGSPixMapPartOnCGContext (CGContextRef gc, GSPixMapHandle pixMap, const GSRect& srcRect, const GSRect& destRect,
											 Int32 cgContextHeight, AlphaChannelUsage acUsage = CopyAlphaChannel);

enum GXImageOwneship {
	GXImageCopyData,
	GXImageTakeOwnership,
	GXImageReferData
};

GX_DLL_EXPORT
CGImageRef GX_CALL GXImageCreateFromGSPixMap (GSPixMapHandle source,
                                              const GSRect* srcRectP = nullptr,
                                              GXImageOwneship pixMapOwnership = GXImageCopyData,
                                              Int32 depth = 0);

#endif
