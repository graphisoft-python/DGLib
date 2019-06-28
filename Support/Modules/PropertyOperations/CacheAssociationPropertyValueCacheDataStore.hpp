#ifndef CACHE_ASSOCIATION_PROPERTY_VALUE_CACHE_DATA_STORE_HPP
#define CACHE_ASSOCIATION_PROPERTY_VALUE_CACHE_DATA_STORE_HPP

#pragma once

#include "PropertyValueCacheDataStore.hpp"
#include "ProjectTypes.hpp"


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT CacheAssociationPropertyValueCacheDataStore : public PropertyValueCacheDataStore 
{
public:
	class PROPERTY_OPERATIONS_DLL_EXPORT ElemDataODBObjectWrapper : public ODB::Object 
	{
		DECLARE_DYNAMIC_CLASS_INFO (ElemDataODBObjectWrapper);
	public:
		ElemDataODBObjectWrapper ();
		ElemDataODBObjectWrapper (const ElemDataODBObjectWrapper& source);
		ElemDataODBObjectWrapper (const ElemDataConstRef& elemData);
		~ElemDataODBObjectWrapper ();

		virtual ElemDataODBObjectWrapper* Clone () const override;

		const PropertyValueCacheDataStore::ElemDataConstRef& GetElemData () const { return elemData; }

		virtual GSErrCode	WriteIsolatedState (GS::OChannel& oc) const override;
		virtual GSErrCode	ReadIsolatedState (GS::IChannel& ic) override;
		virtual USize		GetIsolatedSize (void) const override;

	private:
		PropertyValueCacheDataStore::ElemDataConstRef elemData;
	};

	typedef ODB::CacheAssociation1N<EDB::GeneralElem, ElemDataODBObjectWrapper> ElemCacheDataAssocType;
	
	CacheAssociationPropertyValueCacheDataStore (ElemCacheDataAssocType& elemCacheDataAssoc);
	virtual ~CacheAssociationPropertyValueCacheDataStore ();

	virtual GS::Array<ElemDataConstRef>	Get (const GS::Array<ElemContentId>& elemContentIds) const override;
	virtual void						Set (const ElemContentId& elemContentId, const ElemDataConstRef& elemData) override;

	void Clear (const EDB::ProjectConstRef& project);

private:
	ElemCacheDataAssocType& elemCacheDataAssoc;
};

}

#endif 
