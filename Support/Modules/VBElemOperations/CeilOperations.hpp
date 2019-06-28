#ifndef CEIL_OPERATIONS_HPP
#define CEIL_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElements
#include "Ceil.hpp"
#include "CeilDefault.hpp"

// from VBElemOperations
#include "GDLGlobalCalculations.hpp"
#include "VBElemSurfaceDescriptor.hpp"
#include "VBElemOperationsTypes.hpp"


class VB_ELEM_OPERATIONS_DLL_EXPORT CeilOperations
{
public:
	enum MaterialSelector {
		TopMaterial,
		BottomMaterial,
		SideMaterial,
		CutElemMaterial
	};

	template <class CeilType>
	static VBElemSurfaceDescriptor	GetMaterial (const CeilType& ceil,
								 const ADB::AttributeSetConstRef& attributeSet,
								 MaterialSelector selector,
								 bool pbcConversion,
								 short compositeIndex = -1);

	static VBElemSurfaceDescriptor GetMaterialOfDefaultCeil (const VBElem::CeilDefault* ceil,
										   const ADB::AttributeSetConstRef& attributeSet,
										   MaterialSelector selector,
										   bool pbcConversion,
										   short compositeIndex = -1);

	static void		GetStandaloneVisibleMaterials (VBElem::CeilConstRef ceil, bool pbcConversion, GS::HashSet<short>& materials);

	static bool HasVisibleSkin				  (VBElem::CeilConstRef elemRef, EffectiveComposite::Structure structure);

	static UInt32	GetComponentNumber (VBElem::CeilConstRef ceil);

	static short	GetComponentFlags (VBElem::CeilConstRef ceil, short componentIdx);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::CeilConstRef& ceil);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::CeilConstRef& ceil);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::CeilRef& ceil);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::CeilDefault& ceilDef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::CeilDefault& ceilDef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(VBElem::CeilDefault& ceilDef);
};

template <class CeilType>
VBElemSurfaceDescriptor CeilOperations::GetMaterial (const CeilType& ceil,
									const ADB::AttributeSetConstRef& attributeSet,
									MaterialSelector selector,
									bool pbcConversion,
									short compositeIndex)
{
	const bool hasValidSideMaterial = (ceil->GetElemStructure ().IsBasic () || compositeIndex != -1);

	switch (selector) {
		case TopMaterial:
			if (!pbcConversion || ceil->GetTopMaterial ().GetOverride ())
				return VBElemSurfaceDescriptor::FromSurface (ceil->GetTopMaterial ().GetIndex ());
			break;
		case BottomMaterial:
			if (!pbcConversion || ceil->GetBottomMaterial ().GetOverride ())
				return VBElemSurfaceDescriptor::FromSurface (ceil->GetBottomMaterial ().GetIndex ());
			break;
		case CutElemMaterial:
			if (compositeIndex < 0 || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (ceil->GetDefaultSideMaterial ().GetIndex ());
			break;
		case SideMaterial:
			if (ceil->GetDefaultSideMaterial ().GetOverride () || !hasValidSideMaterial)
				return VBElemSurfaceDescriptor::FromSurface (ceil->GetDefaultSideMaterial ().GetIndex ());
			break;
		default:
			DBBREAK ();
	}

	short buildMat = 0;

	if (ceil->GetElemStructure ().IsBasic ()) {
		buildMat = ceil->GetElemStructure ().GetBasicBuildMatIndex ();
	} else {
		DBASSERT (ceil->GetElemStructure ().IsComposite ());
		VBAttr::CompWallConstRef compWall = VBAttr::GetConstCompWall (attributeSet, ceil->GetElemStructure ().GetCompositeIndex ());
		if (compWall != nullptr) {
			if (compositeIndex < 0 || compositeIndex >= compWall->GetSkinNumber ()) {
				compositeIndex = (selector == BottomMaterial) ? compWall->GetSkinNumber () - 1 : 0;
			}
			buildMat = compWall->GetSkinBuildingMaterialIndex (compositeIndex);
		}
	}

	return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat, attributeSet);
}


#endif // CEIL_OPERATIONS_HPP
