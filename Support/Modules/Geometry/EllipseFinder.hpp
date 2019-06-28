#if !defined (ELLIPSE_FINDER_HPP)
#define ELLIPSE_FINDER_HPP

#pragma once
#include "GeometricDefinitions.h"
#include "OptimizationProblem.hpp"
#include "Point2D.hpp"
#include "SensValue.hpp"

namespace Geometry
{

class Ellipse; 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT EllipseFinder : public OptimizationProblem, public OptimizationVarOwner
{
public:
	static size_t NumVars () { return 4; }

	EllipseFinder (const GS::Array <Coord>& onEllipsPointsInit);
	virtual ~EllipseFinder ();

	void CalcEllipse (Ellipse& e);

private:
	virtual void StartOptimization () override /*OptimizationProblem*/;
	virtual void GetOptVariableValues (AlgVector& optVarVals) const override /*OptimizationProblem*/;
	virtual void SetOptVariableValues (const size_t iterCntr, const AlgVector& optVarVals) override /*OptimizationProblem*/;

	virtual void CalcStep (const size_t optimizationIterCntr, AlgVector& optVarStepVals) const override /*OptimizationProblem*/;

	virtual void EvaluateObjective (const AlgVector& at, double& objValue) override /*OptimizationProblem*/;
	virtual void EvaluateObjective (AlgVector& at, double& objValue) override /*OptimizationProblem*/;
	virtual void EvaluateObjective (AlgVector& at, SensValue& objValue) override /*OptimizationProblem*/;

	virtual void StoreConvergenceData () override final {}
	virtual bool IsSolutionSatisfactory (double& maxNormError) const override /*OptimizationProblem*/;
	virtual bool MustStopSolution () const override /*OptimizationProblem*/;



	void GetEllipse (Coord& origo, Vector2d& mainAxis, Vector2d& sideAxis) const;
	void CalcObjective (double& objValue) const;
	void CalcObjective (SensValue& objValue) const;

	void CalcGenDiameter (const Coord& p, double& diameter) const;
	void CalcGenDiameter (const Coord& p, SensValue& diameter) const;

	void CalcAllGenDoubleDiameters () const;
	void CalcAllGenSensDiameters () const;

	virtual void Transfer (const AlgVector& optVarVals, TransferOp& tr) override /*OptimizationVarOwner*/;
	virtual void Transfer (AlgVector& optVarVals, TransferOp& tr) override /*OptimizationVarOwner*/;
	virtual size_t GetNumOptVars () const override /*OptimizationVarOwner*/;

	//optimization variables:
	SensValue	f1X, f1Y;
	SensValue	f2X, f2Y;

	//the points, supposed to be on an ellips to be found:
	const GS::Array <Coord> onEllipsPoints;

	//on flight cache data:
	mutable GS::Array <double>		DoubleDiameters;
	mutable GS::Array <SensValue>	SensDiameters;
};

}

#endif //ELLIPSE_FINDER_HPP

