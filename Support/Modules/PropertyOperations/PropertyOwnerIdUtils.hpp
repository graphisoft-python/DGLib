// Contact person : KV

#ifndef PROPERTY_OWNER_UTILS_HPP
#define PROPERTY_OWNER_UTILS_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "Optional.hpp"

// from ODB
#include "ODBIdSpace.hpp"

// from BIMData
#include "BIMDataTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsTypes.hpp"
#include "PropertyOperationsExport.hpp"

// =====================================================================================================================

namespace Property {

PROPERTY_OPERATIONS_DLL_EXPORT_FOR_TEST
BIMData::BIMDataHandlerConstPtr CreateConstBIMDataHandler (const Property::PropertyOwner& propertyOwner, ODB::IdSpace* idSpace);

PROPERTY_OPERATIONS_DLL_EXPORT_FOR_TEST
GS::Optional<BIMData::BIMDataHandlerPtr> CreateEditableBIMDataHandler (const Property::PropertyOwner& propertyOwner, ODB::IdSpace* idSpace);

}


#endif
