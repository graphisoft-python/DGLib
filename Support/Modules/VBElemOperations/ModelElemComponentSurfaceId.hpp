#ifndef	MODELELEM_COMPONENT_SURFACE_ID_HPP
#define	MODELELEM_COMPONENT_SURFACE_ID_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElemOperations
#include "ModelElemComponentId.hpp"
#include "ModelCalculationsDefinitions.hpp"

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT ModelElemComponentSurfaceId
{
private:
	static GS::ClassInfo classInfo;
public:
	ModelElemComponentSurfaceId ();
	ModelElemComponentSurfaceId (const ModelElemComponentId& componentId, const ModelCalculations::SurfaceId& surfaceId);

	bool operator== (const ModelElemComponentSurfaceId& other) const;
	bool operator!= (const ModelElemComponentSurfaceId& other) const;

	const VBEO::ModelElemComponentId&		GetComponentId () const;
	const ModelCalculations::SurfaceId&		GetSurfaceId () const;

	operator GS::HashValue () const;

	GSErrCode	Write (GS::OChannel& oc) const;
	GSErrCode	Read (GS::IChannel& ic);

private:
	GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	VBEO::ModelElemComponentId componentId;
	ModelCalculations::SurfaceId surfaceId;
};

}

#endif
