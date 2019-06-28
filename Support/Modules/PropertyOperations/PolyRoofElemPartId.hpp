// Contact person :	KiP

#ifndef POLYROOF_ELEMPARTID_HPP
#define POLYROOF_ELEMPARTID_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "HashCommon.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

// === Predeclarations =================================================================================================

namespace Modeler {
	class MeshBody;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PolyRoofElemPartId
{
public:
	PolyRoofElemPartId ();
	PolyRoofElemPartId (UInt32 baseEdgeUId, UInt32 levelIdx);

	static PolyRoofElemPartId CreateFromBody (const Modeler::MeshBody& body);

	bool operator== (const PolyRoofElemPartId& other) const;
	bool operator!= (const PolyRoofElemPartId& other) const;

	operator GS::HashValue () const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

	UInt32	GetBaseEdgeUId () const;
	UInt32	GetLevelIdx () const;

private:
	UInt32 baseEdgeUId;
	UInt32 levelIdx;
};

}

#endif
