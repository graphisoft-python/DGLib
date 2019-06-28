#ifndef	MODELELEM_COMPONENT_HPP
#define	MODELELEM_COMPONENT_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "Optional.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT ModelElemComponent
{
public:
	enum class Type
	{
		Undefined,
		Core,
		Finish,
		Other
	};

	virtual ~ModelElemComponent ();

	virtual ModelElemComponentId				GetId () const = 0;
	virtual	Type								GetType () const = 0;
	virtual	GS::Optional<double>				GetThickness () const = 0;
	virtual	GS::Optional<double>				GetCrossSectionHeight () const = 0;
	virtual	GS::Optional<double>				GetCrossSectionWidth () const = 0;
	virtual	GS::Optional<double>				GetCrossSectionArea () const = 0;
	virtual VBAttr::BuildingMaterialConstRef	GetBuildingMaterial () const = 0;
	virtual	short								GetCutFillForegroundPen () const = 0;
	virtual short								GetCutFillBackgroundPen () const = 0;

	// TODO KiP atgondolni ennek a 3 fuggvenynek a letjogosultsagat...
	virtual GS::Optional<short>					GetSkinEndFaceLinePen () const = 0;					// valid for Composite elem
	virtual GS::Optional<short>					GetProfileHatchDefaultContourLinePen () const = 0;	// valid for Profile elem
	virtual GS::Optional<short>					GetBasicElemCutLinePen () const = 0;				// valid for Basic elem
};


}

#endif
