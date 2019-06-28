// *********************************************************************************************************************
// Description:		Try to generate stair baseline solutions by eliminating constraints
//
// Module:			VBElemOperations
// Namespace:		StairOperations
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRSOLVER_HPP_
#define _STAIRSOLVER_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElemOperations
#include "StairSolverStrategy.hpp"
#include "StairSolverStrategyCreator.hpp"
#include "StairSolverImageGenerator.hpp"
#include "StairSolverStrategyChanges.hpp"

// from VBElements
#include "VBElements/StairTypes.hpp"
#include "VBElements/StairDefault.hpp"
#include "VBElements/StairPolylineEdgeData.hpp"
#include "VBElements/StairPolylineVertexData.hpp"

#include "VBElemOperationsExport.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------

namespace StairOperations {

class VB_ELEM_OPERATIONS_DLL_EXPORT Solver
{
public:
	typedef std::function<void (const Solving::StrategyRef, const NewDisplay::NativeImage&, const GS::Array<Solving::StrategyChanges::Change>&)>	SolutionEnumerator;

	enum SolverResult {
		NoSolvingNeeded,
		SolutionFound,
		CannotSolve
	};

protected:
	VBElem::StairConstRef						m_stair;
	VBElem::StairPolyline						m_baseline;
	VBElem::StairRestrictions					m_restrictions;
	Solving::StrategyCreator					m_creator;
	mutable GS::Array<VBElem::StairPolyline>	m_solutions;	// for only internal use to filter equal baselines

private:
	static const UInt32 MaxSolutionNumber;

public:
	Solver (VBElem::StairConstRef stair);
	Solver (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions);
	virtual ~Solver ();

	bool			IsValidState (void);
	bool			HasSolution (void);
	void			EnumerateSolutions (const double viewAngle, double resolutionFactor, const SolutionEnumerator& enumerator);
	virtual bool	ApplyStrategy (VBElem::StairRef stair, const Solving::StrategyRef strategy) = 0;

	VBElem::StairRestrictions	GetStairRestrictions (void) const { return m_restrictions; }

	static void		NextImageColorSet (void);
	static Solving::StrategyRef GetEmptyStrategy (void);

private:
	Solving::StrategyProcessor	GetStrategyProcessor (const double viewAngle, double resolutionFactor, const SolutionEnumerator& enumerator);
	bool						AddSolution (const VBElem::StairPolyline& baseline) const;
	void						ClearSolutions (void) const;
	bool						ApplyStrategy_Internal (VBElem::StairRef stair, const Solving::StrategyRef strategy);
};


class VB_ELEM_OPERATIONS_DLL_EXPORT BaselineSolver : public Solver
{
protected:
	VBElem::StairPolyline		m_result;
public:
	BaselineSolver (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions);	
	virtual ~BaselineSolver ();

	virtual bool	ApplyStrategy (VBElem::StairRef stair, const Solving::StrategyRef strategy) override;

	SolverResult	Validate (VBElem::StairPolyline* baseline);

	const VBElem::StairPolyline& GetValidBaseline (void) const { return m_baseline; }

	const VBElem::StairPolyline& GetResultBaseline (void) const { return m_result; }

};


class VB_ELEM_OPERATIONS_DLL_EXPORT ContinueBaselineSolver : public BaselineSolver
{
public:
	ContinueBaselineSolver (VBElem::StairConstRef stair, const VBElem::StairPolyline& baseline, const VBElem::StairRestrictions& restrictions);
	virtual ~ContinueBaselineSolver ();

	virtual bool	ApplyStrategy (VBElem::StairRef stair, const Solving::StrategyRef strategy) override;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT DefaultSolver : public Solver
{
private:
	VBElem::StairDefault* const	m_stairDefault;
	VBElem::StairDefault		m_validStairDefault;
	VBElem::StairDefaultChanges	m_changes;

public:
	DefaultSolver (VBElem::StairConstRef stair, VBElem::StairDefault* stairDefault);
	DefaultSolver (VBElem::StairConstRef stair, VBElem::StairDefault* stairDefault, const VBElem::StairDefaultChanges& changes);
	virtual ~DefaultSolver ();

	virtual bool	ApplyStrategy (VBElem::StairRef stair, const Solving::StrategyRef strategy) override;

	static bool		ApplyStrategy (VBElem::StairRef stair,
									const Solving::StrategyRef strategy,
									const VBElem::StairDefault* stairDefault,
									const VBElem::StairDefaultFieldMask& mask);

	enum ValidateMode {
		IgnoreSolutions,
		ApplySolutions
	};

	SolverResult	Validate (ValidateMode validateMode = ApplySolutions);

};

} // namespace StairOperations

#endif	// _STAIRSOLVER_HPP_