
#ifndef _GPUSTRUCTURES_HPP_
#define _GPUSTRUCTURES_HPP_

#include "GPUEnums.hpp"
#include "GraphixDefinitions.hpp"

namespace Graphix {

// NOTE: GL supports negtive values, while newer APIs don't...do your math!!!

struct GRAPHIX_DLL_EXPORT Origin
{
	uint32_t x, y, z;

	Origin ();
	Origin (uint32_t _x, uint32_t _y, uint32_t _z);
};

struct GRAPHIX_DLL_EXPORT Size
{
	uint32_t width;
	uint32_t height;
	uint32_t depth;

	Size ();
	Size (uint32_t _w, uint32_t _h, uint32_t _d);
};

struct GRAPHIX_DLL_EXPORT Region
{
	uint32_t x, y, z;
	uint32_t width, height, depth;

	Region ();
	Region (uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w, uint32_t _h, uint32_t _d);
};

class GRAPHIX_DLL_EXPORT Color
{
private:
	float v[4];

public:
	float& r = v[0];
	float& g = v[1];
	float& b = v[2];
	float& a = v[3];

	Color ();
	Color (const Color& other);
	Color (uint32_t abgr);
	Color (float red, float green, float blue, float alpha);

	Color& operator =(const Color& other);
	float& operator [](int index)		{ return v[index]; }
	float operator [](int index) const	{ return v[index]; }

	operator uint32_t () const;

	static const uint32_t Black = 0xff000000;
	static const uint32_t Red = 0xff0000ff;
	static const uint32_t Green = 0xff00ff00;
	static const uint32_t Blue = 0xffff0000;
};

struct GRAPHIX_DLL_EXPORT Rect
{
	uint32_t x, y;
	uint32_t width, height;

	Rect ();
};

struct GRAPHIX_DLL_EXPORT Viewport
{
	float x, y;
	float width, height;
	float znear, zfar;

	Viewport ();
};

}

#endif
