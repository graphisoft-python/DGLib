// Contact person : KiP

#ifndef PROPERTY_OWNER_HASHKEY_HPP
#define PROPERTY_OWNER_HASHKEY_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "Optional.hpp"

// from ModelCalculations
#include "ModelCalculationsDefinitions.hpp"

// from VBElemOperations
#include "ModelElemComponentId.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PolyRoofElemPartId.hpp"
#include "FreeShapeElemPartId.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyOwnerHashKey
{
public:
	PropertyOwnerHashKey ();
	PropertyOwnerHashKey (const GS::Guid& elemGuid,
						  const GS::Optional<VBEO::ModelElemComponentId>& componentId = GS::NoValue,
						  const GS::Optional<ModelCalculations::SurfaceId>& surfaceId = GS::NoValue,
						  const GS::Optional<PolyRoofElemPartId>& polyRoofElemPartId = GS::NoValue,
						  const GS::Optional<FreeShapeElemPartId>& freeShapeElemPartId = GS::NoValue,
						  bool isHoleReplacement = false);

	bool operator== (const PropertyOwnerHashKey& other) const;
	bool operator!= (const PropertyOwnerHashKey& other) const;
	
	operator GS::HashValue () const;

	GSErrCode	Read	(GS::IChannel& ic);
	GSErrCode	Write	(GS::OChannel& oc) const;

private:
	GS::Guid elemGuid;
	bool isCompenent;
	bool isSurface;
	bool isPolyRoofElemPart;
	bool isFreeShapeElemPart;
	bool isHoleReplacement;
	VBEO::ModelElemComponentId componentId;
	ModelCalculations::SurfaceId surfaceId;
	PolyRoofElemPartId polyRoofElemPartId;
	FreeShapeElemPartId freeShapeElemPartId;
};

}


#endif
