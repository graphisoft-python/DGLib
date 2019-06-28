#ifndef SHELL_OPERATIONS_HPP
#define SHELL_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from VBElements
#include "Shell.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElemOperations
#include "GDLGlobalCalculations.hpp"
#include "VBElemSurfaceDescriptor.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT ShellOperations
{
public:
	enum MaterialSelector {
		ReferenceSideMaterial,
		OppositeSideMaterial,
		SideMaterial,
		CutElemMaterial,
		InnerReferenceSideMaterial,
		InnerOppositeSideMaterial
	};

	template <class ShellType>
	static VBElemSurfaceDescriptor GetMaterial (const ShellType& shell,
								 const ADB::AttributeSetConstRef& attributeSet,
								 MaterialSelector selector,
								 bool pbcConversion,
								 short componentIndex = -1);

	template <class ShellType>
	static VBElemSurfaceDescriptor	GetStructureMaterial (const ShellType& shell,
										  const ADB::AttributeSetConstRef& attributeSet,
										  MaterialSelector selector,
										  short componentIndex = -1);

	static void		GetStandaloneVisibleMaterials (VBElem::ShellConstRef shell, bool pbcConversion, GS::HashSet<short>& materials);

	static UInt32	GetComponentNumber (VBElem::ShellConstRef shell);

	static short	GetComponentFlags (VBElem::ShellConstRef shell, short componentIdx);
};

template <class ShellType>
VBElemSurfaceDescriptor ShellOperations::GetMaterial (	const ShellType& shell,
										const ADB::AttributeSetConstRef& attributeSet,
										MaterialSelector selector,
										bool pbcConversion,
										short componentIndex)
{
	const bool hasValidSideMaterial = (shell->GetElemStructure ().IsBasic () || componentIndex != -1);

	switch (selector) {
		case ReferenceSideMaterial:
			if (shell->GetReferenceSideMaterial ().GetOverride () || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (shell->GetReferenceSideMaterial ().GetIndex ());
			break;
		case OppositeSideMaterial:
			if (shell->GetOppositeSideMaterial ().GetOverride () || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (shell->GetOppositeSideMaterial ().GetIndex ());
			break;
		case SideMaterial:
			if (shell->GetDefaultSideMaterial ().GetOverride () || !hasValidSideMaterial || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (shell->GetDefaultSideMaterial ().GetIndex ());
			break;
		default:
			DBBREAK ();
			//lint -fallthrough
		case InnerReferenceSideMaterial:
		case InnerOppositeSideMaterial:
		case CutElemMaterial:
			if (componentIndex < 0 || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (shell->GetDefaultSideMaterial ().GetIndex ());
			break;
	}

	return GetStructureMaterial (shell, attributeSet, selector, componentIndex);
}

template <class ShellType>
VBElemSurfaceDescriptor ShellOperations::GetStructureMaterial (	const ShellType& shell,
												const ADB::AttributeSetConstRef& attributeSet,
												MaterialSelector selector,
												short componentIndex)
{
	short buildMat = 0;

	if (shell->GetElemStructure ().IsBasic ()) {
		buildMat = shell->GetElemStructure ().GetBasicBuildMatIndex ();
	} else {
		VBAttr::CompWallConstRef compWall = VBAttr::GetConstCompWall (attributeSet, shell->GetElemStructure ().GetCompositeIndex ());
		if (compWall != nullptr) {
			if (componentIndex < 0 || componentIndex >= compWall->GetSkinNumber ())
				componentIndex = (selector == OppositeSideMaterial || selector == InnerOppositeSideMaterial) ? compWall->GetSkinNumber () - 1 : 0;
			buildMat = compWall->GetSkinBuildingMaterialIndex (componentIndex);
		}
	}

	return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat, attributeSet);
}

#endif // SHELL_OPERATIONS_HPP
