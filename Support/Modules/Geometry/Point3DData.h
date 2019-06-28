/****************************************************************************/
/*																			*/
/*					3D Point, Vector and their operations					*/
/*																			*/
/****************************************************************************/


#if !defined (POINT3DDATA_H)
#define POINT3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2DData.h"
#include "Coord3d.h"

namespace Geometry {

/* coord */
GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVCoord3D (GS::PlatformSign inplatform, Coord3D *c3);

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	SetCoord3D (const Coord* pC, const double z);		/*vv73*/

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	SetCoord3D (const Coord& c, const double z = 0);

GEOMETRY_DLL_EXPORT Coord	GEOM_CALL	SetCoord2D (const Coord3D* pC);

GEOMETRY_DLL_EXPORT Coord	GEOM_CALL	SetCoord2D (const Coord3D& pC);

GEOMETRY_DLL_EXPORT Coord	GEOM_CALL	SetCoord2D (const double x, const double y);

GEOMETRY_DLL_EXPORT double	GEOM_CALL	Dist3D (const Coord3D& c1, const Coord3D& c2);

GEOMETRY_DLL_EXPORT double	GEOM_CALL	TetraVolume (const Coord3D* p1, const Coord3D* p2, const Coord3D* p3, const Coord3D* p4);

GEOMETRY_DLL_EXPORT void	GEOM_CALL	MatProdVect (Int32 n, double* mat, double* vect, double* newv);

/* vector */
GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	SetVector3D (const Vector2d& c, const double z = 0);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	NegVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT Vector3D*	GEOM_CALL	SetVectorPtr3D (Vector3D *w,double x, double y, double z);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	AddVector3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	SubVector3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT double	GEOM_CALL	LenVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT double	GEOM_CALL	LenSqrVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsUnitVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	UnitVector3D (const Vector3D& v);			/* sm041 */

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	StrictUnitVector3D (Vector3D* v);

inline				double		MulsVectors3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	MulVector3D (const Vector3D& v, double r);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	MulvVectors3D (const Vector3D& a, const Vector3D& b);

GEOMETRY_DLL_EXPORT double	GEOM_CALL	UnitVectorPtr3D (const Vector3D *v, Vector3D *w);

GEOMETRY_DLL_EXPORT Vector3D*	GEOM_CALL	SubVectorPtr3D (const Vector3D *v1, const Vector3D *v2, Vector3D *w);

GEOMETRY_DLL_EXPORT Vector3D*	GEOM_CALL	MulVectorPtr3D (const Vector3D *v, double r, Vector3D *w);

GEOMETRY_DLL_EXPORT Coord3D		GEOM_CALL MiddleCoord3D (const Coord3D* a, const Coord3D* b);

GEOMETRY_DLL_EXPORT Vector3D*	GEOM_CALL	MulvVectorsPtr3D (const Vector3D *a, const Vector3D *b, Vector3D *w);

inline				Vector3D*	LinePt3D (const Coord3D& r0, const Vector3D& e, double lambda, Coord3D *pp);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsEqualCoordPtr3D (const Coord3D *c1, const Coord3D *c2);		/*vv73*/

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsEqualCoordPtr3D (const Coord3D &c1, const Coord3D &c2);		/*vv73*/

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsColinVectors3D (Vector3D v1, Vector3D v2);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	PolarCoord3D (double r, double fi, double theta);

GEOMETRY_DLL_EXPORT double	GEOM_CALL	GetVector3DAngle (const Vector3D& v1);
GEOMETRY_DLL_EXPORT double	GEOM_CALL	GetVectors3DAngle (const Vector3D& v1, const Vector3D& v2);
GEOMETRY_DLL_EXPORT double	GEOM_CALL	CalcRTAngleAndRTAxis (Vector3D a, Vector3D b, Vector3D & rtAxis); //angle for rotating a to b
// creates an orthogonal vector
GEOMETRY_DLL_EXPORT Vector3D GEOM_CALL	GetOrthogonalVector3D (const Vector3D& in_vect);

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL InterpolateCoord3D (const Coord3D& a, const Coord3D& b, double ratio);

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	RotCoord3D (
						const Coord3D*	oc,
						const Coord3D*	wc,
						double			si,
						double			co);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	NormVectorUnitPtr3D (const Vector3D *p1, Vector3D *p2, Vector3D *pp);

GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMRotateVect (
						double rx, double ry, double rz, double alpha,
						double *x, double *y, double *z);

GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMRotatePoint (double vx, double vy, double vz,
						double rx, double ry, double rz, double alpha,
						double *px, double *py, double *pz);

GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Coord3D (GS::PlatformSign inplatform, F_Coord3D *c);
GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Coord3D (GS::PlatformSign inplatform, GS::PlatformSign toplatform, F_Coord3D *c);

GEOMETRY_DLL_EXPORT bool	IsEqualCoord3D (const Coord3D& c1, const Coord3D& c2);
GEOMETRY_DLL_EXPORT bool	IsEqualCoord3D (const Coord3D& c1, const Coord3D& c2, double epsilon);
GEOMETRY_DLL_EXPORT double	Dist3DSqr (const Coord3D& c1, const Coord3D& c2);

GEOMETRY_DLL_EXPORT bool	AreParallelVectors (const Vector3D& v1, const Vector3D& v2);

}

inline double Geometry::MulsVectors3D (const Vector3D& v1, const Vector3D& v2)
{
	return v1 * v2;
}

inline Vector3D* Geometry::LinePt3D (const Coord3D& r0, const Vector3D& e, double lambda, Coord3D *pp)
{
	pp->x = r0.x + lambda * e.x;
	pp->y = r0.y + lambda * e.y;
	pp->z = r0.z + lambda * e.z;
	return pp;
}

#endif
