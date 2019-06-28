#ifndef PROPERTYSTATUSCACHE_HPP
#define PROPERTYSTATUSCACHE_HPP

#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "PropertyOwner.hpp"
#include "PropertyOwnerHashKey.hpp"

namespace PropertyOperations
{

enum class CachedPropertyStatus
{
	Unknown,			// not calculated yet
	NotExisting,
	NotEvaluable,
	Evaluable
}; 

class PROPERTY_OPERATIONS_DLL_EXPORT OwnerPropertyStatusCache
{
public:
	OwnerPropertyStatusCache ();
	virtual ~OwnerPropertyStatusCache ();

	CachedPropertyStatus	GetStatus (const GS::Guid& guid) const;
	void					SetStatus (const GS::Guid& guid, CachedPropertyStatus status);

private:
	GS::HashTable<GS::Guid, CachedPropertyStatus> statusCache;
};

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyStatusCache
{
public:
	PropertyStatusCache ();
	virtual ~PropertyStatusCache ();

	CachedPropertyStatus	GetStatus (const Property::PropertyOwner& owner, const GS::Guid& guid) const;
	void					SetStatus (const Property::PropertyOwner& owner, const GS::Guid& guid, CachedPropertyStatus status);
	void					ClearStatus (const Property::PropertyOwner& owner);

private:
	bool					IsCacheableOwner (const Property::PropertyOwner& owner) const;

	GS::HashTable<Property::PropertyOwnerHashKey, OwnerPropertyStatusCache> statusCache;
};

typedef GS::Ref<PropertyStatusCache> PropertyStatusCachePtr;

}

#endif
