// *********************************************************************************************************************
// Description:		
// Module:			GSATLib
// Contact person:	
// *********************************************************************************************************************

#ifndef GS_GSAT_VBELEMS2D_HPP
#define GS_GSAT_VBELEMS2D_HPP

#pragma once

// === Includes ========================================================================================================

#include "GSATData.hpp"

// from GSDisplay
#include "MacroElemListContainer.hpp"


// === Predeclarations =================================================================================================

class Display;


// === Function prototypes  ============================================================================================

namespace GSAT {


class GSATLIB_DLL_EXPORT VBElems2D : public Data {
	DECLARE_DYNAMIC_CLASS_INFO (VBElems2D)

public:
	VBElems2D ();
	VBElems2D (const double displayScale, const SL::ShowOptions showOptions);
	virtual ~VBElems2D ();

	virtual GS::Object*			Clone (void) const override;

	virtual GSErrCode			Read	(GS::IChannel& ic) override;
	virtual GSErrCode			Write	(GS::OChannel& oc) const override;
	
	virtual void				ToContext	(NewDisplay::NativeContext&		context,
											 const SL::Transformation2D&	modelToScreen,
											 const Box2DData&				modelBox) const override;
	
	virtual bool				Compare (const Data&		other) const override;
	bool 						Compare (const VBElems2D&	other) const;

	SL::MacroElemListOwnerContainer*			GetMacroElemListPtr ();
	const SL::MacroElemListOwnerContainer*		GetMacroElemListPtr () const;

private:
	VBElems2D (const VBElems2D&);				// DISABLED
	VBElems2D&	operator= (const VBElems2D&);	// DISABLED

	Display						GetDisplay (const SL::Transformation2D& boxToScreen, const Box2DData& modelBox) const;

private:
	SL::MacroElemListOwnerContainer	list;
	double							displayScale;
	SL::ShowOptions					showOptions;
};


}	// namespace GSAT

#endif
