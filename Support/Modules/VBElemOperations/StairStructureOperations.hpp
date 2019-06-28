// *********************************************************************************************************************
// Contact person:	TBa
// *********************************************************************************************************************

#ifndef STAIRSTRUCTUREOPERATIONS_HPP
#define STAIRSTRUCTUREOPERATIONS_HPP

#pragma once

#include "VBElemOperationsExport.hpp"
#include "VBElemSurfaceDescriptor.hpp"
#include "VBElements/StairStructureTypes.hpp"
#include "VBElements/BeamSupportStairStructureTypes.hpp"
#include "VBElements/MonolithStairStructureTypes.hpp"
#include "VBElements/SideStairStructureTypes.hpp"
#include "VBElements/UnderSupportStairStructureTypes.hpp"
#include "VBElements/CantileveredSupportStairStructureTypes.hpp"
#include "VBElements/RiserTypes.hpp"
#include "VBElements/TreadTypes.hpp"
#include "VBElements/StairTypes.hpp"
#include "VBElements/StairStructureCut.hpp"

#include "VBElements/TreadPolygonVertexData.hpp"
#include "VBElements/TreadPolygonEdgeData.hpp"

#include "Polygon2DClassDefinition.hpp"

namespace VBElem {
	class StairStructureDraining;
};

namespace StairStructureOperations
{
	enum MaterialSelector {
		TopMaterial,
		BottomMaterial,
		LeftMaterial,
		RightMaterial,
		CutElemMaterial
	};

	VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor GetMonolithMaterial (const VBElem::MonolithStairStructureConstRef& structure,
																	     const ADB::AttributeSetConstRef& attributeSet,
																	     MaterialSelector selector);

	VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor GetMonolithDrainingMaterial (const VBElem::StairStructureDraining& draining, const VBElem::MonolithStairStructureConstRef& structure, const ADB::AttributeSetConstRef& attributeSet);


	// Unifies the structure along Run-Run connections and returns if the unified structure starts with tread
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		StartsWithTreadUnified			(const VBElem::StairStructureConstRef& structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		StartsWithTread					(const VBElem::StairStructureConstRef& structure);
	// Unifies the structure along Run-Run connections and returns if the unified structure ends with tread
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		EndsWithTreadUnified			(const VBElem::StairStructureConstRef&	structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool		EndsWithTread					(const VBElem::StairStructureConstRef& structure);

	VB_ELEM_OPERATIONS_DLL_EXPORT Vector	GetTreadEdgeNormal				(const VBElem::TreadPolygon::ConstEdgeIterator& it);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	CalculateDefaultRiserOffset		(const VBElem::StairStructureConstRef& structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	CalculateThicknessAtRiser		(double normCoeff, UInt32 runStartTreadIndex, UInt32 runEndTreadIndex, UInt32 iRiser, double thickness, double thickness2);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	CalcSteppedRiserReflectedOffset (const VBElem::RiserConstRef& riser, double levelDiff, double horizontalThickness, double verticalThickness);

	VB_ELEM_OPERATIONS_DLL_EXPORT Sector				GetEdgeSector (const VBElem::TreadPolygon& poly, const VBElem::TreadPolygonEdgeType type);
	VB_ELEM_OPERATIONS_DLL_EXPORT bool					DoesPolygonContainPartOfSector (const VBElem::TreadPolygon& poly, Sector sector);
	VB_ELEM_OPERATIONS_DLL_EXPORT VBElem::TreadPolygon	ParallelVerticalCutPoly (const VBElem::TreadPolygon& landing, double dx, VBElem::TreadPolygonEdgeType type = VBElem::LeadingEdge, UInt32* resNum = nullptr);
	VB_ELEM_OPERATIONS_DLL_EXPORT VBElem::TreadPolygon	VerticalCutPoly (const VBElem::TreadPolygon& landing, Vector cutDir, Coord cutPoint, VBElem::TreadPolygonEdgeType type = VBElem::LeadingEdge, UInt32* resNum = nullptr);

	VB_ELEM_OPERATIONS_DLL_EXPORT VBElem::TreadPolygon	GetExtensionPolyAlongLanding (const VBElem::TreadPolygon& landing, 
																					  double dx, 
																					  VBElem::StairStructureCut::ExtensionType extensionType, 
																					  VBElem::TreadPolygonEdgeType type = VBElem::LeadingEdge);

	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::MonolithStairStructureConstRef structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::SideStairStructureConstRef structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::UnderSupportStairStructureConstRef structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT Box3D GetModelBounds (VBElem::CantileveredSupportStairStructureConstRef structure);

	VB_ELEM_OPERATIONS_DLL_EXPORT void GetStandaloneVisibleMaterials (VBElem::StairStructureConstRef stairStructure, bool pbcConversion, GS::HashSet<short>& materials);

	VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor GetMaterial (const VBElem::StairStructureConstRef& stairStructure,
																 const ADB::AttributeSetConstRef& attributeSet,
																 MaterialSelector selector,
																 bool pbcConversion);


	VB_ELEM_OPERATIONS_DLL_EXPORT void	CalculateStairStructureGlobals (const VBElem::StairStructureConstRef&	ss,
																		GS::Array<double>&						geom,
																		GS::Array<Int32>&						edgeFlags,
																		GS::Array<Int32>&						connectionFlags,
																		GS::Array<double>&						connectionOffsets);
	
	VB_ELEM_OPERATIONS_DLL_EXPORT double	ApproxBeamSupportSlope (const VBElem::TreadConstRef& tread, const VBElem::RiserConstRef& riser);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	GetNonBreakMarkEdgeOffsetForSideSupport (const VBElem::SideStairStructureConstRef& structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	GetNonBreakMarkEdgeOffsetForBeamSupport (const VBElem::BeamSupportStairStructureConstRef& structure);
	VB_ELEM_OPERATIONS_DLL_EXPORT double	GetNonBreakMarkEdgeOffsetForMonolith	(const VBElem::MonolithStairStructureConstRef& structure);

	VB_ELEM_OPERATIONS_DLL_EXPORT void		FillConnFlagsAndOffsets (const VBElem::StairStructureConstRef&	ss, GS::Array<Int32>& connectionFlags, GS::Array<double>& connectionOffsets);

	VB_ELEM_OPERATIONS_DLL_EXPORT void		GetStructure2DGeometryForGDLGlobals (const GS::Array<VBElem::StairBoundaryPolyline>& polylines, const GS::Array<UInt32>& sideFlags, GS::Array<double>& geom, GS::Array<Int32>& flags);

	inline VBElem::TreadPolygonEdgeType	InvertLeadTrail (VBElem::TreadPolygonEdgeType type)
	{
		return type == VBElem::LeadingEdge ? VBElem::TrailingEdge : VBElem::LeadingEdge;
	}

} // namespace StairStructureOperations

#endif // STAIRSTRUCTUREOPERATIONS_HPP
