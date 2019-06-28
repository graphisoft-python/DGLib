#if !defined (CIRCLE2DDATA_H)
#define CIRCLE2DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Sector2DData.h"

/****************************************************************************/
/*																			*/
/*					2D Circle and its operations							*/
/*																			*/
/****************************************************************************/


struct Circle {
	Coord	o;			/* Origin	*/
	double	r;			/* Radius	*/
};


namespace Geometry {

class Direction2D;

inline Circle SetCircle (
						const Coord*		o,
						double				r);


GEOMETRY_DLL_EXPORT Direction2D GEOM_CALL GetCircleTangent (
						const Circle&		circle,
						const Coord&		tangentPoint);		/* always counter-clockwise direction on the circle */


GEOMETRY_DLL_EXPORT void GEOM_CALL Circle_3Pt (
						const Coord&		c1,
						const Coord&		c2,
						const Coord&		c3,
						Coord*				origo,
						bool*				exist);

GEOMETRY_DLL_EXPORT void GEOM_CALL Circle_2Pt1Lin (const Coord&		c1,
					 const Coord&		c2,
					 const Sector&		s,
					 const Coord&		refCo,
					 Coord*		origo,
					 bool 	*exist);

GEOMETRY_DLL_EXPORT void GEOM_CALL Circle_1Pt2Lin (const Coord&		c,
					 const Sector&		s1,
					 const Sector&		s2,
					 const Coord&		refCo,
					 Coord*		origo,
					 bool 	*exist);

GEOMETRY_DLL_EXPORT void GEOM_CALL Circle_3Lin (const Sector&	s1,
				  const Sector&	s2,
				  const Sector&	s3,
				  const Coord&		refCo,
				  Coord*			origo,
				  bool 	*exist);

GEOMETRY_DLL_EXPORT double GEOM_CALL ChordAngle (double	len,				/* sm014... */
				   double	radius);

GEOMETRY_DLL_EXPORT char GEOM_CALL XCircleLine	(const Circle	*c,
					 const Sector	*s,
					 Sector			*xs);

GEOMETRY_DLL_EXPORT char GEOM_CALL XCircleLineEps (const Circle	*c,
						const Sector	*s,
						Sector			*xs,
						double			eps);

GEOMETRY_DLL_EXPORT char GEOM_CALL XCircleSector (const Circle	*c,
					   const Sector	*s,
					   Sector		*xs);

GEOMETRY_DLL_EXPORT char GEOM_CALL XCircleSectorEps (const Circle	*c,
					   const Sector	*s,
					   Sector		*xs,
					   double		eps);

GEOMETRY_DLL_EXPORT char GEOM_CALL XCircleRayEps (const Circle	*c,
					   const Sector	*s,
					   Sector		*xs,
					   double		eps);

GEOMETRY_DLL_EXPORT bool GEOM_CALL XCircles (const Circle	*c1,
				  const Circle	*c2,
				  Sector		*xs);

GEOMETRY_DLL_EXPORT bool GEOM_CALL XCirclesEps (const Circle	*c1,
					 const Circle	*c2,
					 Sector			*xs,
					 double			eps);

GEOMETRY_DLL_EXPORT	bool GEOM_CALL IsPointOnCircle (const Coord& point, const Circle& circle);

GEOMETRY_DLL_EXPORT GS::Array<Coord> GEOM_CALL CalcCircleLineIntersections (const Circle& circle, const Coord& lineCoord, const Vector& lineDir);


// class for calculating outer common tangent lines to two circles and touch points of circles and tangent lines
// Outer means: the two input circles are on the same side of tangent line
// Right (resp. left) tangent line is which has touch points on the right (resp. left) side of the central line of the two circle
// viewed from center of circle1 towards the center of circle2
class GEOMETRY_DLL_EXPORT CircleOuterCommonTangentCalculator {
private:
	// input:
	const Circle&	mCircle1;
	const Circle&	mCircle2;

	// calculated:
	UInt32	mTangentNum;			// number of outer tangents: 0, 1 or 2 (for identical circles we set 0, not infinity)
	Vector	mLeftTangentDirUnit;	// unit direction of left tangent line (orientation same as central line from circle1 to circle2)
	Vector	mRightTangentDirUnit;	// unit direction of right tangent line (orientation same as central line from circle1 to circle2)
	Vector	mLeftRadialDirUnit;		// unit direction radial vector from circle center to touch point on left tangent line (same for the two circles)
	Vector	mRightRadialDirUnit;	// unit direction radial vector from circle center to touch point on right tangent line (same for the two circles)

public:
	CircleOuterCommonTangentCalculator (const Circle& circle1, const Circle& circle2);
	UInt32	GetNumberOfOuterTangents () const	{ return mTangentNum; }
	Vector	GetLeftTangentDir		() const	{ DBASSERT (mTangentNum > 0); return mLeftTangentDirUnit;	}
	Vector	GetRightTangentDir		() const	{ DBASSERT (mTangentNum > 0); return mRightTangentDirUnit;	}
	Vector	GetRadialToLeftTangent	() const	{ DBASSERT (mTangentNum > 0); return mLeftRadialDirUnit;	}
	Vector	GetRadialToRightTangent	() const	{ DBASSERT (mTangentNum > 0); return mRightRadialDirUnit;	}
	Coord	GetLeftTangentTouchOn1	() const	{ DBASSERT (mTangentNum > 0); return mCircle1.o + mLeftRadialDirUnit * mCircle1.r;	}
	Coord	GetLeftTangentTouchOn2	() const	{ DBASSERT (mTangentNum > 0); return mCircle2.o + mLeftRadialDirUnit * mCircle2.r;	}
	Coord	GetRightTangentTouchOn1	() const	{ DBASSERT (mTangentNum > 0); return mCircle1.o + mRightRadialDirUnit * mCircle1.r;	}
	Coord	GetRightTangentTouchOn2	() const	{ DBASSERT (mTangentNum > 0); return mCircle2.o + mRightRadialDirUnit * mCircle2.r;	}
#if defined (DEBUVERS)
	void	DumpGDL () const;
#endif
};


GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLCircle (GS::XMLIChannel& ic, Circle& c);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLCircle (GS::XMLOChannel& oc, const Circle& c);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Circle& c)	{ return Geometry::ReadXMLCircle (ic, c); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Circle& c)	{ return Geometry::WriteXMLCircle (oc, c); }

}

/****************************************************************************/
/*					INLINE function implementations							*/
/****************************************************************************/
inline Circle Geometry::SetCircle (const Coord	*o, double		r)
{
	Circle  c;

	c.o = *o;
	c.r = r;

	return (c);
}

#endif
