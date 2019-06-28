// *********************************************************************************************************************
// Description:		CachePropertyDefinitionContainerSetExtension class
//
// Module:			PropertyOperations
// Namespace:		PropertyOperations
// Contact person:	TZ
//
// SG compatible
// *********************************************************************************************************************

#ifndef CACHEPROPERTYDEFINITIONCONTAINERSETEXTENSION_HPP
#define CACHEPROPERTYDEFINITIONCONTAINERSETEXTENSION_HPP

#pragma once

// from ReferenceElemManager
#include "CacheRootObjectExtension.hpp"

// PropertyOperations
#include "PropertyOperationsExport.hpp"


namespace PropertyOperations {

// === CachePropertyDefinitionContainerSetExtension class ==============================================================

class PROPERTY_OPERATIONS_DLL_EXPORT CachePropertyDefinitionContainerSetExtension : public SRM::CacheRootObjectExtension {
public:
	struct PROPERTY_OPERATIONS_DLL_EXPORT BreakInfoback : public GS::IDeletable {
		bool hasPropertyCreateRight;
		bool hadPropertyToCreate;

		BreakInfoback (bool hasPropertyCreateRight, bool hadPropertyToCreate) :
			hasPropertyCreateRight (hasPropertyCreateRight),
			hadPropertyToCreate (hadPropertyToCreate)
		{}
		virtual ~BreakInfoback ();
	};

private:
	static CachePropertyDefinitionContainerSetExtension instance;

	CachePropertyDefinitionContainerSetExtension ();

	CachePropertyDefinitionContainerSetExtension (const CachePropertyDefinitionContainerSetExtension&);				// disabled
	CachePropertyDefinitionContainerSetExtension& operator= (const CachePropertyDefinitionContainerSetExtension&);	// disabled

public:
	virtual void		AppendRootObjectSet						(ODB::ConstRef<TW::Object>					rootObject,
																 RootObjectSetCollectingMode				rootObjectSetCollectingMode,
																 ODB::ConstRefList<ODB::Object>&			rootObjectSet) override;
	
	virtual void		RemoveUnusedDependentObjects			(ODB::ConstRefList<ODB::Object>&			sourceObjectSet,
																 ODB::ConstRefList<ODB::Object>&			removedObjects) override;

	virtual GSErrCode	CacheMergePreProcess					(ODB::IdSpace*								cacheIdSpace,
																 ODB::ConstRef<TW::Object>					cacheRootObject,
																 ODB::Delta&								mergeDelta,
																 GS::Ref<GS::IDeletable>&					cacheMergeData) override;

	virtual GSErrCode	CacheMergePostProcess					(ODB::Ref<TW::Object>						cacheRootObject,
																 const ODB::Delta&							mergeDelta,
																 GS::Ref<GS::IDeletable>					cacheMergeData) override;

	virtual void		CollectAffectedObjects					(ODB::ConstRef<TW::Object>					cacheRootObject,
																 const ODB::Delta&							mergeDelta,
																 GS::Ref<GS::IDeletable>					cacheMergeData,
																 bool*										outWholeCacheAffected,
																 SRM::ConstRefSet*							outAffectedObjects) override;

	virtual void		AppendCommonProxyCacheObjects			(ODB::ConstRef<TW::Object>					cacheRootObject,
																 SRM::ConstRefSet&							commonProxyCacheObjects) override;

	virtual GSErrCode	FilterInstanceDelta						(ODB::ConstRef<TW::Object>					cacheRootObject,
																 ODB::ConstRef<TW::Object>					projectRootObject,
																 ODB::Delta&								instanceDelta,
																 const SRM::IdTable&						instanceMapTable,
																 const SRM::IdTable&						inverseMapTable,
																 VBElem::ReferenceElemConstRef				refElem,
																 const GS::HashSet<ODB::Id>&				boundaryRootObjectIds,
																 REM::IsolatedProcessing&					isolatedProcessing) override;

	virtual GSErrCode	BindToProjectRootObjectSet				(ODB::ConstRef<TW::Object>					cacheRootObject,
																 ODB::ConstRef<TW::Object>					projectRootObject,
																 ODB::BindableDelta&						instanceDelta,
																 const SRM::IdTable&						instanceMapTable,
																 const SRM::IdTable&						inverseMapTable,
																 VBElem::ReferenceElemConstRef				refElem,
																 GS::Array<OA::IdLink>&						unbindedLinks,
																 SRM::ProxyIdToLostConnectionDataTable&		objectSpecificLostConnectionDataTable,
																 GS::HashTable<short, double>*				outAggregatedLevelDiffs,
																 ADB::IAttributeNewIndexTable*				attrNewIndexTable) override;

	virtual GSErrCode	PreProcessReferenceElemBreak			(VBElem::ReferenceElemRef					mainRefElem,
																 const ODB::RefList<ODB::Object>&			subtreeProxyObjects,
																 GS::Ref<GS::IDeletable>&					breakData,
																 REM::TeamworkControl*						twControl,
																 GS::Array<GS::Ref<GS::IDeletable>>*		infobacks) override;

	virtual GSErrCode	PostProcessReferenceElemBreak			(GS::Ref<GS::IDeletable>					breakData,
																 REM::TeamworkControl*						twControl,
																 GS::Array<GS::Ref<GS::IDeletable>>*		infobacks) override;

	virtual GSErrCode	PostProcessClearProxyProperties			(const GS::HashSet<EDB::GeneralElemRef>&	sourceElemList,
																 ODB::Ref<TW::Object>						targetProjectRootObject,
																 REM::TeamworkControl*						finalTargetTwControl,
																 GS::Array<GS::Ref<GS::IDeletable>>*		infobacks) override;

	virtual GSErrCode	BindCommonPartsOfInstances				(REM::ModuleSingletonConstRef				moduleSingleton,
																 ODB::ConstRef<TW::Object>					projectRootObject,
																 ODB::BindableDelta&						delta) override;

	virtual GSErrCode	PrepareProjectForCacheSave				(ODB::ConstRef<TW::Object>					cacheRootObject,
																 REM::Project*								project,
																 const SRM::IdTable&						cacheToSourceMapTable) override;

	virtual GSErrCode	FilterRootObjectDeltaForCacheSave		(ODB::ConstRef<TW::Object>					cacheRootObject,
																 ODB::Delta&								rootObjectDelta) override;

	virtual GSErrCode	BindToProjectForCacheSave				(ODB::ConstRef<TW::Object>					cacheRootObject,
																 ODB::ConstRef<TW::Object>					projectRootObject,
																 ODB::BindableDelta&						mappedRootObjectDelta,
																 const SRM::IdTable&						cacheToSourceMapTable) override;

	virtual GSErrCode	PostProcessForCacheSave					(ODB::Ref<TW::Object>						projectRootObject,
																 REM::Project*								project) override;

	virtual GSErrCode	PrepareGeneratedSourceProject			(REM::Project*								sourceProject,
																 SRM::ReferenceElemCacheConstRef			cacheToUpdate) override;

	virtual GSErrCode	ConvertRootObjectSetToNew				(REM::Project*								project,
																 SRM::ReferenceElemCacheRef					cache,
																 Int32										plVersion,
																 bool*										needRecreateProxyObjects) override;

	virtual GSErrCode	ConvertRootObjectSetToOld				(SRM::ReferenceElemCacheRef					cache,
																 Int32										plVersion) override;
};

}	// namespace PropertyOperations

#endif	// CACHEPROPERTYDEFINITIONCONTAINERSETEXTENSION_HPP
