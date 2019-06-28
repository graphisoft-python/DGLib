// Contact person : KiP

#ifndef PROPERTY_CALLBACK_INFO_HPP
#define PROPERTY_CALLBACK_INFO_HPP

// === Includes ========================================================================================================

#include "PropertyOperationsExport.hpp"
#include "PropertyTechnology.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT CallbackPermissions 
{
public:
	enum Flags : Int32
	{
		ValueCachePermission			= 0x0001,
		QuantityCalculatorPermission	= 0x0002,
		ArchicadPermission				= 0x0004,
		IFCPermission					= 0x0008,

		NoPermissions					= 0,
		AllPermissions					= ValueCachePermission | QuantityCalculatorPermission | ArchicadPermission | IFCPermission
	};

	explicit CallbackPermissions (Int32 permissionFlagsForQuery = NoPermissions, Int32 permissionFlagsForModification = NoPermissions);

	bool IsFlagBitSetForAnyOfTheseTechnologies (const TechnologyList& technologies, Technology::ActionType actionType) const;

private:
	Int32 permissionFlagsForQuery;
	Int32 permissionFlagsForModification;
};

}

#endif