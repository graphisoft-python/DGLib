// *********************************************************************************************************************
// Description:		Converts the smooth bottom monolith stair structure's surface
//
// Module:			VBElemOperations
// Namespace:		StairOperations
// Contact person:	TBa, CsetA
//
// *********************************************************************************************************************

#ifndef SMOOTHBOTTOMBEGINENDCALCULATOR_HPP
#define SMOOTHBOTTOMBEGINENDCALCULATOR_HPP

#pragma once

#include "TreadTypes.hpp"
#include "StairStructureTypes.hpp"

#include "VBElemOperationsExport.hpp"

namespace StairOperations {

class VB_ELEM_OPERATIONS_DLL_EXPORT SmoothBottomBeginEndCalculator {
private:
	VBElem::StairStructureConstRef		m_structure;
	GS::Array<double>					m_defaultLevels;	// elevations of structure top under each tread without any customizations
	double								m_defRiserOffset;	// Horizontal offset of structure trailing edge relative to trailing of scheme polygon under riser
															// Calculated from the default levels, nosing, slanting, etc.
	double								m_prevStructureLevel;
	bool								m_isOneStepped;
	double								m_begLevelCorrection;
	double								m_endLevelCorrection;
	bool								m_isThinning;

	GS::Array<double>					m_thicknessAtRiser;		// Needed thickness of structure at riser (non-identical if structure IsThinning)
	double								m_thickness;
	double								m_thickness2;			// if structure is not thinning then it is equal to thickness
	double								m_offset;				// used for headroom z offset
	VBElem::TreadConstRef				m_beginTread;
	VBElem::TreadConstRef				m_endTread;

	SmoothBottomBeginEndCalculator (const VBElem::StairStructureConstRef& structure);

public:
	SmoothBottomBeginEndCalculator ();
	static SmoothBottomBeginEndCalculator CreateForStructure	(const VBElem::StairStructureConstRef& structure, const GS::Array<double>& thicknessAtRisers);
	static SmoothBottomBeginEndCalculator CreateForStructure	(const VBElem::StairStructureConstRef& structure);
	static SmoothBottomBeginEndCalculator CreateForDraining		(const VBElem::StairStructureConstRef& structure, double thickness);
	static SmoothBottomBeginEndCalculator CreateForHeadroom		(const VBElem::StairStructureConstRef& structure, double thickness, double offset);

	bool		GetBottomLineForSmoothBegin	(Coord* bottomLinePt, Vector* bottomLineDir) const;
	bool		GetBottomLineForSmoothEnd	(Coord* bottomLinePt, Vector* bottomLineDir) const;
	double		GetLoweringForSmoothAtBegin	(bool useLevelCorrection) const;
	double		GetLoweringForSmoothAtEnd	(bool useLevelCorrection) const;

	double		GetSlopeAtBegin () const;
	double		GetSlopeAtEnd () const;

	double		GetZOffset		() const { return m_offset;}
	double		GetThickness	() const { return m_thickness; }
	double		GetThickness2	() const { return m_thickness2; }

	PlaneEq		GetBeginCutPlane			(const VBElem::TreadPolygon& firstPoly, bool invert = false) const;
	PlaneEq		GetEndCutPlane				(const VBElem::TreadPolygon& lastPoly, bool invert = false) const;
};

VB_ELEM_OPERATIONS_DLL_EXPORT double	CalcRunLandingAutomaticDX (const SmoothBottomBeginEndCalculator& smoothCalc, double runEndLevel, double landingBottomLevel);
VB_ELEM_OPERATIONS_DLL_EXPORT double	CalcLandingRunAutomaticDX (const SmoothBottomBeginEndCalculator& smoothCalc, double runStartLevel, double levelToReach);

} // namespace

#endif // SMOOTHBOTTOMBEGINENDCALCULATOR_HPP
