// Contact person : KiP
// Description : Interface collection to access the VBElem data members shown in Floor Plan and Section TabPage on Settings Dialog.

#ifndef	FLOOR_PLAN_APPEARANCE_HPP
#define	FLOOR_PLAN_APPEARANCE_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElemOperations
#include "VBElemOperationsTypes.hpp"
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT FloorPlanAppearance
{
public:
	virtual ~FloorPlanAppearance ();

	virtual FloorPlanCutFillPenOverrideRef			GetCutFillPenOverride			() const = 0;
};

class VB_ELEM_OPERATIONS_DLL_EXPORT FloorPlanAppearanceModifier : public FloorPlanAppearance
{
public:
	virtual ~FloorPlanAppearanceModifier ();

	virtual FloorPlanCutFillPenOverrideRef			GetCutFillPenOverride			() const override = 0;
	virtual FloorPlanCutFillPenOverrideModifierRef	GetCutFillPenOverrideModifier	() const = 0;
};

}

#endif
