// Contact person : ViP

#ifndef PROPERTY_MERGE_OPERATIONS_HPP
#define PROPERTY_MERGE_OPERATIONS_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "EDBGeneralDefinitions.hpp"
#include "BindTable.hpp"
#include "ProjectTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// =====================================================================================================================

namespace PropertyOperations {

namespace DBMerge {

PROPERTY_OPERATIONS_DLL_EXPORT
void GetAllPropertyObjects (EDB::ProjectConstRef srcEDBProject, ODB::ConstRefList<ODB::Object>& propertyObjects, GS::HashSet<ODB::Id>& propertyIds);

PROPERTY_OPERATIONS_DLL_EXPORT
void GetUsedPropertyObjects (EDB::ProjectConstRef srcEDBProject, const GS::HashSet<EDB::GeneralElemConstRef>& elemList, ODB::ConstRefList<ODB::Object>& propertyObjects, GS::HashSet<ODB::Id>& propertyIds, GS::HashSet<ODB::Id>& classificationId);

PROPERTY_OPERATIONS_DLL_EXPORT
void DeleteNotUsedPropertyDefinitions (ODB::IdSpace* tmpIdSpace, GS::HashSet<ODB::Id>& propertyIds);

PROPERTY_OPERATIONS_DLL_EXPORT
void AppendObjectsToMerge (ODB::ConstRefList<ODB::Object>&																							objectsToMerge,
						   const Property::UserDefinedPropertyDefinitionGroupConstRefList&															mergeAsNewPropertyGroups,
						   const GS::HashTable<Property::UserDefinedPropertyDefinitionConstRef, Property::UserDefinedPropertyDefinitionGroupRef>&	mergeAsNewPropertyDefinitions);

PROPERTY_OPERATIONS_DLL_EXPORT
void FillBindTablePropertyContainer (EDB::BindTable*											bindTable,
									 Property::UserDefinedPropertyDefinitionContainerConstRef	targetPropertyDefinitionContainer,
									 Property::UserDefinedPropertyDefinitionContainerConstRef	sourcePropertyDefinitionContainer);

PROPERTY_OPERATIONS_DLL_EXPORT
void SetClientCreatedToNewObjects (ODB::IdSpace*																											idSpace,
								   const Property::UserDefinedPropertyDefinitionGroupConstRefList&															mergeAsNewPropertyGroups,
								   const GS::HashTable<Property::UserDefinedPropertyDefinitionConstRef, Property::UserDefinedPropertyDefinitionGroupRef>&	mergeAsNewPropertyDefinitions);

PROPERTY_OPERATIONS_DLL_EXPORT
GSErrCode MergePropertyContainerWithRelinkElements (Property::UserDefinedPropertyDefinitionContainerRef			targetPropertyDefinitionContainer,
													Property::UserDefinedPropertyDefinitionContainerConstRef	sourcePropertyDefinitionContainer,
													const EDB::GeneralElemRefList&								elemsToRelink,
													bool														hasPropertyCreateRight,
													bool*														hadPropertyToCreate);

PROPERTY_OPERATIONS_DLL_EXPORT
GSErrCode MergePropertyContainerWithCopyConnections (Property::UserDefinedPropertyDefinitionContainerRef					targetPropertyDefinitionContainer,
													 Property::UserDefinedPropertyDefinitionContainerConstRef				sourcePropertyDefinitionContainer,
													 const GS::HashTable<EDB::GeneralElemRef, EDB::GeneralElemConstRef>&	elemsToCopyConnections,
													 bool																	hasPropertyCreateRight,
													 bool*																	hadPropertyToCreate);

}

}

#endif
