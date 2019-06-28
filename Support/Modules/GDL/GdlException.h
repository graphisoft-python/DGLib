// *****************************************************************************
//
// GDL / GdlIpException definition
//
// Contact person: SD
//
// *****************************************************************************

#ifndef _GdlIpException_H_
#define _GdlIpException_H_

#pragma once

#include	"iGDLDefs.h"
#include	"UniString.hpp"
#include	"GSException.hpp"

namespace GDL {

enum GdlErrType {GdlErrSimple, GdlErrWithStr, GdlErrWithInt};

class Exception : public GS::GSException {
public:
	Exception (const GSErr& aErrCode);
	Exception (const GSErr& aErrCode, const GS::UniString& aStr);
	Exception (const GSErr& aErrCode, const Int32& aInt);
	virtual ~Exception () throw ();
public:
	GdlErrType		gdlErrType;
	GS::UniString	errStr;
	Int32			errInt;
};
}
#endif
