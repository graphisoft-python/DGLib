// *********************************************************************************************************************
// Description:		Stair modifiers base class
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRPARTMODIFIER_HPP_
#define _STAIRPARTMODIFIER_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElements
#include "VBElements/StairTypes.hpp"
#include "VBElements/TreadTypes.hpp"

// from GSRoot
#include "Ref.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

class StairPartModifier
{
public:
	enum class Effect : Int32
	{
		NoChange		= 0x00,
		PositionChanged	= 0x01,
		GeometryChanged = 0x02
	};

	enum TurningType {
		UndefinedTurning,
		SymmetricLanding,
		NonSymmetricLanding,
		DINWinder,
		NZEWinder,
		SIPWinder,
		AGNWinder
	};

	enum SegmentType {
		UndefinedSegment,
		StepsSegment,
		LandingSegment,
		DividedLandingSegment,
		WinderSegment
	};

	virtual ~StairPartModifier ();

	virtual Effect	EffectOnTread			(VBElem::TreadConstRef /*tread*/)							const { return Effect::NoChange; }
	virtual Effect	EffectOnWalkingline		(void)														const { return Effect::NoChange; }
	virtual Effect	EffectOnSegmentLength	(const UInt32 /*segmentIndex*/)								const { return Effect::NoChange; }
	virtual Effect	EffectOnSegmentType		(const UInt32 /*segmentIndex*/, SegmentType& /*segment*/)	const { return Effect::NoChange; }
	virtual Effect	EffectOnTurning			(const UInt32 /*turningIndex*/, TurningType& /*turning*/)	const { return Effect::NoChange; }
	virtual Int32	EffectOnTreadNum		(void)														const { return 0; }

	static bool		Test (Effect effect, Effect test);

protected:
	static Effect CalculateOpenLockEffectOnTread (VBElem::TreadConstRef tread, const UInt32 openedEdgeIndex);
};

typedef GS::Ref<StairPartModifier> StairPartModifierRef;


inline StairPartModifier::Effect operator| (StairPartModifier::Effect left, StairPartModifier::Effect right)
{
	return (StairPartModifier::Effect)(static_cast<Int32>(left) | static_cast<Int32>(right));
}

inline StairPartModifier::Effect& operator|= (StairPartModifier::Effect& left, StairPartModifier::Effect right)
{
	left = (StairPartModifier::Effect)(static_cast<Int32>(left) | static_cast<Int32>(right));
	return left;
}

inline StairPartModifier::Effect operator& (StairPartModifier::Effect left, StairPartModifier::Effect right)
{
	return (StairPartModifier::Effect)(static_cast<Int32>(left) & static_cast<Int32>(right));
}

inline StairPartModifier::Effect& operator&= (StairPartModifier::Effect& left, StairPartModifier::Effect right)
{
	left = (StairPartModifier::Effect)(static_cast<Int32>(left) & static_cast<Int32>(right));
	return left;
}


#endif	// _STAIRPARTMODIFIER_HPP_