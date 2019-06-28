// *********************************************************************************************************************
// Description:		CurtainWallModelViewOption
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	FLA
//
// SG compatible
// *********************************************************************************************************************
#if !defined (_CURTAINWALLMODELVIEWOPTION_HPP_)
#define _CURTAINWALLMODELVIEWOPTION_HPP_

#include "VBElemOperationsExport.hpp"
#include "CurtainWallOperationsTypes.hpp"

#include "Object.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT CurtainWallModelViewOption : public GS::Object {
DECLARE_CLASS_INFO

private:
	CurtainWallMVO::CWComponentDetailLevel	cwFrameDetailLevel;
	CurtainWallMVO::CWComponentDetailLevel	cwPanelDetailLevel;
	CurtainWallMVO::CWComponentDetailLevel	cwJunctionDetailLevel;
	CurtainWallMVO::CWComponentDetailLevel	cwAccessoryDetailLevel;

public:
	CurtainWallModelViewOption ();
	virtual ~CurtainWallModelViewOption ();

public:
	bool operator== (const CurtainWallModelViewOption& rhs) const;
	bool operator!= (const CurtainWallModelViewOption& rhs) const;

public:
	CurtainWallMVO::CWComponentDetailLevel	GetFrameDetailLevel						(void) const;
	CurtainWallMVO::CWComponentDetailLevel	GetPanelDetailLevel						(void) const;
	CurtainWallMVO::CWComponentDetailLevel	GetJunctionDetailLevel					(void) const;
	CurtainWallMVO::CWComponentDetailLevel	GetAccessoryDetailLevel					(void) const;

	void									SetFrameDetailLevel						(CurtainWallMVO::CWComponentDetailLevel detailLevel);
	void									SetPanelDetailLevel						(CurtainWallMVO::CWComponentDetailLevel detailLevel);
	void									SetJunctionDetailLevel					(CurtainWallMVO::CWComponentDetailLevel detailLevel);
	void									SetAccessoryDetailLevel					(CurtainWallMVO::CWComponentDetailLevel detailLevel);

	Int32									GetCWFrameDetailLevelForGDL				(void) const;
	Int32									GetCWPanelDetailLevelForGDL				(void) const;
	Int32									GetCWJunctionDetailLevelForGDL			(void) const;
	Int32									GetCWAccessoryDetailLevelForGDL			(void) const;

	static Int32							GetCWFrameDefaultDetailLevelForGDL		(void);
	static Int32							GetCWPanelDefaultDetailLevelForGDL		(void);
	static Int32							GetCWJunctionDefaultDetailLevelForGDL	(void);
	static Int32							GetCWAccessoryDefaultDetailLevelForGDL	(void);

// ----- GS::Object --------------------------------------------------------------

public:
	virtual Object*		Clone (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;

// ----- Other Serialization -----------------------------------------------------

	GSErrCode			ReadXML (GS::XMLIChannel& ic);
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const;

// ----- Auxilary functions ------------------------------------------------------

private:
	GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};


#endif // _CURTAINWALLMODELVIEWOPTION_HPP_
