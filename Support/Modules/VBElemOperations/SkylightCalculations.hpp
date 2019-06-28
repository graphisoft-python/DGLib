/****************************************************************************/
/*																			*/
/*		       				Skylight Calculations		       				*/
/*																			*/
/****************************************************************************/

#ifndef	_SkylightCalculations_HPP_
#define	_SkylightCalculations_HPP_

#pragma once

// from VBElemOperations
#include	"VBElemOperationsExport.hpp"

// from VBElements
#include	"VBElements/SkylightTypes.hpp"
#include	"VBElements/ShellTypes.hpp"


namespace VBCalculations {

class CurrentStoryCutLevels;

VB_ELEM_OPERATIONS_DLL_EXPORT
bool		IsSkylightVisibleOnFloor (	const VBElem::SkylightConstRef&					skylight, 
										const VBElem::ShellBaseConstRef&				shellBase, 
										const short										floorNum, 
										const VBElem::ElemDisplayOptions&				displayOption,
										const VBCalculations::CurrentStoryCutLevels&	gFloorPlanCutLevels);
}

#endif
