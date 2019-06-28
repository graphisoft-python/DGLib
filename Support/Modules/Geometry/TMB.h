// *****************************************************************************
// TMB routines.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#ifndef	_TMB_H_
#define	_TMB_H_

#pragma once

#include "GeometricDefinitions.h"
#include "Point3DData.h"


typedef struct BASTRAN {
	double	tmx[9];
} BASTRAN;				/* 72 */

namespace Geometry {

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBSet (BASTRAN *bastran, const COORD3 *e1, const COORD3 *e2, const COORD3 *e3);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBVect (const BASTRAN *bastran, const COORD3 *r, COORD3 *rr);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBCalcRottran (const COORD3 *t, double alpha, BASTRAN *rottran);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBRotate (BASTRAN *bastran, COORD3 *t, double alpha);
}

#endif
