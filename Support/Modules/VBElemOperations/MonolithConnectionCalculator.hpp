// *********************************************************************************************************************
// Description:		MonolithConnectionCalculator
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	TBa
//
// SG compatible
// *********************************************************************************************************************

#ifndef MONOLITH_CONNECTION_CALCULATOR_HPP
#define MONOLITH_CONNECTION_CALCULATOR_HPP

#pragma once

#include "VBElemOperationsExport.hpp"

#include "StairTypes.hpp"
#include "TreadTypes.hpp"
#include "RiserTypes.hpp"
#include "StairStructureTypes.hpp"
#include "MonolithStairStructureTypes.hpp"

namespace VBElem {
class StairStructureCut;
class StairStructureDraining;
}

namespace VBCalculations
{

class VB_ELEM_OPERATIONS_DLL_EXPORT MonolithConnectionCalculator {
protected:
	VBElem::StairStructureConstRef	m_structure;

	// positive dx means cut, negative dx means extension
	double	m_cutDX;
	double	m_cutCX;

	double	m_landingLineDX;
	double	m_landingCorrection;

	bool	m_cutFirstTread;			// if true the real boundary starts from the second tread
	bool	m_startsFromFirstRiser;		// if true the real boundary starts from the leading edge of the first structure polygon
	bool	m_keepLandingRisers;
	bool	m_invertedDetailEdges;		// needed for run-end cutout connections

public:
	MonolithConnectionCalculator (const VBElem::StairStructureConstRef& structure);
	virtual ~MonolithConnectionCalculator ();

	virtual double	GetCutDX				() const { return m_cutDX * m_landingCorrection; }
	virtual double	GetCutCX				() const { return m_cutCX * m_landingCorrection; }
	double	GetLandingLineDX		() const { return m_landingLineDX * m_landingCorrection; }
	
	bool	CutFirstTread			() const { return m_cutFirstTread; }
	bool	StartsFromFirstRiser	() const { return m_startsFromFirstRiser; }
	bool	KeepLandingRisers		() const { return m_keepLandingRisers; }
	bool	InvertedDetailEdges		() const { return m_invertedDetailEdges;  }

	virtual void	CalculateBegin ();
	virtual void	CalculateEnd ();
	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& /*cutObject*/) {}
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& /*cutObject*/) {}
	virtual void	CalcRunLandingData		(const VBElem::StairStructureCut& /*cutObject*/) {}
	virtual void	CalcLandingRunData		(const VBElem::StairStructureCut& /*cutObject*/) {}
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& /*cutObject*/) {}
	virtual void	CalcRunEndTreadData		(const VBElem::StairStructureCut& /*cutObject*/) {}
	virtual void	CalcRunRunData			(const VBElem::StairStructureCut& /*cutObject*/, const VBElem::RiserConstRef& /*riser*/) {}
};

class SmoothMonolithConnectionCalculator;
class SteppedMonolithConnectionCalculator;
class FlatMonolithConnectionFPCalculator;
class BeamMonolithConnectionFPCalculator;

class SmoothMonolithConnectionRCPCalculator;
class SteppedMonolithConnectionRCPCalculator;
class FlatMonolithConnectionRCPCalculator;
class BeamMonolithConnectionRCPCalculator;


class VB_ELEM_OPERATIONS_DLL_EXPORT MonolithFPConnectionCalculator : public MonolithConnectionCalculator {
public:
	using MonolithConnectionCalculator::MonolithConnectionCalculator;

	using SmoothCalculator			= SmoothMonolithConnectionCalculator;
	using SteppedCalculator			= SteppedMonolithConnectionCalculator;
	using FlatCalculator			= FlatMonolithConnectionFPCalculator;
	using BeamMonolithCalculator	= BeamMonolithConnectionFPCalculator;

	virtual void	CalcRunRunData (const VBElem::StairStructureCut& cutObject, const VBElem::RiserConstRef& riser) override;
};

class VB_ELEM_OPERATIONS_DLL_EXPORT MonolithRCPConnectionCalculator : public MonolithConnectionCalculator {
protected:
	GS::Optional<double>	m_connectionBreakDX;

public:
	using MonolithConnectionCalculator::MonolithConnectionCalculator;

	using SmoothCalculator			= SmoothMonolithConnectionRCPCalculator;
	using SteppedCalculator			= SteppedMonolithConnectionRCPCalculator;
	using FlatCalculator			= FlatMonolithConnectionRCPCalculator;
	using BeamMonolithCalculator	= BeamMonolithConnectionRCPCalculator;

	virtual GS::Optional<double>	GetConnectionBreakDX () const;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT SmoothMonolithConnectionCalculator : public MonolithFPConnectionCalculator {
public:
	using MonolithFPConnectionCalculator::MonolithFPConnectionCalculator;

	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunLandingData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcLandingRunData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndTreadData		(const VBElem::StairStructureCut& cutObject) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT SteppedMonolithConnectionCalculator : public MonolithFPConnectionCalculator {
public:
	using MonolithFPConnectionCalculator::MonolithFPConnectionCalculator;

	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunLandingData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcLandingRunData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndTreadData		(const VBElem::StairStructureCut& cutObject) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT SmoothMonolithConnectionRCPCalculator : public MonolithRCPConnectionCalculator {
public:
	using MonolithRCPConnectionCalculator::MonolithRCPConnectionCalculator;

	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunLandingData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcLandingRunData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndTreadData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunRunData			(const VBElem::StairStructureCut& cutObject, const VBElem::RiserConstRef& riser) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT SteppedMonolithConnectionRCPCalculator : public MonolithRCPConnectionCalculator {
public:
	using MonolithRCPConnectionCalculator::MonolithRCPConnectionCalculator;

	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunLandingData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcLandingRunData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndTreadData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunRunData			(const VBElem::StairStructureCut& cutObject, const VBElem::RiserConstRef& riser) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT FlatMonolithConnectionFPCalculator : public MonolithFPConnectionCalculator {
public:
	using MonolithFPConnectionCalculator::MonolithFPConnectionCalculator;

	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& cutObject) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT FlatMonolithConnectionRCPCalculator : public MonolithRCPConnectionCalculator {
public:
	using MonolithRCPConnectionCalculator::MonolithRCPConnectionCalculator;

	virtual void	CalcRunStartRiserData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunStartTreadData	(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunLandingData		(const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcRunEndRiserData		(const VBElem::StairStructureCut& cutObject) override;
};



class VB_ELEM_OPERATIONS_DLL_EXPORT DrainingConnectionCalculator {
protected:
	VBElem::MonolithStairStructureConstRef	m_runStructure;
	VBElem::MonolithStairStructureConstRef	m_landingStructure;

	VBElem::StairDrainingSide				m_side;

public:
	DrainingConnectionCalculator	(VBElem::StairDrainingSide side);
	virtual ~DrainingConnectionCalculator ();

	virtual double	CalculateOffset	() const = 0;

	VBElem::MonolithStairStructureConstRef		GetRunStructure () const;
	VBElem::MonolithStairStructureConstRef		GetLandingStructure () const;

protected:
	static double CalculateSteppedOffset (double depthH, double depthV, const VBElem::TreadConstRef& beforeTread);
};


class VB_ELEM_OPERATIONS_DLL_EXPORT DrainingRLConnectionCalculator : public DrainingConnectionCalculator {
public:
	DrainingRLConnectionCalculator	(const VBElem::MonolithStairStructureConstRef& structure, VBElem::StairDrainingSide side);

	virtual double	CalculateOffset	() const override;

private:
	double	CalculateSteppedOffset	(const VBElem::StairStructureDraining& landingDraining) const;
	double	CalculateSmoothOffset	(const VBElem::StairStructureDraining& landingDraining) const;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT DrainingLRConnectionCalculator : public DrainingConnectionCalculator {
public:
	DrainingLRConnectionCalculator	(const VBElem::MonolithStairStructureConstRef& structure, VBElem::StairDrainingSide side);

	virtual double	CalculateOffset	() const override;

private:
	double	CalculateSteppedOffset	(const VBElem::StairStructureDraining& runDraining) const;
	double	CalculateSmoothOffset	(const VBElem::StairStructureDraining& runDraining) const;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT BeamMonolithConnectionFPCalculator : public MonolithFPConnectionCalculator {
public:
	using MonolithFPConnectionCalculator::MonolithFPConnectionCalculator;

	virtual void	CalcRunLandingData (const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcLandingRunData (const VBElem::StairStructureCut& cutObject) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT BeamMonolithConnectionRCPCalculator : public MonolithRCPConnectionCalculator {
public:
	using MonolithRCPConnectionCalculator::MonolithRCPConnectionCalculator;

	virtual void	CalcRunLandingData (const VBElem::StairStructureCut& cutObject) override;
	virtual void	CalcLandingRunData (const VBElem::StairStructureCut& cutObject) override;
};

} // namespace VBCalculations

#endif // MONOLITH_CONNECTION_CALCULATOR_HPP
