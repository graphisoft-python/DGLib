// -----------------------------------------------------------------------------
// Windows specific (DIB) PROTOTYPES for GSPixMap
// -----------------------------------------------------------------------------
#if !defined (GRAPHICS2DWIN_H)
#define GRAPHICS2DWIN_H

#pragma once

#include	<stdio.h>
#include	<string.h>

#include	"GXExport.h"

#include	"GSPix.h"
#include	"Graphics2D.h"
#include	"Win32Interface.hpp"	// We need it because of windows.h and we need the define magic


#define	DIBROWBYTES(pixels, width)	(4 * (((Int32) (pixels) * (Int32) (width) + 31) / 32))

namespace Gdiplus {
	class Image;
}

GX_DLL_EXPORT
GSPixMapHandle GX_CALL GraphicsToGSPixMap (Gdiplus::Image *image, GSPixelType pFormat = GSPT_Unknown);

GX_DLL_EXPORT
GSPixelType GX_CALL GetGraphicsPixelType (Gdiplus::Image *image);

GX_DLL_EXPORT
Gdiplus::Image* GX_CALL PixMapToGdiPlusImage (GSPixMapHandle pHdl);

GX_DLL_EXPORT
GSErr	GX_CALL	GXGSPixMap2DIB (
						GSPixMapHandle	pixMap,
						const GSRect*	partRect,
						GSPtr*			bitmapInfo,
						Int32*			bmpSize = nullptr);

GX_DLL_EXPORT
GSErr	GX_CALL	GXDIB2GSPixMap (GSPtr bitmapInfo, Int32 dibSize, GSPixMapHandle* pixMap);

GX_DLL_EXPORT
GSErr	GX_CALL GXDIBSection2PixMap (GSPtr dibSection, GSPixMapHandle *hPixMap);

GX_DLL_EXPORT
Int32		GX_CALL CGXConvertBitmap (GSPtr* dstBmp, short dstDepth, const GSPtr srcBmp, bool dither, bool defColTab);

GX_DLL_EXPORT
GSHandle	GX_CALL CGXCreatePalette (const GSPtr pBmpPtr);

GX_DLL_EXPORT
GSErr	GX_CALL	GXDDB2GSPixMap (HDC hdc, HBITMAP hBmp, GSPixMapHandle* pixMap, GSRect* rect = nullptr);

GX_DLL_EXPORT
GSErr	GX_CALL	GXDDB2DIB (HDC hDC, HBITMAP hBmp, GSPtr* pDIB, Int32* pSize, GSRect* rect = nullptr);

GX_DLL_EXPORT
BOOL	GX_CALL GXGetDIBInfo (BITMAPINFO *dibPtr, Int32 *pnColors, RECT *pBiRect, Int32 *pRowBytes,
					  Int32 *pHeadSize, Int32 *pBiSizeImage, Int32 *pBiFullSize);



GX_DLL_EXPORT
GSErr	GX_CALL	CreateBMIFromGSPixMap (GSPixMapHandle pixmapHdl, BITMAPINFO** ppBmp, bool bitfield32);

GX_DLL_EXPORT
GSErr	GX_CALL	GXDrawGSPixMapPartOnHDC (HDC hDC,
										 GSPixMapHandle pixMap,
										 const GSRect& srcRect,
										 const GSRect& dstRect,
										 bool withDither = true,
										 bool useDefaultColorTable = false,
										 AlphaChannelUsage acUsage = CopyAlphaChannel);

#endif
