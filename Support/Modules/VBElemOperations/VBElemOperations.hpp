#ifndef VB_ELEM_OPERATIONS__HPP
#define VB_ELEM_OPERATIONS__HPP

#include "VBElemOperationsExport.hpp"
#include "GeneralElem.hpp"
#include "ProfileCoordinateSystem.hpp"
#include "LabelTypes.hpp"
#include "GDLBasedElemTypes.hpp"
#include "VBElemOperationsTypes.hpp"

// from VBElements
#include "VBElements/ProfileTypes.hpp"

namespace LM {
	class LibrarySet;
}

// =====================================================================================================================
//  VBElemOperations
// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT VBElemOperations
{
public:
	typedef const std::function<void (const EDB::GeneralElemConstRef&)>& GeneralElemConstFn;

	enum SetHeightLocation {
		SHL_Top,
		SHL_Bottom
	};

	enum RefPointLocation {
		RPL_Beg,
		RPL_End
	};


public:
	static void			ForEachSubElem (EDB::GeneralElemConstRef elemRef, GeneralElemConstFn fn);

	static double		GetAbsoluteTop		(EDB::GeneralElemConstRef elemRef);
	static double		GetAbsoluteBottom	(EDB::GeneralElemConstRef elemRef);

	static Box3D		GetModelBounds		(EDB::GeneralElemConstRef elemRef);
	static bool			Is3DType			(EDB::GeneralElemConstRef elemRef);

	static UInt32		GetComponentNumber	(EDB::GeneralElemConstRef elemRef);
	static short		GetComponentFlags	(EDB::GeneralElemConstRef elemRef, short componentIdx);

	static void			SetSlantedHeight	(EDB::GeneralElemRef elemRef,
											 double z,
											 VBElemOperations::SetHeightLocation location);

	static void			GetStandaloneVisibleMaterials (EDB::GeneralElemConstRef elemRef, bool pbcConversion, GS::HashSet<short>& surfaces);
	
	static bool			ElemHasVisibleSkin	(EDB::GeneralElemConstRef elemRef, 
											EffectiveComposite::Structure structure);

	static ProfileCoordinateSystem	GetProfileCoordinateSystem (EDB::GeneralElemConstRef elemRef, UInt32 createFlags, RefPointLocation location);	//#KiP_Refactor meg kellene szuntetni (a ProfileCoordinateSystem class-t is)

	static void					RelinkElemAfterCopy (const EDB::GeneralElemConstRef& originalElem, const EDB::GeneralElemRef& newElem);

	static bool					HasInfoString		(EDB::GeneralElemConstRef elemRef);
	static GS::UniString		GetInfoString		(EDB::GeneralElemConstRef elemRef);
	static void					SetInfoString		(EDB::GeneralElemRef elemRef, const GS::UniString infoString);

	static VBElem::LabelRef		GetListingLabel		(EDB::GeneralElemConstRef generalElem);

	static GS::UniString		GetLibPartNameById	(const LM::LibPartId& libPartId, const LM::LibrarySet* librarySet);
	static GS::UniString		GetLibPartName		(VBElem::GDLBasedElemConstRef gdlBasedElem, const LM::LibrarySet* librarySet);
	static GS::UniString		GetLibPartName		(const VBElem::GDLBasedElemDefault* gdlBasedElemDefault, const LM::LibrarySet* librarySet);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const EDB::GeneralElemConstRef& elemRef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const EDB::GeneralElemConstRef& elemRef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const EDB::GeneralElemRef& elemRef);

	static VBElem::ParametricProfileRef			GetIProfile			(EDB::GeneralElemRef elemRef);
	static VBElem::ParametricProfileConstRef	GetConstIProfile	(EDB::GeneralElemConstRef elemRef);
};

#endif // VB_ELEM_OPERATIONS__HPP
