#ifndef VB_ELEM_DEFAULT_OPERATIONS__HPP
#define VB_ELEM_DEFAULT_OPERATIONS__HPP

#include "Optional.hpp"
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"

// from VBElements
#include "VBElements/ProfileTypes.hpp"

namespace GS {
	class UniString;
}

namespace EDB {
	class DefaultElem;
}

// =====================================================================================================================
//  VBElemDefaultOperations
// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT VBElemDefaultOperations
{
public:
	static bool						HasInfoString		(const EDB::DefaultElem& defaultElem);
	static GS::UniString			GetInfoString		(const EDB::DefaultElem& defaultElem);
	static void						SetInfoString		(EDB::DefaultElem& defaultElem, const GS::UniString infoString);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const EDB::DefaultElem& defaultElem);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const EDB::DefaultElem& defaultElem);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(EDB::DefaultElem& defaultElem);

	static VBElem::ParametricProfile*			GetIProfile			(EDB::DefaultElem& defaultElem);
	static const VBElem::ParametricProfile*		GetConstIProfile	(const EDB::DefaultElem& defaultElem);
};

#endif // VB_ELEM_DEFAULT_OPERATIONS__HPP
