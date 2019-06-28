// *********************************************************************************************************************
// Description:		Try to generate stair baseline solutions by eliminating constraints
//
// Module:			VBElemOperations
// Namespace:		StairOperations::Solving
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRSOLVERSTRATEGYCHANGES_HPP_
#define _STAIRSOLVERSTRATEGYCHANGES_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElemOperations
#include "StairSolverStrategy.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

namespace StairOperations {
namespace Solving {

class StrategyChanges
{
public:
	enum ChangeType {
		WalkinglineChanged,
		SegmentLengthChanged,
		SegmentTypeChanged,
		TurningChanged,
		TreadNumChanged
	};

	struct Change
	{
		ChangeType	m_type;
		UInt32		m_index;
		double		m_value;
		Int32		m_diff;
		StairPartModifier::TurningType m_turningType;
		StairPartModifier::SegmentType m_segmentType;

		Change (ChangeType type, UInt32 index, double value, Int32 diff,
			StairPartModifier::TurningType turningType = StairPartModifier::UndefinedTurning, StairPartModifier::SegmentType segmentType = StairPartModifier::UndefinedSegment) :
			m_type (type), m_index (index), m_value (value), m_diff (diff), m_turningType (turningType), m_segmentType (segmentType)
		{
		}
	};

private:
	VBElem::StairConstRef	m_stair;
	const StrategyRef		m_strategy;

public:
	StrategyChanges (VBElem::StairConstRef stair, const StrategyRef strategy);
	~StrategyChanges ();

	GS::Array<Change>	GetChanges ();
};

} // namespace Solving
} // namespace StairOperations

#endif	// _STAIRSOLVERSTRATEGYCHANGES_HPP_