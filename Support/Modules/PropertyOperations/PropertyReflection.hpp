// *********************************************************************************************************************
// *********************************************************************************************************************

#if !defined (PROPERTYREFLECTION_HPP)
#define PROPERTYREFLECTION_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Property
#include "PropertyTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PropertyOperations {

PROPERTY_OPERATIONS_DLL_EXPORT void PropertyContainerSetCreated (Property::UserDefinedPropertyDefinitionContainerSetConstRef containerSet);
PROPERTY_OPERATIONS_DLL_EXPORT void PropertyContainerSetDeleted (Property::UserDefinedPropertyDefinitionContainerSetConstRef containerSet);

} // namespace PropertyOperations

#endif
