/****************************************************************************/
/*																			*/
/*					2D Line, Sector and their operations					*/
/*																			*/
/****************************************************************************/
#if !defined (SECTOR2DDATA_H)
#define SECTOR2DDATA_H

#pragma once

// from GSRoot
#include "PagedArray.hpp"

// from Geometry
#include "GeometricDefinitions.h"
#include "Point2DData.h"

struct F_Sector {
	Geometry::Point2f	c1;
	Geometry::Point2f	c2;
};				/* 16 */			/* 2D line segment	*/

struct Sector {
	Coord	c1;
	Coord	c2;

	Sector () : c1 (Coord (0.0, 0.0)), c2 (Coord (0.0, 0.0)) {}
	Sector (const Coord& inC1, const Coord& inC2) : c1 (inC1), c2 (inC2) {}
};				/* 32 */			/* 2D line segment	*/

namespace Geometry {

	typedef const std::function<void (const Sector&)>& SectorResultFn;

	enum DistType {
		POS_DIST,		// Positive distant
		SIGN_DIST		// Signed distant
	};

	inline				Sector SetSector (const Coord& c1, const Coord& c2);

	GEOMETRY_DLL_EXPORT void   GEOM_CALL	IVSector (GS::PlatformSign inplatform, Sector *s);

	GEOMETRY_DLL_EXPORT double GEOM_CALL	LenSector (const Sector& s);

	GEOMETRY_DLL_EXPORT Vector GEOM_CALL	SectorVector (const Sector& sct);

	GEOMETRY_DLL_EXPORT void   GEOM_CALL	InvertSectorOrientation (Sector* sct);

	GEOMETRY_DLL_EXPORT bool   GEOM_CALL	IsLineCoord (const Coord& pt, const Sector& sct);

	GEOMETRY_DLL_EXPORT Sector GEOM_CALL	OffsetSector (const Sector& sector, const Vector& offset);

	GEOMETRY_DLL_EXPORT bool   GEOM_CALL	InternalCoord (
							const Sector&			sector,
							const Coord&			point,
							Geometry::Boundary		sectorBegEnd,
							double					eps = Eps);

	inline				double DistLineCoord (const Sector& ln, const Coord& pt);

	GEOMETRY_DLL_EXPORT double GEOM_CALL	DistCoordSectorPtr (const Coord *p, const Sector *s, DistType distType = POS_DIST);

	GEOMETRY_DLL_EXPORT Coord  GEOM_CALL	CoordProjSector (const Coord& c, const Sector& s);

	GEOMETRY_DLL_EXPORT double GEOM_CALL	CoordProjSectorParam (const Coord& c, const Sector& s);

	GEOMETRY_DLL_EXPORT Coord  GEOM_CALL	MirrorCoord (const Sector&	s, const Coord&	wc);

	GEOMETRY_DLL_EXPORT void   GEOM_CALL	CalcWithSector (Sector* s, double 	width);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsSectorPointIntersect (
							const Sector&	s,
							const Coord&	pt,
							Boundary		sectorBegBoundary,
							Boundary		sectorEndBoundary,
							double			eps);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XLines (
											const Sector&	s1,
											const Sector&	s2,
											Coord*			xc,
											double*			xt1 = nullptr,
											double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XLinesEps  (
							const Sector&	s1,
							const Sector&	s2,
							Coord			*xc,
							double			eps,
							double			radEps,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);		/* mi46 */

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XRayLineEps (
							const Sector&	s1,
							const Sector&	s2,
							Boundary		rayBoundaries,
							Coord			*xc,
							double			eps,
							double			radEps,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectorLineEps (
							const Sector&	s1,
							const Sector&	s2,
							Boundary		sectorBoundaries,
							Coord			*xc,
							double			eps,
							double			radEps,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectorRayEps (
							const Sector&	s1,
							const Sector&	s2,
							Boundary		boundaries,
							Coord			*xc,
							double			eps,
							double			radEps,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XRaysEps (
							const Sector&	s1,
							const Sector&	s2,
							Boundary		rayBoundaries,
							Coord*			xc,
							double			eps,
							double			radEps,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectors (
							const Sector&	s1,
							const Sector&	s2,
							Boundary		sectorBoundaries,
							Coord*			xc,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectorsEps (
							const Sector&	s1,
							const Sector&	s2,
							Boundary		sectorBoundaries,
							Coord*			xc,
							double			eps,
							double			radEps,
							double*			xt1 = nullptr,
							double*			xt2 = nullptr);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	XSectorsOverLapByDist  (
							const Sector&	s1,
							const Sector&	s2,
							Sector*			xs = nullptr,
							double			epsIn = Eps);

	GEOMETRY_DLL_EXPORT Int32	GEOM_CALL	XSectorsOverLap (
							const Sector*	s1,
							const Sector*	s2,
							Coord*			xc);

	GEOMETRY_DLL_EXPORT short	GEOM_CALL	PGSegmInt (
							const Coord*	pb,
							const Coord*	pe,
							const Coord*	qb,
							const Coord*	qe,
							Coord*			qint,
							double			invlenp,
							double			invlenq,
							double			eps);

	 GEOMETRY_DLL_EXPORT void	GEOM_CALL	SplitSectorsByLinesEps (
							const GS::PagedArray<Sector>&	sectors,
							const GS::PagedArray<Sector>&	lines,
							Boundary						sectorBoundaries,
							GS::PagedArray<Sector>*			resSectors,
							double							eps,
							double							radEps);

	 GEOMETRY_DLL_EXPORT	bool	GEOM_CALL	IsHorizontalSector (const Sector& sector, double eps = EPS);
	 GEOMETRY_DLL_EXPORT	bool	GEOM_CALL	IsVerticalSector (const Sector& sector, double eps = EPS);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	IVF_Sector (GS::PlatformSign inplatform, F_Sector *s);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsPointInPositiveSide (const Coord& p, const Sector& s);
	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	IsPointInNegativeSide (const Coord& p, const Sector& s);
	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	ArePointsInSameSide (const Sector& s, const Coord& p1, const Coord& p2);
	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL ReadXMLSector	(GS::XMLIChannel& ic, Sector& sec);
	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL WriteXMLSector	(GS::XMLOChannel& oc, const Sector& sec);
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Sector& sec)	{ return Geometry::ReadXMLSector (ic, sec); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Sector& sec)	{ return Geometry::WriteXMLSector (oc, sec); }

	GEOMETRY_DLL_EXPORT double SpecDistPointToSector (const Coord& c, const Sector& s, double* overHang = nullptr);

} // namespace Geometry


/****************************************************************************/
/*					INLINE function implementations							*/
/****************************************************************************/

inline Sector Geometry::SetSector (const Coord&	c1,
								   const Coord&	c2)
{
	return Sector (c1, c2);
}		/* SetSector */


inline double Geometry::DistLineCoord (const Sector& ln, const Coord& pt)

{
	return Geometry::Dist (CoordProjSector (pt, ln), pt);
}

#endif
