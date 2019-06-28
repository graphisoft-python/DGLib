// *********************************************************************************************************************
// Description:		Phasing Manager utilities
//
// Module:			Phasing
// Namespace:		PhasingManager
// Contact person:	FP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PHASINGMANAGERUTILS_HPP)
#define PHASINGMANAGERUTILS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include	"PhasingExport.hpp"
#include	"PhasingTypes.hpp"

// from ElementManager
#include	"Project.hpp"

// from LibraryManager
#include	"LibrarySet.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PhasingManager {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------
PHASING_DLL_EXPORT Phasing::PlanTypeRef			FindPlanTypeCategory (EDB::ProjectRef prj);
PHASING_DLL_EXPORT Phasing::PlanTypeConstRef	FindPlanTypeCategory (EDB::ProjectConstRef prj);


//--- Plan Type related methods
PHASING_DLL_EXPORT
Phasing::PlanTypeValueConstRef		GetDerivedElemPlanType (const EDB::GeneralElemConstRef& elem, const Phasing::PlanTypeConstRef& planTypeCategory);
PHASING_DLL_EXPORT
bool								IsPlanTypeDependent (const Phasing::PlanTypeValueConstRef& planTypeValue);
PHASING_DLL_EXPORT
Phasing::PlanTypeConstRef			GetPlanTypeCategory (CAT::CategorySetConstRef categorySet);
PHASING_DLL_EXPORT 
Phasing::PlanTypeRef				GetPlanTypeCategory (EDB::ProjectRef prj, bool isMainProject);
PHASING_DLL_EXPORT
Phasing::PlanTypeConstRef			GetPlanTypeCategory (EDB::ProjectConstRef prj, bool isMainProject);
PHASING_DLL_EXPORT
Phasing::PlanTypeValueConstRef		FindPlanTypeValueByName (Phasing::PlanTypeConstRef planTypeCategory, const GS::UniString& planTypeName);
PHASING_DLL_EXPORT
Phasing::PlanTypeValueConstRef		FindPlanTypeValueByNameFailureProof (Phasing::PlanTypeConstRef planTypeCategory, const GS::UniString& planTypeName);
PHASING_DLL_EXPORT
Phasing::PlanTypeValueConstRef		FindFirstValidPlanTypeValue (Phasing::PlanTypeConstRef planTypeCategory);

//--- Renovation Status related methods
PHASING_DLL_EXPORT
Phasing::RenovationStatusType		GetDerivedRenovationStatus (const EDB::GeneralElemConstRef& elem, const Phasing::RenovationStatusConstRef& renovationStatusCategory, 
																const LM::LibrarySet* librarySet, bool* defined);
PHASING_DLL_EXPORT
Phasing::RenovationStatusType			RenovationStatusValueToType (const Phasing::RenovationStatusValueConstRef& renovationStatusValue);
PHASING_DLL_EXPORT
Phasing::RenovationStatusValueConstRef	ProjectRenovationStatusTypeToValue (const Phasing::RenovationStatusType renovationStatusType, const EDB::ProjectConstRef& prj);
PHASING_DLL_EXPORT
Phasing::RenovationStatusType		GetOppositeStatus (Phasing::RenovationStatusType holeStatus);

//--- GraphicOverride related methods
PHASING_DLL_EXPORT
bool								IsOverrideEnabled (const Phasing::RenovationStatusType status, const Phasing::PlanTypeValueConstRef& planTypeValue);

PHASING_DLL_EXPORT
bool								IsStatusVisible (const Phasing::RenovationStatusType status, const Phasing::PlanTypeValueConstRef& planTypeValue);

PHASING_DLL_EXPORT
bool								IsStatusShown (const Phasing::RenovationStatusType status, const Phasing::PlanTypeValueConstRef& planTypeValue);

PHASING_DLL_EXPORT
bool								IsOverrideSymbolic (const Phasing::RenovationStatusType status, const Phasing::PlanTypeValueConstRef& planTypeValue);

PHASING_DLL_EXPORT
bool								IsElemVisible (const EDB::GeneralElemConstRef& elem, const Phasing::PlanTypeValueConstRef& planTypeValue, 
												   const Phasing::PlanTypeConstRef& planTypeCategory, const Phasing::RenovationStatusConstRef& renovationStatusCategory, const LM::LibrarySet* librarySet);
PHASING_DLL_EXPORT
bool								IsElemVisible (const EDB::GeneralElemConstRef& elem, const Phasing::RenovationStatusType elemStatus, const Phasing::PlanTypeValueConstRef& planTypeValue,
												   const Phasing::PlanTypeConstRef& planTypeCategory, const Phasing::RenovationStatusConstRef& renovationStatusCategory, const LM::LibrarySet* librarySet);
PHASING_DLL_EXPORT
bool								IsWindowDoorVisible (const EDB::GeneralElemConstRef& elem, const Phasing::PlanTypeValueConstRef& planTypeValue, 
														const Phasing::PlanTypeConstRef& planTypeCategory, const Phasing::RenovationStatusConstRef& renovationStatusCategory);

PHASING_DLL_EXPORT
bool								IsHoleReplacementVisible (const EDB::GeneralElemConstRef& opening, const Phasing::PlanTypeValueConstRef& planTypeValue, 
															  const Phasing::PlanTypeConstRef& planTypeCategory, const Phasing::RenovationStatusConstRef& renovationStatusCategory);


}	// namespace PhasingManager

#endif //PHASINGMANAGERUTILS_HPP