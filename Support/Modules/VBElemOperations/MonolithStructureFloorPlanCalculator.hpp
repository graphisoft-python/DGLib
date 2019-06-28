// *********************************************************************************************************************
// Description:		MonolithStructureFloorPlanCalculator
//
// Module:			VBElemOperations
// Namespace:		VBCalculations
// Contact person:	TBa
//
// SG compatible
// *********************************************************************************************************************

#ifndef MONOLITH_FLOORPLAN_CALCULATOR_HPP
#define MONOLITH_FLOORPLAN_CALCULATOR_HPP

#pragma once

#include "MonolithStructureCalculatorBase.hpp"
#include "MonolithConnectionCalculator.hpp"

#include "Polygon2D.hpp"

#include "StairTypes.hpp"
#include "TreadTypes.hpp"
#include "TreadPolygonEdgeData.hpp"
#include "TreadPolygonVertexData.hpp"
#include "MonolithStairStructureTypes.hpp"


namespace VBCalculations
{

class VB_ELEM_OPERATIONS_DLL_EXPORT MonolithStructureFloorPlanCalculator : public MonolithStructureCalculatorBase {
protected:
	GS::Owner<MonolithFPConnectionCalculator> m_beginConnectionCalc;
	GS::Owner<MonolithFPConnectionCalculator> m_endConnectionCalc;

	VBElem::TreadPolygon		m_leftDrainingPoly;
	VBElem::TreadPolygon		m_rightDrainingPoly;

	GS::Array<Sector>			m_riserLines;			// this stores the outer (visible) edge of the riser
	GS::Array<Sector>			m_riserDetailLines;		// this stores the inner edge of the riser when it is slanted
	GS::Array<Sector>			m_cutRiserLines;		// same as above but cut with draining
	GS::Array<Sector>			m_cutRiserDetailLines;	// same as above but cut with draining

	GS::Array<Sector>			m_drainingLines;
	GS::Array<Sector>			m_drainingDetailLines;
	GS::Array<Sector>			m_drainingOffsetLines;
	GS::Array<Sector>			m_drainingConnectionLines;
	GS::Array<Sector>			m_cutLandingLines;
	
public:
	MonolithStructureFloorPlanCalculator	(const VBElem::StairStructureConstRef& structure);

	virtual void	Calculate () override;

	virtual GS::Array<GS::Pair<Sector, MonolithSectorFlag>>						GetMonolithRiserSectors () const override;
	virtual GS::Array<GS::Pair<MonolithTreadPolygon, MonolithPolygonFlag>>		GetMonolith2DPolygons () const override;

protected:
	void	CalcRisers ();
	void	CalcLandingRiser ();
	void	CalcLandingLines ();
	void	FilterRisers ();
	void	CalcDrainingPolygons (const VBElem::MonolithStairStructureConstRef& monStructure);
	void	CalcDrainingRisers (const VBElem::MonolithStairStructureConstRef& monStructure, VBElem::StairDrainingSide side);
	void	CalcDrainingConnections (const VBElem::MonolithStairStructureConstRef& monStructure);
	void	CutRisersWithDraining (const GS::Array<Sector>& source, GS::Array<Sector>& target);
	void	FlagConnectionEdges ();
	void	CalcRCPConnectionLines ();

	virtual MonolithTreadPolygon			GetFlaggedEndConnectionPolygon () const override;

	virtual MonolithFPConnectionCalculator*	GetBeginConnectionCalculator	() override { return m_beginConnectionCalc.Get (); };
	virtual MonolithFPConnectionCalculator*	GetEndConnectionCalculator		() override { return m_endConnectionCalc.Get (); };

	virtual const MonolithFPConnectionCalculator*	GetBeginConnectionCalculator () const override { return m_beginConnectionCalc.Get (); };
	virtual const MonolithFPConnectionCalculator*	GetEndConnectionCalculator	 () const override { return m_endConnectionCalc.Get (); };

public:
	static VBElem::TreadPolygon	CreateDrainingPolygon (VBElem::StairDrainingSide side, VBElem::StairStructureDraining draining, const VBElem::StairConstRef& stair, const VBElem::TreadPolygon& intersectPoly);
};

} // namespace VBCalculations

#endif // MONOLITH_FLOORPLAN_CALCULATOR_HPP
