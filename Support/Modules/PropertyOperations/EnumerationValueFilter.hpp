// Contact person :	KiP

#ifndef ENUMERATIONVALUE_FILTER_HPP
#define ENUMERATIONVALUE_FILTER_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "SharedObject.hpp"
#include "HashSet.hpp"

// from Property
#include "SingleVariant.hpp"
#include "VariantTypeTemplates.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "PropertyAdditionalDataStore.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT EnumerationValueFilter : public GS::SharedObject
{
public:
	virtual ~EnumerationValueFilter ();

	virtual bool NeedToProcess (const GS::Variant* enumKey) const = 0;
	virtual bool NeedToProcess (const GS::Variant* enumKey, const PropertyOwner& propertyOwner) const = 0;
};

typedef GS::SharedPtr<EnumerationValueFilter> EnumerationValueFilterPtr;
typedef GS::ConstSharedPtr<EnumerationValueFilter> EnumerationValueFilterConstPtr;


template <typename ValueType>
class ValueBasedEnumerationValueFilter : public EnumerationValueFilter
{
public:
	enum Mode
	{
		Include,
		FilterOut
	};

	ValueBasedEnumerationValueFilter (const GS::HashSet<Int32> relevantValues, Mode mode);
	virtual ~ValueBasedEnumerationValueFilter ();

	virtual bool NeedToProcess (const GS::Variant* enumKey) const override;
	virtual bool NeedToProcess (const GS::Variant* enumKey, const PropertyOwner& propertyOwner) const override;

private:
	GS::HashSet<ValueType> relevantValues;
	Mode mode;
};

template <typename ValueType>
Property::ValueBasedEnumerationValueFilter<ValueType>::ValueBasedEnumerationValueFilter (const GS::HashSet<Int32> relevantValues, Mode mode) :
	relevantValues (relevantValues),
	mode (mode)
{
}

template <typename ValueType>
Property::ValueBasedEnumerationValueFilter<ValueType>::~ValueBasedEnumerationValueFilter ()
{
}

template <typename ValueType>
bool Property::ValueBasedEnumerationValueFilter<ValueType>::NeedToProcess (const GS::Variant* enumKey) const
{
	typedef typename GS::GetSingleVariantType<ValueType>::Type VariantType;
	if (DBERROR (!GS::Variant::IsType<VariantType> (enumKey))) {
		return false;
	}
	const ValueType valueFromEnumKey = VariantType::Get (enumKey);
	return ((mode == Include) && relevantValues.Contains (valueFromEnumKey)) || ((mode == FilterOut) && !relevantValues.Contains (valueFromEnumKey));
}

template <typename ValueType>
bool Property::ValueBasedEnumerationValueFilter<ValueType>::NeedToProcess (const GS::Variant* enumKey, const PropertyOwner& /*propertyOwner*/) const
{
	return NeedToProcess (enumKey);
}


PROPERTY_OPERATIONS_DLL_EXPORT
PropertyAdditionalDataStore<EnumerationValueFilterConstPtr>& GetEnumerationValueFilterStore ();

PROPERTY_OPERATIONS_DLL_EXPORT
const PropertyAdditionalDataStore<EnumerationValueFilterConstPtr>& GetConstEnumerationValueFilterStore ();

}

#endif
