// *********************************************************************************************************************
// Description:		CurtainWallOperationsTypes
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	FLA
//
// SG compatible
// *********************************************************************************************************************

#ifndef _CURTAINWALLOPERATIONSTYPES_HPP_
#define _CURTAINWALLOPERATIONSTYPES_HPP_

#include "Definitions.hpp"

namespace CurtainWallMVO {


enum CWComponentDetailLevel {
	// Controls the way curtain wall components are displayed
	CWCompNoDrawing			= 0,
	CWCompLinearDrawing		= 1,
	CWCompSchematicDrawing	= 2,
	CWCompSimplifiedDrawing = 3,
	CWCompFullDrawing		= 4
};


};

#endif // _CURTAINWALLOPERATIONSTYPES_HPP_