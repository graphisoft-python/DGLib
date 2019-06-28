/****************************************************************************/
/*																			*/
/*								GSPixMap DEFINITION							*/
/*																			*/
/****************************************************************************/

#ifndef	_GSPix_H_
#define	_GSPix_H_

#pragma once

#include "Color.hpp"
#include "GSRoot.hpp"
#include "PatternExport.h"

// This struct must be the same, as the RGBColor struct in the Mac Headers
struct GS_RGBColor {
	unsigned short red;                 /*magnitude of red component*/
	unsigned short green;               /*magnitude of green component*/
	unsigned short blue;                /*magnitude of blue component*/
};


inline GSErrCode	ReadRGBColor  (GS::IChannel& ic, GS_RGBColor& obj)
{
	ic.Read (obj.red);
	ic.Read (obj.green);
	ic.Read (obj.blue);

	return ic.GetInputStatus ();
}


inline GSErrCode	WriteRGBColor (GS::OChannel& oc, const GS_RGBColor& obj)
{
	oc.Write (obj.red);
	oc.Write (obj.green);
	oc.Write (obj.blue);

	return oc.GetOutputStatus ();
}

PATTERN_DLL_EXPORT GSErrCode WriteXMLRGB (GS::XMLOChannel& oc, const char* tagName, const GS_RGBColor& rgb);
PATTERN_DLL_EXPORT GSErrCode ReadXMLRGB (GS::XMLIChannel& ic, const char* tagName, GS_RGBColor& rgb);

inline GSErrCode 	ReadXMLRGB (GS::XMLIChannel& ic, GS_RGBColor& rgb)									{ return ReadXMLRGB(ic, "RGBColor", rgb); }
inline GSErrCode 	WriteXMLRGB (GS::XMLOChannel& oc, const GS_RGBColor& rgb)							{ return WriteXMLRGB (oc, "RGBColor", rgb); }

namespace GS {
	inline GSErrCode 	ReadXML (GS::XMLIChannel& ic, GS_RGBColor& rgb)										{ return ReadXMLRGB(ic, rgb); }
	inline GSErrCode 	WriteXML (GS::XMLOChannel& oc, const GS_RGBColor& rgb)								{ return WriteXMLRGB (oc, rgb); }
	inline GSErrCode 	ReadXML (GS::XMLIChannel& ic, const char* tagName, GS_RGBColor& rgb)				{ return ReadXMLRGB(ic, tagName, rgb); }
	inline GSErrCode 	WriteXML (GS::XMLOChannel& oc, const char* tagName, const GS_RGBColor& rgb)			{ return WriteXMLRGB (oc, tagName, rgb); }
}

inline bool operator== (const GS_RGBColor& rgbColor1, const GS_RGBColor& rgbColor2)
{
	if (rgbColor1.red != rgbColor2.red)
		return false;
	if (rgbColor1.green != rgbColor2.green)
		return false;
	if (rgbColor1.blue != rgbColor2.blue)
		return false;
	return true;
}


inline bool operator!= (const GS_RGBColor& rgbColor1, const GS_RGBColor& rgbColor2)
{
	return !(rgbColor1 == rgbColor2);
}


struct GX_ARGBColor {
	static const unsigned char MAXVAL = 255;	// for a valid color, all component holds a value between 0 and MAXVAL

	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
};


/*-- GSPattern --*/
struct GSPattern {
	unsigned char pat[8];

	explicit GSPattern ()
	{
		memset (pat, 0, 8*sizeof (unsigned char));
	}

	GSPattern (unsigned char p0, unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4, unsigned char p5, unsigned char p6, unsigned char p7)
	{
		pat[0] = p0; pat[1] = p1; pat[2] = p2; pat[3] = p3;
		pat[4] = p4; pat[5] = p5; pat[6] = p6; pat[7] = p7;
	}

	GSPattern& operator= (const GSPattern& rhs)
	{
		if (this != &rhs)
			memcpy (pat, rhs.pat, 8*sizeof (unsigned char));

		return *this;
	}

	bool IsEmpty () const
	{
		return (*((UInt32*) &pat[0]) == 0x0) && (*((UInt32*) &pat[4]) == 0x0);
	}

	bool IsFull () const
	{
		return (*((UInt32*) &pat[0]) == 0xFFFFFFFF) && (*((UInt32*) &pat[4]) == 0xFFFFFFFF);
	}
};

struct GSPoint {
	Int32	v;
	Int32	h;
};

struct GSRect {
	Int32	top;
	Int32	left;
	Int32	bottom;
	Int32	right;

	bool operator== (const GSRect& other) const
	{
		return top == other.top &&
			left == other.left &&
			bottom == other.bottom &&
			right == other.right;
	}
};

enum GSPixelType {
	GSPT_ARGB	= 0,
	GSPT_ALongRGB,			// internal usage
	GSPT_BlackWhite,
	GSPT_256Gray,
	GSPT_Unknown
};

/*
 The structure of the GSPixMap:
	- the header (GSPixMap structure)
	- the pixel information (it is always 32 bit/pixel)
*/

struct GSPixMap;

typedef struct GSPixMap GSPixMap;

typedef GSPixMap **GSPixMapHandle;

PATTERN_DLL_EXPORT Gfx::Color	GS_RGBColorToGfxColor (const GS_RGBColor& rgbColor);
PATTERN_DLL_EXPORT GS_RGBColor	GfxColorToGS_RGBColor (const Gfx::Color& gfxColor);

#endif
