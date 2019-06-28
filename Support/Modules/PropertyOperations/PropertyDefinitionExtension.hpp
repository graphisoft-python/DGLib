// Contact person : KiP

#ifndef PROPERTYDEFINITION_EXTENSION_HPP
#define PROPERTYDEFINITION_EXTENSION_HPP

#pragma once

// === Includes ========================================================================================================

// from Property
#include "PropertyDefinition.hpp"
#include "PropertyValue.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "PropertyEvaluationEnvironment.hpp"
#include "PropertyTechnology.hpp"
#include "PropertyStatusCache.hpp"

// =====================================================================================================================

namespace Property {

enum class PropertyValueSourceType
{
	NoValue,
	OwnCustomValue,
	InheritedCustomValue,
	DefaultValue
};


namespace Technologies
{
PROPERTY_OPERATIONS_DLL_EXPORT extern const Technology QuantityCalculator;
PROPERTY_OPERATIONS_DLL_EXPORT extern const Technology ValueCache;
PROPERTY_OPERATIONS_DLL_EXPORT extern const Technology ArchicadAccess;
PROPERTY_OPERATIONS_DLL_EXPORT extern const Technology IFCAccess;
}



class PROPERTY_OPERATIONS_DLL_EXPORT PropertyDefinitionExtension : public PropertyDefinition
{
protected:
	PropertyDefinitionExtension (const PropertyDefinitionConstPtr& propertyDefinition, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv);
public:
	virtual ~PropertyDefinitionExtension ();

	virtual GS::Guid									GetGuid								() const override final;
	virtual GS::UniString								GetName								() const override final;
	virtual PropertyDefinitionUserId					GetUserId							() const override final;
	virtual GS::UniString								GetDescription						() const override final;
	virtual const IValueDescriptor*						GetValueDescriptor					() const override final;
	virtual PropertyValue								GetDefaultValue						() const override final;
	virtual PropertyDefinitionGroupConstPtr				GetGroup							() const override final;
	virtual Measure										GetMeasure							() const override final;
	virtual bool										ValueCanBeEditable					() const override final;
	virtual GS::AutoPtr<GS::Variant>					ResolvePropertyValue				(const GS::Variant* originalValue) const override final;
	virtual AdditionalDataStorePropertyKey				GetAdditionalDataStorePropertyKey	() const override final;
	virtual AdditionalDataStoreGroupKey					GetAdditionalDataStoreGroupKey		() const override final;

	virtual GSErrCode									WriteContentForChecksum				(GS::OChannel& oc) const override final;

	virtual Measure										GetPropertyOwnerDependentMeasure	(const PropertyOwner& propertyOwner) const = 0;
	virtual bool										IsAvailable							(const PropertyOwner& propertyOwner) const = 0;				//TODO B-466 KiP: IsApplicableTo jobb nev lenne!
	virtual bool										IsEvaluable							(const PropertyOwner& propertyOwner) const = 0;				//TODO B-466 KiP: CanBeEvaluatedFor jobb nev lenne!
			PropertyValue								GetValue							(const PropertyOwner& propertyOwner, const GS::VariantConversionRules& conversionRules) const;	
			GS::AutoPtr<GS::Variant>					GetDisplayValue						(const PropertyOwner& propertyOwner, const GS::VariantConversionRules& conversionRules) const;
			PropertyValueSourceType						GetValueSourceType					(const PropertyOwner& propertyOwner) const;
	virtual	GS::Optional<PropertyOwnerConstPtr>			GetValueSource						(const PropertyOwner& propertyOwner) const = 0;
	virtual bool										ValueIsEditable						(const PropertyOwner& propertyOwner) const = 0;
			void										SetValue							(const PropertyOwner& propertyOwner, const GS::Variant* newValue) const;
	virtual void										RemoveCustomValue					(const PropertyOwner& propertyOwner) const = 0;
	virtual	bool										UsesAnyOfTheseTechnologies			(const TechnologyList& technologies, Technology::ActionType actionType) const = 0;

	using PropertyDefinition::ContainsAdditionalData;
	using PropertyDefinition::GetAdditionalData;

	template <typename DataType> bool					ContainsAdditionalData				(const PropertyAdditionalDataStore<DataType>& dataStore, const PropertyOwner& propertyOwner) const;
	template <typename DataType> const DataType&		GetAdditionalData					(const PropertyAdditionalDataStore<DataType>& dataStore, const PropertyOwner& propertyOwner) const;

protected:
	PropertyEvaluationEnvironmentSourceConstPtr propEvalEnv;
	PropertyDefinitionConstPtr propertyDefinition;

	PropertyValue										CreateUndefinedValue () const;

private:
	GS::AutoPtr<GS::Variant>							ConvertToDisplayValue (const PropertyOwner& propertyOwner, const PropertyValue& propertyValue) const;
	
	virtual PropertyValue								GetEvaluatedValue (const PropertyOwner& propertyOwner, const GS::VariantConversionRules& conversionRules) const = 0;
			bool										IsValidValue (const GS::Variant* value) const;
	virtual	void										SetValidValue (const PropertyOwner& propertyOwner, const GS::Variant* newValue) const = 0;

	virtual GS::Array<AdditionalDataStorePropertyKey>	GetAdditionalDataStorePropertyKeys (const PropertyOwner& propertyOwner) const = 0;
	virtual GS::Array<AdditionalDataStoreGroupKey>		GetAdditionalDataStoreGroupKeys (const PropertyOwner& propertyOwner) const = 0;
};

template <typename DataType>
bool PropertyDefinitionExtension::ContainsAdditionalData (const PropertyAdditionalDataStore<DataType>& dataStore, const PropertyOwner& propertyOwner) const
{
	GS::Array<AdditionalDataStorePropertyKey> propertyKeys = GetAdditionalDataStorePropertyKeys (propertyOwner);
	for (UIndex i = 0; i < propertyKeys.GetSize (); ++i) {
		if (dataStore.ContainsData (propertyKeys[i])) {
			return true;
		}
	}
	GS::Array<AdditionalDataStoreGroupKey> groupKeys = GetAdditionalDataStoreGroupKeys (propertyOwner);
	for (UIndex i = 0; i < groupKeys.GetSize (); ++i) {
		if (dataStore.ContainsData (groupKeys[i])) {
			return true;
		}
	}
	return false;
}

template <typename DataType>
const DataType& PropertyDefinitionExtension::GetAdditionalData (const PropertyAdditionalDataStore<DataType>& dataStore, const PropertyOwner& propertyOwner) const
{
	GS::Array<AdditionalDataStorePropertyKey> propertyKeys = GetAdditionalDataStorePropertyKeys (propertyOwner);
	for (UIndex i = 0; i < propertyKeys.GetSize (); ++i) {
		if (dataStore.ContainsData (propertyKeys[i])) {
			return dataStore.GetData (propertyKeys[i]);
		}
	}
	GS::Array<AdditionalDataStoreGroupKey> groupKeys = GetAdditionalDataStoreGroupKeys (propertyOwner);
	for (UIndex i = 0; i < groupKeys.GetSize (); ++i) {
		if (dataStore.ContainsData (groupKeys[i])) {
			return dataStore.GetData (groupKeys[i]);
		}
	}
	DBBREAK ();
	throw PropertyAdditionalDataStoreMissingDataException ();
}


PropertyDefinitionExtensionConstPtr CreatePropertyDefintionExtension (const UserDefinedPropertyDefinitionEquivalenceClassConstRef& propertyDefinition, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv, const PropertyOperations::PropertyStatusCachePtr& statusCache);
PropertyDefinitionExtensionConstPtr CreatePropertyDefintionExtension (const StaticBuiltInPropertyDefinitionConstPtr& propertyDefinition, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv);
PropertyDefinitionExtensionConstPtr CreatePropertyDefintionExtension (const DynamicBuiltInPropertyDefinitionConstPtr& propertyDefinition, const PropertyEvaluationEnvironmentSourceConstPtr& propEvalEnv);

}

#endif
