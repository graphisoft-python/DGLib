// Contact person : KiP

#ifndef PROPERTY_OPERATIONS_TYPES_HPP
#define PROPERTY_OPERATIONS_TYPES_HPP

#pragma once

// from GSRoot
#include "SharedObject.hpp"

// from Property
#include "PropertyTypes.hpp"


namespace Property {

	class PropertyOwner;
	typedef GS::ConstSharedPtr<PropertyOwner> PropertyOwnerConstPtr;

	class StaticBuiltInPropertyDefinition;
	typedef GS::SharedPtr<StaticBuiltInPropertyDefinition> StaticBuiltInPropertyDefinitionPtr;
	typedef GS::ConstSharedPtr<StaticBuiltInPropertyDefinition> StaticBuiltInPropertyDefinitionConstPtr;

	class StaticBuiltInPropertyDefinitionGroup;
	typedef GS::SharedPtr<StaticBuiltInPropertyDefinitionGroup> StaticBuiltInPropertyDefinitionGroupPtr;
	typedef GS::ConstSharedPtr<StaticBuiltInPropertyDefinitionGroup> StaticBuiltInPropertyDefinitionGroupConstPtr;

	class StaticBuiltInPropertyDefinitionContainer;
	typedef GS::SharedPtr<StaticBuiltInPropertyDefinitionContainer> StaticBuiltInPropertyDefinitionContainerPtr;
	typedef GS::ConstSharedPtr<StaticBuiltInPropertyDefinitionContainer> StaticBuiltInPropertyDefinitionContainerConstPtr;

	class DynamicBuiltInPropertyDefinition;
	typedef GS::SharedPtr<DynamicBuiltInPropertyDefinition> DynamicBuiltInPropertyDefinitionPtr;
	typedef GS::ConstSharedPtr<DynamicBuiltInPropertyDefinition> DynamicBuiltInPropertyDefinitionConstPtr;

	class DynamicBuiltInPropertyDefinitionGroup;
	typedef ODB::Ref<DynamicBuiltInPropertyDefinitionGroup> DynamicBuiltInPropertyDefinitionGroupRef;
	typedef ODB::ConstRef<DynamicBuiltInPropertyDefinitionGroup> DynamicBuiltInPropertyDefinitionGroupConstRef;

	class DynamicBuiltInPropertyDefinitionContainer;
	typedef ODB::Ref<DynamicBuiltInPropertyDefinitionContainer> DynamicBuiltInPropertyDefinitionContainerRef;
	typedef ODB::ConstRef<DynamicBuiltInPropertyDefinitionContainer> DynamicBuiltInPropertyDefinitionContainerConstRef;

	class PropertyDefinitionExtension;
	typedef GS::SharedPtr<PropertyDefinitionExtension> PropertyDefinitionExtensionPtr;
	typedef GS::ConstSharedPtr<PropertyDefinitionExtension> PropertyDefinitionExtensionConstPtr;

	class PropertyEvaluationEnvironmentSource;
	typedef GS::SharedPtr<PropertyEvaluationEnvironmentSource> PropertyEvaluationEnvironmentSourcePtr;
	typedef GS::ConstSharedPtr<PropertyEvaluationEnvironmentSource> PropertyEvaluationEnvironmentSourceConstPtr;

	class PropertyValueCache;
	typedef GS::SharedPtr<PropertyValueCache> PropertyValueCachePtr;
	typedef GS::ConstSharedPtr<PropertyValueCache> PropertyValueCacheConstPtr;

	class ClassId;
	class PropertyAccessor;
}

namespace EDB {
	class DefaultElem;
	class GeneralElem;
	typedef ODB::Ref<GeneralElem> GeneralElemRef;
	typedef ODB::ConstRef<GeneralElem> GeneralElemConstRef;
}

typedef GS::Array<GS::Guid> GuidArray;

#endif

