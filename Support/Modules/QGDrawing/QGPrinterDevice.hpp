// *****************************************************************************
//
//                                Class PrinterDevice
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGPRINTERDEVICE_HPP
#define QGPRINTERDEVICE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGDrawableDevice.hpp"

// ============================== class PrinterDevice ==========================

namespace QG {

class IPrinterDeviceImp;

class QG_DLL_EXPORT PrinterDevice : public QG::DrawableDevice {
private:
	IPrinterDeviceImp*	imp;

	PrinterDevice (const PrinterDevice&);
	PrinterDevice& operator=(const PrinterDevice&);

public:
	PrinterDevice (void* deviceContext, void* pageInfo = nullptr);
	PrinterDevice (void* deviceContext, double dpiValue, void* pageInfo = nullptr); 	// any virtual resolution can be set as initial value

	double			GetRealResolution (void) const override;
};

}	// namespace QG
// ______________________________ class PrinterDevice __________________________

#endif	// QGPRINTERDEVICE_HPP
