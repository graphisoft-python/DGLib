#ifndef PROPERTY_VALUE_CACHE_HPP
#define PROPERTY_VALUE_CACHE_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "SharedObject.hpp"
#include "PagedArray.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// === Predeclarations =================================================================================================

namespace Property {
	class PropertyValue;
}

//======================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyValueCache : public GS::SharedObject
{
public:
	class PROPERTY_OPERATIONS_DLL_EXPORT ValueCalculator
	{
	public:
		virtual ~ValueCalculator ();

		virtual GS::Guid				GetPropertyGuid () const = 0;
		virtual PropertyOwnerConstPtr	CreatePropertOwnerForCache (const PropertyOwner& originalPropertyOwner) const = 0;
		virtual bool					IsEvaluable (const PropertyOwner& propertyOwner) const = 0;
		virtual PropertyValue			CalculateValue (const PropertyOwner& propertyOwner) const = 0;

		virtual void PushHint (const GS::PagedArray<EDB::GeneralElemConstRef>& elems) = 0;
		virtual void PopHint () = 0;
	};

	class Key 
	{
	public:
		Key () : valid (false) {}
		Key (const ODB::Id& key) : key (key), valid (true) {}
		
		const ODB::Id&	GetId	() const { DBASSERT (valid); return key; }
		bool			IsValid () const { return valid; }

	private:
		ODB::Id	key;
		bool valid;
	};

	class PROPERTY_OPERATIONS_DLL_EXPORT KeyCalculator 
	{
	public:
		virtual	~KeyCalculator ();
		virtual GS::Array<Key> CalculateKey (const GS::Array<EDB::GeneralElemConstRef>& elems) = 0;
	};

	virtual ~PropertyValueCache ();

	virtual PropertyValue GetValue (ValueCalculator& valueCalculator, const PropertyOwner& propertyOwner) = 0;
	virtual void SetHint (const GS::Array<PropertyOwnerConstPtr>& hint) = 0;
};

}

#endif
