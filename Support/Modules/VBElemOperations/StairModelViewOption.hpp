// *********************************************************************************************************************
// Description:		StairModelViewOption
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD, JG, CSP, KG
//
// SG compatible
// *********************************************************************************************************************
#if !defined (_STAIRMODELVIEWOPTION_HPP_)
#define _STAIRMODELVIEWOPTION_HPP_

#include "VBElemOperationsExport.hpp"
#include "StairOperationsTypes.hpp"

#include "Object.hpp"
#include "StairSchemeModelViewOption.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT StairModelViewOption : public GS::Object {
DECLARE_CLASS_INFO

private:
	StairMVO::Stair3DDetailLevel	stair3DDetailLevel;
	StairMVO::Stair2DDisplayMode	stair2DDisplayMode;
	UInt32							stairFloorPlanComponentFlags;
	UInt32							stairReflectedComponentFlags;
	StairSchemeModelViewOption		stairSchemeMVO;
	bool							stairHeadroomEnabled;
	UInt32							stairHeadroomMaterial;

public:
	StairModelViewOption ();
	virtual ~StairModelViewOption ();

public:
	bool operator== (const StairModelViewOption& rhs) const;
	bool operator!= (const StairModelViewOption& rhs) const;

public:
	StairMVO::Stair3DDetailLevel		Get3DDetailLevel					(void) const;
	StairMVO::Stair2DDisplayMode		Get2DDisplayMode					(void) const;
	bool								Get2DDisplayComponentState			(StairMVO::Stair2DDisplayMode displayMode, StairMVO::Stair2DDisplayComponent component) const;
	UInt32								GetFloorPlanComponentFlags			(void) const;
	UInt32								GetReflectedComponentFlags			(void) const;
	const StairSchemeModelViewOption&	GetStairSchemeModelViewOption		(void) const;
	const bool							IsHeadroomDisplayEnabled			(void) const;
	const short							GetHeadroomMaterial					(void) const;

	void								Set3DDetailLevel					(StairMVO::Stair3DDetailLevel detailLevel);
	void								Set2DDisplayMode					(StairMVO::Stair2DDisplayMode displayMode);
	void								Set2DDisplayComponentState			(StairMVO::Stair2DDisplayMode displayMode, StairMVO::Stair2DDisplayComponent component, bool value);
	void								SetFloorPlanComponentFlags			(UInt32 flags);
	void								SetReflectedComponentFlags			(UInt32 flags);
	void								SetStairSchemeModelViewOption		(const StairSchemeModelViewOption& schemeMVO);
	void								SetHeadroomDisplayEnabled			(const bool value);
	void								SetHeadroomMaterial					(const short value);

public:
	bool								Is2DDisplayComponentEnabled			(StairMVO::Stair2DDisplayMode displayMode, StairMVO::Stair2DDisplayComponent component) const;
	Int32								GetStair2DDisplayModeForGDL			() const;
	Int32								GetStair2DDisplayComponentsForGDL	() const;

	static Int32						GetStair2DDefaultDisplayModeForGDL			();
	static Int32						GetStair2DDefaultDisplayComponentsForGDL	();

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
	GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};


#endif // _STAIRMODELVIEWOPTION_HPP_
