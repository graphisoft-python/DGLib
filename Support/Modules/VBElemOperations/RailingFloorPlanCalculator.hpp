// *********************************************************************************************************************
// Description:		RailingFloorPlanCalculator
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD
//
// SG compatible
// *********************************************************************************************************************
#if !defined _RAILING_FLOORPLAN_CALCULATOR_HPP_
#define _RAILING_FLOORPLAN_CALCULATOR_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "Array.hpp"
#include "Pair.hpp"
#include "Object.hpp"

// from Geometry
#include "Polyline2D.hpp"
#include "Polygon2D.hpp"

// from ElementManager
#include "Floor.hpp"

// from VBElements
#include "VBElements/RailingTypes.hpp"
#include "VBElements/RailBaseTypes.hpp"
#include "RailingFloorPlanGeometry.hpp"

// from VBCalculations
#include "RailingSubElemEnumerator.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------
namespace VBCalculations
{
	struct GDLGlobalCalcEnvir;
}

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------
namespace VBCalculations
{
// === class RailingFloorPlanCalculator ==================================================================================

class RailingFloorPlanCalculator
{
public:

	struct RailingParts : public GS::Object
	{
		DECLARE_CLASS_INFO
	public:
		GS::HashTable<VBElem::RailBaseConstRef, RailGeometryData>							railFullGeometry;
		GS::HashTable<VBElem::RailBaseConstRef, RailGeometryData>							railLowerPartGeometry;
		GS::HashTable<VBElem::RailBaseConstRef, RailGeometryData>							railMiddlePartGeometry;
		GS::HashTable<VBElem::RailBaseConstRef, RailGeometryData>							railUpperPartGeometry;
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingSubElemGeometryData>		subElemGeometryFull;
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingSubElemGeometryData>		subElemGeometryLower;
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingSubElemGeometryData>		subElemGeometryMiddle;
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingSubElemGeometryData>		subElemGeometryUpper;

		GS::HashTable<VBElem::RailingSubElementConstRef, RailingStatusData>					railingStatusDatas;

		GS::Array<Geometry::Polygon2D>														breakMarkEliminationPolygons;
		GS::Array<RailingBreakMarkGeometryData>										 		railingBreakMarkGeometries;
		GS::HashSet<VBElem::RailingSubElementConstRef>										subElemsInBreakMaks;
		GS::HashTable<VBElem::RailBaseConstRef, GS::Array<GS::ArrayFB<double, 2>>>			postCoords;
		GS::HashTable<VBElem::RailingSegmentConstRef, GS::Array<GS::Pair<Coord, Coord>>>	breakMarkOffsets;
	public:
		RailingParts ();
	public:
		virtual	GS::Object*	Clone (void) const override;
		virtual	GSErrCode	Read (GS::IChannel& ic) override;
		virtual	GSErrCode	Write (GS::OChannel& oc) const override;

	private:
		GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	};

private:
	VBElem::RailingConstRef																				mRailing;
	const VBCalculations::GDLGlobalCalcEnvir&															mEnvir;
	EDB::FloorConstRef																					mActFloor;
	RailingSubElemConstEnumerator																		mEnumerator;
	GS::Array<VBElem::RailingSegmentConstRef>															mSegmentOrder;
	GS::HashTable<VBElem::RailingSegmentConstRef, GS::Pair<Geometry::Real, Geometry::Real>>				mSegmentIntervals;
	GS::HashTable<VBElem::RailingSegmentConstRef, GS::HashSet<VBElem::RailBaseConstRef>>				mSegmentToRails;
	GS::HashTable<VBElem::RailingSegmentConstRef, GS::HashSet<VBElem::RailingPanelConstRef>>			mSegmentToPanels;
	GS::HashTable<VBElem::RailingSegmentConstRef, GS::HashSet<VBElem::RailingPostBaseConstRef>>			mSegmentToPosts;
	GS::HashTable<VBElem::RailBaseConstRef, VBElem::RailBaseConnectionConstRef>							mRailsToConnections;
	GS::HashSet<VBElem::RailBaseConnectionConstRef>														mReplacedConnections;

public:
	RailingFloorPlanCalculator (const VBElem::RailingConstRef& railing, const VBCalculations::GDLGlobalCalcEnvir& envir);

	void						Calculate									(RailingParts& data);
	VBElem::RailingConstRef		GetRailing									(void) const										 { return mRailing; }

private:
	template<typename Type>
	void						FillSegmentToRailTableByType				();
	void						FillSegmentToRailTable						();
	void						FillSegmentToPanelTable						();
	void						FillSegmentToPostBaseTable					();

	template<typename Type>
	void						FillRailToConnectionsTableByType ();
	void						FillRailToConnectionsTable ();

	template<typename Type>
	void						CalculateRailType							(RailingParts& data);

	void						CalculateTopRail							(RailingParts& data);
	void						CalculateHandrails							(RailingParts& data);
	void						CalculateRails								(RailingParts& data);
	void						CalculatePanels								(RailingParts& data) const;

	void						CalculateConnections						(RailingParts& data) const;
	void						CalculateStatuses							(RailingParts& data) const;

	void						ConsolidateConnectionPartsAfterBreakMarks	(RailingParts& data) const;

	void						CalculateToprailEndings						(RailingParts& data) const;
	void						CalculateHandrailEndings					(RailingParts& data) const;
	void						CalculateRailEndings						(RailingParts& data) const;
	void						CalculateRailingRailEndings					(RailingParts& data) const;

	void						CalculateRailingBreakMarkGeometryDatas		(RailingParts& data) const;

	void						CutRailGeometriesWithBreakMarks				(RailingParts& data) const;
	void						CutRailCenterLinesWithBreakMarks			(RailingParts& data) const;
	void						CutPanelGeometriesWithBreakMarks			(RailingParts& data) const;
	void						CutPanelCenterLinesWithBreakMarks			(RailingParts& data) const;

	void						CalculateEliminationPolygons				(RailingParts& data) const;
	void						CalculateBreakMarkEliminationIntervals		(RailingParts& data) const;
	void						CalculatePostRailingPositions				(RailingParts& data) const;

	void						StorePostTypeCoords							(RailingParts& data) const;

	template<typename Type>
	void						GatherRailingSubElemsInEliminationPolygonsByType	(RailingParts& data) const;
	void						GatherRailingSubElemsInEliminationPolygons			(RailingParts& data) const;
public:
	template<typename RailingType>
	inline static GS::Pair<double, double>	GetRailBasedElemSideOffsets				(const RailingType& railSubElemRef);
	template<typename RailingType>
	inline static GS::Pair<double, double>	GetRailBasedElemTopBottomOffsets		(const RailingType& railSubElemRef);
private:
	const Geometry::Real&				GetSegmentLengthBeginning					(const VBElem::RailingSegmentConstRef& segmentRef) const;
	const Geometry::Real&				GetSegmentLengthEnding						(const VBElem::RailingSegmentConstRef& segmentRef) const;
	VBElem::RailingSegmentConstRef		GetRailingSegmentAtLength					(double length) const;
};


template<typename RailingType>
GS::Pair<double, double> RailingFloorPlanCalculator::GetRailBasedElemSideOffsets (const RailingType& railSubElemRef)
{
	GS::Pair<double, double> result;

	const Box2DData crossSection = railSubElemRef->GetCrossSectionDimensions ();
	const double left = -crossSection.xMin;
	const double right = crossSection.xMax;
	if (DBVERIFY_GUID (!(Geometry::IsNearZero (left) && Geometry::IsNearZero (right)), "{5D277157-B838-466F-A298-E3AA7D518528}")) {
		result = GS::Pair<double, double> (left, right);
	} else {
		result = GS::Pair<double, double> (Geometry::IsNearZero (left) ? 2 * Eps : left, Geometry::IsNearZero (right) ? 2 * Eps : right);
	}

	auto handrailEndRef = ODB::DynamicCast<VBElem::HandrailEnd> (railSubElemRef);
	auto handrailRef = handrailEndRef == nullptr ? ODB::DynamicCast<VBElem::Handrail> (railSubElemRef) : ODB::DynamicCast<VBElem::Handrail> (handrailEndRef->GetConnectedRailBase ());

	if (handrailRef != nullptr) {
		if (Geometry::IsLess<double> (handrailRef->GetCalculatedYOffset (), 0.0) || handrailRef->IsLeftSideHandrail ()) {
			GS::Swap (result.first, result.second);
		}
	}
	
	return result;
}


template<>
inline GS::Pair<double, double>	RailingFloorPlanCalculator::GetRailBasedElemSideOffsets<VBElem::RailingPanelConstRef> (const VBElem::RailingPanelConstRef& railSubElemRef)
{
	const Box2DData crossSection = railSubElemRef->GetCrossSectionDimensions ();
	const double left = GS::Abs (crossSection.xMax - crossSection.xMin) / 2.0;
	const double right = left;
	if (DBVERIFY_GUID (!(Geometry::IsNearZero (left) && Geometry::IsNearZero (right)), "{5D277157-B838-466F-A298-E3AA7D518528}")) {
		return GS::Pair<double, double> (left, right);
	} else {
		return GS::Pair<double, double> (Geometry::IsNearZero (left) ? 2 * Eps : left, Geometry::IsNearZero (right) ? 2 * Eps : right);
	}
}


template<typename RailingType>
GS::Pair<double, double> RailingFloorPlanCalculator::GetRailBasedElemTopBottomOffsets (const RailingType& railSubElemRef)
{
	const Box2DData crossSection = railSubElemRef->GetCrossSectionDimensions ();
	const double bottom = -crossSection.yMin;
	const double top = crossSection.yMax;
	if (DBVERIFY_GUID (!(Geometry::IsNearZero (bottom) && Geometry::IsNearZero (top)), "{5D277157-B838-466F-A298-E3AA7D518528}")) {
		return GS::Pair<double, double> (bottom, top);
	} else {
		return GS::Pair<double, double> (Geometry::IsNearZero (bottom) ? 2 * Eps : bottom, Geometry::IsNearZero (top) ? 2 * Eps : top);
	}
}

}		// namespace VBCalculations

#endif	// _RAILING_FLOORPLAN_CALCULATOR_HPP_
