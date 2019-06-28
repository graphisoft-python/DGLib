// *********************************************************************************************************************
// Description:		DerivedModelData Manager
//					UserData to Model3D
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	VSZG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (DMDMANAGER_HPP)
#define DMDMANAGER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

#include	"GSModelerExport.h"
#include	"ShadowBodiesDMD.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


class GSMODELER_DLL_EXPORT DMDManager : public GS::Object
{
public:
	DMDManager (const Model3D* model);
	~DMDManager ();

	// Automatic DMD generation, synchronization
	//const ShadowBodiesDMD*	AcquireShadowBodiesDMD (SunDirection) const;


	// Improper access: later must be reorganized
	ShadowBodiesDMD*			GetShadowBodiesDMDPtr ();

private:
	const Model3D*		m_model;				// no Model3DPtr, cyclic references = no auto dispose
	ShadowBodiesDMD*	m_shadowBodiesDMD;		// first time: limited (only 1 instance)
	
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


GSMODELER_DLL_EXPORT
DMDManager*			AcquireDMDManager (Modeler::ConstModel3DPtr model);

GSMODELER_DLL_EXPORT
DMDManager*			GetDMDManager (Modeler::ConstModel3DPtr model);

GSMODELER_DLL_EXPORT
DMDManager*			GetDMDManager (const Modeler::Model3DViewer& viewer);

 GSMODELER_DLL_EXPORT
 Modeler::SightPtr		GetShadowBodySight (Modeler::SightPtr parentSight);

}	// namespace Modeler

#endif
