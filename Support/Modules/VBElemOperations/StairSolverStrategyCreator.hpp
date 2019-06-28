// *********************************************************************************************************************
// Description:		Try to generate stair baseline solutions by eliminating constraints
//
// Module:			VBElemOperations
// Namespace:		StairOperations::Solving
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRSOLVERSTRATEGYCREATOR_HPP_
#define _STAIRSOLVERSTRATEGYCREATOR_HPP_

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

typedef std::function<bool (const StrategyRef)> StrategyProcessor;

class StrategyCreator
{
private:
	enum SolverCallbackResult {
		NotSolution,
		Solution,
		Solution_ReachedMax
	};

	typedef std::function<SolverCallbackResult (const StrategyRef)> SolverCallback;
	typedef std::function<bool (const SolverCallback&, VBElem::StairConstRef, const VBElem::StairPolyline&)> StrategyMethod;

	class StrategyMethodProcessor {
	private:
		SolverCallback					m_callback;
		const UInt32					m_maxStrategyNum;
		UInt32							m_currentStrategyNum;
		VBElem::StairConstRef			m_stair;
		const VBElem::StairPolyline&	m_baseline;

	public:
		StrategyMethodProcessor (const StrategyProcessor& processor, const UInt32 maxStrategyNum, const VBElem::StairPolyline& baseline, VBElem::StairConstRef stair);
		~StrategyMethodProcessor ();

		bool Process (const StrategyMethod& method);
	};

	template <class OffsetWalkinglineType>
	class OffsetWalkinglineInstantiator
	{
	public:
		StairModifierRef	CreateOffsetWalkingline (const VBElem::WalkingLinePosition position, const double offset) const;
	};

	template <class ChangeStepNumType>
	class ChangeStepNumInstantiator
	{
	public:
		StairModifierRef	CreateChangeStepNum (const Int32 diff) const;
	};

	VBElem::StairConstRef			m_stair;
	const VBElem::StairPolyline&	m_baseline;

	static const double	MinimumWalkinglineOffsetMetric;
	static const double	MinimumWalkinglineOffsetImperial;
	static const double	WalkinglineOffsetSmallIntervalMetric;
	static const double	WalkinglineOffsetSmallIntervalImperial;
	static const UInt32	WalkinglineOffsetIntervalMultiplier;

public:
	StrategyCreator (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	~StrategyCreator ();

	StrategyRef	GetUltimateStrategy (void) const;
	void		EnumerateStrategies (const StrategyProcessor& processor, const UInt32 max) const;

private:
	static double		GetMinimumWalkinglineOffset (void);
	static double		GetWalkinglineOffsetSmallInterval (void);
	static StrategyRef	GetUltimateStrategy (const VBElem::StairPolyline& baseline);

	template <typename OffsetWalkinglineType>
	static bool OffsetWalkingLineCore	(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline, const OffsetWalkinglineInstantiator<OffsetWalkinglineType>& instantiator);
	template <typename ChangeStepNumType>
	static bool ChangeNumberOfStepsCore	(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline, const ChangeStepNumInstantiator<ChangeStepNumType>& instantiator);

	static bool OffsetWalkingLine											(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OpenFirstLock												(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OffsetWalkinglineWithOpenFirstLock							(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool ChangeNumberOfSteps											(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool ChangeNumberOfStepsWithOpenFirstLock						(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OpenOneLockExceptFirst										(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OpenFirstAndAnotherLock										(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool WinderTypeChange											(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool WinderTypeChangeWithOpenFirstLock							(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool SegmentTypeChange											(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OneWinderToSymmetricLanding									(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OneWinderToNonSymmetricLanding								(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OneWinderToNonSymmetricLandingWithOpenFirstLock				(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool AllWinderToSymmetricLanding									(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool AllWinderToNonSymmetricLandingWithAllSegmentToRun			(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool OpenAllLock													(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
	static bool UltimateMethod												(const SolverCallback& solverCallback, VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline);
};

} // namespace Solving
} // namespace StairOperations

#endif	// _STAIRSOLVERSTRATEGYCREATOR_HPP_