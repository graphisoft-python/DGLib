// *****************************************************************************
// Line type attribute
// VBAttributes, platform-independent
//
// Namespaces:        Contact person:
//	LineType				CSF
//	LineTypeField			CSF
//	LineTypeFieldMask		CSF
//	LineTypeObserver		CSF
//	LineTypeChanges			CSF
//	LineTypeSet				CSF
//	LineTypeSetObserver	CSF
//
// [SG compatible]
// *****************************************************************************

#if !defined (LINETYPE_HPP)
#define LINETYPE_HPP

#pragma once

//============================== Includes =================================

#include	"AutoPtr.hpp"
#include	"VBAttributesEnv.hpp"
#include	"generalattribute.hpp"
#include	"basicgeometry.h"
#include	"LineItemsData.hpp"
#include	"AttributeTypeSet.hpp"
#include	"fill.hpp"

// Pattern
#include	"DashedLinePattern.hpp"
#include	"LineTypeDefinitions.hpp"
#include	"LinePattern.h"
#include	"PatternTypeDefinitions.hpp"

//===================== Begin of the VBAttr namespace =====================

namespace VBAttr {

//======================== Class LineType  ==========================

class LineTypeObserver;
class LineTypeSet;

class VBATTRIBUTES_DLL_EXPORT LineType : public ADB::GeneralAttribute {
	DECLARE_DYNAMIC_CLASS_INFO (LineType)

public:
		// constants

	enum Fields {
		Scale			= ADB::GeneralAttribute::Last + 1,	// First field in LineType
		PeriodLength	= ADB::GeneralAttribute::Last + 2,
		Height			= ADB::GeneralAttribute::Last + 3,
		Type			= ADB::GeneralAttribute::Last + 4,
		LineFlags		= ADB::GeneralAttribute::Last + 5,
		LineItemsList	= ADB::GeneralAttribute::Last + 6,	// Last field in LineType
		Last			= ADB::GeneralAttribute::Last + 6
	};

#define _LINETYPE_DATA_MEMBERS_																							\
private:																												\
		/* data members */																								\
																														\
	double							defineScale;	/* the scale (0.0 for fixed scale) */								\
	double							linePeriod;		/* the length of a period, don't care for solid */					\
	double							lineHeight;		/* the height of the line (0.0 for solid and dashed lines) */		\
	GX::Pattern::LineTypes			lineType;		/* GX::Pattern::SolidLine, DashedLine, SymbolLine (0: invalid) */	\
	short							lineFlags;		/* FixScale, ScaleWithPlan (0: invalid) */							\
	short							dummy1;			/* Not Used */																\
	LineItemsData					lineItems;		/* line items memo id */

	mutable GX::Pattern::DashedLinePattern	dashedLinePattern;

	_LINETYPE_DATA_MEMBERS_

// Transaction management class

private:
	class VBATTRIBUTES_DLL_EXPORT IsolatedState : public ADB::GeneralAttribute::IsolatedState {
		private:
			friend class LineType;

			_LINETYPE_DATA_MEMBERS_

		public:
			virtual ~IsolatedState ();
	};

public:
		// constructors

						LineType ();
						LineType (const LineType& source);
					   ~LineType ();

		// operator overloading

	LineType&			operator= (const LineType& source);

		// get methods

	GSType				GetTypeId (void) const  override { return TypeId_LineType; }

	inline	double		GetScale (void) const { return defineScale; }
	inline	double		GetPeriodLength (void) const { return linePeriod; }
	inline	double		GetHeight (void) const { return lineHeight; }

	inline	GX::Pattern::LineTypes			GetType (void) const { return lineType; }
	inline	bool		IsSolidLine (void) const { return (lineType == GX::Pattern::SolidLine); }
	inline	bool		IsDashedLine (void) const { return (lineType == GX::Pattern::DashedLine); }
	inline	bool		IsSymbolLine (void) const { return (lineType == GX::Pattern::SymbolLine); }

	inline	short		GetLineFlags (void) const { return lineFlags; }
	inline	bool		IsFixScaledLine (void) const { return (lineFlags & GX::Pattern::FixScale) > 0; }
	inline	bool		IsScaledWithPlanLine (void) const { return (lineFlags & GX::Pattern::ScaleWithPlan) > 0; }

	inline	const LineItemsData&			GetLineItems (void) const { return lineItems; }
	const GX::Pattern::DashedLinePattern&	GetDashedLinePattern (void) const;
	GSErrCode			GetLineItemsList (GX::Pattern::LineItems*** lineItemsHandle, short* nLineItems) const;


	FieldMask			Compare (ADB::GeneralAttributeConstRef attribute) const override;

	LineType*			Clone (void) const override;

		// set methods

	void				SetScale (double newScale);
	void				SetPeriodLength (double newPeriodLength);
	void				SetHeight (double newHeight);
	void				SetType (GX::Pattern::LineTypes newType);
	void				SetLineFlags (short newFlags);
	GSErrCode			SetLineItemsList (const GX::Pattern::LineItems * const ** lineItemsList, short nLineItems);

	void				Synchronize (ADB::GeneralAttributeConstRef newAttribute, const FieldMask& changes) override;

		// check methods

	bool				CheckAttribute (void) const override;
	GSErrCode			CorrectAttribute (void) override;

		// observer methods

	void				Attach (LineTypeObserver& observer);
	void				Detach (LineTypeObserver& observer);

	void				Notify (GS::EventObserver* observer, const FieldMask* changes) const override;

		// memo methods

	bool				HasMemoData () const override;
	bool				HasSameMemoData (ADB::GeneralAttributeConstRef attribute) const override;

		// read / write methods
public:
	GSErrCode			Read (GS::IChannel& ic) override;
	GSErrCode			Write (GS::OChannel& oc) const override;
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const override;
	GSErrCode			ReadXML (GS::XMLIChannel& ic) override;

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode			ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

		// convert methods

	short					ConvertLineTypesToShort (GX::Pattern::LineTypes lineTypes) const;
	GX::Pattern::LineTypes	ConvertShortToLineTypes (short shortLineType) const;

public:
		// copy methods

	void				Copy (ADB::GeneralAttributeConstRef newAttribute) override;

private:
		// memo methods

	GSErrCode			Destruct (void) override;

		// compute methods

	void				ComputeDashedLinePattern () const;


public:
		// Transaction management methods

	virtual	GSErrCode					StoreIsolatedState   			(ODB::Object::IsolatedState* isolatedState) const override;
	virtual	GSErrCode					RestoreIsolatedState 			(const ODB::Object::IsolatedState* isolatedState) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState				(void) const override;
	virtual USize						GetIsolatedSize					(void) const override;
	virtual	GSErrCode					WriteIsolatedState   			(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadIsolatedState 				(GS::IChannel& ic) override;

		// TWObject methods

	GSErrCode			ReadTWIsolatedState  (GS::IChannel& ic) override;
	GSErrCode			WriteTWIsolatedState (GS::OChannel& oc) const override;

	virtual	bool		IsEqual (ADB::GeneralAttributeConstRef attrib) const override;
};

//--------------------------------------------------------------------

typedef ODB::Ref<LineType>			LineTypeRef;
typedef ODB::ConstRef<LineType>		LineTypeConstRef;

//--------------------------------------------------------------------

#define LineTypeField(idx) FieldIDT<VBAttr::LineType>(ADB::GeneralAttribute::GetClassInfoStatic ()->GetId (), idx)
typedef FieldMaskT<VBAttr::LineType>		LineTypeFieldMask;

//========================= Class LineTypeObserver =========================
//
// Observer class for LineType
//
//==========================================================================

class VBATTRIBUTES_DLL_EXPORT LineTypeObserver : public ADB::GeneralAttributeObserver {
protected:
		// destructor

	virtual ~LineTypeObserver () {}

public:
		// changed methods

	virtual void	ScaleChanged (LineTypeConstRef);
	virtual void	PeriodLengthChanged (LineTypeConstRef);
	virtual void	HeightChanged (LineTypeConstRef);
	virtual void	TypeChanged (LineTypeConstRef);
	virtual void	LineFlagsChanged (LineTypeConstRef);
	virtual void	LineItemsListChanged (LineTypeConstRef);
};

//========================== Class LineTypeChanges =========================
//
// An implemented observer class for LineType
//
//==========================================================================

class VBATTRIBUTES_DLL_EXPORT LineTypeChanges : public LineTypeObserver {
private:
		// data members

	LineTypeFieldMask	changes;

public:
		// constructors

	LineTypeChanges (LineType* lineType);
   ~LineTypeChanges ();

		// set methods

	void	ResetChanges (void);

		// get methods

	const LineTypeFieldMask&	GetChanges (void) const;

		// changed methods (ADB::GeneralAttributeObserver interface)

	void	NameChanged (ADB::GeneralAttributeConstRef) override;
	void	IndexChanged (ADB::GeneralAttributeConstRef) override;
	void	FlagsChanged (ADB::GeneralAttributeConstRef) override;
	void	ModificationTimeChanged (ADB::GeneralAttributeConstRef) override;
	void	UserDataChanged (GSType owner1, GSType owner2) override;

		// changed methods (LineTypeObserver interface)

	void	ScaleChanged (LineTypeConstRef) override;
	void	PeriodLengthChanged (LineTypeConstRef) override;
	void	HeightChanged (LineTypeConstRef) override;
	void	TypeChanged (LineTypeConstRef) override;
	void	LineFlagsChanged (LineTypeConstRef) override;
	void	LineItemsListChanged (LineTypeConstRef) override;
};

//====================== End of the VBAttr namespace ======================

}

//================ External functions for class LineType  =================

namespace VBAttr {
	VBATTRIBUTES_DLL_EXPORT LineTypeRef					GetLineType (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT LineTypeConstRef			GetConstLineType (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT const GS::AutoPtr<GX::Pattern::LineData>
														GetConstLineData (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT GS::UniString				GetLineTypeName (ADB::AttributeSetConstRef attributeSet, short index);
	VBATTRIBUTES_DLL_EXPORT void						ConvertLineAttrToLineData (VBAttr::LineTypeConstRef lineAttrRef, GX::Pattern::LineData& lineData, bool visible = true);
	VBATTRIBUTES_DLL_EXPORT void						ConvertLineAttrToLineData (const VBAttr::LineType& lineAttrRef, GX::Pattern::LineData& lineData, bool visible = true);
	VBATTRIBUTES_DLL_EXPORT void						ConvertLineDataToLineAttr (const GX::Pattern::LineData& lineData, VBAttr::LineType* lineTypePoi);

	VBATTRIBUTES_DLL_EXPORT GX::Pattern::LineDataRef	GetLineData (LineTypeConstRef attr);
	VBATTRIBUTES_DLL_EXPORT GX::Pattern::FillDataRef	GetFillData (FillConstRef attr);
}

#endif
