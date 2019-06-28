#ifndef CURTAINWALL_OPERATIONS_HPP
#define CURTAINWALL_OPERATIONS_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "CurtainWall.hpp"

// from VElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"

// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT CurtainWallOperations
{
public:
	static void GetStandaloneVisibleMaterials (VBElem::CurtainWallConstRef curtainWall, bool pbcConversion, GS::HashSet<short>& materials);

	enum class EnumerationMode
	{
		IncludeSegments,
		OmitSegments
	};

	static void EnumerateSubElements (const VBElem::CurtainWallConstRef& curtainWall, CurtainWallOperations::EnumerationMode mode, const std::function<void (const VBElem::CWSubElementConstRef&)>& enumerator);

	//static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::CurtainWallConstRef& curtainWall);
	//static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::CurtainWallRef& curtainWall);

	static GS::Int32	GetBoundaryPlacementForGDL (const VBElem::CWFrameConstRef& cwFrame);

	static void	CalculateCW3DReferencePolyline (VBElem::CurtainWallConstRef cw, GS::Array<Coord3D>* coordsArray);
};

#endif // CURTAINWALL_OPERATIONS_HPP
