// *********************************************************************************************************************
// Description:		Elem and Body canonizer
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_BODYCANONIZER_HPP)
#define GS_MODELER_BODYCANONIZER_HPP

#pragma once


// from Model3D
#include	"Model3D/Model3DPrivExp.h"
#include	"SharedPtr.hpp"


namespace Modeler {

class Elem;
typedef GS::ConstSharedPtr<Elem>		ConstElemPtr;


MODEL3D_PRIVATE_EXPORT
ConstElemPtr	MOD3D_PRIV	CanonizeElem (const ConstElemPtr elem);


}	// namespace Modeler


#endif // GS_MODELER_BODYCANONIZER_HPP
