// *********************************************************************************************************************
// Description:		StairOperationsTypes
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	NYD, JG, CSP, KG
//
// SG compatible
// *********************************************************************************************************************

#ifndef _STAIROPERATIONSTYPES_HPP_
#define _STAIROPERATIONSTYPES_HPP_

namespace StairMVO {

enum Stair3DDetailLevel {
	// Controls the way stairs are displayed in 3D
	StairFullDrawing = 1,
	StairSchematicDrawing = 2
};

enum Stair2DDisplayMode {
	// Controls the way stairs are displayed in 2D
	StairFloorPlanDisplay = 1,
	StairReflectedCeilingDisplay = 2
};

enum Stair2DDisplayComponent {
	// Components that the 2D display may use
	StairWalkingLine = 0,
	StairNumbering = 1,
	StairUPDOWNText = 2,
	StairDescription = 3,
	StairTreadAccessories = 4,
	StairStructureBeamSupport = 5,
	StairStructureStringers = 6,
	StairStructureCantilevered = 7,
	StairStructureMonolith = 8
};

};

#endif // _STAIROPERATIONSTYPES_HPP_