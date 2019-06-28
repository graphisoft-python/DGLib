// *********************************************************************************************************************
// File:			GetPropertyDefinitionsCommand.hpp
//
// Module:		    PropertyOperations
// Namespace:		Property
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef GETPROPERTYDEFINITIONSCOMMAND_HPP
#define GETPROPERTYDEFINITIONSCOMMAND_HPP

#pragma once


#include "MVCCommand.hpp"
#include "ProjectTypes.hpp"
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "TWCommandPermissions.hpp"


namespace Property {


// === class GetPropertyDefinitionsCommand =============================================================================

class PROPERTY_OPERATIONS_DLL_EXPORT GetPropertyDefinitionsCommand  : public MVC::CommandImp
{
	DECLARE_DYNAMIC_CLASS_INFO (GetPropertyDefinitionsCommand)

public:
	GetPropertyDefinitionsCommand () = default;
	GetPropertyDefinitionsCommand (const EDB::ProjectConstRef& project);

	virtual void								SetContext (const ODB::ObjectRef& context) override;
	virtual GS::ErrorStatus						Execute (void) override;
	virtual GS::ObjectState						GetResult (void) const override;

	GS::Array<PropertyDefinitionConstPtr>		GetResultPropertyDefinitions (void) const;

private:
	EDB::ProjectConstRef						mProject;				// the project which contains the PropertyDefinitions
	GS::Array<PropertyDefinitionConstPtr>		mPropertyDefinitions;	// list of all Property definitions (result of the query)
};


}	// namespace Property


#endif
