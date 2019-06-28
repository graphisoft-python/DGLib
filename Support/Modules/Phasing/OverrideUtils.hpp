// *****************************************************************************
//
//						Override Utils
//
// Module:	Phasing
// Contact person: BB
//
// SG compatible
//
// *****************************************************************************

#if !defined (OVERRIDEUTILS_HPP)
#define OVERRIDEUTILS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include	"PhasingExport.hpp"
#include	"PhasingTypes.hpp"

#include	"GeneralElem.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Phasing {

// --- ExtraOverride ----------------------------------------------------------------------------------------

PHASING_DLL_EXPORT
bool	HiddenByExtraOverride (const EDB::GeneralElemConstRef& elem, const Phasing::RenovationStatusType status, 
							   const PlanTypeValueConstRef& planType, const RenovationStatusConstRef& renovationStatusCategory);

PHASING_DLL_EXPORT
bool	NotOverrideByExtraOverride (const EDB::GeneralElemConstRef& elem,
									const Phasing::RenovationStatusType status,
									const Phasing::PlanTypeValueConstRef& planType);


PHASING_DLL_EXPORT
short	GetGraphicOverrideIndexFromStatus (const RenovationStatusType& status);

}

#endif	// OVERRIDEUTILS_HPP
