// *********************************************************************************************************************
// Description:		Polyline25D definition
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	TAd
//
// SG compatible
// *********************************************************************************************************************

#if !defined (__POLYLINE25D_HPP__)
#define __POLYLINE25D_HPP__

#pragma once

// from GSRoot
#include "GSRoot.hpp"
#include "Coord3d.h"
#include "Plane.hpp"
#include "Polyline2D.hpp"


namespace Geometry {

GEOMETRY_DLL_EXPORT	Vector3D	GEOM_CALL	MirrorVector3D (const Vector3D& vec, const Vector3D& normal);
GEOMETRY_DLL_EXPORT	Coord3D		GEOM_CALL	LerpCoord3D (const Coord3D& c1, const Coord3D& c2, double t);
GEOMETRY_DLL_EXPORT	Coord		GEOM_CALL	ToCoord2D (const Coord3D& c);
GEOMETRY_DLL_EXPORT	Coord3D		GEOM_CALL	ToCoord3D (const Coord& c, double z);
GEOMETRY_DLL_EXPORT	Coord3D		GEOM_CALL	ToCoord3D (const Coord& origo, double radius, double fi, double z);
GEOMETRY_DLL_EXPORT	Int32		GEOM_CALL	CompareAngles (const Coord& origo, const Coord& beg, const Coord& a, const Coord& b);
GEOMETRY_DLL_EXPORT	Plane		GEOM_CALL	PlaneWithCoords (const Coord3D& a, const Coord3D& b, const Coord3D& c);
GEOMETRY_DLL_EXPORT	void		GEOM_CALL	SetPlaneWithCoords (Plane& plane, const Coord3D& a, const Coord3D& b, const Coord3D& c);

/*  Arc - Plane intersection: finds all intersections, but chooses only one (or none) based on criteria.
	- Gives back an intersection point on the arc, the first from where we would go BEHIND the cutplane.
	- Ideally the cutplane should always face outwards from the arc and we 'cut' the piece that's in front of it.
	- 'fromBeg' = true means we are looking for a new beg point, so search from the beginning coord.  */

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	FindArcPlaneIntersection (const Coord3D& beg, const Coord3D& end, const Coord& origo2D, double arcAngle, const Plane& plane, bool fromBeg, Coord3D& intersection);

GEOMETRY_DLL_EXPORT GS::Array<Coord3D>	GEOM_CALL	FindArcPlaneIntersections (const Coord3D& beg, const Coord3D& end, const Coord& origo2D, double arcAngle, const Plane& plane, bool fromBeg);

GEOMETRY_DLL_EXPORT bool		GEOM_CALL	FindSectorPlaneIntersection (const Sector3D& sector, const Plane& plane, Coord3D& intersection);

GEOMETRY_DLL_EXPORT double		GEOM_CALL	GetCorrectArcAngle (const Coord& origo, const Coord& c1, const Coord& c2, double totalArcAngle);
GEOMETRY_DLL_EXPORT bool		GEOM_CALL	GetAngleOfPointOnArc (const Coord& arcStartPoint, const Coord& arcEndPoint, const Coord& pointOnArc, double& angleOfPointOnArcOut);
GEOMETRY_DLL_EXPORT bool		GEOM_CALL	ProjectCoordToEdge (const Coord& coord, const Coord& edgeBegC, const Coord& edgeEndC, double edgeArcAngle, Coord& projectedCoordOut);

class GEOMETRY_DLL_EXPORT Polyline25D {
public:
	enum IntersectionType {
		Trivial,						// trivial solution
		Midpoint,						// there is a 2d segment of solutions, take the middle point
		Tangential,						// tangential case, trivial intersection in 3d
		Rejected						// there were 2 possible solutions (arc), one was trivial, the other is the rejected
	};

	struct Intersection {
		Coord3D point;
		double prevXOffset;
		double nextXOffset;
	};

	typedef GS::HashTable<IntersectionType, Intersection>	Intersections;


private:
	// core data, must be saved
	GS::Array<Coord3D>		line;
	double					arcAngle;
	Plane*					firstCutPlane;
	Plane*					lastCutPlane;

	// calculated data, can be recalculated from core
	GS::Array<Coord3D>		cutLine;
	double					cutArcAngle;
	GS::Array<double>		arcFis;					// arc fi values
	Coord					origo2D;
	double					radius2D;
	double					length2D;
	double					cutLength3D;
	double					cutLength2D;
	GS::Array<double>		lengths2D;
	Vector3D				firstTangent;
	Vector3D				lastTangent;
	Coord3D					firstCut;
	Coord3D					lastCut;
	Box3DType				boundingBox;
	double					cutOffsetFrontLength2D;
	double					cutOffsetEndLength2D;

public:
	Polyline25D (void);
	Polyline25D (const Polyline25D& source);
	~Polyline25D (void);

	Polyline25D&				operator =					(const Polyline25D& source);
	bool						operator ==					(const Polyline25D& source) const;
	bool						operator !=					(const Polyline25D& source) const;

	GSErrCode					ReadXML						(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode					WriteXML					(GS::XMLOChannel& oc, const char* tagName = nullptr) const;
	
	GSErrCode					Read						(GS::IChannel& ic);
	GSErrCode					Write						(GS::OChannel& oc) const;
	
	void						SetLine						(const GS::Array<Coord3D>& points, double arcAngle);

	void						Offset						(double xOffset, double yOffset, double zOffset);

	void						OffsetX						(double xOffset);
	void						OffsetY						(double yOffset);
	void						OffsetZ						(double zOffset);
	void						Cut							(double x1, double x2, bool removeRedundantPoints = true);
	void						CutAndOffset				(double x1, double x2, double yOffset, double zOffset, bool removeRedundantPoints = true);

	static Polyline25D			GetInterpolated				(const Polyline25D& r1, const Polyline25D& r2, double t);
	static Polyline25D			GetReversed					(const Polyline25D& line);

	void						CutBeginningWithPlane		(const Plane& plane);
	void						CutEndingWithPlane			(const Plane& plane);
	void						ClearFirstCutPlane			(void);
	void						ClearLastCutPlane			(void);
	void						CutWithPlanes				(const Plane* first, const Plane* last);
	void						FinalizeCuts				(void);
	bool						HasBothCutPlanes			(void) const												{ return firstCutPlane != nullptr && lastCutPlane != nullptr;	}
	bool						HasFirstCutPlane			(void) const												{ return firstCutPlane != nullptr;								}
	bool						HasLastCutPlane				(void) const												{ return lastCutPlane != nullptr;								}
	Plane						GetFirstCutPlane			(void) const												{ return HasFirstCutPlane () ? *firstCutPlane : Plane ();		}
	Plane						GetLastCutPlane				(void) const												{ return HasLastCutPlane () ? *lastCutPlane : Plane ();			}
	bool						IsCutByPlane				(const Plane& plane, bool fromBeg, bool extendable, Coord3D* intersection = nullptr, double* xOffset = nullptr) const;

	Coord3D						GetLinePoint				(double xOffset, Vector3D* normal = nullptr, Vector3D* tangent = nullptr) const;
	Coord3D						GetHomogenLinePoint			(double xHomogen, Vector3D* normal = nullptr, Vector3D* tangent = nullptr) const;
	
	const GS::Array<Coord3D>&	GetLinePoints				(void) const												{ return cutLine;										}
	double						GetArcAngle					(void) const												{ return cutArcAngle;									}
	GS::Array<double>			GetArcAngles				(void) const;
	double						GetLength2D					(void) const												{ return cutLength2D;									}
	double						GetLength3D					(void) const												{ return cutLength3D;									}
	bool						IsArc						(void) const												{ return abs (arcAngle) > 0.0;							}
	GS::Array<double>			GetLengths2D				(void) const;
	GS::Array<double>			GetLengths3D				(void) const;
	GS::Array<double>			GetSlopeAngles				(void) const;
	
	const Vector3D&				GetFirstTangent				(void) const												{ return firstTangent;									}
	const Vector3D&				GetLastTangent				(void) const												{ return lastTangent;									}
	const Coord3D&				GetFirstCutPoint			(void) const												{ return firstCut;										}
	const Coord3D&				GetLastCutPoint				(void) const												{ return lastCut;										}
	double						GetCutOffsetFrontLength2D	(void) const												{ return cutOffsetFrontLength2D;						}
	double						GetCutOffsetEndLength2D		(void) const												{ return cutOffsetEndLength2D;							}

	double						GetUncutLength2D			(void) const												{ return length2D;										}
	GS::Array<double>			GetUncutArcAngles			(void) const;
	const GS::Array<Coord3D>&	GetUncutLinePoints			(void) const												{ return line;											}
	double						GetUncutArcAngle			(void) const												{ return arcAngle;										}

	Coord						GetOrigo					(void) const												{ return origo2D;										}
	double						GetRadius					(void) const												{ return radius2D;										}

	bool						IsEmpty						(void) const												{ return line.GetSize() < 2;							}
	const Box3DType&			GetBoundingBox				(void) const												{ return boundingBox;									}
	void						GetPolylineAndZ				(Polyline2D& polyline, GS::Array<double>& z) const;
	
	// return the intersection point with the following polyline - might be an extension point
	Intersections				FindIntersectionPoint		(const Polyline25D& next, double tangentialOffset = 0.0) const;

	// same line or same arc, same direction
	bool						IsTangential2D				(const Polyline25D& other) const;

	// same line or same arc, same direction and connecting endpoints
	bool						IsContinuous2D				(const Polyline25D& other) const;
	bool						IsContinuous3D				(const Polyline25D& other) const;

	Plane						GetLineCutPlane				(double xOffset) const;										// facing is matching with the beg plane

	// get the homogen X value along the polyline that's closest to a given point - 2d checking
	double						GetHomogenXOffset			(const Coord3D& coord) const;

private:
	void						Reset						(void);

	void						OffsetX_NoRecalculation		(double xOffset);
	void						OffsetY_NoRecalculation		(double yOffset);
	void						OffsetZ_NoRecalculation		(double zOffset);
	void						Cut_NoRecalculation			(double x1, double x2, bool removeRedundantPoints);

	void						CutBeginningWithPlane		(void);
	void						CutEndingWithPlane			(void);
	void						Recalculate					(void);
	void						RecalculateCutSpecificData	(void);

public:
	Intersections				FindIntersectionPointWithMaxStretch	(const Polyline25D& next, double tangentialOffset, double maxStretchFactor) const;
};



inline Coord3D		Polyline25D::GetHomogenLinePoint (double xHomogen, Vector3D* normal /*= nullptr*/, Vector3D* tangent /*= nullptr*/) const
{
	return GetLinePoint (xHomogen * length2D, normal, tangent);
}


inline Vector3D		GEOM_CALL	MirrorVector3D (const Vector3D& vec, const Vector3D& normal)
{
	// mirror tangent to normal:    t' = t + 2(dot(n, t) * n - t) = 2dot(n, t) * n - t, where ||n|| = ||t|| = 1
	Vector3D mirrored = 2.0 * MulsVectors3D (normal, vec) * normal - vec;
	mirrored.NormalizeVector ();
	return mirrored;
}


inline Coord3D		GEOM_CALL	LerpCoord3D (const Coord3D& c1, const Coord3D& c2, double t)
{
	return c1 + t * (c2 - c1);
}


inline Coord		GEOM_CALL	ToCoord2D (const Coord3D& c)
{
	return Coord (c.x, c.y);
}


inline Coord3D		GEOM_CALL	ToCoord3D (const Coord& c, double z)
{
	return Coord3D (c.x, c.y, z);
}


inline Coord3D		GEOM_CALL	ToCoord3D (const Coord& origo, double radius, double fi, double z)
{
	return Coord3D (origo.x + radius * Cos (Angle (fi)), origo.y + radius * Sin (Angle (fi)), z);
}


inline Int32		GEOM_CALL	CompareAngles (const Coord& origo, const Coord& beg, const Coord& a, const Coord& b)		// return -1 if 'a' is closer to 'beg' than 'b'
{
	double begFi = ArcTan (beg.y - origo.y, beg.x - origo.x);
	double aFi = ArcTan (a.y - origo.y, a.x - origo.x);
	double bFi = ArcTan (b.y - origo.y, b.x - origo.x);

	double aAng = abs (aFi - begFi);
	double bAng = abs (bFi - begFi);

	if (aAng > PI)
		aAng = 2 * PI - aAng;

	if (bAng > PI)
		bAng = 2 * PI - bAng;

	return (aAng < bAng) ? -1 : ((aAng > bAng) ? 1 : 0);
}


inline Plane		GEOM_CALL	PlaneWithCoords (const Coord3D& a, const Coord3D& b, const Coord3D& c)
{
	Plane plane;
	SetPlaneWithCoords (plane, a, b, c);
	return plane;
}


inline void			GEOM_CALL	SetPlaneWithCoords (Plane& plane, const Coord3D& a, const Coord3D& b, const Coord3D& c)
{
	Vector3D normal = (b - a) ^ (c - a);
	normal.NormalizeVector ();
	plane.SetPlane (a, normal);
}

}


#endif