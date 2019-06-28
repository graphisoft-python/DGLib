// Contact person :	KV

#ifndef CATEGORY_TO_CLASSIFICATION_PROPERTY_CONVERSION_HPP
#define CATEGORY_TO_CLASSIFICATION_PROPERTY_CONVERSION_HPP

#pragma once

#include "PropertyOperationsExport.hpp"
#include "ClassificationItem.hpp"
#include "ClassificationSystem.hpp"
#include "ProjectTypes.hpp"

namespace CLS {

PROPERTY_OPERATIONS_DLL_EXPORT
CLS::ClassificationItemConstRef FindClassificationItemForOldCategoryValue (const EDB::ProjectConstRef& project, const ODB::Id& categoryValueId);

PROPERTY_OPERATIONS_DLL_EXPORT
CLS::ClassificationSystemConstRef FindFirstClassificationSystem (const EDB::ProjectConstRef& project);

}

#endif
