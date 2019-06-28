// *********************************************************************************************************************
// File:			GetElemPropertiesCommand.hpp
//
// Module:		    PropertyOperations
// Namespace:		Property
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef GETELEMPROPERTIESCOMMAND_HPP
#define GETELEMPROPERTIESCOMMAND_HPP

#pragma once


#include "MVCCommand.hpp"
#include "Owner.hpp"
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "TWCommandPermissions.hpp"

namespace Property {


// === class GetElemPropertiesCommand ==================================================================================

class PROPERTY_OPERATIONS_DLL_EXPORT GetElemPropertiesCommand : public MVC::CommandImp
{
	DECLARE_DYNAMIC_CLASS_INFO (GetElemPropertiesCommand)

public:
	struct PropertyValue {
		PropertyValue (const GS::Guid& propertyId, bool isDefault, Owner<GS::Variant> value);

		GS::Guid			propertyId;
		bool				isDefault;
		Owner<GS::Variant>	value;
	};

	GetElemPropertiesCommand () = default;
	explicit GetElemPropertiesCommand (const EDB::GeneralElemConstRef& elem);

	GetElemPropertiesCommand (const GetElemPropertiesCommand&) = delete;				// because of Owner member
	GetElemPropertiesCommand& operator= (const GetElemPropertiesCommand&) = delete;		// because of Owner member

	virtual GS::ErrorStatus							RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
	virtual GS::ErrorStatus							Execute (void) override;
	virtual GS::ObjectState							GetResult (void) const override;

	const GS::Array<PropertyValue>&	GetResultPropertyValues (void) const;

private:
	EDB::GeneralElemConstRef		mElem;				// element to query
	GS::Array<PropertyValue>		mPropertyValues;	// list of the Property values of the element (result of the query)
};


}	// namespace Property


#endif
