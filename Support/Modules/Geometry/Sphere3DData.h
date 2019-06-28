#if !defined (SPHERE3DDATA_H)
#define SPHERE3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"

/****************************************************************************/
/*																			*/
/*					3D Sphere and its operations							*/
/*																			*/
/****************************************************************************/


typedef struct {
	Coord3D	o;			/* Origin	*/
	double	r;			/* Radius	*/
} Sphere3D;


struct Sector3D;

namespace Geometry {

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSphereLine3D (const Sphere3D	*sp,
					   const Sector3D	*s,
					   Sector3D			*xs);

}

#endif
