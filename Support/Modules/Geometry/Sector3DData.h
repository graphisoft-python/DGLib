// *****************************************************************************
// C style struct for 3D Line, Sector and their operations
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (SECTOR3DDATA_H)
#define SECTOR3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point3DData.h"
#include "Box3DData.h"
#include "PagedArray.hpp"

/* 3D line segment	*/ /* 48 bytes */

struct Sector3D {
	Coord3D	c1;
	Coord3D	c2;
	Sector3D (const Coord3D& c1, const Coord3D& c2) : c1 (c1), c2 (c2) {}
	Sector3D () : c1 (0., 0., 0.), c2 (0., 0., 0.) {}
};
// forward declarations
typedef GS::PagedArray<Sector3D>	GSPagedArray_Sector3D;
typedef GS::PagedArray<Int32>		GSPagedArray_int;

namespace Geometry {

GEOMETRY_DLL_EXPORT Sector3D	GEOM_CALL	SetSector3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT Vector3D	GEOM_CALL	SectorVector3D (const Sector3D& s);

GEOMETRY_DLL_EXPORT Coord3D		GEOM_CALL	CoordProjSector3D (const Coord3D& c, const Sector3D& s);

GEOMETRY_DLL_EXPORT double		GEOM_CALL	CoordProjSector3DParam (const Coord3D& c, const Sector3D& s);

GEOMETRY_DLL_EXPORT double 		GEOM_CALL	LenSector3D (const Sector3D& s);

GEOMETRY_DLL_EXPORT double		GEOM_CALL	CoordSectorDist3D (const Coord3D& point, const Sector3D& sector);

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	IsCoord3DInSector (const Coord3D& wc, const Sector3D& s);

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	IsLineCoord3D (const Coord3D* wc, const Sector3D* s);

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	XLines3D (const Sector3D* s1, const Sector3D* s2, Coord3D* ccc,
													  double* xt1 = nullptr, double* xt2 = nullptr);

GEOMETRY_DLL_EXPORT bool GEOM_CALL XLine3DsEps  (
										const Sector3D*		s1,
										const Sector3D*		s2,
										Coord3D*			xc,
										double				eps,
										double				radEps,
										double*				xt1 = nullptr,
										double*				xt2 = nullptr);

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	MinDistanceLine3Ds (
															const Vector3D	& p0, 
															const Vector3D	& t0, 
															const Vector3D	& p1, 
															const Vector3D	& t1, 
															double			& alpha_0, 
															double			& alpha_1);

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	XSectors3D (const Sector3D* s1, const Sector3D* s2, Coord3D* ccc,
														double* xt1 = nullptr, double* xt2 = nullptr);

//		Intersection with epsilon
GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSector3DsEps (
						const Sector3D&	s1,
						const Sector3D&	s2,
						Boundary		sectorBoundaries,
						Coord3D*		xc,
						double			eps,
						double*			xt1 = nullptr,
						double*			xt2 = nullptr);		/* mi46 */

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectors3DOverLapByDist  (const Sector3D&	s1,
																  const Sector3D&	s2,
																  Sector3D*			xs = nullptr,
																  double			epsIn = Eps);

GEOMETRY_DLL_EXPORT Int32	GEOM_CALL	XSector3DOverLap  (	const Sector3D*	s1,
															const Sector3D*	s2,
															double			eps,
															Coord3D*		xc1,
															Coord3D*		xc2);

GEOMETRY_DLL_EXPORT Box3DType GEOM_CALL Sector3DBox3D (const Sector3D *s);

GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL ReadXMLSector3D	(GS::XMLIChannel& ic, Sector3D& sec);
GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL WriteXMLSector3D	(GS::XMLOChannel& oc, const Sector3D& sec);
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Sector3D& sec)	{ return Geometry::WriteXMLSector3D (oc, sec); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Sector3D& sec)	{ return Geometry::ReadXMLSector3D (ic, sec); }
}

#endif
