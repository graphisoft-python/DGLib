// *****************************************************************************
// C style struct for 2D Vectors and Points
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (POINT2DDATA_H)
#define POINT2DDATA_H

#pragma once


#include <math.h>

#include "GeometricDefinitions.h"
#include "Real.hpp"
#include "Coord.h"

namespace GS {
	class IChannel;
	class OChannel;
}

namespace Geometry {

	inline				Coord	SetCoord (double x, double y);

	inline				Coord*	SetCoordPtr (Coord *pC, double x, double y);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL PolarCoord (const Coord* origo, double r, double a);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL ToGlobalCoords (const Coord& localOrigo, const Vector& localDirection, const Coord& localRep);


	inline				bool	IsEqualCoord (const Coord& c1, const Coord& c2, double epsilon);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL IsColinVectors (const Vector& v1, const Vector& v2);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL IVCoord (GS::PlatformSign inplatform, Coord *c);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL IVCoord (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Coord *c);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL IVVector (GS::PlatformSign inplatform, Vector *v);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL IVVector (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Vector *v);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL GrowCoord (const Coord&	origo, Coord *c, double factor);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL RotCoord (const Coord *oc, const Coord	*wc, double si, double co);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL RotCoord (const Coord &oc, const Coord	&wc, double si, double co);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL RotCoord0 (const Coord* wc, double si, double co);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL RotCoord0 (const Coord& wc, double si, double co);

	inline				double	Dist (const Coord&	c1, const Coord& c2);

	inline				double	DistSqr (const Coord& c1, const Coord& c2);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL ComputeFi (const Coord& c1, const Coord& c2);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL CalcRotFi (double 	a1, double	a2, bool	negArc);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL ComputeRotFi (const Coord* o, const Coord* c1, const Coord* c2, bool negArc);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL ComputeRotFi (const Coord& o, const Coord& c1, const Coord& c2, bool negArc);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL GetVectorsRelAngle (const Vector& a1, const Vector& a2);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL GetCornerAngle (const Coord& o, const Coord& c1, const Coord& c2);


	GEOMETRY_DLL_EXPORT double	GEOM_CALL LenVector (const Vector& v);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL LenSqrVector (const Vector& v);

	GEOMETRY_DLL_EXPORT Vector	GEOM_CALL UnitVector (const Vector& v);

	GEOMETRY_DLL_EXPORT Vector*	GEOM_CALL UnitVectorPtr (Vector* pU, const Vector	*pV);

	GEOMETRY_DLL_EXPORT Vector	GEOM_CALL NormVector (const Vector& v);
	GEOMETRY_DLL_EXPORT Vector	GEOM_CALL Rot90CW (const Vector& v);	//clockwise rotation with 90 degree
	GEOMETRY_DLL_EXPORT Vector	GEOM_CALL Rot90ACW (const Vector& v);	//anti clockwise rotation with 90 degree

	GEOMETRY_DLL_EXPORT Vector*	GEOM_CALL AddVectorPtr (Vector* pU, const Vector	*pV1, const Vector	*pV2);

	GEOMETRY_DLL_EXPORT Vector*	GEOM_CALL SubVectorPtr (Vector* pU, const Vector	*pV1, const Vector	*pV2);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL MulvVectors (const Vector& v1, const Vector& v2);

	GEOMETRY_DLL_EXPORT double	GEOM_CALL MulsVectors (const Vector& v1, const Vector& v2);

	GEOMETRY_DLL_EXPORT Vector	GEOM_CALL MulVector (const Vector& v, double r);

	GEOMETRY_DLL_EXPORT Vector*	GEOM_CALL MulVectorPtr (Vector* v, double	r);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL MiddleCoord (const Coord* a, const Coord* b);

	GEOMETRY_DLL_EXPORT Vector	GEOM_CALL SubPoint (const Coord& p1, const Coord& p2);

	GEOMETRY_DLL_EXPORT Coord	GEOM_CALL InterpolateCoord (const Coord& a, const Coord& b, double ratio);

	inline Coord SetCoord (double x, double y)
	{
		Coord	c;

		c.x = x;
		c.y = y;
		return c;
	}

	inline Coord* SetCoordPtr (Coord* pC, double x, double y)
	{
		pC->x = x;
		pC->y = y;
		return pC;
	}

	inline double DistSqr (const Coord& c1, const Coord& c2)
	{
		double		dx, dy;

		dx = c1.x - c2.x;
		dy = c1.y - c2.y;
		return dx * dx + dy * dy;
	}


	inline double Dist (const Coord& c1, const Coord& c2)
	{
		double		dx, dy;

		dx = c1.x - c2.x;
		dy = c1.y - c2.y;
		return sqrt(dx * dx + dy * dy);
	}


	inline bool IsEqualCoord (const Coord& c1, const Coord& c2, double epsilon)
	{
		return IsNearZero (DistSqr (c1, c2), epsilon * epsilon);
	}

}

	GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, Coord& coord);
	GEOMETRY_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const Coord& coord);

namespace Geometry {

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Coord (GS::PlatformSign inplatform, Point2f *c);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Coord (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Point2f *c);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Vector (GS::PlatformSign inplatform, Vector2f *v);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Vector (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Vector2f *v);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	F_CoordToCoord (Coord* dCo, const Point2f* fCo);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	CoordToF_Coord (Point2f* fCo, const Coord* dCo);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	GetExtremePointsOfPointSetByDir (const GS::Array<Coord>& pointSet, const Vector& direction, GS::Array<Coord>& minima, GS::Array<Coord>& maxima);

}

#endif
