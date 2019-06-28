#ifndef COLUMN_OPERATIONS_HPP
#define COLUMN_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBElemOperations
#include "GDLGlobalCalculations.hpp"
#include "ProfileInterface.hpp"
#include "ProfileCoordinateSystem.hpp"
#include "VBElemOperations.hpp"
#include "VBElemSurfaceDescriptor.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElements
#include "Column.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT ColumnOperations
{
public:
	enum MaterialSelector {
		TopMaterial,
		BotMaterial,
		SideMaterial,
		InsideMaterial,
		WrappingTopMaterial,
		WrappingBotMaterial,
		CropUpwardsMaterial,
		CropDownwardsMaterial,
		CutElemMaterial,
		OutsideMaterial // returns veneer material if has veneer, returns column material otherwise
	};

	template <class ColumnType>
	static VBElemSurfaceDescriptor GetMaterial (const ColumnType& column,
								 const ADB::AttributeSetConstRef& attributeSet,
								 MaterialSelector selector,
								 bool pbcConversion,
								 Int32 componentIndex = -1,
								 const ProfileInterface* profile3DData = nullptr);

	template <class ColumnType>
	static bool		IsWrappingColumn (const ColumnType& column);

	static void		GetStandaloneVisibleMaterials (VBElem::ColumnConstRef column, bool pbcConversion, GS::HashSet<short>& materials);

	static UInt32	GetComponentNumber (VBElem::ColumnConstRef column);

	static short	GetComponentFlags (VBElem::ColumnConstRef column, short componentIdx);

	static double	GetRoundColumnRadius (VBElem::ColumnConstRef column);

	static void		SetRoundColumnRadius (const VBElem::ColumnRef& column, double newRadius);

	static double	GetWidth (VBElem::ColumnConstRef column);

	static double	GetDepth (VBElem::ColumnConstRef column);

	static void		SetWidth (VBElem::ColumnRef column, double newWidth);

	static void		SetDepth (VBElem::ColumnRef column, double newDepth);
	
	static void		SetHomeStory (VBElem::ColumnRef column, const short homeStoryNum);

	static Vector3D	GetColumnDirection (VBElem::ColumnConstRef column);

	static Vector3D GetColumnVector (VBElem::ColumnConstRef column);

	static Box3DType GetRawBounds3D (const VBElem::ColumnConstRef& column);

	static ProfileCoordinateSystem	GetProfileCoordinateSystem (VBElem::ColumnConstRef column, 
																UInt32 createFlags, 
																VBElemOperations::RefPointLocation location);

	static bool HasVisibleSkin (VBElem::ColumnConstRef elemRef, EffectiveComposite::Structure structure);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::ColumnConstRef& column);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::ColumnConstRef& column);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::ColumnRef& column);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::ColumnDefault& columnDef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::ColumnDefault& columnDef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(VBElem::ColumnDefault& columnDef);
};

template <class ColumnType>
VBElemSurfaceDescriptor ColumnOperations::GetMaterial (	const ColumnType& column,
										const ADB::AttributeSetConstRef& attributeSet,
										MaterialSelector selector,
										bool pbcConversion,
										Int32 componentIndex,
										const ProfileInterface* profile3DData)
{
	bool missingProfileData = (column->GetCrossSectType () != CrossSect_Simple && profile3DData == nullptr);

	switch (selector) {
		case TopMaterial:
			if (column->GetOverrideMaterial () || !pbcConversion || missingProfileData)
				return VBElemSurfaceDescriptor::FromSurface (column->GetMaterial ());
			break;
		case BotMaterial:
			if (column->GetOverrideMaterial () || !pbcConversion || missingProfileData)
				return VBElemSurfaceDescriptor::FromSurface (column->GetMaterial ());
			break;
		case SideMaterial:
		case OutsideMaterial:
			if (column->GetOverrideMaterial () || !pbcConversion || missingProfileData)
				return VBElemSurfaceDescriptor::FromSurface (column->GetMaterial ());
			break;
		case InsideMaterial:
			return GetMaterial (column, attributeSet, CutElemMaterial, pbcConversion, componentIndex, profile3DData);
		case WrappingTopMaterial:
		case WrappingBotMaterial:
			{
				if (column->GetOverrideMaterial () || !pbcConversion) {
					return GetMaterial (column, attributeSet, selector == WrappingTopMaterial ? TopMaterial : BotMaterial, pbcConversion, componentIndex, profile3DData);
				}

				const short buildMat = column->GetVeneerThickness () == 0.0 ? column->GetElemStructure ().GetCoreIndex () : column->GetElemStructure ().GetVeneerIndex  ();
				return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat, attributeSet);
			}
			break;
		case CutElemMaterial:
			if (componentIndex < 0 || !pbcConversion) {
				return VBElemSurfaceDescriptor::FromSurface (column->GetMaterial ());
			}
			break;
		default: 
			DBBREAK ();
			return VBElemSurfaceDescriptor::FromSurface (column->GetMaterial ());
			break;
	}

	short buildMat = 0;
	short material = 0;
	// in PBC mode the column with CrossSect_Simple converted as a profiled column, so here comes a component index
	if (column->GetCrossSectType () != CrossSect_Profiled && componentIndex == -1) {
		if (selector == OutsideMaterial && column->GetVeneerThickness () > 0.0) {
			buildMat = column->GetElemStructure ().GetVeneerIndex ();
		} else {
			buildMat = column->GetElemStructure ().GetCoreIndex ();
		}
	} else if (profile3DData != nullptr && profile3DData->IsValid ()) {
		if (componentIndex >= 0 && componentIndex < (Int32)profile3DData->GetComponentCount ()) {
			buildMat = profile3DData->GetComponentBuildingMaterialIndex (componentIndex);
		} else {
			material = column->GetMaterial ();
		}
	}
	
	if (buildMat != 0) {
		return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat, attributeSet);
	}

	return VBElemSurfaceDescriptor::FromSurface (material);
}

template <class ColumnType>
bool ColumnOperations::IsWrappingColumn (const ColumnType& column)
{
	if (column->GetElemStructure ().IsProfile () || column->IsSlanted ()) {
		return false;
	}

	if (fabs (column->GetVeneerThickness ()) >= Eps && column->GetVeneerType () == VBElem::Column::VeneerTypeFinish) {
		return false;
	}

	return column->IsWrapping ();
}

#endif // COLUMN_OPERATIONS_HPP
