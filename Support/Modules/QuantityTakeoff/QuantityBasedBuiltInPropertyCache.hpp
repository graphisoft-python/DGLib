#ifndef QUANTITY_BASED_BUILT_IN_PROPERTY_CACHE_HPP
#define QUANTITY_BASED_BUILT_IN_PROPERTY_CACHE_HPP

#pragma once

#include "QuantityTakeoffExport.hpp"

#include "QuantityBasedBuiltInPropertyCacheKeyCalculator.hpp"

#include "PropertyValueCacheSession.hpp"

#include "CacheAssociationPropertyValueCacheDataStore.hpp"

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT QuantityBasedBuiltInPropertyCache : public Property::PropertyValueCache
{
public:
	QuantityBasedBuiltInPropertyCache (const GS::SharedPtr<QuantityModel>& quantityModel);

	virtual Property::PropertyValue GetValue (Property::PropertyValueCache::ValueCalculator& valueCalculator, const Property::PropertyOwner& propertyOwner) override;
	virtual void SetHint (const GS::Array<Property::PropertyOwnerConstPtr>& hint) override;

	~QuantityBasedBuiltInPropertyCache ();

	static void	Clear (const EDB::ProjectConstRef& project);

private:
	GS::SharedPtr<QuantityModel>									quantityModel;
	QuantityBasedBuiltInPropertyCacheKeyCalculator					keyCalculator;
	Property::PropertyValueCachePtr 								cache;

	static Property::CacheAssociationPropertyValueCacheDataStore	dataStore;
};


} // namespace QT

#endif // QUANTITY_BASED_BUILT_IN_PROPERTY_CACHE_HPP
