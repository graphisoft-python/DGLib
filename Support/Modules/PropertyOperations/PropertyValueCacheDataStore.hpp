#ifndef PROPERTY_VALUE_CACHE_DATA_STORE_HPP
#define PROPERTY_VALUE_CACHE_DATA_STORE_HPP

#pragma once

#include "ODBObject.hpp"
#include "ODBCacheAssociation1N.hpp"
#include "PropertyOperationsTypes.hpp"
#include "Variant.hpp"
#include "PropertyOwnerHashKey.hpp"


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyValueCacheDataStore 
{
public:
	class PROPERTY_OPERATIONS_DLL_EXPORT ElemData : public GS::SharedObject
	{
	public:
		ElemData ();
		ElemData (const ElemData& source);
		ElemData& operator= (const ElemData& source);
		virtual ~ElemData ();

		bool GetValue (const GS::Guid& propertyGuid, const PropertyOwner& propertyOwner, GS::AutoPtr<GS::Variant>& value) const;
		void SetValue (const GS::Guid& propertyGuid, const PropertyOwner& propertyOwner, const GS::Variant* value);

		GSErrCode	Write (GS::OChannel& oc) const;
		GSErrCode	Read (GS::IChannel& ic);
		USize		GetSizeInBytes () const;

	private:
		GS::HashTable<GS::Guid, GS::HashTable<PropertyOwnerHashKey, GS::AutoPtr<GS::Variant>>> values;
	};

	typedef GS::SharedPtr<ElemData> ElemDataRef;
	typedef GS::ConstSharedPtr<ElemData> ElemDataConstRef;
	typedef GS::Pair<EDB::GeneralElemConstRef, ODB::Id> ElemContentId;

	virtual ~PropertyValueCacheDataStore ();

	virtual GS::Array<ElemDataConstRef>	Get (const GS::Array<ElemContentId>& elemContentIds) const = 0;
	virtual void						Set (const ElemContentId& elemContentId, const ElemDataConstRef& elemData) = 0;
};

}

#endif
