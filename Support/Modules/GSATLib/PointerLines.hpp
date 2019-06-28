#ifndef GS_GSAT_POINTERLINES_HPP
#define GS_GSAT_POINTERLINES_HPP

#pragma once

// === Includes ========================================================================================================

#include "GSATData.hpp"

// from GSRoot
#include "Ref.hpp"

// from VBElements
#include "IGeometryData.hpp"

// === Predeclarations =================================================================================================


// === Function prototypes  ============================================================================================

namespace GSAT {


class GSATLIB_DLL_EXPORT PointerLines : public Data {
	DECLARE_DYNAMIC_CLASS_INFO (PointerLines)

public:
	PointerLines ();
	PointerLines (const GS::Array<GS::Ref<EI::IGeometryData>>& geometryDataArray);
	virtual ~PointerLines ();

	virtual GS::Object*		Clone	(void) const override;

	virtual	GSErrCode		Read	(GS::IChannel& ic) override;
	virtual GSErrCode		Write	(GS::OChannel& oc) const override;

	virtual void			ToContext (NewDisplay::NativeContext&	context,
									   const SL::Transformation2D&	modelToScreen,
									   const Box2DData&				modelBox) const override;

	virtual bool			Compare (const Data&			other) const override;
	bool					Compare (const PointerLines&	other) const;

private:
	GS::Array<GS::Ref<EI::IGeometryData>>	geometryDataArray;
};


}	// namespace GSAT

#endif