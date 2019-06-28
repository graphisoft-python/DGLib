#ifndef BEAM_OPERATIONS__HPP
#define BEAM_OPERATIONS__HPP

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperations.hpp"
#include "ProfileInterface.hpp"
#include "GDLGlobalCalculations.hpp"
#include "VBElemSurfaceDescriptor.hpp"

// from VBElements
#include "BeamTypes.hpp"
#include "CrossSectType.hpp"
#include "GeneralElem.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"

// =====================================================================================================================
//  BeamOperations
// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT BeamOperations
{
public:
	enum MaterialSelector {
		LeftMaterial,
		TopMaterial,
		RightMaterial,
		BotMaterial,
		SideMaterial,
		CutElemMaterial,
		HoleMaterial,
		CropMaterial
	};

	template <class BeamType>
	static VBElemSurfaceDescriptor		GetMaterial (const BeamType& beam,
												 const ADB::AttributeSetConstRef& attributeSet,
												 MaterialSelector selector,
												 bool pbcConversion,
												 Int32 componentIndex = -1,
												 const ProfileInterface* profile3DData = nullptr);

	static void						DragHoles (VBElem::BeamRef beam, double x, double z);
	
	static void						SetSlantedHeight (VBElem::BeamRef beam, double z, VBElemOperations::SetHeightLocation location);

	static UInt32					GetComponentNumber (VBElem::BeamConstRef beam);

	static short GetComponentFlags (VBElem::BeamConstRef beam, short componentIdx);

	static void						GetStandaloneVisibleMaterials (VBElem::BeamConstRef beam, bool pbcConversion, GS::HashSet<short>& materials);

	static Vector3D					GetDirection3D (VBElem::BeamConstRef beam, VBElemOperations::RefPointLocation location); 

	static GS::Optional<GenArc>		GetReferenceLineArc (const VBElem::BeamConstRef& beam);

	static ProfileCoordinateSystem	GetProfileCoordinateSystem (VBElem::BeamConstRef beam, 
																UInt32 createFlags, 
																VBElemOperations::RefPointLocation location);

	static bool HasVisibleSkin				  (VBElem::BeamConstRef elemRef, EffectiveComposite::Structure structure);

	static Box3DType GetRawBounds3D (const VBElem::BeamConstRef& beam);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::BeamConstRef& beam);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::BeamConstRef& beam);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::BeamRef& beam);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::BeamDefault& beamDef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::BeamDefault& beamDef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(VBElem::BeamDefault& beamDef);
};

template <class BeamType>
VBElemSurfaceDescriptor	BeamOperations::GetMaterial (const BeamType& beam,
									 const ADB::AttributeSetConstRef& attributeSet,
									 MaterialSelector selector,
									 bool pbcConversion,
									 Int32 componentIndex,
									 const ProfileInterface* profile3DData)
{
	const bool missingProfileData = (beam->GetCrossSectType () != CrossSect_Simple && profile3DData == nullptr);

	switch (selector) {
	case LeftMaterial:
		if (beam->GetOverrideLeftMaterial () || !pbcConversion || missingProfileData)
			return VBElemSurfaceDescriptor::FromSurface (beam->GetLeftMaterial ());
		break;
	case TopMaterial:
		if (beam->GetOverrideTopMaterial () || !pbcConversion || missingProfileData)
			return VBElemSurfaceDescriptor::FromSurface (beam->GetTopMaterial ());
		break;
	case RightMaterial:
		if (beam->GetOverrideRightMaterial () || !pbcConversion || missingProfileData)
			return VBElemSurfaceDescriptor::FromSurface (beam->GetRightMaterial ());
		break;
	case BotMaterial:
		if (beam->GetOverrideBottomMaterial () || !pbcConversion || missingProfileData)
			return VBElemSurfaceDescriptor::FromSurface (beam->GetBottomMaterial ());
		break;
	case CutElemMaterial:
	case CropMaterial:
		if (componentIndex < 0 || !pbcConversion)
			return VBElemSurfaceDescriptor::FromSurface (beam->GetSideMaterial ());
		break;
	case SideMaterial:
		if (beam->GetOverrideSideMaterial () || !pbcConversion || missingProfileData)
			return VBElemSurfaceDescriptor::FromSurface (beam->GetSideMaterial ());
		break;
	default:
		DBBREAK ();
		return VBElemSurfaceDescriptor::FromSurface (beam->GetSideMaterial ());
	}

	short buildMat = 0;
	short material = 0;
	if (beam->GetCrossSectType () != CrossSect_Profiled) {
		buildMat = beam->GetElemStructure ().GetBasicBuildMatIndex ();
	} else if (profile3DData != nullptr && profile3DData->IsValid ()) {
		if (componentIndex >= 0 && componentIndex < (Int32) profile3DData->GetComponentCount ()) {
			buildMat = profile3DData->GetComponentBuildingMaterialIndex (componentIndex);
		} else {
			material = beam->GetSideMaterial ();
		}
	}
	if (buildMat != 0) {
		return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat, attributeSet);
	}

	return VBElemSurfaceDescriptor::FromSurface (material);
}


#endif // BEAM_OPERATIONS__HPP 