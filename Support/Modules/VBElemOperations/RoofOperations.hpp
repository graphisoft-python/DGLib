#ifndef ROOF_OPERATIONS_HPP
#define ROOF_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBElements
#include "PolyRoof.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElemOperations
#include "GDLGlobalCalculations.hpp"
#include "VBElemSurfaceDescriptor.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT RoofOperations
{
public:
	enum MaterialSelector {
		TopMaterial,
		BotMaterial,
		SideMaterial,
		CutElemMaterial
	};

	template <class RoofType>
	static VBElemSurfaceDescriptor	GetMaterial (const RoofType& roof,
								 const ADB::AttributeSetConstRef& attributeSet,
								 MaterialSelector selector,
								 bool pbcConversion,
								 short componentIndex = -1);

	template <class RoofType>
	static VBElemSurfaceDescriptor	GetStructureMaterial (const RoofType& roof,
										  const ADB::AttributeSetConstRef& attributeSet,
										  MaterialSelector selector,
										  short componentIndex = -1);

	static void		GetStandaloneVisibleMaterials (VBElem::RoofConstRef roof, bool pbcConversion, GS::HashSet<short>& materials);

	static UInt32	GetComponentNumber (VBElem::RoofConstRef roof);

	static short	GetComponentFlags (VBElem::RoofConstRef roof, short componentIdx);

	static void		EnumerateExpectedPolyRoofPlanes (const VBElem::PolyRoofConstRef& polyRoof, const std::function<void (UInt32 baseEdgeUnId, UIndex levelIdx)>& enumerator);
	
	static void		EnumerateExistingPolyRoofPlanes (const VBElem::PolyRoofConstRef& polyRoof, const std::function<void (UInt32 baseEdgeUnId, UIndex levelIdx)>& enumerator);

};

template <class RoofType>
VBElemSurfaceDescriptor RoofOperations::GetMaterial (	const RoofType& roof,
									const ADB::AttributeSetConstRef& attributeSet,
									MaterialSelector selector,
									bool pbcConversion,
									short componentIndex)
{
	const bool hasValidSideMaterial = (roof->GetElemStructure ().IsBasic () || componentIndex != -1);

	switch (selector) {
		case TopMaterial:
			if (roof->GetOppositeSideMaterial ().GetOverride () || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (roof->GetOppositeSideMaterial ().GetIndex ());
			break;
		case BotMaterial:
			if (roof->GetReferenceSideMaterial ().GetOverride () || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (roof->GetReferenceSideMaterial ().GetIndex ());
			break;
		case SideMaterial:
			if (roof->GetDefaultSideMaterial ().GetOverride () || !hasValidSideMaterial || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (roof->GetDefaultSideMaterial ().GetIndex ());
			break;
		default:
			DBBREAK ();
			//lint -fallthrough
		case CutElemMaterial:
			if (componentIndex < 0 || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (roof->GetDefaultSideMaterial ().GetIndex ());
			break;
	}

	return GetStructureMaterial (roof, attributeSet, selector, componentIndex);
}

template <class RoofType>
VBElemSurfaceDescriptor RoofOperations::GetStructureMaterial (	const RoofType& roof,
												const ADB::AttributeSetConstRef& attributeSet,
												MaterialSelector selector,
												short componentIndex)
{
	short buildMat = 0;

	if (roof->GetElemStructure ().IsBasic ()) {
		buildMat = roof->GetElemStructure ().GetBasicBuildMatIndex ();
	} else {
		VBAttr::CompWallConstRef compWall = VBAttr::GetConstCompWall (attributeSet, roof->GetElemStructure ().GetCompositeIndex ());
		if (compWall != nullptr) {
			if (compWall != nullptr) {
				if (componentIndex < 0 || componentIndex >= compWall->GetSkinNumber ()) {
					componentIndex = (selector == BotMaterial) ? compWall->GetSkinNumber () - 1 : 0;
				}
				buildMat = compWall->GetSkinBuildingMaterialIndex (componentIndex);
			}
		}
	}

	return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat, attributeSet);
}

#endif // ROOF_OPERATIONS_HPP
