
#ifndef ALWAYS_CALCULATE_PROPERTY_VALUE_CACHE_HPP
#define ALWAYS_CALCULATE_PROPERTY_VALUE_CACHE_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "PropertyValueCache.hpp"

//======================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT AlwaysCalculatePropertyValueCacheImpl : public PropertyValueCache		// TODO B-470 temporary
{
public:
	AlwaysCalculatePropertyValueCacheImpl ();
	virtual ~AlwaysCalculatePropertyValueCacheImpl ();

	virtual PropertyValue GetValue (PropertyValueCache::ValueCalculator& valueCalculator, const PropertyOwner& propertyOwner) /*const ?*/ override;
	virtual void SetHint (const GS::Array<PropertyOwnerConstPtr>& hint) override;
};

}

#endif
