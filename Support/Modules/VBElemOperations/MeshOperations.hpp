#ifndef MESH_OPERATIONS_HPP
#define MESH_OPERATIONS_HPP

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElements
#include "Mesh.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"
#include "VBElemSurfaceDescriptor.hpp"


class VB_ELEM_OPERATIONS_DLL_EXPORT MeshOperations
{
public:
	enum MaterialSelector {
		TopMaterial,
		BottomMaterial,
		SideMaterial,
		CutElemMaterial
	};

	template <class MeshType>
	static VBElemSurfaceDescriptor GetMaterial (	const MeshType& mesh,
								const ADB::AttributeSetConstRef& attributeSet,
								MaterialSelector selector,
								bool pbcConversion);

	static void		GetStandaloneVisibleMaterials (VBElem::MeshConstRef mesh, bool pbcConversion, GS::HashSet<short>& materials);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::MeshConstRef& mesh);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::MeshConstRef& mesh);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::MeshRef& mesh);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::MeshDefault& meshDef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::MeshDefault& meshDef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(VBElem::MeshDefault& meshDef);
};

template <class MeshType>
VBElemSurfaceDescriptor MeshOperations::GetMaterial (	const MeshType& mesh,
									const ADB::AttributeSetConstRef& attributeSet,
									MaterialSelector selector,
									bool pbcConversion)
{
	switch (selector) {
		case TopMaterial:
			if (!pbcConversion || mesh->GetOverrideTopMaterial ())
				return VBElemSurfaceDescriptor::FromSurface (mesh->GetTopMaterial ());
			break;
		case BottomMaterial:
			if (!pbcConversion || mesh->GetOverrideBottomMaterial ())
				return VBElemSurfaceDescriptor::FromSurface (mesh->GetBottomMaterial ());
			break;
		case SideMaterial:
			if (!pbcConversion || mesh->GetOverrideSideMaterial ())
				return VBElemSurfaceDescriptor::FromSurface (mesh->GetSideMaterial ());
			break;
		case CutElemMaterial:
			if (!pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (mesh->GetSideMaterial ());
			break;
		default:
			DBBREAK ();
	}

	const short buildMat = mesh->GetElemStructure ().GetBasicBuildMatIndex ();

	return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface(buildMat, attributeSet);
}

#endif // MESH_OPERATIONS_HPP
