// Contact person :	KiP

#ifndef NAME_REPLACER_ADDITIONAL_DATA_HPP
#define NAME_REPLACER_ADDITIONAL_DATA_HPP

#pragma once

// === Includes ========================================================================================================

// from Property
#include "PropertyAdditionalDataStore.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

// =====================================================================================================================
//	
//	!!! HACK !!!
//
//	Do not use it, except Elevation to XXX Reference Level properties!
//
// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyNameReplacer : public GS::SharedObject
{
public:
	virtual ~PropertyNameReplacer ();
	virtual GS::UniString GetReplacedName () const = 0;
};

typedef GS::ConstSharedPtr<PropertyNameReplacer> PropertyNameReplacerConstPtr;


PROPERTY_OPERATIONS_DLL_EXPORT
PropertyAdditionalDataStore<PropertyNameReplacerConstPtr>& GetPropertyNameReplacerStore ();

PROPERTY_OPERATIONS_DLL_EXPORT
const PropertyAdditionalDataStore<PropertyNameReplacerConstPtr>& GetConstPropertyNameReplacerStore ();

}

#endif
