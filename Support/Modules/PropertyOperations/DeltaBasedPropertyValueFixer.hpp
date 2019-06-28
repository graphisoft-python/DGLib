// *********************************************************************************************************************
// Contact person:	BoZ
// *********************************************************************************************************************

#ifndef DELTA_BASED_PROPERTY_VALUE_FIXER_HPP
#define DELTA_BASED_PROPERTY_VALUE_FIXER_HPP

#pragma once

#include "PropertyOperationsExport.hpp"
#include "PropertyTypes.hpp"
#include "ODBChangeProcessor.hpp"

namespace ODB {
class DependencyNode;
}

namespace PropertyOperations {

class PROPERTY_OPERATIONS_DLL_EXPORT DeltaBasedPropertyValueFixer : public ODB::BatchChangeProcessor
{
	DECLARE_DYNAMIC_CLASS_INFO (DeltaBasedPropertyValueFixer)

public:
	virtual GSErrCode	Process (const ODB::ObjectRefList& objects, const Changes& changes) override;
	virtual Triggers	GetTriggers () const override;

	static	GSErrCode	ProcessDelta (const ODB::Delta& delta);
};

PROPERTY_OPERATIONS_DLL_EXPORT extern ODB::DependencyNode	deltaBasedPropertyValueFixer;

}

#endif
