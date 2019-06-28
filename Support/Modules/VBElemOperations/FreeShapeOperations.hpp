#ifndef FREESHAPE_OPERATIONS_HPP
#define FREESHAPE_OPERATIONS_HPP

// from VBElements
#include "FreeShapeTypes.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"


class VB_ELEM_OPERATIONS_DLL_EXPORT FreeShapeOperations
{
public:
	enum MaterialSelector {
		SideMaterial,
		CutElemMaterial
	};

	static void		GetStandaloneVisibleMaterials (VBElem::FreeShapeConstRef freeShape, bool pbcConversion, GS::HashSet<short>& materials);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::FreeShapeConstRef& freeShape);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::FreeShapeConstRef& freeShape);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::FreeShapeRef& freeShape);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::FreeShapeDefault& freeShapeDef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::FreeShapeDefault& freeShapeDef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(VBElem::FreeShapeDefault& freeShapeDef);
};

#endif // FREESHAPE_OPERATIONS_HPP
