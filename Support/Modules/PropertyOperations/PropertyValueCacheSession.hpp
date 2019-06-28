#ifndef PROPERTY_VALUE_CACHE_SESSION_HPP
#define PROPERTY_VALUE_CACHE_SESSION_HPP

#pragma once

#include "HashSet.hpp"
#include "PropertyOwner.hpp"
#include "PropertyValueCache.hpp"
#include "PropertyValueCacheDataStore.hpp"


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyValueCacheSession : public PropertyValueCache 
{
public:
	using PropertyValueCache::ValueCalculator;

	PropertyValueCacheSession (PropertyValueCacheDataStore& dataStore, KeyCalculator& keyCalculator);
	virtual ~PropertyValueCacheSession ();

	virtual PropertyValue GetValue (ValueCalculator& valueCalculator, const PropertyOwner& propertyOwner) override;
	virtual void SetHint (const GS::Array<PropertyOwnerConstPtr>& hint) override;

private:
	struct ElemSessionData
	{
		PropertyValueCache::Key cacheKey;
		PropertyValueCacheDataStore::ElemDataRef newData;
		PropertyValueCacheDataStore::ElemDataConstRef storedData;

		bool GetValue (const GS::Guid& propertyGuid, const PropertyOwner& propertyOwner, PropertyValue& value);
		void SetValue (const GS::Guid& propertyGuid, const PropertyOwner& propertyOwner, const GS::Variant* value);
	};

	ElemSessionData& GetElemSessionData (const EDB::GeneralElemConstRef& elem, const ValueCalculator& valueCalculator);
	PropertyValue CalculateAndStoreValue (ValueCalculator& valueCalculator, const PropertyOwnerConstPtr& propertyOwnerForCache);
	void LoadSessionDataFromStore (const EDB::GeneralElemConstRef& elem, bool needLoadHintElemsData, const ValueCalculator& valueCalculator);
	void MergeNewSessionDataToStore ();


	PropertyValueCacheDataStore& dataStore;
	KeyCalculator& keyCalculator;

	GS::Array<PropertyOwnerConstPtr> hint;

	GS::HashSet<GS::Guid> loadedPropertiesOfHintElems;
	GS::HashSet<GS::Guid> calculatedPropertiesOfHintElems;
	GS::HashTable<EDB::GeneralElemConstRef, ElemSessionData> sessionData;
};

}

#endif
