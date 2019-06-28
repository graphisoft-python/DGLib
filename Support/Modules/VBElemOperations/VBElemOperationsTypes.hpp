#ifndef VBELEM_OPERATIONS_TYPES_HPP
#define VBELEM_OPERATIONS_TYPES_HPP

#pragma once

// from GSRoot
#include "Ref.hpp"


namespace VBEO {

class ModelElemStructure;
typedef GS::Ref<ModelElemStructure> ModelElemStructureRef;

class ModelElemComponent;
typedef GS::Ref<ModelElemComponent> ModelElemComponentRef;

class ModelElemComponentId;

class FloorPlanCutFillPenOverride;
class FloorPlanCutFillPenOverrideModifier;
typedef GS::Ref<FloorPlanCutFillPenOverride> FloorPlanCutFillPenOverrideRef;
typedef GS::Ref<FloorPlanCutFillPenOverrideModifier> FloorPlanCutFillPenOverrideModifierRef;

class FloorPlanAppearance;
class FloorPlanAppearanceModifier;
typedef GS::Ref<FloorPlanAppearance> FloorPlanAppearanceRef;
typedef GS::Ref<FloorPlanAppearanceModifier> FloorPlanAppearanceModifierRef;

}

#endif
