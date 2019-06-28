#ifndef GS_GSAT_DATA_HPP
#define GS_GSAT_DATA_HPP

#pragma once


// http://wiki/w/M-312_Vectorial_2D_References_for_GSAT/Overall_Model#Technol.C3.B3gia


// === Includes ========================================================================================================

#include "GSATLibExport.hpp"

// from GSRoot
#include "Definitions.hpp"


// === Predeclarations =================================================================================================

struct Box2DData;

namespace GS {
	class IChannel;
	class OChannel;
}

namespace NewDisplay {
	class NativeContext;
}

namespace SL {
	class Transformation2D;
}


// === Function prototypes  ============================================================================================

namespace GSAT {


class GSATLIB_DLL_EXPORT Data : public GS::Object {
	DECLARE_CLASS_INFO

public:
	Data ();
	virtual ~Data ();

	virtual GS::Object*		Clone		(void) const override = 0;

	virtual GSErrCode		Read		(GS::IChannel& ic) override = 0;
	virtual GSErrCode		Write		(GS::OChannel& oc) const override = 0;

	virtual void			ToContext	(NewDisplay::NativeContext&		context,
										 const SL::Transformation2D&	modelToScreen,
										 const Box2DData&				modelBox) const = 0;

	virtual bool			Compare		(const Data& other) const = 0;
};


}	// namespace GSAT

#endif
