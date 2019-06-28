#ifndef VB_ELEM_OPERATIONS_EXTENSION__HPP
#define VB_ELEM_OPERATIONS_EXTENSION__HPP

#include "Extension.hpp"
#include "GeneralElem.hpp"
#include "VBElementsBase/ModelElement.hpp"
#include "VBElemOperations.hpp"
#include "VBElemOperationsExport.hpp"

//from ModelCalculations
#include "ProjectionSurface.hpp"

// =====================================================================================================================
//  VBElemOperationsExtension
// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT VBElemOperationsExtension: public GS::Extension
{
public:
	static GS::ExtensionId id;

	VBElemOperationsExtension (GS::ClassInfo* target);
	virtual ~VBElemOperationsExtension ();

	virtual void			ForEachSubElem (EDB::GeneralElemConstRef elemRef, VBElemOperations::GeneralElemConstFn fn) const = 0;

	virtual double			GetAbsoluteTop		(EDB::GeneralElemConstRef elemRef) const = 0;
	virtual double			GetAbsoluteBottom	(EDB::GeneralElemConstRef elemRef) const = 0;

	virtual Box3D			GetModelBounds		(EDB::GeneralElemConstRef elemRef) const = 0;
	virtual bool			Is3DType			(EDB::GeneralElemConstRef elemRef) const = 0;

	virtual UInt32			GetComponentNumber	(EDB::GeneralElemConstRef elemRef) const = 0;
	virtual	short			GetComponentFlags	(EDB::GeneralElemConstRef elemRef, short componentIdx) const = 0;

	virtual void			SetSlantedHeight	(EDB::GeneralElemRef elemRef,
												 double z, 
												 VBElemOperations::SetHeightLocation location) const = 0;

	virtual void			GetStandaloneVisibleMaterials	(EDB::GeneralElemConstRef elemRef,
															 bool pbcConversion, 
															 GS::HashSet<short>& surfaces) const = 0;

	virtual ProfileCoordinateSystem		GetProfileCoordinateSystem (EDB::GeneralElemConstRef elemRef, 
																	UInt32 createFlags,
																	VBElemOperations::RefPointLocation location) const = 0;

	virtual bool				HasInfoString	(EDB::GeneralElemConstRef elemRef) const = 0;
	virtual void				SetInfoString	(EDB::GeneralElemRef elemRef, const GS::UniString& infoString) const = 0;

	virtual bool				HasVisibleSkin	(EDB::GeneralElemConstRef elemRef, EffectiveComposite::Structure structure) const = 0;

	virtual GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const EDB::GeneralElemConstRef& elemRef) const = 0;
	virtual GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const EDB::GeneralElemConstRef& elemRef) const = 0;
	virtual GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const EDB::GeneralElemRef& elemRef) const = 0;

	virtual VBElem::ParametricProfileRef		GetIProfile			(EDB::GeneralElemRef elemRef) const = 0;
	virtual VBElem::ParametricProfileConstRef	GetConstIProfile	(EDB::GeneralElemConstRef elemRef) const = 0;
};

#endif // VB_ELEM_OPERATIONS_EXTENSION__HPP
