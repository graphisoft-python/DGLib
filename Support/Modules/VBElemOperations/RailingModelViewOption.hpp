// *********************************************************************************************************************
// Description:		RailingModelViewOption
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD, JG, CSP, KG
//
// SG compatible
// *********************************************************************************************************************
#if !defined (_RAILINGMODELVIEWOPTION_HPP_)
#define _RAILINGMODELVIEWOPTION_HPP_

#include "VBElemOperationsExport.hpp"
#include "RailingOperationsTypes.hpp"

#include "Object.hpp"
#include "RailingSchemeModelViewOption.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT RailingModelViewOption : public GS::Object {
DECLARE_CLASS_INFO

private:
	RailingMVO::Railing3DDetailLevel			railing3DDetailLevel;
	RailingMVO::Railing2DDisplayComponentsFlag	railing2DDisplayComponentsFlags;
	RailingSchemeModelViewOption				railingSchemeMVO;

public:
	RailingModelViewOption ();
	virtual ~RailingModelViewOption ();

public:
	bool operator== (const RailingModelViewOption& rhs) const;
	bool operator!= (const RailingModelViewOption& rhs) const;

public:
	RailingMVO::Railing3DDetailLevel			Get3DDetailLevel				(void) const;
	bool										Is2DDisplayComponentEnabled		(RailingMVO::Railing2DDisplayComponentsFlag component) const;
	RailingMVO::Railing2DDisplayComponentsFlag	Get2DDisplayComponentsFlag		(void) const;
	const RailingSchemeModelViewOption&			GetRailingSchemeModelViewOption	(void) const;

	void										Set3DDetailLevel				(RailingMVO::Railing3DDetailLevel detailLevel);
	void										Enable2DDisplayComponents		(RailingMVO::Railing2DDisplayComponentsFlag component);
	void										Disable2DDisplayComponents		(RailingMVO::Railing2DDisplayComponentsFlag component);
	void										Set2DDisplayComponentsFlag		(RailingMVO::Railing2DDisplayComponentsFlag	flags);
	void										SetRailingSchemeModelViewOption	(const RailingSchemeModelViewOption& schemeMVO);

	Int32										GetRailing2DDisplayComponentsForGDL (void) const;

	static Int32								GetRailing2DDefaultDisplayComponentsForGDL	(void);

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


#endif // _RAILINGMODELVIEWOPTION_HPP_
