/****************************************************************************/
/*																			*/
/*					3D Plane and its operations								*/
/*																			*/
/****************************************************************************/


#if !defined (PLANE3DDATA_H)
#define PLANE3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Circle2DData.h"

#include "Point3DData.h"
#include "Sector3DData.h"
#include "Ellipse2DData.h"


/* 3D plane equation (pa*x + pb*y + pc*z + pd = 0) */
struct PlaneEq {
	double		pa;
	double		pb;
	double		pc;
	double		pd;

	PlaneEq () : pa (0.0), pb (0.0), pc (0.0), pd (0.0) {}
	PlaneEq (double a, double b, double c, double d) : pa (a), pb (b), pc (c), pd (d) {}
	
	PlaneEq (const Vector3D& normalVector, const Coord3D& pointOnPlane)
		: pa (normalVector.x)
		, pb (normalVector.y)
		, pc (normalVector.z)
		, pd (-(normalVector * pointOnPlane))
	{ /* do nothing */ }
};


namespace Geometry {

class Plane;

struct Triangle3D {
	Coord3D		c1;
	Coord3D		c2;
	Coord3D		c3;
};

GEOMETRY_DLL_EXPORT	Coord3D	GEOM_CALL	GetAnOnPlanePoint (const PlaneEq& plane);

GEOMETRY_DLL_EXPORT PlaneEq	GEOM_CALL	SetPlaneEq (const Coord3D& onPlanePoint, const Vector3D& planeNormal);

GEOMETRY_DLL_EXPORT Triangle3D	GEOM_CALL	SetTriangle (const Coord3D& c1, const Coord3D& c2, const Coord3D& c3);

GEOMETRY_DLL_EXPORT void	GEOM_CALL	SetUpGenPlane (PlaneEq* plane, const Coord3D* c0, const Vector3D* nn);		/*vv124*/

GEOMETRY_DLL_EXPORT void	GEOM_CALL	SetUpHorPlane (PlaneEq* plane, double zlev);		/*vv121*/

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	PlaneCoord3D (const Coord	*wc, const PlaneEq* p);		/*vv72*/

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	PlaneCoord3D (const Coord	&wc, const PlaneEq& p);		/*vv72*/

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	ProjCoord3DToPlane (const Coord3D* wc, const PlaneEq* p);	/*vv120*/

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	ProjCoord3DToPlane (const Coord3D& wc, const PlaneEq& p);	/*vv120*/

GEOMETRY_DLL_EXPORT Vector3D GEOM_CALL	ProjVector3DToPlane (const Vector3D& wc, const Vector3D& pNormal);	/*AACS*/

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsPlaneCoord3D (const Coord3D* wc, const PlaneEq* p);	/*vv72*/

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsPlaneCoord3D (const Coord3D& wc, const PlaneEq& p);	/*vv72*/

GEOMETRY_DLL_EXPORT double	GEOM_CALL	DistPlaneCoord3D (const Coord3D &wc,const PlaneEq &p);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsCoord3DAbovePlane (const Coord3D& wc, const PlaneEq& p);	

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	ArePlanesEqual (const PlaneEq& eq1, const PlaneEq& eq2, const double eps = Eps);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsCoplanar (const Coord3D* p1, const Coord3D* p2, const Coord3D* p3, const Coord3D* p4);

GEOMETRY_DLL_EXPORT Vector3D    GEOM_CALL	NormVector3D (const Triangle3D& p);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	ArePointsOnPlane (
							Int32			n,
							const double*	x,
							const double*	y,
							const double*	z,
							PlaneEq*		pl = nullptr);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	ArePointsOnPlane (const GS::Array<Coord3D>& points, PlaneEq* pl = nullptr);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectorNormalizedPlane (const Sector3D& s,
																const PlaneEq& p,
																Coord3D* intersectionPoint,
																double* intersectionParam);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectorPlane (const Sector3D& s,
													  const PlaneEq& p,
													  Coord3D* intersectionPoint,
													  double* intersectionParam);

GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	XSectorPlane (const Sector3D& s, const Triangle3D& p, bool* exist);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XPlanes (const PlaneEq& p1, const PlaneEq& p2, Sector3D* s);

GEOMETRY_DLL_EXPORT char	GEOM_CALL	XCylarcLine3D (
							const Ellipse*	el,
							const Plane*	plane,
							const Sector3D*	s,
							Sector3D*		xs);	/*vv72*/

GEOMETRY_DLL_EXPORT char	GEOM_CALL	XCylarcSector3D (
							const Ellipse	*el,
							const Plane		*plane,
							const Sector3D	*s,
							Sector3D		*xs);	/*vv72*/

GEOMETRY_DLL_EXPORT char	GEOM_CALL	XCylarcs (
							const Ellipse	*el1,
							const Plane		*plane1,
							const Ellipse	*el2,
							const Plane		*plane2,
							Coord3D			xs[4]) CAN_THROW ((GeometryException));	/*vv72*/

GEOMETRY_DLL_EXPORT PlaneEq	GEOM_CALL	PlaneEqFromTriangle (const Triangle3D& plane);

// creates a plane from the points and returns true if all points are coplanar
GEOMETRY_DLL_EXPORT bool	GEOM_CALL	CreatePlaneEq (
											const GS::PagedArray<Coord3D>& in_pointArray,
											PlaneEq& out_p);

// creates the regression plane to the given points and returns true if the plane is created
GEOMETRY_DLL_EXPORT bool	GEOM_CALL	GetRegressionPlane (
							const GS::PagedArray<Coord3D>&	points,
							PlaneEq&						plane,
							Coord3D							*basePoint = nullptr);

// creates least squares plane to the given points (orthogonal regression in 3d)
GEOMETRY_DLL_EXPORT PlaneEq	GEOM_CALL	GetLeastSquaresPlane (
							Int32			n,
							const double*	x,
							const double*	y,
							const double*	z);

// creates least squares plane to the given points (orthogonal regression in 3d)
GEOMETRY_DLL_EXPORT PlaneEq	GEOM_CALL	GetLeastSquaresPlane (const GS::Array<Coord3D>& inputCoords);

GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL ReadXMLTriangle3D (GS::XMLIChannel& ic, Triangle3D& t);
GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL WriteXMLTriangle3D (GS::XMLOChannel& oc, const Triangle3D& t);

GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL ReadXMLPlaneEq (GS::XMLIChannel& ic, PlaneEq& p);
GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL WriteXMLPlaneEq (GS::XMLOChannel& oc, const PlaneEq& p);

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::Triangle3D& t)	{ return Geometry::ReadXMLTriangle3D (ic, t); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::Triangle3D& t)	{ return Geometry::WriteXMLTriangle3D (oc, t); }

inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const PlaneEq& p)	{ return Geometry::WriteXMLPlaneEq (oc, p); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, PlaneEq& p)	{ return Geometry::ReadXMLPlaneEq (ic, p); }
}


#endif
