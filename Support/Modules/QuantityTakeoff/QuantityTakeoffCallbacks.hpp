// Contact person : KiP

#ifndef QUANTITY_TAKEOFF_CALLBACKS_HPP
#define QUANTITY_TAKEOFF_CALLBACKS_HPP

#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "IrregularPolygon2DClassDefinition.hpp"

// from GSModeler
#include "Sight.hpp"

// from DisplayDLL
#include "ScreenTypes.hpp"
#include "ScreenBasics.hpp"

// from VBAttributes
#include "EffectiveComposite.hpp"

// from VBElements
#include "BeamTypes.hpp"
#include "WallTypes.hpp"
#include "RoomTypes.hpp"

// from VBElemOperations
// #include "WallFloorPlanCalculations.hpp"
// #include "ColumnFloorPlanCalculations.hpp"

// from QuantityTakeoff
#include "QuantityTakeoffExport.hpp"

// === Predeclarations =================================================================================================

namespace ModelCalculations {
	typedef Geometry::CustomMultiPolygon2D<bool, Geometry::PolyId, Geometry::PolyId, Geometry::PolyId>	ProjectedMultiPolygon;
}

namespace VBElem {
	class WallConnectionList;
}

namespace VBCalculations {
	struct WallComputingEnvir;
	struct WallBeamConnectionEnvir;
	struct WallCutPlaneData;
	struct ColumnSectRec;
}

namespace Validator {
	class ElemValidator;
}

namespace SL {
	struct RebuildEnvirData;
}

namespace RoomRelations {
	class RoomRelationData;
}

struct WallPart;

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT QTCallBackInterface
{
public:
	virtual ~QTCallBackInterface ();

	virtual	void	DrawBeam (VBElem::BeamConstRef					whichBeam,
							  bool									ghostelem,
							  short									markupPen,
							  bool									nOnlyCalc,
							  const EffectiveComposite::Structure	structureDisplay,
							  const SL::SecondaryDrawIndexType		drwSIndex,
							  Validator::ElemValidator*				elemValidator,
							  bool									ghostColor,
							  bool									drawBeam,
							  bool									drawLabel) const = 0;

	// Used to calc wPoly, and wce, wbce. should be removed when wPoly calculation has implementation in lower modul, and other callbacks that use wce, wbce are removed.
	virtual void	CalculateWPoly (VBElem::WallConstRef							pWall,
									Geometry::IrregularPolygon2D*					outWPoly,
									Int32											floor,
									VBCalculations::WallComputingEnvir* const		wce = nullptr,
									VBCalculations::WallBeamConnectionEnvir* const	wbce = nullptr) const = 0;

	// Used to get the number of the connected columns. Should use some kind of 3D calculation, and be removed when thats done.
	virtual	Int32	ConnectColumns (VBElem::WallConstRef						pWall,
									GS::Array<VBCalculations::ColumnSectRec>&	connColumns,
									SL::RebuildEnvirData*						rebuild,
									bool										from2D,
									bool										style2D,
									short										showElemFloor) const = 0;

	virtual	bool	CheckTLConn (short												showElemFloor,
								 VBCalculations::WallCutPlaneData*					wCutPlane,
								 VBElem::WallConstRef								whichWall,
								 VBElem::WallConstRef								connWall,
								 bool												conBegFl,
								 VBCalculations::WallComputingEnvir* const			wce,
								 VBCalculations::WallBeamConnectionEnvir* const		wbce) const = 0;

	virtual	void	ChooseWall2Conns (short									showElemFloor,
									  VBElem::WallConnectionList&			connections,
									  VBElem::WallConstRef					otherWall,
									  bool									updateComplPoly,
									  VBCalculations::WallCutPlaneData*		wCutPlane) const = 0;

	virtual	void	GetWallPartsAndZonesOfWall (VBElem::WallConstRef									wall,
												GS::Array< GS::Pair<WallPart, VBElem::RoomConstRef> >&	wallPartZoneList) const = 0;

	virtual void	CalcRoomSurfVol (VBElem::RoomConstRef pRoom,
									 double *volume,
									 double *bound_surf,
									 double *top_surf,
									 double *bot_surf,
									 double *roof_top_surf,
									 double *roof_bot_surf,
									 double *slab_top_surf,
									 double *slab_bot_surf,
									 double *beam_top_surf,
									 double *beam_bot_surf,
									 double *wall_inset_top,
									 double *wall_inset_back,
									 double *wall_inset_side,
									 ModelCalculations::ProjectedMultiPolygon* projected_floor = nullptr) const = 0;


	virtual void	GetRelationZone (const VBElem::RoomConstRef& rRoom, const GS::ClassInfo* otherElemClassInfo, RoomRelations::RoomRelationData& roomData) const = 0;
};

}

#endif
