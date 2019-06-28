// *********************************************************************************************************************
// Description:		GDL Request data handler class
//
// Module:			VBElemOperations
// Namespace:		GDLOperations
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GDLREQUESTDATA_HPP)
#define GDLREQUESTDATA_HPP

#pragma once

// from GSRoot
#include	"Definitions.hpp"
#include	"Md5.hpp"

// from VBElemOperations
#include	"VBElemOperationsExport.hpp"
#include	"CurrentStoryCutLevels.hpp"
#include	"GDLGlobalCalculations.hpp"
#include	"GDLOperations.hpp"

// from VBElements
#include	"VBElements/NumFormat.hpp"

// from Phasing
#include	"PhasingTypes.hpp"

// from VBAttributes
#include	"MEPDomain.hpp"


namespace GS {
	class OChannel;
}

namespace GDLOperations {

class	VB_ELEM_OPERATIONS_DLL_EXPORT	FontNamesList : public GS::SharedObject
{
	FontNamesList (const FontNamesList&);				// forbidden
	FontNamesList (const FontNamesList&&);				// forbidden
	FontNamesList& operator= (const FontNamesList&);	// forbidden
	FontNamesList& operator= (const FontNamesList&&);	// forbidden

public:
	FontNamesList (const GS::Array<GS::UniString>& fontNames);
	virtual ~FontNamesList (void);

	const MD5::FingerPrint&	GetMd5Checksum (void) const
	{
		return m_md5Fingerprint;
	}

	USize	GetSize (void) const
	{
		return m_fontNames.GetSize ();
	}

	const GS::UniString&	operator[] (UIndex idx) const
	{
		return m_fontNames[idx];
	}

private:
	GS::Array<GS::UniString>	m_fontNames;
	MD5::FingerPrint			m_md5Fingerprint;
};
typedef GS::SharedPtr<FontNamesList>	FontNamesListPtr; 

struct	VB_ELEM_OPERATIONS_DLL_EXPORT	NumKindFormat
{
	short					norm;
	short					angleFormat;
	short					angleDecimals;
	short					roundInch;
	short					lenDecimals;
	bool					show0Whole;
	char					show0Inch;
	char					showSmall5;

	NumKindFormat ();
	NumKindFormat (	const short	normIn,
					const short	angleFormatIn,
					const short	angleDecimalsIn,
					const short	roundInchIn,
					const short	lenDecimalsIn,
					const bool	show0WholeIn,
					const char	show0InchIn,
					const char	showSmall5In);

	GSErrCode	Write (GS::OChannel& oc) const;
};

class	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLRequestData : public VBCalculations::GDLGlobalCalcEnvir
{
public:
	static const USize	LenNumListLength	= 3;

public:
	GS::UniString							appName;
	UInt32									appVersion;
	UInt32									appKeySerialNum;
	bool									appIsCommercial;
	GS::UniString							configurationNumber;
	
	VBElem::NewNumFormat					dFormat;

	VBElem::LenNumFormat					lenNumList [LenNumListLength];
	VBElem::AngNumFormat					angNumList;
	bool									useDisplayedValues;

	GS::UniString							roomCategoryName;
	GS::UniString							roomCategoryCode;

	bool									cleanInters;

	Int32									floorplanoption;
	double									viewAngle;

	GS::UniString							layoutFormat;
	GS::UniString							modelFormat;

	NumKindFormat							layoutNumFormat;
	NumKindFormat							modelNumFormat;
	NumKindFormat							angleNumFormat;

	GS::ArrayFB<GS::UniString, 3>			planTitleStrings;

	GS::UniString							project_zeroStr;
	GS::UniString							altitudeStr;
	GS::UniString							refLevel1UStr;
	GS::UniString							refLevel2UStr;
	double									refLevel1Val;
	double									refLevel2Val;
	double									altitude;

	GS::UniString							storyStr;

	VBCalculations::CurrentStoryCutLevels	gFloorPlanCutLevels;

	Phasing::PlanTypeValueConstRef			actPlanType;
	Phasing::PlanTypeConstRef				planTypeCategory;
	Phasing::RenovationStatusConstRef		renovationStatusCategory;

	bool									dvdSet;
	GDLOperations::DocumentViewDirection	documentViewDirection;

	GS::UniString							emptyWindStr;
	GS::UniString							emptyDoorStr;
	GS::UniString							basicStampStr;
	GS::UniString							emptySkylightStr;

	bool									showWindowObjectWithDim;
	bool									showDoorObjectWithDim;

	GS::UnID								zoneStampID;
	GS::UnID								modelElemID;
	
	bool									reflectedCeilingPlan;

	bool									isMEPEnabled;
	GS::UniString							renovationStr;
	GS::UniString							ifcElementPropertiesStr;
	GS::UniString							idStr;
	GS::UniString							ifcElementTypeStr;
	GS::UniString							ifcACIFCIDStr;
	GS::UniString							ifcExternalIFCIDStr;
	GS::Array<GS::UniString>				bendTypeNames;
	ODB::Id									briCategoryInstId;

	struct	MEPConnectorConnTypes : public GS::HasReadWriteMethods<MEPConnectorConnTypes> {
		VBAttr::MEPDomain			domain;
		GS::Array<GS::UniString>	guids;
		GS::Array<GS::UniString>	names;
		GS::Array<Int32>			styles;

		GSErrCode	Read (GS::IChannel& ic) = delete;
		GSErrCode	Write (GS::OChannel& oc) const;
	};
	GS::HashTable<Int32, MEPConnectorConnTypes>	connectorClassToConnTypesTable;

	FontNamesListPtr						fontNamesListPtr;

	GDLRequestData (void) :
		appVersion (0),
		appKeySerialNum (0),
		appIsCommercial (false),
		cleanInters (false),
		floorplanoption (0),
		viewAngle (0.0),
		refLevel1Val (0.0),
		refLevel2Val (0.0),
		altitude (0.0),
		dvdSet (false),
		documentViewDirection (GDLOperations::DVDUnset),
		showWindowObjectWithDim (false),
		showDoorObjectWithDim (false),
		reflectedCeilingPlan (false),
		isMEPEnabled (false)
	{
	}

	GDLRequestData (const GS::UniString&								appNameIn,
					const UInt32										appVersionIn,
					const UInt32										appKeySerialNumIn,
					const bool											appIsCommercialIn,
					const GS::UniString&								configurationNumberIn,
					const VBElem::NewNumFormat&							dFormatIn,
					const VBElem::LenNumFormat							(&lenNumListIn)[LenNumListLength],
					const VBElem::AngNumFormat&							angNumListIn,
					const bool											useDisplayedValuesIn,
					const GS::UniString&								roomCategoryNameIn,
					const GS::UniString&								roomCategoryCodeIn,
					const bool											cleanIntersIn,
					const Int32											floorplanoptionIn,
					const double										viewAngleIn,
					const GS::UniString&								layoutFormatIn,
					const GS::UniString&								modelFormatIn,
					const NumKindFormat&								layoutNumFormatIn,
					const NumKindFormat&								modelNumFormatIn,
					const NumKindFormat&								angleNumFormatIn,
					const GS::Array<GS::UniString>&						planTitleStringsIn,
					const GS::UniString									project_zeroStrIn,
					const GS::UniString									altitudeStrIn,
					const GS::UniString									refLevel1UStrIn,
					const GS::UniString									refLevel2UStrIn,
					const double										refLevel1ValIn,
					const double										refLevel2ValIn,
					const double										altitudeIn,
					const GS::UniString&								storyStrIn,
					const VBCalculations::CurrentStoryCutLevels&		gFloorPlanCutLevelsIn,
					const Phasing::PlanTypeValueConstRef&				actPlanTypeIn,
					const Phasing::PlanTypeConstRef&					planTypeCategoryIn,
					const Phasing::RenovationStatusConstRef&			renovationStatusCategoryIn,
					const GDLOperations::DocumentViewDirection*			documentViewDirectionIn,
					const GS::UniString&								emptyWindStrIn,
					const GS::UniString&								emptyDoorStrIn,
					const GS::UniString&								basicStampStrIn,
					const GS::UniString&								emptySkylightStrIn,
					const bool											showWindowObjectWithDimIn,
					const bool											showDoorObjectWithDimIn,
					const GS::UnID&										zoneStampIDIn,
					const GS::UnID&										modelElemIDIn,
					const bool											reflectedCeilingPlanIn,
					const bool											isMEPEnabledIn,
					const GS::UniString&								renovationStrIn,
					const GS::UniString&								ifcElementPropertiesStrIn,
					const GS::UniString&								idStrIn,
					const GS::UniString&								ifcElementTypeStrIn,
					const GS::UniString&								ifcACIFCIDStrIn,
					const GS::UniString&								ifcExternalIFCIDStrIn,
					const GS::Array<GS::UniString>&						bendTypeNamesIn,
					const ODB::Id&										briCategoryInstIdIn,
					const GS::HashTable<Int32, MEPConnectorConnTypes>&	connectorClassToConnTypesTableIn,
					const FontNamesListPtr&								fontNamesListPtrIn) :
		GDLGlobalCalcEnvir (),

		appName (appNameIn),
		appVersion (appVersionIn),
		appKeySerialNum (appKeySerialNumIn),
		appIsCommercial (appIsCommercialIn),
		configurationNumber (configurationNumberIn),
		dFormat (dFormatIn),
		angNumList (angNumListIn),
		useDisplayedValues (useDisplayedValuesIn),
		roomCategoryName (roomCategoryNameIn),
		roomCategoryCode (roomCategoryCodeIn),
		cleanInters (cleanIntersIn),
		floorplanoption (floorplanoptionIn),
		viewAngle (viewAngleIn),
		layoutFormat (layoutFormatIn),
		modelFormat (modelFormatIn),
		layoutNumFormat (layoutNumFormatIn),
		modelNumFormat (modelNumFormatIn),
		angleNumFormat (angleNumFormatIn),
		planTitleStrings (planTitleStringsIn),
		project_zeroStr (project_zeroStrIn),
		altitudeStr (altitudeStrIn),
		refLevel1UStr (refLevel1UStrIn),
		refLevel2UStr (refLevel2UStrIn),
		refLevel1Val (refLevel1ValIn),
		refLevel2Val (refLevel2ValIn),
		altitude (altitudeIn),
		storyStr (storyStrIn),
		gFloorPlanCutLevels (gFloorPlanCutLevelsIn),
		actPlanType (actPlanTypeIn),
		planTypeCategory (planTypeCategoryIn),
		renovationStatusCategory (renovationStatusCategoryIn),
		dvdSet (documentViewDirectionIn != nullptr),
		documentViewDirection (documentViewDirectionIn != nullptr ? *documentViewDirectionIn : GDLOperations::DVDUnset),
		emptyWindStr (emptyWindStrIn),
		emptyDoorStr (emptyDoorStrIn),
		basicStampStr (basicStampStrIn),
		emptySkylightStr (emptySkylightStrIn),
		showWindowObjectWithDim (showWindowObjectWithDimIn),
		showDoorObjectWithDim (showDoorObjectWithDimIn),
		zoneStampID (zoneStampIDIn),
		modelElemID (modelElemIDIn),
		reflectedCeilingPlan (reflectedCeilingPlanIn),
		isMEPEnabled (isMEPEnabledIn),
		renovationStr (renovationStrIn),
		ifcElementPropertiesStr (ifcElementPropertiesStrIn),
		idStr (idStrIn),
		ifcElementTypeStr (ifcElementTypeStrIn),
		ifcACIFCIDStr (ifcACIFCIDStrIn),
		ifcExternalIFCIDStr (ifcExternalIFCIDStrIn),
		bendTypeNames (bendTypeNamesIn),
		briCategoryInstId (briCategoryInstIdIn),
		connectorClassToConnTypesTable (connectorClassToConnTypesTableIn),
		fontNamesListPtr (fontNamesListPtrIn)
	{
		for (UIndex i = 0; i < LenNumListLength; ++i)
			lenNumList[i] = lenNumListIn[i];
	}

	virtual ~GDLRequestData ();
};

	
}	// namespace GDLOperations

#endif	// GDLREQUESTDATA_HPP
