// Contact person: KiP

#ifndef DYNAMIC_BUILTIN_PROPERTY_UTILS_HPP
#define DYNAMIC_BUILTIN_PROPERTY_UTILS_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "CategoryTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT DynaimcBuiltInPropertyUtils
{
public:
	static	bool					IsCategoryProperty (const DynamicBuiltInPropertyDefinitionConstPtr& propertyDefinition);
	static	CAT::CategoryConstRef	GetCategoryFromCategoryProperty (const DynamicBuiltInPropertyDefinitionConstPtr& propertyDefinition);
};


}

#endif
