// Contact person : KiP

#ifndef	PROJECTIONSHAPEFACTORY_HPP
#define	PROJECTIONSHAPEFACTORY_HPP

#pragma once

// === Includes ========================================================================================================

// from GSModeler
#include "ProjectionSurface.hpp"
#include "Model3D/Elem.hpp"

// from VBElements
#include "WallTypes.hpp"
#include "CeilTypes.hpp"
#include "MeshTypes.hpp"
#include "ShellTypes.hpp"
#include "BeamTypes.hpp"
#include "ColumnTypes.hpp"
#include "PlaneRoofTypes.hpp"
#include "PolyRoofTypes.hpp"
#include "TreadTypes.hpp"
#include "RiserTypes.hpp"
#include "RailBaseTypes.hpp"
#include "RailBaseEndTypes.hpp"
#include "RailBaseConnectionTypes.hpp"
#include "RailingPostBaseTypes.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

typedef		GS::HashTable<UIndex, UIndex>	BodyIdxToComponentIdxMap;

class VB_ELEM_OPERATIONS_DLL_EXPORT ProjectionSurfaceFactory
{
public:
	static ModelCalculations::ProjectionSurfaceRef	GetCeilProjectionSurface ();
	static ModelCalculations::ProjectionSurfaceRef	GetMeshProjectionSurface ();
	static ModelCalculations::ProjectionSurfaceRef	GetWallProjectionSurface (VBElem::WallConstRef wall, short componentIndex);
	static ModelCalculations::ProjectionSurfaceRef	GetBeamProjectionSurface (VBElem::BeamConstRef beam, short componentIndex);
	static ModelCalculations::ProjectionSurfaceRef	GetColumnProjectionSurface (VBElem::ColumnConstRef column, short componentIndex);
	static ModelCalculations::ProjectionSurfaceRef	GetPlaneRoofProjectionSurface (VBElem::PlaneRoofConstRef planeRoof);
	static ModelCalculations::ProjectionSurfaceRef	GetPolyRoofProjectionSurface (VBElem::PolyRoofConstRef polyRoof, UInt32 baseEdgeUId, UInt32 levelIdx);
	static ModelCalculations::ProjectionSurfaceRef	GetShellProjectionSurface (VBElem::ShellConstRef shell, const Modeler::ConstElemPtr& refElem, const BodyIdxToComponentIdxMap& bodyIdxToComponentIdxMap, short componentIndex);
	static ModelCalculations::ProjectionSurfaceRef	GetPolyWallProjectionSurface (const Modeler::ConstElemPtr& refElem);
	static ModelCalculations::ProjectionSurfaceRef	GetTreadProjectionSurfaceForTopSurface (const VBElem::TreadConstRef& tread);
	static ModelCalculations::ProjectionSurfaceRef	GetTreadProjectionSurfaceForFrontSurface (const VBElem::TreadConstRef& tread);
	static ModelCalculations::ProjectionSurfaceRef	GetRiserProjectionSurfaceForFrontSurface (const VBElem::RiserConstRef& riser);
};

class VB_ELEM_OPERATIONS_DLL_EXPORT ProjectionCurveFactory
{
public:
	static ModelCalculations::ProjectionCurveRef	GetBeamProjectionCurve (const VBElem::BeamConstRef& beam);
	static ModelCalculations::ProjectionCurveRef	GetColumnProjectionCurve (const VBElem::ColumnConstRef& column);
	static ModelCalculations::ProjectionCurveRef	GetWallProjectionCurve (const VBElem::WallConstRef& wall);
	static ModelCalculations::ProjectionCurveRef	GetRailBaseProjectionCurve (const VBElem::RailBaseConstRef& railBase);
	static ModelCalculations::ProjectionCurveRef	GetRailingPostBaseProjectionCurve (const VBElem::RailingPostBaseConstRef& rainigPostBase);
};

#endif	//SKINAREAPROJECTION_HPP
