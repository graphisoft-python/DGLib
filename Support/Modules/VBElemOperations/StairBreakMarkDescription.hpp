// *********************************************************************************************************************
// Description:		StairBreakMarkDescription
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	KG
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIR_BREAKMARK_DESCRIPTION_HPP_
#define _STAIR_BREAKMARK_DESCRIPTION_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"

// from Geometry
#include "Coord.h"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------
// --- Constant definitions	--------------------------------------------------------------------------------------------
// --- Declaration -----------------------------------------------------------------------------------------------------

namespace VBCalculations
{
// === struct StairBreakMarkDescription ==================================================================================


struct VB_ELEM_OPERATIONS_DLL_EXPORT StairBreakMarkDescription
{
	enum BreakMarkPosition {
		LowerBreakMarkBottomLine	= 1,
		LowerBreakMarkTopLine		= 2,
		UpperBreakMarkBottomLine	= 3,
		UpperBreakMarkTopLine		= 4
	};

	bool															validLowerBreakMarkPos;
	bool															validUpperBreakMarkPos;
	double															lowerBreakMarkAngle;
	double															upperBreakMarkAngle;
	double															lowerBreakMarkDistance;
	double															upperBreakMarkDistance;

	Coord															breakMarkLowerPoint;
	Coord															breakMarkLowerDistancePoint;
	Coord															breakMarkLowerRotationPoint;
	Coord															breakMarkUpperPoint;
	Coord															breakMarkUpperDistancePoint;
	Coord															breakMarkUpperRotationPoint;
	GS::Array<GS::Array<Coord>>										breakMarkEndPoints; //Use BreakMarkPosition for indexing
	GS::Array<GS::Array<Coord>>										breakMarkOverhangEndPoints; //Use BreakMarkPosition for indexing

	StairBreakMarkDescription ();

	GSErrCode						Read							(GS::IChannel& ic);
	GSErrCode						Write							(GS::OChannel& oc) const;
};
	

}		// namespace VBCalculations

#endif	// _STAIR_BREAKMARK_DESCRIPTION_HPP_