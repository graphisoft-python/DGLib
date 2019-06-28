// *********************************************************************************************************************
// Description:		Simple data class representing a Bezier spline
//
// Module:			Geometry
// *********************************************************************************************************************

#ifndef BEZIERDETAILS_HPP
#define BEZIERDETAILS_HPP

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "GeometricDefinitions.h"
#include "Coord.h"
#include "Box2DData.h"
#include "Circle2DData.h"
#include "GenArc2DData.h"
#include "Sector2DData.h"
#include "Array.hpp"

namespace Geometry {

struct DirType {
	double		lenPrev;			/* Bezier direction length prev/next */
	double		lenNext;
	double		dirAng;				/* Bezier direction Angle */
};

// --- BezierDetails ---------------------------------------------------------------------------------------------------

class GEOMETRY_DLL_EXPORT BezierDetails {

private:
	GS::Array<Coord>		coords;
	GS::Array<DirType>		dirs;
	bool					closed;

public:
	BezierDetails ();
	BezierDetails (const BezierDetails&);

	BezierDetails&	operator= (const BezierDetails&);

	BezierDetails (Int32 nCoords, const Coord** hCoords, const DirType** hDirs);
	BezierDetails (Int32 nCoords, const Coord* pCoords, const DirType* pDirs);

	Int32 GetCoordsNum () const { return coords.GetSize (); }
//	const Coord** const	GetCoords () const { return const_cast<const Coord** const> (coords); }
//	const DirType** const GetDirType () const { return const_cast<const DirType** const> (dirs); }

	const Coord* const	GetCoordsPtr () const { return coords.GetContent (); }
	const DirType* const GetDirsPtr () const { return dirs.GetContent (); }

	bool SetData (Int32 nCoords, const Coord* pCoords, const DirType* pDirs);
	bool SetData (const GS::Array<Coord>& aCoords, const GS::Array<DirType>& aDirs);
	bool GetData (GS::Array<Coord>& aCoords, GS::Array<DirType>& aDirs) const;

	bool IsClosed () const { return closed; }
	void SetClosed (bool clo) { closed = clo; }

	void GetBezierDirPoint (Int32 cIndex, bool forward, Coord* cc) const;

	GSErrCode		Read  (GS::IChannel& ic);
	GSErrCode		Write (GS::OChannel& oc) const;
};


GEOMETRY_DLL_EXPORT void TangentLines (const Coord& p, const BezierDetails& bez, SectorResultFn fn);
GEOMETRY_DLL_EXPORT void TangentLines (const Sector& s, const BezierDetails& bez, SectorResultFn fn);
GEOMETRY_DLL_EXPORT void NormalLines (const Coord& p, const BezierDetails& bez, SectorResultFn fn);
GEOMETRY_DLL_EXPORT void NormalLines (const Sector& s, const BezierDetails& bez, SectorResultFn fn);


} // namespace Geometry

#endif // BEZIERDETAILS_HPP
