// Contact person : KiP

#ifndef PROPERTY_OPERATIONS_PROPERTYVSEXPRESSIONVALUECONVERTER_HPP
#define PROPERTY_OPERATIONS_PROPERTYVSEXPRESSIONVALUECONVERTER_HPP

#pragma once

#include "PropertyOperationsExport.hpp"

#include "Variant.hpp"
#include "VariantConversionRules.hpp"
#include "PropertyDefinitionExtension.hpp"
#include "ExpressionValue.hpp"
#include "EvaluationLocaleSettings.hpp"
#include "PropertyMeasure.hpp"

// =====================================================================================================================

namespace Property {


class PROPERTY_OPERATIONS_DLL_EXPORT IPropertyTypeInfo
{
public:
	IPropertyTypeInfo ();
	virtual ~IPropertyTypeInfo ();

	virtual Measure								GetMeasure () const = 0;
	virtual CollectionType						GetCollectionType () const = 0;
	virtual ValueType							GetValueType () const = 0;
	virtual const IValueDescriptor*				GetValueDescriptor () const = 0;
	virtual const GS::VariantConversionRules&	GetVariantConversionRules () const = 0;
};


typedef GS::Ref<IPropertyTypeInfo>	IPropertyTypeInfoPtr;


class PROPERTY_OPERATIONS_DLL_EXPORT IResolvablePropertyTypeInfo : public IPropertyTypeInfo
{
public:
	IResolvablePropertyTypeInfo ();
	virtual ~IResolvablePropertyTypeInfo ();

	virtual GS::Owner<GS::Variant>				ResolvePropertyValue (const PropertyValue& propertyValue) const = 0;
};


class PROPERTY_OPERATIONS_DLL_EXPORT UserDefinedPropertyTypeInfo : public IResolvablePropertyTypeInfo
{
public:
	UserDefinedPropertyTypeInfo (const UserDefinedPropertyDefinitionConstRef& propertyDefinition, 
								 const GS::VariantConversionRules& variantConversionRules);
	virtual ~UserDefinedPropertyTypeInfo ();

	virtual Measure								GetMeasure () const override;
	virtual CollectionType						GetCollectionType () const override;
	virtual ValueType							GetValueType () const override;
	virtual const IValueDescriptor*				GetValueDescriptor () const override;
	virtual const GS::VariantConversionRules&	GetVariantConversionRules () const override;
	virtual GS::Owner<GS::Variant>				ResolvePropertyValue (const PropertyValue& propertyValue) const override;

private:
	UserDefinedPropertyDefinitionConstRef	propertyDefinition;
	const GS::VariantConversionRules&		variantConversionRules;
};


class PROPERTY_OPERATIONS_DLL_EXPORT PropertyDefinitionExtensionTypeInfoForConversion : public IResolvablePropertyTypeInfo
{
public:
	PropertyDefinitionExtensionTypeInfoForConversion (const PropertyDefinitionExtensionConstPtr& propertyExtension,
													  const ADB::AttributeSetConstRef& attributeSet, 
													  const GS::VariantConversionRules& variantConversionRules);
	virtual ~PropertyDefinitionExtensionTypeInfoForConversion ();

	virtual Measure								GetMeasure () const override;
	virtual CollectionType						GetCollectionType () const override;
	virtual ValueType							GetValueType () const override;
	virtual const IValueDescriptor*				GetValueDescriptor () const override;
	virtual const GS::VariantConversionRules&	GetVariantConversionRules () const override;
	virtual GS::Owner<GS::Variant>				ResolvePropertyValue (const PropertyValue& propertyValue) const override;

private:
	PropertyDefinitionExtensionConstPtr				propertyExtension;
	const ADB::AttributeSetConstRef&				attributeSet;
	const GS::VariantConversionRules&				variantConversionRules;
};

PROPERTY_OPERATIONS_DLL_EXPORT
bool IsSupportedExpressionPropertyCollectionType (Property::CollectionType collectionType, const Property::IValueDescriptor* valueDescriptor);

PROPERTY_OPERATIONS_DLL_EXPORT
bool IsSupportedExpressionPropertyMeasure (const Property::Measure& measure);

PROPERTY_OPERATIONS_DLL_EXPORT
GS::Owner<GS::VariantConversionRules> CreateVariantConversionRulesForExpression (Int32 nonUnitDecimalPrecision, const EP::IParsingLocaleSettings& localeSettings);

PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		CreateUndefinedExpressionValueForProperty (const IPropertyTypeInfo& info);
PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		PropertyValueToExpressionValue (const IResolvablePropertyTypeInfo& typeInfo, const PropertyValue& propertyValue, const EvaluationEnvironment<CallbackPermissions::NoPermissions>& env);

PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		ResolvedPropertyValueToNativeExpressionValue (const IPropertyTypeInfo& typeInfo, const GS::Variant* resolvedValue);

PROPERTY_OPERATIONS_DLL_EXPORT
GS::Owner<GS::Variant>	ExpressionValueToPropertyValue (const IPropertyTypeInfo& typeInfo, const EE::ExpressionValue& expressionValue);

}

#endif
