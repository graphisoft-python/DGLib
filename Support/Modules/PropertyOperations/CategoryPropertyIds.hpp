// Contact person: KiP

#ifndef CATEGORY_PROPERTY_IDS_HPP
#define CATEGORY_PROPERTY_IDS_HPP

#pragma once

// === Includes ========================================================================================================

// from ElementManager
#include "CategoryTypes.hpp"
#include "ProjectTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

// =====================================================================================================================

namespace Property {

PROPERTY_OPERATIONS_DLL_EXPORT	extern const GS::Guid	 StructuralFunctionCategoryPropertyId;
PROPERTY_OPERATIONS_DLL_EXPORT	extern const GS::Guid	 PositionCategoryPropertyId;
PROPERTY_OPERATIONS_DLL_EXPORT	extern const GS::Guid	 RenovationStatusCategoryPropertyId;
PROPERTY_OPERATIONS_DLL_EXPORT	extern const GS::Guid	 RenovationFilterCategoryPropertyId;
PROPERTY_OPERATIONS_DLL_EXPORT	extern const GS::Guid	 BRICategoryPropertyId;

PROPERTY_OPERATIONS_DLL_EXPORT	bool					IsExistingCategoryPropertyGuid (const GS::Guid& propertyGuid);
PROPERTY_OPERATIONS_DLL_EXPORT	GS::Guid				GetPropertyGuidOfCategory (const CAT::CategoryConstRef& category);
PROPERTY_OPERATIONS_DLL_EXPORT	CAT::CategoryConstRef	GetCategoryByPropertyGuid (const GS::Guid& propertyGuid, const EDB::ProjectConstRef& project);
PROPERTY_OPERATIONS_DLL_EXPORT	GS::Guid				GetPropertyGuidToCategoryGuid (const GS::Guid& categoryGuid, const EDB::ProjectConstRef& project);

}

#endif
