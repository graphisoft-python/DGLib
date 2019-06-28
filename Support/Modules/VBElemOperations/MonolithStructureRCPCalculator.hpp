// *********************************************************************************************************************
// Description:		MonolithStructureRCPCalculator
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	TBa
//
// SG compatible
// *********************************************************************************************************************

#ifndef MONOLITH_RCP_CALCULATOR_HPP
#define MONOLITH_RCP_CALCULATOR_HPP

#pragma once

#include "MonolithStructureCalculatorBase.hpp"
#include "MonolithConnectionCalculator.hpp"
#include "StairStructureTypes.hpp"


namespace VBCalculations
{

class VB_ELEM_OPERATIONS_DLL_EXPORT MonolithStructureRCPCalculator : public MonolithStructureCalculatorBase {
protected:
	GS::Owner<MonolithRCPConnectionCalculator> m_beginConnectionCalc;
	GS::Owner<MonolithRCPConnectionCalculator> m_endConnectionCalc;

	GS::Array<Sector>	m_riserLines;
	GS::Array<Sector>	m_riserDetailLines;
	GS::Array<Sector>	m_landingLines;

	bool				m_leadEdgeIsHiddenConnection;
	bool				m_trailConnectionEdgeIsHidden;
	
public:
	MonolithStructureRCPCalculator (const VBElem::StairStructureConstRef& structure);

	virtual void	Calculate () override;

	virtual GS::Array<GS::Pair<Sector, MonolithSectorFlag>>	GetMonolithRiserSectors () const override;

protected:
	virtual MonolithTreadPolygon	GetFlaggedBeginConnectionPolygon () const override;
	virtual MonolithTreadPolygon	GetFlaggedEndConnectionPolygon () const override;
	virtual MonolithTreadPolygon	GetGDLBoundary () const override;

	void	CalcRisers ();
	void	CalcConnectionLines ();
	void	CalcLandingLines ();
	void	CalcBeginBearNibLines ();
	void	FlagConnectionEdges ();

	virtual MonolithRCPConnectionCalculator*	GetBeginConnectionCalculator	() override { return m_beginConnectionCalc.Get (); };
	virtual MonolithRCPConnectionCalculator*	GetEndConnectionCalculator		() override { return m_endConnectionCalc.Get (); };

	virtual const MonolithRCPConnectionCalculator*	GetBeginConnectionCalculator () const override { return m_beginConnectionCalc.Get (); };
	virtual const MonolithRCPConnectionCalculator*	GetEndConnectionCalculator	 () const override { return m_endConnectionCalc.Get (); };
};

}

#endif // MONOLITH_RCP_CALCULATOR_HPP
