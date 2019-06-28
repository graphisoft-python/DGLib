// Contact person : KiP

#ifndef QUANTITYTAKEOFF_TYPES_HPP
#define QUANTITYTAKEOFF_TYPES_HPP

#pragma once

// === Includes ========================================================================================================

// from ModelCalculations
#include "ModelCalculationsTypes.hpp"

// =====================================================================================================================

namespace QT {

class QuantityModel;
typedef GS::SharedPtr<QuantityModel> QuantityModelPtr;
typedef GS::ConstSharedPtr<QuantityModel> QuantityModelConstPtr;

class VBModelElemQuantityCalculator;
class BeamQuantityCalculator;
class CeilQuantityCalculator;
class ColumnQuantityCalculator;
class CurtainWallQuantityCalculator;
class CWAccessoryQuantityCalculator;
class CWFrameQuantityCalculator;
class CWJunctionQuantityCalculator;
class CWSegmentQuantityCalculator;
class CWPanelQuantityCalculator;
class FreeShapeQuantityCalculator;
class GDLObjectQuantityCalculator;
class HandrailQuantityCalculator;
class InnerPostQuantityCalculator;
class MeshQuantityCalculator;
class PlaneRoofQuantityCalculator;
class PolyRoofQuantityCalculator;
class PolyRoofElemPartQuantityCalculator;
class RailQuantityCalculator;
class RailBaseQuantityCalculator;
class RailBaseEndQuantityCalculator;
class RailBaseConnectionQuantityCalculator;
class RailingQuantityCalculator;
class RailingPanelQuantityCalculator;
class RailingPostQuantityCalculator;
class RailingPostBaseQuantityCalculator;
class RailingSegmentQuantityCalculator;
class RiserQuantityCalculator;
class RoofQuantityCalculator;
class RoomQuantityCalculator;
class ShellQuantityCalculator;
class SkylightQuantityCalculator;
class StairQuantityCalculator;
class StairStructureQuantityCalculator;
class ToprailQuantityCalculator;
class TreadQuantityCalculator;
class WallQuantityCalculator;
class WallOpeningQuantityCalculator;

}



#endif