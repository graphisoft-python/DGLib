// Contact person :	KiP

#ifndef FREESHAPE_ELEMPARTID_HPP
#define FREESHAPE_ELEMPARTID_HPP

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

	class PROPERTY_OPERATIONS_DLL_EXPORT FreeShapeElemPartId
	{
	public:
		FreeShapeElemPartId ();
		FreeShapeElemPartId (GSIndex floorIdx);

		bool operator== (const FreeShapeElemPartId& other) const;
		bool operator!= (const FreeShapeElemPartId& other) const;

		operator GS::HashValue () const;

		GSErrCode	Read (GS::IChannel& ic);
		GSErrCode	Write (GS::OChannel& oc) const;

		GSIndex	GetFloorIdx () const;

	private:
		GSIndex floorIdx;
	};

}

#endif
