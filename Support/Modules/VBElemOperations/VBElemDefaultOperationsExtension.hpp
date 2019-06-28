#ifndef VB_ELEM_DEFAULT_OPERATIONS_EXTENSION__HPP
#define VB_ELEM_DEFAULT_OPERATIONS_EXTENSION__HPP

// from GSRoot
#include "Extension.hpp"
#include "Optional.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"

// from VBElements
#include "VBElements/ProfileTypes.hpp"

namespace EDB {
	class DefaultElem;
}

// =====================================================================================================================
//  VBElemDefaultOperationsExtension
// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT VBElemDefaultOperationsExtension: public GS::Extension
{
public:
	static GS::ExtensionId id;

	VBElemDefaultOperationsExtension (GS::ClassInfo* target);
	virtual ~VBElemDefaultOperationsExtension ();

	virtual bool					HasInfoString	(const EDB::DefaultElem& defaultElem) const = 0;
	virtual GS::UniString			GetInfoString	(const EDB::DefaultElem& defaultElem) const = 0;
	virtual void					SetInfoString	(EDB::DefaultElem& defaultElem, const GS::UniString& infoString) const = 0;

	virtual GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure (const EDB::DefaultElem& defaultElem) const = 0;
	virtual GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance (const EDB::DefaultElem& defaultElem) const = 0;
	virtual GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier (EDB::DefaultElem& defaultElem) const = 0;

	virtual VBElem::ParametricProfile*			GetIProfile			(EDB::DefaultElem& defaultElem) const = 0;
	virtual const VBElem::ParametricProfile*	GetConstIProfile	(const EDB::DefaultElem& defaultElem) const = 0;
};

#endif // VB_ELEM_DEFAULT_OPERATIONS_EXTENSION__HPP
