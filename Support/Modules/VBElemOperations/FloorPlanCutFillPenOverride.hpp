// Contact person : KiP

#ifndef	FLOOR_PLAN_CUTFILLPEN_OVERRIDE_HPP
#define	FLOOR_PLAN_CUTFILLPEN_OVERRIDE_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT FloorPlanCutFillPenOverride
{
public:
	virtual ~FloorPlanCutFillPenOverride ();

	virtual	bool	IsForegroundPenOverridden () const = 0;
	virtual	bool	IsBackgroundPenOverridden () const = 0;
	virtual	short	GetForegroundPen () const = 0;
	virtual	short	GetBackgroundPen () const = 0;
};

class VB_ELEM_OPERATIONS_DLL_EXPORT FloorPlanCutFillPenOverrideModifier : public FloorPlanCutFillPenOverride
{
public:
	virtual ~FloorPlanCutFillPenOverrideModifier ();

	virtual void	SetForegroundPenIsOverriden (bool isOverridden) = 0;
	virtual void	SetBackgroundPenIsOverriden (bool isOverridden) = 0;
	virtual	void	SetForegroundPen (short foregroundPen) = 0;
	virtual	void	SetBackgroundPen (short backgroundPen) = 0;
};

}

#endif
