// *********************************************************************************************************************
// Description:		GRAPHISOFT Basic Type Conversion
//
// Namespace:		-
// Contact person:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (IV_HPP)
#define	IV_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"GSRootExport.hpp"

// =====================================================================================================================
// Inline helper funtions
// =====================================================================================================================

GSROOT_DLL_EXPORT bool GSCALL NeedByteSwap (GS::PlatformSign platformSign);

GSROOT_DLL_EXPORT void GSCALL IVBool (GS::PlatformSign platform, bool* pBool);
GSROOT_DLL_EXPORT void GSCALL IVSByte (GS::PlatformSign platform, char* pSByte);
GSROOT_DLL_EXPORT void GSCALL IVUByte (GS::PlatformSign platform, unsigned char* pUByte);
GSROOT_DLL_EXPORT void GSCALL IVShort (GS::PlatformSign platform, short* pShort);
GSROOT_DLL_EXPORT void GSCALL IVUShort (GS::PlatformSign platform, unsigned short *pUShort);
GSROOT_DLL_EXPORT void GSCALL IVLong (GS::PlatformSign platform, Int32 *pLong);
GSROOT_DLL_EXPORT void GSCALL IVULong (GS::PlatformSign platform, UInt32 *pULong);
GSROOT_DLL_EXPORT void GSCALL IVInt64 (GS::PlatformSign platform, Int64 *pInt64);
GSROOT_DLL_EXPORT void GSCALL IVUInt64 (GS::PlatformSign platform, UInt64 *pUInt64);
GSROOT_DLL_EXPORT void GSCALL IVFloat (GS::PlatformSign platform, float *pFloat);
GSROOT_DLL_EXPORT void GSCALL IVDouble (GS::PlatformSign platform, double *pDouble);
GSROOT_DLL_EXPORT void GSCALL IVUString (GS::PlatformSign platform, GS::uchar_t* pUString, UInt32 stringLength);

GSROOT_DLL_EXPORT void GSCALL IVBools (GS::PlatformSign platform,bool* pBool, Int32 nBools);
GSROOT_DLL_EXPORT void GSCALL IVSBytes (GS::PlatformSign platform,char* pSByte, Int32 nSBytes);
GSROOT_DLL_EXPORT void GSCALL IVUBytes (GS::PlatformSign platform,unsigned char* pUByte, Int32 nUBytes);
GSROOT_DLL_EXPORT void GSCALL IVShorts (GS::PlatformSign platform,short* pShort, Int32 nShorts);
GSROOT_DLL_EXPORT void GSCALL IVUShorts (GS::PlatformSign platform,unsigned short *pUShort, Int32 nUShorts);
GSROOT_DLL_EXPORT void GSCALL IVLongs (GS::PlatformSign platform,Int32 *pLong, Int32 nLongs);
GSROOT_DLL_EXPORT void GSCALL IVULongs (GS::PlatformSign platform,UInt32 *pULong, Int32 nULongs);
GSROOT_DLL_EXPORT void GSCALL IVInt64s (GS::PlatformSign platform,Int64 *pInt64, Int32 nInt64s);
GSROOT_DLL_EXPORT void GSCALL IVUInt64s (GS::PlatformSign platform,UInt64 *pUInt64, Int32 nUInt64s);
GSROOT_DLL_EXPORT void GSCALL IVFloats (GS::PlatformSign platform,float *pFloat, Int32 nFloats);
GSROOT_DLL_EXPORT void GSCALL IVDoubles (GS::PlatformSign platform,double *pDouble, Int32 nDoubles);

GSROOT_DLL_EXPORT void GSCALL IVBool (GS::PlatformSign from, GS::PlatformSign to, bool* pBool);
GSROOT_DLL_EXPORT void GSCALL IVSByte (GS::PlatformSign from, GS::PlatformSign to, char* pSByte);
GSROOT_DLL_EXPORT void GSCALL IVUByte (GS::PlatformSign from, GS::PlatformSign to, unsigned char* pUByte);
GSROOT_DLL_EXPORT void GSCALL IVShort (GS::PlatformSign from, GS::PlatformSign to, short* pShort);
GSROOT_DLL_EXPORT void GSCALL IVUShort (GS::PlatformSign from, GS::PlatformSign to, unsigned short *pUShort);
GSROOT_DLL_EXPORT void GSCALL IVLong (GS::PlatformSign from, GS::PlatformSign to, Int32 *pLong);
GSROOT_DLL_EXPORT void GSCALL IVULong (GS::PlatformSign from, GS::PlatformSign to, UInt32 *pULong);
GSROOT_DLL_EXPORT void GSCALL IVInt64 (GS::PlatformSign from, GS::PlatformSign to, Int64 *pInt64);
GSROOT_DLL_EXPORT void GSCALL IVUInt64 (GS::PlatformSign from, GS::PlatformSign to, UInt64 *pUInt64);
GSROOT_DLL_EXPORT void GSCALL IVFloat (GS::PlatformSign from, GS::PlatformSign to, float *pFloat);
GSROOT_DLL_EXPORT void GSCALL IVDouble (GS::PlatformSign from, GS::PlatformSign to, double *pDouble);
GSROOT_DLL_EXPORT void GSCALL IVUString (GS::PlatformSign from, GS::PlatformSign to, GS::uchar_t* pUString, UInt32 stringLength);

GSROOT_DLL_EXPORT void GSCALL IVBools (GS::PlatformSign from, GS::PlatformSign to, bool* pBool, Int32 nBools);
GSROOT_DLL_EXPORT void GSCALL IVSBytes (GS::PlatformSign from, GS::PlatformSign to, char* pSByte, Int32 nSBytes);
GSROOT_DLL_EXPORT void GSCALL IVUBytes (GS::PlatformSign from, GS::PlatformSign to, unsigned char* pUByte, Int32 nUBytes);
GSROOT_DLL_EXPORT void GSCALL IVShorts (GS::PlatformSign from, GS::PlatformSign to, short* pShort, Int32 nShorts);
GSROOT_DLL_EXPORT void GSCALL IVUShorts (GS::PlatformSign from, GS::PlatformSign to, unsigned short *pUShort, Int32 nUShorts);
GSROOT_DLL_EXPORT void GSCALL IVLongs (GS::PlatformSign from, GS::PlatformSign to, Int32 *pLong, Int32 nLongs);
GSROOT_DLL_EXPORT void GSCALL IVULongs (GS::PlatformSign from, GS::PlatformSign to, UInt32 *pULong, Int32 nULongs);
GSROOT_DLL_EXPORT void GSCALL IVInt64s (GS::PlatformSign from, GS::PlatformSign to, Int64 *pInt64, Int32 nInt64s);
GSROOT_DLL_EXPORT void GSCALL IVUInt64s (GS::PlatformSign from, GS::PlatformSign to, UInt64 *pUInt64, Int32 nUInt64s);
GSROOT_DLL_EXPORT void GSCALL IVFloats (GS::PlatformSign from, GS::PlatformSign to, float *pFloat, Int32 nFloats);
GSROOT_DLL_EXPORT void GSCALL IVDoubles (GS::PlatformSign from, GS::PlatformSign to, double *pDouble, Int32 nDoubles);

#endif
