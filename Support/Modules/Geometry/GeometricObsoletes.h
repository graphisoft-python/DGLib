// *****************************************************************************
// Obsolete functions in Geometry
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (GEOMETRICOBSOLETES_H)
#define GEOMETRICOBSOLETES_H

#pragma once

#include "GeometricDefinitions.h"
#include "Box2DData.h"

struct PolyArcRec;

namespace Geometry {


inline double	DistCPtr (const Coord* c1, const Coord* c2)
{
	return Dist (*c1, *c2);
}


inline double	ComputeFiPtr (const Coord* c1, const Coord* c2)
{
	return ComputeFi (*c1, *c2);
}


inline double	LenVectorPtr (const Vector* v)
{
	return LenVector (*v);
}


inline Sector	SetSectorCPtr (const Coord* c1, const Coord* c2)
{
	return SetSector (*c1, *c2);
}


inline bool		CoordInBox(const Coord& c, const Box2DData& b, double eps)
{
	return IsBoxPointIntersect (b, c, Geometry::Boundary_Closed, (eps));
}

}	// namespace Geometry

GEOMETRY_DLL_EXPORT bool GEOM_CALL CUClipPoly (Box2DData *clip,
					Int32 ipa, Int32 *parts,
					Int32 ipb, UInt32 *pends,
					Int32 ipc, double *pcoos,
					Int32 *jpa, Int32 **cparts,
					Int32 *jpb, UInt32 **cpends,
					Int32 *jpc, double **cpcoos,
					Int32 *wrcode);

namespace Geometry {

#define OutsidePoly		0		/* CoordInPoly Return values	*/
#define InsidePoly		1
#define OnPolyEdge		2

	GEOMETRY_DLL_EXPORT void GEOM_CALL GetOriandAngle(						/* RJ003 */
			const	PolyArcRec*	arcP,	/* fgy032 */
			Int32				arcInd,
			const Coord*		c1,
			const Coord*		c2,
			Coord*				ori,
			double*				fi);

	GEOMETRY_DLL_EXPORT void GEOM_CALL Arc_Extent_Dir(const Coord   *origo,
						const Coord	*firstP,
						const Coord	*lastP,
						double  angle,
						double  radius,
						double	*miny,
						double	*maxy,
						double	*minx,
						double	*maxx,
						char    *arcFirstDir,
						char    *arcSecondDir);

	GEOMETRY_DLL_EXPORT short GEOM_CALL Check_CoordInPoly (Int32			nSubPolys,
						 Int32					nArcs,
						 const Coord			*myPolyCoordsPtr,
						 const Int32			*mySubPolyEndsPtr,
						 const PolyArcRec		*myPolyArcsPtr,
						 const Coord			*theCoord,
						 Int32					*coordIndex);
}

#define DistCPtr3D(c1, c2) Dist3D (*(c1), *(c2))

#define MulsVectorsPtr3D(v1, v2) MulsVectors3D (*(v1), *(v2))

#define LenVectorPtr3D(v) LenVector3D (*(v))

#define GetVectorsPtr3DAngle(v1, v2) GetVectors3DAngle (*(v1), *(v2))

#endif
