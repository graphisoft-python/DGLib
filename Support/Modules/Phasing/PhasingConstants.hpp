// *********************************************************************************************************************
// Description:		Phasing constants
//
// Module:			Phasing
// Namespace:		Phasing
// Contact person:	BeA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PHASINHMANAGERCONSTANTS_HPP)
#define PHASINHMANAGERCONSTANTS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include	"PhasingExport.hpp"

#include	"RenovationStatusCategory.hpp"
#include	"RenovationStatusValue.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------


namespace Phasing {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	// --- Variable declarations -------------------------------------------------------------------------------------------

extern const GS::UniString&					PlanTypeCategoryName;
extern const GS::UniString&					PlanTypeCategoryLongName;
extern const GS::UniString&					PlanTypeCategoryObjectName;
extern const GS::UniString&					UndefinedPlanTypeValueName;
extern const GS::UniString&					LocalizedLegacyRenovationStatus;

extern const GS::UnID&						PatchID;

PHASING_DLL_EXPORT
void	InitConstants (	const GS::UniString& planTypeCategoryName,
						const GS::UniString& planTypeCategoryLongName,
						const GS::UniString& planTypeCategoryObjectName,
						const GS::UniString& undefinedPlanTypeValueName,
						const GS::UniString& localizedLegacyRenovationStatus,
						const GS::UnID& patchID
					);


	// --- Function declarations -------------------------------------------------------------------------------------------
}	// namespace Phasing

#endif // PHASINHMANAGERCONSTANTS_HPP