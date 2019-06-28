// *****************************************************************************
//
//                                Class Extension
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#ifndef EXTENSION_HPP
#define EXTENSION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "Object.hpp"
#include "StaticInstantiable.hpp"

namespace GS { class ClassInfo; }



// ============================== Class Extension ==============================

namespace GS {

typedef UInt32 ExtensionId;

class GSROOT_DLL_EXPORT Extension: public StaticInstantiable {
private:
	ExtensionId		id;		// identifier of the extension obtained from derived classes
	GS::ClassInfo*	target;	// target class to be extended

protected:
	Extension (ExtensionId* id, GS::ClassInfo* target);
	virtual ~Extension ();

public:
	ExtensionId	GetId (void) const;
};


template <class E>
inline E*	GetExtension (const GS::Object* object)
{
	return object->GetClassInfo ()->GetExtension<E> ();
}

}	// namespace GS
// ______________________________ Class Extension ______________________________


#endif
