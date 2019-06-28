// *********************************************************************************************************************
// Description:		MonolithStructureCalculatorBase
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	TBa
//
// SG compatible
// *********************************************************************************************************************

#ifndef MONOLITH_CALCULATOR_BASE_HPP
#define MONOLITH_CALCULATOR_BASE_HPP

#pragma once

#include "VBElemOperationsExport.hpp"

#include "Polygon2D.hpp"

#include "StairTypes.hpp"
#include "TreadTypes.hpp"
#include "TreadPolygonEdgeData.hpp"
#include "TreadPolygonVertexData.hpp"
#include "MonolithStairStructure.hpp"
#include "StairStructureCut.hpp"
#include "StairStructureBottom.hpp"

namespace VBCalculations
{

class MonolithConnectionCalculator;

class VB_ELEM_OPERATIONS_DLL_EXPORT TreadPolygon2DEdgeData
{
public:
	enum EdgeVisibility {
		VisibleContour		= 1,
		VisibleConnection	= 2,
		HiddenConnection	= 3
	};

private:
	VBElem::TreadPolygonEdgeType	treadPolygonEdgeType;
	bool							visible;
	EdgeVisibility					visibility;

public:
	TreadPolygon2DEdgeData ();
	TreadPolygon2DEdgeData (const VBElem::TreadPolygonEdgeData& rhs);

	// ... accessors .......................................................................................................
	VBElem::TreadPolygonEdgeType	GetEdgeType			() const { return treadPolygonEdgeType; }
	void							SetEdgeType			(VBElem::TreadPolygonEdgeType edgeType) { treadPolygonEdgeType = edgeType; }

	bool							IsVisible			() const				{ return visible; }
	void							SetVisible			(bool _visible)			{ visible = _visible; }

	void							SetEdgeVisibleType	(EdgeVisibility vis)	{ visibility = vis; }
	EdgeVisibility					GetEdgeVisibleType	() const				{ return visibility; }

	Int32							GetVisibleFlag		() const				{ return visible ? static_cast<Int32> (visibility) : 0; }

	// ... operators .......................................................................................................
public:
	bool							operator ==					(const TreadPolygon2DEdgeData& rv) const { return treadPolygonEdgeType == rv.treadPolygonEdgeType && visible == rv.visible && visibility == rv.visibility; }
	bool							operator !=					(const TreadPolygon2DEdgeData& rv) const { return !(*this == rv); }
};

using MonolithTreadPolygon = Geometry::CustomPolygon2D<VBElem::TreadPolygonVertexData, TreadPolygon2DEdgeData, Geometry::PolyId, Geometry::PolyId>;
using MonolithTreadMultiPolygon = Geometry::CustomMultiPolygon2D<VBElem::TreadPolygonVertexData, TreadPolygon2DEdgeData, Geometry::PolyId, Geometry::PolyId>;

MonolithTreadPolygon VB_ELEM_OPERATIONS_DLL_EXPORT	ConvertPolygon (const VBElem::TreadPolygon& poly, TreadPolygon2DEdgeData::EdgeVisibility visibleType = TreadPolygon2DEdgeData::VisibleContour);

enum MonolithSectorFlag {
	GeneralCut				= 1,
	GeneralFull				= 2,
	RiserDetailCut			= 3,
	RiserDetailFull			= 4,
	LandingLineCut			= 5,
	LandingLineFull			= 6,
	ConnectionLine			= 7,
	ConnectionDetail		= 8,
	DrainingRiser			= 9,
	DrainingRiserDetail		= 10,
};

enum MonolithPolygonFlag {
	FlightCutBoundary		= 1,
	FlightSchemeBoundary	= 2,
	LandingCutBoundary		= 3,
	LandingSchemeBoundary	= 4,
	Connection				= 5,
	Draining				= 6
};

class VB_ELEM_OPERATIONS_DLL_EXPORT MonolithStructureCalculatorBase {
protected:
	VBElem::StairStructureConstRef				m_structure;

	VBElem::TreadPolyline						m_walkline;					// the full walkingline of the stair
	VBElem::TreadPolygon						m_simpleBoundary;			// monolith structure boundary without connections (as if every connection is Vertical Cut with dx = 0)
	VBElem::TreadPolygon						m_realBoundary;				// the real boundary of the monolith structure

	VBElem::StairStructureCutRole				m_beginConnectionType;		// begin connection type (RunStart, RunLanding, etc.)
	VBElem::TreadPolygon						m_beginConnection;			// begin connection polygon, only stores extensions
	VBElem::StairStructureCut::ExtensionType	m_beginExtensionType;		// the type of extension used for Landing connections

	VBElem::StairStructureCutRole				m_endConnectionType;		// end connection type (RunStart, RunLanding, etc.)
	VBElem::TreadPolygon						m_endConnection;			// end connection polygon, only stores extensions
	VBElem::StairStructureCut::ExtensionType	m_endExtensionType;			// the type of extension used for Landing connections

	GS::Array<VBElem::TreadConstRef>			m_treads;

	GS::Array<Sector>							m_connectionLines;			// this stores the connection detail polylines (for bearing nib and cut out)
	GS::Array<Sector>							m_invertedConnectionLines;	// this is for detail lines which are inverted
	GS::Array<Sector>							m_landingLines;				// this stores the landing's start and end lines

	bool										m_isPrevBeam;
	bool										m_isNextBeam;

public:
	MonolithStructureCalculatorBase (const VBElem::StairStructureConstRef& structure);

	virtual void	Calculate () = 0;

	virtual GS::Array<GS::Pair<Sector, MonolithSectorFlag>>						GetMonolithRiserSectors () const = 0;
	virtual GS::Array<GS::Pair<MonolithTreadPolygon, MonolithPolygonFlag>>		GetMonolith2DPolygons () const;

protected:
	void	CalculateBaseData ();
	void	CalcConnectionPolygons ();
	Sector	CalcConnectionDetailRiser (double cx, VBElem::TreadPolygonEdgeType edgeType);
	void	CalcConnectionDetailRisers ();
	bool	IsRiserInsideBoundary (const Sector& riser);
	void	CalcRealBoundary ();
	void	CalcRealLandingBoundary ();

	bool	NeedToGenerate ();
	void	CalculateConnectionBreakLine (VBElem::TreadPolygonEdgeType edge, double dx, GS::Array<Sector>& result);
	void	GetLandingRunLine (double dx, GS::Array<Sector>& results) const;

	void	SetGDLBoundaryLeadingEdge	(MonolithTreadPolygon& boundary) const;
	void	SetGDLBoundaryTrailingEdge	(MonolithTreadPolygon& boundary) const;

	virtual MonolithTreadPolygon	GetGDLBoundary () const;
	virtual MonolithTreadPolygon	GetFlaggedBeginConnectionPolygon () const;
	virtual MonolithTreadPolygon	GetFlaggedEndConnectionPolygon () const;

	virtual MonolithConnectionCalculator*	GetBeginConnectionCalculator () = 0;
	virtual MonolithConnectionCalculator*	GetEndConnectionCalculator () = 0;

	virtual const MonolithConnectionCalculator*	GetBeginConnectionCalculator () const = 0;
	virtual const MonolithConnectionCalculator*	GetEndConnectionCalculator () const = 0;

public:
	static VBElem::TreadPolygon	GetExtensionPoly				(const VBElem::TreadPolygon& poly, VBElem::TreadPolygonEdgeType type, double dx, bool reverseFlags = false);
	static VBElem::TreadPolygon	CalculateBoundaryPolygon		(const GS::Array<VBElem::TreadConstRef>& treads, bool isRunEnd);
	static bool					IsRiserInsidePolygon			(const Sector& riser, const VBElem::TreadPolygon& polygon);
	static VBElem::TreadPolygon	ParallelToWalklineVerticalCut	(const VBElem::TreadPolygon& poly, const VBElem::TreadPolyline& walkline, VBElem::TreadPolygonEdgeType type, double dx, bool invert = false);
	static bool					IsEdgeOnContour					(const MonolithTreadPolygon& polyToCheck, MonolithTreadPolygon::ConstEdgeIterator edge);
	static bool					IsEdgeOnContour					(const VBElem::TreadPolygon& polyToCheck, Sector sector);
	static void					SetEdgeVisibility				(VBElem::TreadPolygon& poly, VBElem::TreadPolygonEdgeType type, bool value);
	static void					FlagOutsideEdges				(MonolithTreadPolygon& polyToFlag, MonolithTreadPolygon& polyToTest, TreadPolygon2DEdgeData::EdgeVisibility detailFlag);
	static bool					GetConnectingSector				(const VBElem::TreadPolygon& origPoly, const Coord& extensionEndCoord, double dx, Sector& outSector);
	static void					GetRunLandingLineUnderLanding	(const VBElem::TreadPolygon& landingSchemePoly, const VBElem::TreadPolygon& extensionPoly, double dx, GS::Array<Sector>& results);
};


template<class CalculatorType>
GS::Owner<CalculatorType>	CreateConnectionCalculator (const VBElem::StairStructureConstRef neighborStructure, const VBElem::StairStructureConstRef& structure)
{
	if (structure->IsLanding ()) {
		if (neighborStructure == nullptr) {
			return GS::NewOwned<CalculatorType> (structure);
		} else if (neighborStructure->GetType () == VBElem::SST_BeamSupport) {
			return GS::NewOwned<typename CalculatorType::BeamMonolithCalculator> (structure);
		} else if (neighborStructure->GetBottomType () == VBElem::StairStructureBottom::Smooth) {
			return GS::NewOwned<typename CalculatorType::SmoothCalculator> (structure);
		} else if (neighborStructure->GetBottomType () == VBElem::StairStructureBottom::Stepped) {
			return GS::NewOwned<typename CalculatorType::SteppedCalculator> (structure);
		} else if (neighborStructure->GetBottomType () == VBElem::StairStructureBottom::Flat) {
			return GS::NewOwned<typename CalculatorType::FlatCalculator> (structure);
		}
	} else if (structure->GetBottomType () == VBElem::StairStructureBottom::Smooth) {
		return GS::NewOwned<typename CalculatorType::SmoothCalculator> (structure);
	} else if (structure->GetBottomType () == VBElem::StairStructureBottom::Stepped) {
		return GS::NewOwned<typename CalculatorType::SteppedCalculator> (structure);
	} else if (structure->GetBottomType () == VBElem::StairStructureBottom::Flat) {
		return GS::NewOwned<typename CalculatorType::FlatCalculator> (structure);
	}

	return GS::NewOwned<CalculatorType> (structure);
}

} // namespace VBCalculations

#endif // MONOLITH_CALCULATOR_BASE_HPP
