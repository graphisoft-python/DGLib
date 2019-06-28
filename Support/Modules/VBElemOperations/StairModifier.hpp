// *********************************************************************************************************************
// Description:		Stair modifiers
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRMODIFIER_HPP_
#define _STAIRMODIFIER_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElemOperations
#include "StairPartModifierBase.hpp"

// from VBElements
#include "StairTypes.hpp"
#include "TreadTypes.hpp"
#include "StairRestrictions.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

class IStairModifier : public StairPartModifier
{
public:
	virtual ~IStairModifier ();

	virtual bool IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const = 0;
	virtual bool Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const = 0;
};

typedef GS::Ref<IStairModifier> StairModifierRef;


class OffsetWalkingline : public IStairModifier
{
private:
	VBElem::WalkingLinePosition m_position;
	double m_offset;

public:
	OffsetWalkingline (const VBElem::WalkingLinePosition position, const double offset);
	OffsetWalkingline (const OffsetWalkingline& source);
	virtual ~OffsetWalkingline ();

	virtual bool IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const override;
	virtual bool Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const override;

	virtual StairPartModifier::Effect EffectOnWalkingline (void) const override;
};

typedef GS::Ref<OffsetWalkingline> OffsetWalkinglineRef;


class OffsetWalkinglineOpenFirstLock : public IStairModifier
{
private:
	VBElem::WalkingLinePosition m_position;
	double m_offset;

public:
	OffsetWalkinglineOpenFirstLock (const VBElem::WalkingLinePosition position, const double offset);
	OffsetWalkinglineOpenFirstLock (const OffsetWalkinglineOpenFirstLock& source);
	virtual ~OffsetWalkinglineOpenFirstLock ();

	virtual bool IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const override;
	virtual bool Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const override;

	virtual StairPartModifier::Effect EffectOnWalkingline (void) const override;
	virtual StairPartModifier::Effect EffectOnTread (VBElem::TreadConstRef tread) const override;
	virtual StairPartModifier::Effect EffectOnSegmentLength (const UInt32 segmentIndex) const override;
};

typedef GS::Ref<OffsetWalkinglineOpenFirstLock> OffsetWalkinglineOpenFirstLockRef;


class ChangeStepNum : public IStairModifier
{
private:
	Int32	m_diff;

public:
	ChangeStepNum (const Int32 diff);
	ChangeStepNum (const ChangeStepNum& source);
	virtual ~ChangeStepNum ();

	virtual bool IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const override;
	virtual bool Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const override;

	virtual Int32 EffectOnTreadNum (void) const override;
};

typedef GS::Ref<ChangeStepNum> ChangeStepNumRef;


class ChangeStepNumOpenFirstLock : public IStairModifier
{
private:
	Int32	m_diff;

public:
	ChangeStepNumOpenFirstLock (const Int32 diff);
	ChangeStepNumOpenFirstLock (const ChangeStepNumOpenFirstLock& source);
	virtual ~ChangeStepNumOpenFirstLock ();

	virtual bool IsAvailable (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline) const override;
	virtual bool Execute (VBElem::StairRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions) const override;

	virtual Int32 EffectOnTreadNum (void) const override;
	virtual StairPartModifier::Effect EffectOnTread (VBElem::TreadConstRef tread) const override;
	virtual StairPartModifier::Effect EffectOnSegmentLength (const UInt32 segmentIndex) const override;
};

typedef GS::Ref<ChangeStepNumOpenFirstLock> ChangeStepNumOpenFirstLockRef;


#endif	// _STAIRMODIFIER_HPP_