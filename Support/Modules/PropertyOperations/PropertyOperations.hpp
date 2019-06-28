// Contact person : KiP

#ifndef PROPERTYOPERATIONS_HPP
#define PROPERTYOPERATIONS_HPP

#pragma once

// === Includes ========================================================================================================

#include "AutoPtr.hpp"

// from VBElements
#include "Project.hpp"

// from VBElemOperations
#include "GDLRequests.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// === Function prototypes  ============================================================================================

namespace GDLOperations {

// CollectProperties should be a GDLRequests function, but it depends on this module
PROPERTY_OPERATIONS_DLL_EXPORT
void	CollectProperties (GDLOperations::GDLRequests::IPropertyCollector& collector,
						   const Property::UserDefinedPropertyDefinitionContainerSetConstRef& containerSet,
						   Property::PropertyEvaluationEnvironmentSourceConstPtr propEvalEnv,
						   const EDB::GeneralElemConstRef& parentElemRef);

PROPERTY_OPERATIONS_DLL_EXPORT
void	CollectDynamicProperties (GDLOperations::GDLRequests::IPropertyCollector& collector,
								  Property::PropertyEvaluationEnvironmentSourceConstPtr propEvalEnv,
								  const EDB::GeneralElemConstRef& parentElemRef,
								  const GS::Guid& dynamicGroupId,
								  const GS::UniString& groupDisplayName);

}

#endif
