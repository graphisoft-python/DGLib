// Contact person :	KiP

#ifndef COMPONENT_BUILDING_MATERIAL_GETTER_HPP
#define COMPONENT_BUILDING_MATERIAL_GETTER_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "PropertyEvaluationEnvironment.hpp"

// === Predeclarations =================================================================================================

namespace VBAttr {
	class BuildingMaterial;
	typedef ODB::Ref<BuildingMaterial> BuildingMaterialRef;
	typedef ODB::ConstRef<BuildingMaterial> BuildingMaterialConstRef;
}

namespace VBEO {
	class ModelElemComponentId;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ComponentBuildingMaterialGetter : public GS::SharedObject
{
public:
	virtual ~ComponentBuildingMaterialGetter ();
	virtual VBAttr::BuildingMaterialConstRef GetBuildingMaterial (const PropertyOwnerConstPtr& propertyOwner, const VBEO::ModelElemComponentId& componentId) const = 0;
};

class PROPERTY_OPERATIONS_DLL_EXPORT ComponentBuildingMaterialGetterImpl : public ComponentBuildingMaterialGetter
{
public:
	ComponentBuildingMaterialGetterImpl (const EvaluationEnvironment<CallbackPermissions::QuantityCalculatorPermission>& propEvanEnv);
	virtual ~ComponentBuildingMaterialGetterImpl ();
	virtual VBAttr::BuildingMaterialConstRef GetBuildingMaterial (const PropertyOwnerConstPtr& propertyOwner, const VBEO::ModelElemComponentId& componentId) const override final;

private:
	EvaluationEnvironment<CallbackPermissions::QuantityCalculatorPermission> env;
};

typedef GS::ConstSharedPtr<ComponentBuildingMaterialGetter> ComponentBuildingMaterialGetterConstPtr;

}

#endif
