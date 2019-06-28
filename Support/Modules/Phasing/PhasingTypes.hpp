// *****************************************************************************
//
//					PhasingTypes
//
// Module:			Phasing
// Namespace:		Phasing
// Contact person:	BB
//
// SG compatible
//
// *****************************************************************************


#if !defined PHASINGTYPES_HPP
#define PHASINGTYPES_HPP

#pragma once

// from GSRoot
#include	"Array.hpp"

// from ObjectDatabase
#include	"ODBReference.hpp"

namespace Phasing {

class PlanTypeValue;
class RenovationStatusValue;
class RenovationStatusCategory;
class PlanTypeCategory;

enum RenovationStatusType {
	InvalidStatus		= -1,	// error handling only
	FirstStatusIndex	= 0,

	UndefinedStatus		= 0,	// internal use only, e.g. read from dxf to idf
	ExistingStatus		= 1,	// if read from dxf to plan --- DEFAULT
	NewStatus			= 2,
	DemolishedStatus	= 3,

	MaxStatusIndex		= 3
};

enum RenovationStatusDisplay {
	SettingsDisplay				= 0,	//show
	OverrideDisplay				= 1,	//override
	NotDisplay					= 2		//hide
};

typedef short	IDElem;	

typedef struct {
	RenovationStatusType	renovationStatus;
	bool					isElemEditable;
	IDElem					idLastSelected;
} ElemStatusInformation;

typedef GS::ArrayFB<RenovationStatusDisplay, MaxStatusIndex>	FilterStorageType;
typedef GS::ArrayFB<GS::ArrayFB<short, 2>, MaxStatusIndex>		ExtraOverrideStorageType;

typedef ODB::Ref<PlanTypeCategory>				PlanTypeRef;
typedef ODB::ConstRef<PlanTypeCategory>			PlanTypeConstRef;
typedef ODB::Ref<PlanTypeValue>					PlanTypeValueRef;
typedef ODB::ConstRef<PlanTypeValue>			PlanTypeValueConstRef;
typedef	ODB::RefList<PlanTypeValue>				PlanTypeValueRefList;
typedef	ODB::ConstRefList<PlanTypeValue>		PlanTypeValueConstRefList;

typedef ODB::ConstRef<RenovationStatusCategory>	RenovationStatusConstRef;
typedef ODB::Ref<RenovationStatusCategory>		RenovationStatusRef;
typedef ODB::ConstRef<RenovationStatusValue>	RenovationStatusValueConstRef;
typedef ODB::Ref<RenovationStatusValue>			RenovationStatusValueRef;

typedef	GS::ArrayFB<bool, MaxStatusIndex + 1>	StatusSwitches;
typedef GS::Array<StatusSwitches>				StatusSwitchesArray;

} // namespace Phasing

#endif // PHASINGTYPES_HPP
