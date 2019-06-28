// Contact Person : KiP

#ifndef PROPERTYOPERATIONSEXCEPTIONS_HPP
#define PROPERTYOPERATIONSEXCEPTIONS_HPP

#pragma once

// from Property
#include "PropertyExceptions.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"


namespace Property {

DECLARE_EXCEPTION_CLASS (PropertyOperationsException, PropertyException, Error, PROPERTY_OPERATIONS_DLL_EXPORT)

DECLARE_EXCEPTION_CLASS (PropertyOperationsInvalidCallException, PropertyOperationsException, Error, PROPERTY_OPERATIONS_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (InvalidBuiltInPropertyRelaySetupException, PropertyOperationsException, Error, PROPERTY_OPERATIONS_DLL_EXPORT)

}

#endif
