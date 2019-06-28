// *****************************************************************************
// Description:
//
// Module:			VBCalculations, Platform independent
// Namespace:
// Contact person:	CsP
//
// SG compatible
//
// *****************************************************************************

#if !defined (VBCALCULATIONS_HPP)
#define VBCALCULATIONS_HPP

#if defined (_MSC_VER)
#pragma once
#endif

#include "VBElemOperationsExport.hpp"
#include "GDLGlobalCalculations.hpp"

// from GSRoot
#include "Array.hpp"

// from Geometry
#include "TRANMAT.h"
#include "Coord3d.h"

// from ElementManager
#include "EDBGeneralDefinitions.hpp"
#include "Box3DData.h"

namespace VBElem {
	class  CWPanelAux3DData;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace VBCalculations {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TransformParams {
private:
	bool							cwSchematicDrawing;
	const VBElem::CWPanelAux3DData*	panelData;
	bool							addRoofAngle;

public:
	TransformParams (bool cwsd = false, const VBElem::CWPanelAux3DData* pd = nullptr, bool ara = false) {cwSchematicDrawing = cwsd; panelData = pd; addRoofAngle = ara;}
	inline bool IsCwSchematicDrawing () const {return cwSchematicDrawing;}
	inline const VBElem::CWPanelAux3DData* GetPanelData () const {return panelData;}
	inline bool GetAddRoofAngle () const {return addRoofAngle;}
};

VB_ELEM_OPERATIONS_DLL_EXPORT	bool	Get3DPlaceTransformation (EDB::GeneralElemConstRef elem, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, TRANMAT& transformation, const TransformParams* transformParams = nullptr);
VB_ELEM_OPERATIONS_DLL_EXPORT	void	PreparePrismTransforms (const Vector3D& dirVec, const Vector3D& oriVec, double* rots);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace VBCalculations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
