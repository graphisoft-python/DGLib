// *****************************************************************************
//
//                                 Class Object
//
// Module:		   ARCHICAD
// Namespace:	   Phasing
// Contact person: FP
//
// SG compatible
//
// *****************************************************************************


#if !defined PLANTYPEVALUE_HPP
#define PLANTYPEVALUE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include	"CustomCategoryValue.hpp"

#include	"PhasingTypes.hpp"
#include	"PhasingPrefsData.hpp"
#include	"PhasingExport.hpp"

namespace Phasing {

enum RenovationExtraOverride {
	StartExtraOverrideIndex	= 1,

	HideOpeningLine			= 1,
	HideOpeningDimMarker	= 2,
	HideOpening				= 3,
	HideZoneStamp			= 4,
	HideObjects				= 5,
	SolidCutFill			= 6,
	DoNotIntersect			= 7,
	UseNorwegianX			= 8,
	TransparentFill			= 9,
	DoNotOverrideDimTextLabels	= 10,
	DoNotOverrideDraftings		= 11,
	OpeningInfillContoursAsDemolished = 12,

	MaxExtraOverrideIndex	= 12
};


class PHASING_DLL_EXPORT PlanTypeValue : public CAT::CustomCategoryValue {

	DECLARE_DYNAMIC_CLASS_INFO (PlanTypeValue)

	friend class PlanTypePrefs;

private:
	static GS::UniString undefinedPlanTypeValueNameStatic;

	enum ExtraOverride {
		Mask	= 0,
		Value	= 1
	};

#define _PLANTYPEVALUE_DATA_MEMBERS_						\
private:													\
	FilterStorageType					filter;				\
	ExtraOverrideStorageType			extraOverride;			/* UndefinedStatus-hoz nincs filter es extraOverride! */

	_PLANTYPEVALUE_DATA_MEMBERS_

		// ... Transaction management class ................................................................................

private:
	class IsolatedState : public CAT::CustomCategoryValue::IsolatedState {
	private:
		friend class PlanTypeValue;

		_PLANTYPEVALUE_DATA_MEMBERS_

	public:
		virtual ~IsolatedState ();
	};
	void						InitializeExtraOverrides (void);
public:
	PlanTypeValue ();
	PlanTypeValue (const GS::UniString& name, const bool visible, const bool usableAsCriteria);
	PlanTypeValue (const PlanTypeValue& source);
	~PlanTypeValue ();

	const GS::UniString					GetName					(void) const override;
	bool								IsUndefined				(void) const;

	void								SetStatusDisplay		(RenovationStatusType status, RenovationStatusDisplay statusDisplay);
	RenovationStatusDisplay				GetStatusDisplay		(RenovationStatusType status) const;
	void								CopyStatusDisplays		(PlanTypeValueConstRef source);
	void								SetExtraOverride		(RenovationStatusType status, RenovationExtraOverride index, bool value);
	bool								GetExtraOverride		(RenovationStatusType status, RenovationExtraOverride index) const;
	bool								HasExtraOverride		(RenovationStatusType status, RenovationExtraOverride index) const;
	void								CopyExtraOverrides		(PlanTypeValueConstRef source);

	virtual PlanTypeValueConstRef		FindCounterpart			(EDB::ProjectConstRef destinationProject) const;
	PlanTypeValueConstRef				FindCounterpart			(const PlanTypeValueConstRefList& values) const;

public:
	virtual	GSErrCode					StoreIsolatedState   	(ODB::Object::IsolatedState* isolatedState) const override;
	virtual	GSErrCode					RestoreIsolatedState 	(const ODB::Object::IsolatedState* isolatedState) override;
	virtual	ODB::Object::IsolatedState*	CreateIsolatedState	(void) const override;
private:
	GSErrCode							WriteCoreIsolatedState	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode							ReadCoreIsolatedState 	(GS::IChannel& ic, const GS::InputFrame& frame);
public:
	virtual	GSErrCode					WriteIsolatedState		(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadIsolatedState		(GS::IChannel& ic) override;
	virtual	GSErrCode					WriteTWIsolatedState	(GS::OChannel& oc) const override;
	virtual	GSErrCode					ReadTWIsolatedState		(GS::IChannel& ic) override;
	virtual	GSErrCode					WriteXML				(GS::XMLOChannel& oc) const override;
	virtual	GSErrCode					ReadXML					(GS::XMLIChannel& ic) override;

	void								FillPrefsData (PrefsData* prefsData) const;
	void								SetupFromPrefsData (const PrefsData& planTypePrefsData);

	GSErrCode							GetCheckSum (MD5::FingerPrint& checkSum) const;
};

}

#endif
