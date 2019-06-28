// *********************************************************************************************************************
// Description:		CacheClassificationSystemContainerSetExtension class
//
// Module:			PropertyOperations
// Namespace:		CLS
// Contact person:	TZ
//
// SG compatible
// *********************************************************************************************************************

#ifndef CACHECLASSIFICATIONSYSTEMCONTAINERSETEXTENSION_HPP
#define CACHECLASSIFICATIONSYSTEMCONTAINERSETEXTENSION_HPP

#pragma once

#include "PropertyOperationsExport.hpp"

// from ReferenceElemManager
#include "CacheRootObjectExtension.hpp"

// Classification
#include "ClassificationExport.hpp"


namespace CLS {

// === CacheClassificationSystemContainerSetExtension class ==============================================================

class PROPERTY_OPERATIONS_DLL_EXPORT CacheClassificationSystemContainerSetExtension : public SRM::CacheRootObjectExtension {
public:
	struct PROPERTY_OPERATIONS_DLL_EXPORT BreakInfoback : public GS::IDeletable {
		bool hasClassificationCreateRight;
		bool hadClassificationToCreate;

		BreakInfoback (bool hasClassificationCreateRight, bool hadClassificationToCreate) :
			hasClassificationCreateRight (hasClassificationCreateRight),
			hadClassificationToCreate (hadClassificationToCreate)
		{}
		virtual ~BreakInfoback ();
	};

private:
	static CacheClassificationSystemContainerSetExtension instance;

	CacheClassificationSystemContainerSetExtension ();

	CacheClassificationSystemContainerSetExtension (const CacheClassificationSystemContainerSetExtension&);				// disabled
	CacheClassificationSystemContainerSetExtension& operator= (const CacheClassificationSystemContainerSetExtension&);	// disabled

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

}	// namespace CLS

#endif	// CACHECLASSIFICATIONSYSTEMCONTAINERSETEXTENSION_HPP
