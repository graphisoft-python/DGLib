// Contact person : KiP

#ifndef PROPERTYOPERATIONS_HOTLINK_UTILITY_HPP
#define PROPERTYOPERATIONS_HOTLINK_UTILITY_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "Owner.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

//======================================================================================================================

namespace Property {

class HotlinkUtilitiesModifierGuard;

class PROPERTY_OPERATIONS_DLL_EXPORT HotlinkUtilities
{
public:
	static bool												IsHotlinked (const EDB::GeneralElemConstRef& elem);

	static UserDefinedPropertyDefinitionContainerConstRef	GetOwnPropertyContainer (const EDB::GeneralElemConstRef& elem);

	static UserDefinedPropertyDefinitionConstRef			GetUserDefinedPropertyFromOwnersOwnContainer (const Property::PropertyDefinitionExtension&  property,
																										  const Property::PropertyOwner&				propertyOwner,
																										  ODB::IdSpace*									idSpace);

	class PROPERTY_OPERATIONS_DLL_EXPORT Impl
	{
	public:
		virtual ~Impl ();

		virtual bool											IsHotlinked (const EDB::GeneralElemConstRef& elem) const = 0;
		virtual UserDefinedPropertyDefinitionContainerConstRef	GetOwnPropertyContainer (const EDB::GeneralElemConstRef& elem) const = 0;
		virtual UserDefinedPropertyDefinitionConstRef			GetUserDefinedPropertyFromOwnersOwnContainer (const Property::PropertyDefinitionExtension&  property,
																											  const Property::PropertyOwner&				propertyOwner,
																											  ODB::IdSpace*									idSpace) const;
	};

private:
	friend class HotlinkUtilitiesModifierGuard;
	static Owner<Impl> impl;
};

}

#endif
