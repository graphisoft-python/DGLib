// *********************************************************************************************************************
// Description:		Floor Plan Theoretical Cutting Plane Definition Class As Not Event Source
//
// Module:			VBElemOperations
// Namespace:		VBCalculations
// Contact person:	MA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (FLOOR_PLAN_CUT_DATA_NOEVENT_HPP)
#define FLOOR_PLAN_CUT_DATA_NOEVENT_HPP

#pragma once


// from GSRoot
//#include	"Definitions.hpp"
#include	"Md5.hpp"

// from VBElements
#include	"GeneralElem.hpp"
#include	"VBElementsBase.hpp"
#include	"FloorStructure.hpp"

#include	"VBElemOperationsExport.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace VBCalculations {

// --- Class declaration -----------------------------------------------------------------------------------------------


// ****************************************************************************************
//									FloorPlanCutLevels
// ****************************************************************************************

class VB_ELEM_OPERATIONS_DLL_EXPORT FloorPlanCutLevels {

protected:
	double				currCutLevel;
	double				topCutLevel;
	double				bottomCutLevel;
	short				topCutBaseStoryRelativeIndex;
	short				bottomCutBaseStoryRelativeIndex;
	MD5::FingerPrint	cutDataCheckSum;

	MD5::FingerPrint	CalcCheckSum	(void) const;

	double				fixLevel2Absolute0;

public:

	FloorPlanCutLevels ();

	virtual		~FloorPlanCutLevels ();

	virtual bool Set (	double		cutLevelCurrent,
		double		cutLevelTop,
		double		cutLevelBottom,
		short		topStoryRelInd,
		short		bottomStoryRelIndex,
		double		levelFix2Absolute0);

	void		Get	(	double*		cutLevelCurrent,
		double*		cutLevelTop,
		double*		cutLevelBottom,
		short*		topStoryRelInd,
		short*		bottomStoryRelIndex,
		double*		levelFix2Absolute0) const;

	FloorPlanCutLevels (const FloorPlanCutLevels& source);
	FloorPlanCutLevels&	operator= (const FloorPlanCutLevels& source);

	inline  double				GetBelowFixAbsoluteLevel (void) const;
	inline	MD5::FingerPrint	GetCutDataCheckSum (void) const;

	bool	operator == (const FloorPlanCutLevels& rhs) const;
	bool	operator != (const FloorPlanCutLevels& rhs) const;
};



// --- Initializations -------------------------------------------------------------------------------------------------

inline  FloorPlanCutLevels::FloorPlanCutLevels () :
currCutLevel						(1.1),
	topCutLevel						(0.0),
	topCutBaseStoryRelativeIndex	(1),	//BL2007.01.31.	#55819
	bottomCutLevel					(0.0),
	bottomCutBaseStoryRelativeIndex (0),
	fixLevel2Absolute0				(0)
{
}


// --- Get Information from the Current Floor Plan Cut -----------------------------------------------------------------

inline  double  FloorPlanCutLevels::GetBelowFixAbsoluteLevel (void) const
{
	return (fixLevel2Absolute0);
}

inline  MD5::FingerPrint	FloorPlanCutLevels::GetCutDataCheckSum (void) const
{
	return cutDataCheckSum;
}

inline bool	FloorPlanCutLevels::operator == (const FloorPlanCutLevels& rhs) const
{
	return 
		currCutLevel 					== rhs.currCutLevel &&				
		topCutLevel						== rhs.topCutLevel &&				
		bottomCutLevel					== rhs.bottomCutLevel &&
		topCutBaseStoryRelativeIndex	== rhs.topCutBaseStoryRelativeIndex	&&
		bottomCutBaseStoryRelativeIndex	== rhs.bottomCutBaseStoryRelativeIndex;	
}

inline bool	FloorPlanCutLevels::operator != (const FloorPlanCutLevels& rhs) const
{
	return !(*this == rhs);
}


// ****************************************************************************************
//									CurrentStoryCutLevels
// ****************************************************************************************

class VB_ELEM_OPERATIONS_DLL_EXPORT CurrentStoryCutLevels : public FloorPlanCutLevels {

private:
	// temporary data dependent from the current story
	bool				relativeCalculated;
	double				currCutLevelCalculated;
	double				topCutLevelCalculated;
	double				currentStoryLevel;
	double				topBase2Current;
	double				bottomBase2Current;
	short				currentFloorIndex;


public:

	CurrentStoryCutLevels ();
	CurrentStoryCutLevels (const FloorPlanCutLevels& floorPlanCutDataCore, EDB::FloorStructureConstRef floorStructure, short floorIndex);

	virtual		~CurrentStoryCutLevels ();

	virtual bool Set (	double		cutLevelCurrent,
		double		cutLevelTop,
		double		cutLevelBottom,
		short		topStoryRelInd,
		short		bottomStoryRelIndex,
		double		levelFix2Absolute0) override;

	CurrentStoryCutLevels (const CurrentStoryCutLevels& source);
	CurrentStoryCutLevels&	operator= (const CurrentStoryCutLevels& source);

	virtual bool	SetCurrentFloor (EDB::FloorStructureConstRef floorStructure, short floorIndex) /*override : introduced at this level*/;

	inline  double  GetCutPlaneAbsoluteLevel (void) const;
	inline  double  GetAboveCutPlaneAbsoluteLevel (void) const;
	inline  double  GetBelowPlaneAbsoluteLevel (void) const;

	void	CalculateCutAltitudes (	VBElem::ElemViewDepthLimitations	viewDepth,
		double*								aboveAltitude,
		double*								cutAltitude,
		double*								belowAltitude) const;

	void	CalculateCutLevels (VBElem::ElemViewDepthLimitations	viewDepth,
		double*								aboveLevel,
		double*								cutLevel,
		double*								belowLevel) const;

	EDB::StoryWithRange			GetCurrStoryWithRange () const;

	inline  double				GetCutPlaneLevel (void) const;
	inline  double				GetAboveCutPlaneLevel (void) const;
	inline  double				GetBelowPlaneLevel (void) const;

	inline  double				GetBelowFixLevel (void) const;
	inline  bool				IsRelativeCalculated (void) const;
};


EDB::StoryWithRange VB_ELEM_OPERATIONS_DLL_EXPORT GetStoryWithRange (const FloorPlanCutLevels& floorPlanCutLevels, EDB::GeneralElemConstRef elem, short story);


// --- Initializations -------------------------------------------------------------------------------------------------

inline  CurrentStoryCutLevels::CurrentStoryCutLevels () : FloorPlanCutLevels (),
	relativeCalculated				(false),
	currCutLevelCalculated			(0.0),
	topCutLevelCalculated			(0.0),
	currentStoryLevel				(0.0),
	topBase2Current					(3.0),
	bottomBase2Current				(-3.0),
	currentFloorIndex				(-15000)
{

}


inline  CurrentStoryCutLevels::CurrentStoryCutLevels (const FloorPlanCutLevels& floorPlanCutDataCore, EDB::FloorStructureConstRef floorStructure, short floorIndex) : FloorPlanCutLevels (floorPlanCutDataCore),
	relativeCalculated				(false),
	currCutLevelCalculated			(0.0),
	topCutLevelCalculated			(0.0),
	currentStoryLevel				(0.0),
	topBase2Current					(3.0),
	bottomBase2Current				(-3.0),
	currentFloorIndex				(-15000)
{
	SetCurrentFloor (floorStructure, floorIndex);
}

// --- Get Information from the Current Floor Plan Cut -----------------------------------------------------------------

inline  double  CurrentStoryCutLevels::GetCutPlaneAbsoluteLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (currentStoryLevel + currCutLevelCalculated);
}

inline  double  CurrentStoryCutLevels::GetAboveCutPlaneAbsoluteLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (currentStoryLevel + topBase2Current + topCutLevelCalculated);
}

inline  double  CurrentStoryCutLevels::GetBelowPlaneAbsoluteLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (currentStoryLevel + bottomBase2Current + bottomCutLevel);
}

inline  double  CurrentStoryCutLevels::GetCutPlaneLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (currCutLevelCalculated);
}

inline  double  CurrentStoryCutLevels::GetAboveCutPlaneLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (topBase2Current + topCutLevelCalculated);
}

inline  double  CurrentStoryCutLevels::GetBelowPlaneLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (bottomBase2Current + bottomCutLevel);
}

inline  double  CurrentStoryCutLevels::GetBelowFixLevel (void) const
{
	DBASSERT(relativeCalculated);
	return (fixLevel2Absolute0 - currentStoryLevel);
}

inline  bool  CurrentStoryCutLevels::IsRelativeCalculated (void) const
{
	return relativeCalculated;
}

} // namespace VBCalculations

#endif