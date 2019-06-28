// *****************************************************************************
//
//                                ICustomDrawObject - interface
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined IQGCUSTOMDRAWOBJECT_HPP
#define IQGCUSTOMDRAWOBJECT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGContext.hpp"

namespace QG {

class QG_DLL_EXPORT ICustomDrawObject {
public:
	virtual ~ICustomDrawObject ();
	virtual void Draw (const QG::Rect& dstRect, QG::Context* qgContext, void* nativeContext, const QG::Matrix* matrix, void* nativePath = nullptr) = 0;
};

}	// namespace QG

#endif	// IQGCUSTOMDRAWOBJECT_HPP
