// *********************************************************************************************************************
// Description:		RailingSchemeModelViewOptions
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD, PaP, JG, CSP, KG
//
// SG compatible
// *********************************************************************************************************************
#if !defined (_RAILINGSCHEMEMODELVIEWOPTION_HPP_)
#define _RAILINGSCHEMEMODELVIEWOPTION_HPP_

#include "SchemeModelViewOption.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT RailingSchemeModelViewOption : public SchemeModelViewOption {
DECLARE_CLASS_INFO

public:
	RailingSchemeModelViewOption ();
	RailingSchemeModelViewOption (short surfaceIndex, short cutLineIndex, short cutLinePen, short uncutLineIndex, short uncutLinePen);
	virtual ~RailingSchemeModelViewOption ();

	Object*		Clone (void) const override;

// ----- Other Serialization -----------------------------------------------------

	GSErrCode			ReadXML (GS::XMLIChannel& ic) override;
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const override;
};

#endif // _RAILINGSCHEMEMODELVIEWOPTION_HPP_
