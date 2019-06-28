// Contact person: KiP

#ifndef DYNAMIC_BUILTIN_PROPERTY_DEFINITION_HPP
#define DYNAMIC_BUILTIN_PROPERTY_DEFINITION_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "AutoPtr.hpp"
#include "SharedObject.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "PropertyValue.hpp"
#include "PropertyTechnology.hpp"

// =====================================================================================================================

namespace Property {

template <Int32 permissionFlags>
class EvaluationEnvironment;

class PROPERTY_OPERATIONS_DLL_EXPORT DynamicBuiltInPropertyDefinition : public GS::SharedObject
{
	DECLARE_ROOT_CLASS_INFO

public:
	virtual ~DynamicBuiltInPropertyDefinition ();

	virtual	GS::Guid										GetGuid								() const = 0;
	virtual	GS::UniString									GetName								() const = 0;
	virtual	PropertyDefinitionUserId						GetUserId							() const = 0;
	virtual	GS::UniString									GetDescription						() const = 0;
	virtual	const IValueDescriptor*							GetValueDescriptor					() const = 0;
	virtual	PropertyValue									GetDefaultValue						() const = 0;
	virtual	DynamicBuiltInPropertyDefinitionGroupConstRef	GetGroup							() const = 0;
	virtual	Measure											GetMeasure							() const = 0;
	virtual	bool											ValueCanBeEditable					() const = 0;

	virtual	GSErrCode										WriteContentForChecksum				(GS::OChannel& oc) const = 0;
	virtual GS::AutoPtr<GS::Variant>						ResolvePropertyValue				(const GS::Variant* originalValue) const = 0;

	virtual bool											IsAvailable							(const PropertyOwner& propertyOwner) const = 0;
	virtual bool											IsEvaluable							(const PropertyOwner& propertyOwner) const = 0;
	virtual	PropertyValue									GetValue							(const PropertyOwner& propertyOwner, const GS::VariantConversionRules& conversionRules) const = 0;
	virtual	bool											ValueIsEditable						(const PropertyOwner& propertyOwner) const = 0;
	virtual	void											SetValue							(const PropertyOwner& propertyOwner, const GS::Variant* newValue) const = 0;
	virtual	void											RemoveCustomValue					(const PropertyOwner& propertyOwner) const = 0;
	virtual	Measure											GetPropertyOwnerDependentMeasure	(const PropertyOwner& propertyOwner) const = 0;
	virtual bool											UsesAnyOfTheseTechnologies			(const TechnologyList& technologies, Technology::ActionType actionType) const = 0;
};

PropertyDefinitionConstPtr CreateAdapter (const DynamicBuiltInPropertyDefinitionConstPtr& prop);

}

#endif
