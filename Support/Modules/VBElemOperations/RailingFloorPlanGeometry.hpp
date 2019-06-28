// *********************************************************************************************************************
// Description:		RailingFloorPlanGeometryTypes
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD
//
// SG compatible
// *********************************************************************************************************************
#if !defined _RAILING_FLOORPLAN_GEOMETRY_TYPES_HPP_
#define _RAILING_FLOORPLAN_GEOMETRY_TYPES_HPP_

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
#include "RailBaseTypes.hpp"

// from VBElemOperations
#include "RailingBreaklinePositionInfo.hpp"

namespace VBCalculations {

namespace RailingGeometry {

enum RailingPart
{
	NoShowPart = -100,

	Undefined = 0,

	Lower,
	Middle,
	Upper
};


enum RailingAttributeSet
{
	NoShow = 0,
	Visible = 1,
	Hidden = 2
};

RailingAttributeSet GetAttributeSet (const RailingPart part, const VBElem::RailingGridType gridType);

}

}

namespace GS {

GSErrCode	Read (IChannel& ic, VBCalculations::RailingGeometry::RailingAttributeSet& attributeSet);
GSErrCode	Write (OChannel& oc, const VBCalculations::RailingGeometry::RailingAttributeSet& attributeSet);
GSErrCode	Read (IChannel& ic, GS::Pair<Coord, Coord>& coordPair);
GSErrCode	Write (OChannel& oc, const GS::Pair<Coord, Coord>& coordPair);
}

namespace VBCalculations {

template<typename PolygonType, typename PolygonEdgeItType>
Vector GetTangentAtPoint (const PolygonType& polyline, const Coord& coord, PolygonEdgeItType edgeIt = PolygonEdgeItType ())
{
	GS::Array<GS::Pair<PolygonEdgeItType, Vector>> results = polyline.GetTangentAtPoint (coord);

	DBASSERT (results.GetSize () > 0);

	if (results.GetSize () == 1) {
		return results[0].second;
	} else {
		for (auto itemIt = results.BeginFast (); itemIt != results.EndFast (); ++itemIt) {
			if (itemIt->first == edgeIt) {
				return itemIt->second;
			}
		}

		DBBREAK ();
		return Vector ();
	}
}


template<typename PolygonType>
Vector GetTangentAtPoint (const PolygonType& polyline, const Coord& coord)
{
	GS::Array<GS::Pair<typename PolygonType::ConstEdgeIterator, Vector>> results = polyline.GetTangentAtPoint (coord);

	if (DBVERIFY (results.GetSize () > 0)) {
		DBASSERT (results.GetSize () == 1);
		return results[0].second;
	}

	return Vector ();
}


HalfPlane2DData	GetHalfPlaneDataFromCoordAndNormal (const Coord& origo, const Vector& normal, const bool isInverse);


// --- Custom types ----------------------------------------------------------------------------------------------------
class RailingPolyVertexData : public GS::Object
{
DECLARE_CLASS_INFO
private:
	bool						mIsSplitVertex;
	GS::Optional<double>		mVertexZCoord;
	bool						mExplicitStatusVertex;

public:
	RailingPolyVertexData ();
	~RailingPolyVertexData ();

public:
	bool operator== (const RailingPolyVertexData& rhs) const;
	bool operator!= (const RailingPolyVertexData& rhs) const;

public:
	bool	IsSplitVertex () const;
	void	SetSplitVertex (const bool splitEdge);
	void	SetExplicitIsStatus (const bool isStatusVertex);

	const GS::Optional<double>&		GetZCoord () const;
	void							SetZCoord (const GS::Optional<double> zCoord = GS::NoValue);
	bool							IsExplicitStatusVertex () const;

public:
	virtual GS::Object*	Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};


class RailingPolyEdgeData : public GS::Object
{
DECLARE_CLASS_INFO
public:
enum EdgePosition {
	NoResult = 0,

	TopEdge = 10,
	TopEdgeClosed,

	BottomEdge = 20,
	BottomEdgeClosed,

	RightSide = 30,
	LeftSide,

	CutEdge = 100,
	CutEdgeSingle = 110,
	CutEdgeLower = 120,
	CutEddeUpper,

	RailEdge = 200,
	ConnectionEdge = 201,

	Undefined = 1000 
};

private:
	EdgePosition	mEdgePosition;
	bool			mIsSplitEdge;
	bool			mExplicitStatusEdge;

public:
	RailingPolyEdgeData ();
	~RailingPolyEdgeData ();

public:
	bool operator== (const RailingPolyEdgeData& rhs) const;
	bool operator!= (const RailingPolyEdgeData& rhs) const;

	bool	IsSplitEdge () const;
	void	SetSplitEdge (const bool splitEdge);
	void	SetExplicitIsStatus (const bool isStatusEdge);

public:
	virtual GS::Object*	Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

public:
	void							SetEdgePosition (EdgePosition position);
	EdgePosition					GetEdgePosition () const;

	EdgePosition					IsEndEdge () const;
	EdgePosition					IsBottomEdge () const;
	EdgePosition					IsTopEdge () const;
	EdgePosition					IsCutEdge () const;
	EdgePosition					IsVisibleEdge () const;
	EdgePosition					IsSideEdge () const;

	bool							IsExplicitStatusEdge () const;
};

// --- Type definitions	------------------------------------------------------------------------------------------------
typedef Geometry::CustomPolygon2D<RailingPolyVertexData, RailingPolyEdgeData, Geometry::PolyId, Geometry::PolyId>					RailingPolygon;
typedef Geometry::CustomMultiPolygon2D<RailingPolyVertexData, RailingPolyEdgeData, Geometry::PolyId, Geometry::PolyId>				RailingMultiPolygon;
typedef Geometry::CustomIrregularPolygon2D<RailingPolyVertexData, RailingPolyEdgeData, Geometry::PolyId, Geometry::PolyId>			RailingIrregularPolygon;
typedef Geometry::CustomMultiIrregularPolygon2D<RailingPolyVertexData, RailingPolyEdgeData, Geometry::PolyId, Geometry::PolyId>		RailingMultiIrregularPolygon;
typedef Geometry::CustomPolyline2D<RailingPolyVertexData, RailingPolyEdgeData, Geometry::PolyId>									RailingPolyline;
typedef Geometry::CustomMultiPolyline2D<RailingPolyVertexData, RailingPolyEdgeData, Geometry::PolyId>								RailingMultiPolyline;

// --- Custom types ----------------------------------------------------------------------------------------------------

struct RailGeometryData : public GS::Object
{
DECLARE_CLASS_INFO
public:
	RailingPolygon						boundaryPolygon;
	RailingPolyline						centerLine;
	Geometry::Polyline2D				railingReferenceLine;
	Geometry::Polyline2D				railReferenceLine;
	RailingGeometry::RailingPart		railingPart;
	VBElem::RailBaseConstRef			previousRail;			//Not persistent - runtime use only 
	VBElem::RailBaseConstRef			nextRail;				//Not persistent - runtime use only
	RailingPolyline						leftLine;				//Not persistent - runtime use only
	RailingPolyline						rightLine;				//Not persistent - runtime use only

public:
	virtual GS::Object*	Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};


struct RailingSubElemGeometryData : public GS::Object
{
DECLARE_CLASS_INFO
public:
	RailingPolyline						centerLine;
	RailingPolygon						boundaryPolygon;
	RailingGeometry::RailingPart		railingPart;
	RailingPolyline						leftLine;
	RailingPolyline						rightLine;

public:
	virtual GS::Object*	Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};


class RailingStatusData: public GS::Object
{
	DECLARE_CLASS_INFO
private:
	GS::Array<Coord>					statusCoords;
	GS::Array<Geometry::Polyline2D>		statusLines;

private:
	void	AppendStatuses (const RailingPolygon& boundaryPolygon);
public:
	void	AppendStatuses (const RailGeometryData& data);
	void	AppendStatuses (const RailingSubElemGeometryData& data);
	void	ClearStatusCoords ();

	void	AddStatusCoord (const Coord& coord);
	void	AddStatusPolyline (const Geometry::Polyline2D& coord);

	void	Concatenate (const RailingStatusData& input);

	const GS::Array<Coord>&						GetCoords () const;
	const GS::Array<Geometry::Polyline2D>		GetPolylines () const;

public:
	virtual GS::Object*	Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};


class RailingBreakMarkGeometryData : public GS::Object
{
public:
	struct BreakMarkLineData 
	{
		Geometry::Polyline2D					line;
		RailingGeometry::RailingAttributeSet	attributeSet;
	};

	class CalculationFaliureException : public GS::Exception
	{
	public:
		CalculationFaliureException ();
		virtual ~CalculationFaliureException ();
	};

	DECLARE_CLASS_INFO

public:
	enum BreakMarkPositionResult
	{
		Undefined,
		LowerOnly,
		Both
	};

private:
	UIndex														mBreakMarkIndex;
	Geometry::Real												mBreakMarkPosition;
	Geometry::Real												mBreakMarkDistance;
	Geometry::Angle												mBreakMarkAngle;
	Int32														mBreakMarkAnglePower2Correction;
	VBElem::RailingGridType										mGridType;
	VBElem::RailingBreaklinePositionInfo::PositionInfoType		mPositionInfo;

	Coord														mBreakMarkLowerPoint;
	Vector														mBreakMarkLineLowerPointNormal;
	Coord														mBreakMarkUpperPoint;
	Vector														mBreakMarkLineUpperPointNormal;
	bool														mIsSingleBreakline;
	bool														mIsDownwardPath;

	double														mLowerLeftEndCoordDistance;
	double														mLowerRightEndCoordDistance;
	double														mUpperLeftEndCoordDistance;
	double														mUpperRightEndCoordDistance;

	Coord														mCutArcOrigo;
	bool														mCutArcOrigoSet;

public:
	RailingBreakMarkGeometryData ();
	RailingBreakMarkGeometryData (VBElem::RailingBreaklinePositionInfoConstRef breakLineInfoRef, const Geometry::Polyline2D& railiningReferenceLine, const VBElem::RailingGridType gridType);
	virtual ~RailingBreakMarkGeometryData ();
public:
	virtual GS::Object*	Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

private:
	void									InitMemberVariables (const VBElem::RailingBreaklinePositionInfoConstRef& breakLineInfoRef);
	static bool								UpdateEndCoord (const Coord& coord, const Coord& origo, const Vector& normal, double& resultLeft, double& resultRight);

public:
	double									CalculateActualOffsetDistance (const double amount, const bool left, const bool lower) const;
	void									CalculateBreakMarkPointsAndTangents (const Geometry::Polyline2D& referenceLine);
	GS::ArrayFB<BreakMarkLineData, 2>		GetCalculatedBreakMarksPolylines (const double leftOffset = 0.0, const double rightOffset = 0.0) const;
	Geometry::Polygon2D						GetBreakMarkPolygon () const;

	UIndex									GetBreakMarkIndex () const;
	const Geometry::Real&					GetBreakMarkPosition () const;

	const Coord&							GetLowerPoint () const;
	Vector									GetLowerPointNormal () const;
	const Coord&							GetUpperPoint () const;
	Vector									GetUpperPointNormal () const;

	Int32									GetBreakMarkAnglePow2Correction () const;
	void									SetBreakmarkAnglePow2Correction (const Int32 value);

	bool									IsSingleBreakMark () const;
	bool									IsUpwardDirection () const;

	bool									GetLowerBreakMarkHalfPlane (HalfPlane2DData& output) const;
	bool									GetUpperBreakMarkHalfPlane (HalfPlane2DData& output) const;

	bool									UpdateEndCoords (const Coord& coord);
	void									SetCutArcOrigo (const Coord& origo);
	GS::Pair<double, double>				GetLowerPointDistances () const;
	GS::Pair<double, double>				GetUpperPointDistances () const;
	GS::Pair<Coord, Coord>					GetLowerBreakMarkEndCoords (const double leftOffset = 0.0, const double rightOffset = 0.0) const;
	GS::Pair<Coord, Coord>					GetUpperBreakMarkEndCoords (const double leftOffset = 0.0, const double rightOffset = 0.0) const;
	bool									CheckValidEndCoords () const;

	GS::Pair<double, double>				GetBreakMarkSkipIntervals () const;

	RailingGeometry::RailingAttributeSet	GetLowerBreakMarkAttributeSet () const;
	RailingGeometry::RailingAttributeSet	GetUpperBreakMarkAttrubuteSet () const;

	VBElem::RailingBreaklinePositionInfo::PositionInfoType GetBreakMarkPositionInfo () const;

public:
	bool									operator<	(const RailingBreakMarkGeometryData& rhs) const;
	bool									operator<=	(const RailingBreakMarkGeometryData& rhs) const;
	bool									operator>	(const RailingBreakMarkGeometryData& rhs) const;
	bool									operator>=	(const RailingBreakMarkGeometryData& rhs) const;
	bool									operator==	(const RailingBreakMarkGeometryData& rhs) const;

};
// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

class RailingFloorPlanGeometryCache;
class RailingFloorPlanCalculator;

}		// namespace VBCalculations

#endif	// _RAILING_FLOORPLAN_GEOMETRY_TYPES_HPP_