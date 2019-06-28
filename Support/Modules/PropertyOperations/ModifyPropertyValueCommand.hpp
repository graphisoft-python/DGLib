// *********************************************************************************************************************
// File:			ModifyPropertyValueCommand.hpp
//
// Module:		    PropertyOperations
// Namespace:		Property
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef MODIFYPROPERTYVALUECOMMAND_HPP
#define MODIFYPROPERTYVALUECOMMAND_HPP

#pragma once


#include "MVCCommand.hpp"
#include "TWModifyCommand.hpp"
#include "TWCommandPermissions.hpp"
#include "Owner.hpp"
#include "PropertyOperationsExport.hpp"
#include "PropertyDefinitionExtension.hpp"


namespace Property {


// === class ModifyPropertyValueCommand ================================================================================

class PROPERTY_OPERATIONS_DLL_EXPORT ModifyPropertyValueCommand : public MVC::CommandImp,
																  public TW::ModifyCommand
{
	DECLARE_DYNAMIC_CLASS_INFO (ModifyPropertyValueCommand)

public:
	enum SetToDefaultSelector { SetToDefault };

	ModifyPropertyValueCommand () = default;

	ModifyPropertyValueCommand (const EDB::GeneralElemRef&					elem,
								const PropertyDefinitionExtensionConstPtr&	propDef,
								Owner<GS::Variant>							newValue);

	ModifyPropertyValueCommand (const EDB::GeneralElemRef&					elem,
								const PropertyDefinitionExtensionConstPtr&	propDef,
								SetToDefaultSelector);

	virtual GS::ErrorStatus					RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
	virtual ODB::ObjectRefList				GetReservationRootObjects (void) const override;
	virtual GS::ErrorStatus					Execute (void) override;

private:
	EDB::GeneralElemRef						mElem;				// which element's Property to modify
	PropertyDefinitionExtensionConstPtr		mPropDef;			// the Property to modify
	bool									mSetToDefault;		// if set to true, the value will be set to default
	Owner<GS::Variant>						mNewValue;			// new value of the Property
};


}	// namespace Property


#endif
