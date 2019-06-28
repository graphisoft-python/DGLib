// *********************************************************************************************************************
// Description:		Try to generate stair baseline solutions by eliminating constraints
//
// Module:			VBElemOperations
// Namespace:		StairOperations::Solving
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRSOLVERSTRATEGY_HPP_
#define _STAIRSOLVERSTRATEGY_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElements
#include "VBElements/StairTypes.hpp"
#include "VBElements/StairRestrictions.hpp"

// from VBElemOperations
#include "BaselineModifier.hpp"
#include "StairModifier.hpp"
#include "VBElemOperationsExport.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

namespace StairOperations {
namespace Solving {

class VB_ELEM_OPERATIONS_DLL_EXPORT Strategy
{
protected:
	typedef std::function<StairPartModifier::Effect (const GS::Ref<StairPartModifier>)> ModifierProcessor;

public:
	Strategy ();
	virtual ~Strategy ();

	virtual bool	Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const = 0;
	virtual bool	IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const = 0;

	StairPartModifier::Effect	EffectOnTread (VBElem::TreadConstRef tread) const;
	StairPartModifier::Effect	EffectOnWalkingline (void) const;
	StairPartModifier::Effect	EffectOnSegmentLength (const UInt32 segmentIndex) const;
	StairPartModifier::Effect	EffectOnSegmentType (const UInt32 segmentIndex, StairPartModifier::SegmentType& segmentType) const;
	StairPartModifier::Effect	EffectOnTurning (const UInt32 turningIndex, StairPartModifier::TurningType& turningType) const;
	virtual Int32				EffectOnTreadNum (void) const = 0;

protected:
	virtual StairPartModifier::Effect	AnyModifier (const ModifierProcessor& processor) const = 0;
};		// Strategy

typedef GS::Ref<Strategy> StrategyRef;


class StairModStrategy : public Strategy
{
private:
	StairModifierRef m_modifier;

public:
	StairModStrategy (const StairModStrategy& source);
	StairModStrategy (StairModifierRef modifier);
	virtual ~StairModStrategy ();

	bool	Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const override;
	bool	IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const override;
	Int32	EffectOnTreadNum (void) const override;

protected:
	StairPartModifier::Effect	AnyModifier (const ModifierProcessor& processor) const override;
};		// StairModStrategy

typedef GS::Ref<StairModStrategy> StairModStrategyRef;


class BaselineModStrategy : public Strategy
{
private:
	GS::Array<BaselineModifierRef> m_modifiers;

public:
	BaselineModStrategy ();
	BaselineModStrategy (const BaselineModStrategy& source);
	BaselineModStrategy (BaselineModifierRef modifier);
	virtual ~BaselineModStrategy ();

	bool	Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const override;
	bool	IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const override;
	Int32	EffectOnTreadNum (void) const override;

	void	Add (BaselineModifierRef modifier);

protected:
	StairPartModifier::Effect	AnyModifier (const ModifierProcessor& processor) const override;

private:
	VBElem::StairPolyline	GetModifiedBaseline (const VBElem::StairPolyline& baseline) const;
};		// BaselineModStrategy

typedef GS::Ref<BaselineModStrategy> BaselineModStrategyRef;


} // namespace Solving
} // namespace StairOperations

#endif	// _STAIRSOLVERSTRATEGY_HPP_
