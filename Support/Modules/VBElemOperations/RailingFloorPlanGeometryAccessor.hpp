// *********************************************************************************************************************
// Description:		RailingFloorPlanGeometryAccessor
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD
//
// SG compatible
// *********************************************************************************************************************
#if !defined _RAILING_FLOORPLAN_GEOMETRY_ACCESSOR_HPP_
#define _RAILING_FLOORPLAN_GEOMETRY_ACCESSOR_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "Array.hpp"
#include "Object.hpp"
#include "Optional.hpp"

// from Geometry
#include "Polygon2D.hpp"
#include "Polyline2D.hpp"

// from VBElements
#include "RailingTypes.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "GDLGlobalCalculations.hpp"

// from VBElemOperations
#include "RailingFloorPlanGeometryCache.hpp"

namespace VBCalculations
{

class VB_ELEM_OPERATIONS_DLL_EXPORT RailingFloorPlanGeometryAccessor
{
public:
	enum AttributeSet {
		NoShow	= 0,
		Visible	= 1,
		Hidden	= 2
	};

	struct BreakMarkLineData {
		Geometry::Polyline2D	line;
		AttributeSet			attributeSet;
	};

private:
	VBElem::RailingConstRef			mRailing;
	GDLGlobalCalcEnvir				mGlobalCalcEnvir;

public:
	RailingFloorPlanGeometryAccessor (const VBElem::RailingConstRef& railingRef, const GDLGlobalCalcEnvir& gdlEnvir);
	~RailingFloorPlanGeometryAccessor ();

private:
	ODB::ConstRef<RailingFloorPlanGeometryCache::Data>		GetData () const;

public:
	GS::Array<BreakMarkLineData>							GetBreakMarkPolylines () const;
	GS::Optional<GS::Pair<Coord, Coord>>					GetLowerBreakMarkEndPoints (const UIndex breakMarkIndex) const;
	const GS::HashSet<VBElem::RailingSubElementConstRef>&	GetSubElemsInBreakMarks () const;
	
	void													EnumerateStatusCoords (const VBElem::RailingSubElementConstRef& subElemRef, const std::function<void (const Coord&)>& callback);
	void													EnumerateStatusPolyline (const VBElem::RailingSubElementConstRef& subElemRef, const std::function<void (const Geometry::Polyline2D&)>& callback);
	void													EnumerateStatusCoords (const std::function<void (const VBElem::RailingSubElementConstRef&, const Coord&)>& callback);
	void													EnumerateStatusPolyline (const std::function<void (const VBElem::RailingSubElementConstRef&, const Geometry::Polyline2D&)>& callback);

	bool													ElementIsNotVisible (const VBElem::RailingSubElementConstRef& railSubElem) const;
};


void VB_ELEM_OPERATIONS_DLL_EXPORT UpdateRailingFloorPlanGeometryExplicitly (const VBElem::RailingConstRef& railingRef);

class VB_ELEM_OPERATIONS_DLL_EXPORT RailingFloorPlanGeometryTest
{
public:
	static Coord CalculateBreakMarkOverhangStraight (const Coord& breakMarkEndPoint, const double amount, const double breakMarkAngle, const Vector& breakMarkOffsetDirection);
	static Coord CalculateBreakMarkOverhangArc (const Coord& breakMarkEndPoint, const double amount, const Coord arcOrigo, const Vector& breakMarkOffsetDirection);
};

}		// namespace VBCalculations

#endif	// _RAILING_FLOORPLAN_GEOMETRY_ACCESSOR_HPP_