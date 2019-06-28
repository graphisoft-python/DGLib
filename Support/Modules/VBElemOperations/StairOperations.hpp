#ifndef STAIR_OPERATIONS_HPP
#define STAIR_OPERATIONS_HPP

#include "VBElemOperationsExport.hpp"

// from GSRoot
#include "Array.hpp"

// from Geometry
#include "Coord.h"
#include "Polygon2D.hpp"
#include "Polyline2D.hpp"
#include "Box3DData.h"

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElements
#include "StairTypes.hpp"
#include "VBElements/TreadTypes.hpp"
#include "VBElements/RiserTypes.hpp"
#include "VBElements/SymbTypes.hpp"
#include "VBElements/TreadPolygonVertexData.hpp"
#include "VBElements/TreadPolygonEdgeData.hpp"
#include "VBElements/StairStructureTypes.hpp"
#include "VBElements/StairPolylineVertexData.hpp"
#include "VBElements/StairPolylineEdgeData.hpp"
#include "VBElements/MonolithStairStructure.hpp"
#include "VBElements/SideStairStructure.hpp"
#include "VBElements/UnderSupportStairStructure.hpp"

namespace VBCalculations {
	struct GDLGlobalCalcEnvir;
	struct StairBreakMarkDescription;
}

class VBElemSurfaceDescriptor;
class StairModelViewOption;

namespace StairOperations {

	enum VB_ELEM_OPERATIONS_DLL_EXPORT MaterialSelector {
		TopMaterial,
		BottomMaterial,
		SideMaterial,
		CutElemMaterial
	};

	VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor GetMaterial (	const VBElem::StairConstRef& stair,
								const ADB::AttributeSetConstRef& attributeSet,
								MaterialSelector selector,
								bool pbcConversion);

	VB_ELEM_OPERATIONS_DLL_EXPORT void GetStandaloneVisibleMaterials (VBElem::StairConstRef stair, bool pbcConversion, GS::HashSet<short>& materials);

	VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor GetMaterial (const VBElem::StairStructureConstRef& stairStructure,
																  const ADB::AttributeSetConstRef& attributeSet,
																  MaterialSelector selector,
																  bool pbcConversion);

	VB_ELEM_OPERATIONS_DLL_EXPORT void GetStandaloneVisibleMaterials (VBElem::StairConstRef stair, bool pbcConversion, GS::HashSet<short>& materials);
	VB_ELEM_OPERATIONS_DLL_EXPORT void GetStandaloneVisibleMaterials (VBElem::StairStructureConstRef stairStructure, bool pbcConversion, GS::HashSet<short>& materials);

	VB_ELEM_OPERATIONS_DLL_EXPORT bool GetBreakMarkPosition	(const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, const bool upper, const bool isRCP, VBCalculations::StairBreakMarkDescription& breakMarkDescription);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool GetBreakMarkPositionOnFloor (const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, const EDB::FloorConstRef& floor, const bool upper, const bool isRCP, VBCalculations::StairBreakMarkDescription& breakMarkDescription);

	VB_ELEM_OPERATIONS_DLL_EXPORT bool GetRawBreakMarkDescription (const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, const EDB::FloorConstRef& floor, VBCalculations::StairBreakMarkDescription& breakMarkDescription);

	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::StairConstRef stair);
	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::MonolithStairStructureConstRef structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::SideStairStructureConstRef structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::UnderSupportStairStructureConstRef structure);

	struct VB_ELEM_OPERATIONS_DLL_EXPORT StairPartsForBreakMarkEditFeedback
	{
		VBElem::StairPolyline											walkingLineLowerPart;
		VBElem::StairPolyline											walkingLineMiddlePart;
		VBElem::StairPolyline											walkingLineUpperPart;
		VBElem::StairPolyline											walkingLineFull;
		GS::Array<GS::Pair<UIndex, VBElem::TreadPolygon>>				treadPolygonLowerParts;
		GS::Array<GS::Pair<UIndex, VBElem::TreadPolygon>>				treadPolygonMiddleParts;
		GS::Array<GS::Pair<UIndex, VBElem::TreadPolygon>>				treadPolygonUpperParts;
		GS::Array<GS::Pair<UIndex, VBElem::TreadPolygon>>				treadPolygonFull;

		bool															IsValid	(void)	const		{ return treadPolygonLowerParts.GetSize () > 0 || treadPolygonMiddleParts.GetSize () > 0 || treadPolygonUpperParts.GetSize () > 0; }
	};

	VB_ELEM_OPERATIONS_DLL_EXPORT void GetStairPartsForBreakMarkEditFeedback (const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, StairPartsForBreakMarkEditFeedback& stairParts);

	VB_ELEM_OPERATIONS_DLL_EXPORT void CalculateTreadPartsToDraw (const VBElem::StairConstRef&					stair,
										   const VBCalculations::GDLGlobalCalcEnvir&	gdlCalcEnvir,
										   VBElem::TreadConstRefList&					treadsToLowerPart,
										   VBElem::TreadConstRefList&					treadsToMiddlePart,
										   VBElem::TreadConstRefList&					treadsToUpperPart,
										   VBElem::TreadConstRefList&					treadsEntireStair);

	VB_ELEM_OPERATIONS_DLL_EXPORT double	RiserDistanceToAngle				(const VBElem::StairDefault& stairDefault, const VBElem::StairPartRole role, const double undercut);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	RiserAngleToDistance				(const VBElem::StairDefault& stairDefault, const VBElem::StairPartRole role, const double angle);
	VB_ELEM_OPERATIONS_DLL_EXPORT void		SetHomeStory						(VBElem::StairRef stair, const short homeStoryNum);
	
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		StairHasDraining					(const VBElem::StairConstRef& stair);

	VB_ELEM_OPERATIONS_DLL_EXPORT bool		IsAppliedFloorPlanSymb				(const VBElem::StairConstRef& stair, const StairModelViewOption& modelViewOption, const VBElem::SymbConstRef& symb);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		IsAppliedReflectedCeilingPlanSymb	(const VBElem::StairConstRef& stair, const StairModelViewOption& modelViewOption, const VBElem::SymbConstRef& symb);
	VB_ELEM_OPERATIONS_DLL_EXPORT VBElem::StairGridType		GetEffectiveStairGridTypeForDrawing (const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlCalcEnvir, const EDB::FloorConstRef& floor);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		GetStairLowerBreakMarkValid (const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlCalcEnvir, const EDB::FloorConstRef& floor);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		GetStairUpperBreakMarkValid (const VBElem::StairConstRef& stair, const VBCalculations::GDLGlobalCalcEnvir& gdlCalcEnvir, const EDB::FloorConstRef& floor);
	
	VB_ELEM_OPERATIONS_DLL_EXPORT VBElem::TreadConstRef	GetLowerTread (const VBElem::TreadConstRef& tread);
	VB_ELEM_OPERATIONS_DLL_EXPORT VBElem::TreadConstRef	GetUpperTread (const VBElem::TreadConstRef& tread);
	VB_ELEM_OPERATIONS_DLL_EXPORT void					SwapLeadTrailEdges (VBElem::TreadPolygon& poly);
};




#endif // STAIR_OPERATIONS_HPP
