#ifndef	MODELELEM_STRUCTURE_HPP
#define	MODELELEM_STRUCTURE_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "Optional.hpp"

// from ODB
#include "ODBReference.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperationsTypes.hpp"

// === Predeclarations =================================================================================================

namespace VBAttr {
	class CompWall;
	typedef ODB::ConstRef<CompWall> CompWallConstRef;
	class Profile;
	typedef ODB::ConstRef<Profile> ProfileConstRef;
}

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT ModelElemStructure
{
public:
	virtual ~ModelElemStructure ();

	virtual bool								IsBasic				() const = 0;
	virtual bool								IsComposite			() const = 0;
	virtual bool								IsProfile			() const = 0;
	virtual GS::Optional<VBAttr::CompWallConstRef>	GetComposite		() const = 0;
	virtual GS::Optional<VBAttr::ProfileConstRef>	GetProfile			() const = 0;	// TODO KiP ezt valami ProfileDescriptor interface-re kall atalakitani

	virtual GS::Array<ModelElemComponentId>		GetComponentIds		() const = 0;
	virtual	ModelElemComponentRef				GetComponent		(const ModelElemComponentId& componentId) const = 0;
};

}

#endif
