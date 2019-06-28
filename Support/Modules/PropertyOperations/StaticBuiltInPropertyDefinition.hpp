// Contact person: KiP

#ifndef STATIC_BUILTIN_PROPERTY_DEFINITION_HPP
#define STATIC_BUILTIN_PROPERTY_DEFINITION_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "AutoPtr.hpp"
#include "SharedObject.hpp"
#include "GSFriend.hpp"

// from Property
#include "PropertyValue.hpp"
#include "PropertyCallbackPermissions.hpp"
#include "PropertyTechnology.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// === Predeclarations =================================================================================================

namespace Property {
	class PropertyEvaluationEnvironment;
	class AdditionalDataStorePropertyKey;
	class AdditionalDataStoreGroupKey;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT StaticBuiltInPropertyDefinition : public GS::SharedObject
{
	DECLARE_ROOT_CLASS_INFO

protected:
	StaticBuiltInPropertyDefinition (const GS::Guid& guid, const GS::UniString& name);

public:
	virtual ~StaticBuiltInPropertyDefinition ();

			const GS::Guid&									GetGuid								() const;
			const GS::UniString&							GetName								() const;
			const PropertyDefinitionUserId					GetUserId							() const;
			StaticBuiltInPropertyDefinitionGroupConstPtr	GetGroup							() const;

	virtual const IValueDescriptor*							GetValueDescriptor					() const = 0;
	virtual const GS::Variant*								GetDefaultValue						() const = 0;
	virtual	Measure											GetMeasure							() const = 0;
	virtual	bool											ValueCanBeEditable					() const = 0;
	virtual	bool											UsesAnyOfTheseTechnologies			(const TechnologyList& technologies, Technology::ActionType actionType) const = 0;

			GS::AutoPtr<GS::Variant>						ResolvePropertyValue				(const GS::Variant* originalValue) const;

	virtual bool											IsAvailable							(const PropertyOwner& propertyOwner) const = 0;
	virtual bool											IsEvaluable							(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv) const = 0;
	virtual	PropertyValue									GetValue							(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv, const GS::VariantConversionRules& conversionRules) const = 0;
	virtual	bool											ValueIsEditable						(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv) const = 0;
	virtual	void											SetValue							(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv, const GS::Variant* newValue) const = 0;
	virtual	PropertyOwnerConstPtr							GetPropertyValueSource				(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv) const = 0;
	virtual	Measure											GetPropertyOwnerDependentMeasure	(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv) const = 0;

	virtual	GS::Array<AdditionalDataStorePropertyKey>		GetAdditionalDataStorePropertyKeys	(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv) const = 0;
	virtual GS::Array<AdditionalDataStoreGroupKey>			GetAdditionalDataStoreGroupKeys		(const PropertyOwner& propertyOwner, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv) const = 0;

private:
	const GS::Guid guid;
	const GS::UniString name;
	const StaticBuiltInPropertyDefinitionGroup*	group;

public:
	void SetGroup (GS::Friend<StaticBuiltInPropertyDefinitionGroup>, const StaticBuiltInPropertyDefinitionGroup* group);

	StaticBuiltInPropertyDefinition () = delete;
	StaticBuiltInPropertyDefinition (const StaticBuiltInPropertyDefinition&) = delete;
	StaticBuiltInPropertyDefinition& operator= (const StaticBuiltInPropertyDefinition&) = delete;
};

PropertyDefinitionConstPtr CreateAdapter (const StaticBuiltInPropertyDefinitionConstPtr& prop);

}

#endif
