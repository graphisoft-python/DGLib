// *****************************************************************************
//
//                                Class WindowDevice
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGWINDOWDEVICE_HPP
#define QGWINDOWDEVICE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGDrawableDevice.hpp"

// ============================== class WindowDevice ==============================

namespace QG {

class IWindowDeviceImp;

class QG_DLL_EXPORT WindowDevice : public QG::DrawableDevice {
private:
	IWindowDeviceImp*	imp;

	WindowDevice (const WindowDevice&);
	WindowDevice& operator=(const WindowDevice&);

public:
	WindowDevice (void* deviceContext);
	WindowDevice (void* deviceContext, double dpiValue); 	// any virtual resolution can be set as initial value

	virtual	double			GetRealResolution (void) const override;
};

}	// namespace QG
// ______________________________ class WindowDevice ______________________________

#endif	// QGWINDOWDEVICE_HPP
