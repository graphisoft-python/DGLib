// *********************************************************************************************************************
// Description:		StairSchemeModelViewOptions
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD, JG, CSP, KG
//
// SG compatible
// *********************************************************************************************************************
#if !defined (_STAIRSCHEMEMODELVIEWOPTION_HPP_)
#define _STAIRSCHEMEMODELVIEWOPTION_HPP_

#include "SchemeModelViewOption.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT StairSchemeModelViewOption : public SchemeModelViewOption {
DECLARE_CLASS_INFO

public:
	StairSchemeModelViewOption ();
	StairSchemeModelViewOption (short surfaceIndex, short cutLineIndex, short cutLinePen, short uncutLineIndex, short uncutLinePen);
	virtual ~StairSchemeModelViewOption ();

// ----- Other Serialization -----------------------------------------------------

	Object*			Clone (void) const override;

	GSErrCode		ReadXML (GS::XMLIChannel& ic) override;
	GSErrCode		WriteXML (GS::XMLOChannel& oc) const override;

};

#endif // _STAIRSCHEMEMODELVIEWOPTION_HPP_
