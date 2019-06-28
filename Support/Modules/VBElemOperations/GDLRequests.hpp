// *********************************************************************************************************************
// Description:		GDL Request interface implementation
//
// Module:			VBElemOperations
// Namespace:		GDLOperations
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GDLREQUESTS_HPP)
#define GDLREQUESTS_HPP

#pragma once

// from GSRoot
#include	"Definitions.hpp"

// from GDL
#include	"GDLProc.h"

// from VBAttributes
#include	"attributeset.hpp"

// from VBElements
#include "ProfileFillData.hpp"

// from VBElemOperations
#include	"VBElemOperationsExport.hpp"

//from ObjectDatabase
#include	"ODBReference.hpp"

// from Property
#include "PropertyTypes.hpp"
#include "IValueDescriptor.hpp"


namespace ODB {
	template <class Obj> class ConstRef;
}

namespace GS {
	class OChannel;
	class Variant;
}

namespace EDB {
	class DefaultElem;
	class GeneralElem;
	typedef ODB::ConstRef<GeneralElem> GeneralElemConstRef;
}

namespace IPL {
	class PropertySet;
}

namespace CLS {
	class ClassificationSystemContainerSet;
	typedef ODB::ConstRef<ClassificationSystemContainerSet> ClassificationSystemContainerSetConstRef;
}

class ProfileComposite;
class ProfileVectorImage;


namespace LM {
	class LibrarySet;
}

namespace GDLOperations {

class	GDLRequestData;
class	GDLRequestCallbacks;


enum	ViewType {
	VT_FloorPlanDDD,
	VT_Other
};


ULong VB_ELEM_OPERATIONS_DLL_EXPORT GDLElemRef2RndSeed (const EDB::GeneralElemConstRef& elemRef);

class	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLRequests : public IGDLRequests {
protected:
	const GDLRequestCallbacks&		m_callbacks;
	const GDLRequestData&			m_gdlRequestData;
	const EDB::DefaultElem*			m_defaultElem;
	GSUserData*						m_userData;

	Int32							m_isFirstOccasion;
	GS::Array<Coord3D>				m_cpCoords;
	GS::Array<Int32>				m_portIndices;
	GS::Array<Vector3D>				m_dirVs;
	GS::Array<Vector3D>				m_widthVs;	

	EDB::GeneralElemConstRef		m_elemRef;
	UInt64							m_attributesModiStamp;

	GDL_ScriptType					m_scriptType;

	ViewType						m_viewType;
	short							m_floorPlanDDDStory;

public:
	
	GDLRequests (const GDLRequestCallbacks& callbacks, 
				 const GDLRequestData& gdlRequestData, 
				 const EDB::DefaultElem* defaultElem, 
				 const GDL_ScriptType& scriptType,
				 EDB::GeneralElemConstRef elemRef,
				 const ViewType viewType,
				 const short floorPlanDDDStory,
				 UInt64 attributesModiStamp = 0);

	virtual ~GDLRequests ();

	EDB::GeneralElemConstRef GetElemRef (void) const;

	enum	RequestMd5WriteState {
		Fail	= 0,
		Success	= 1
	};
	RequestMd5WriteState	WriteReqMd5Content (const GS::HashSet<GS::Pair<GS::Int32, GS::UniString> >&	requestIDs, 
												const GS::HashSet<GS::UniString>&						applicationQueryNames,
												GS::OChannel&											oc,
												GS::HashSet<GS::Pair<GS::Int32, GS::UniString> >*		nonCacheableRequestIDs = nullptr, 
												GS::HashSet<GS::UniString>*								nonCacheableApplicationQueryNames = nullptr) const;


	static UInt64			CalculateAttributesModiStamp (const ADB::AttributeSetConstRef& attributes);
	
	static EDB::GeneralElemConstRef GetRelevantElemForLabel (const EDB::GeneralElemConstRef& elem, bool fromOwner);
	static EDB::GeneralElemConstRef GetRelevantElemForSymb (const EDB::GeneralElemConstRef& elem, bool fromOwner);

	// ---------------------- requests ----------------------

	virtual bool		NeedToStoreData (Int32 requestNumber) override;

	virtual	Int32		SizeReq (void) override;

	virtual	float		AttrReq (Int32 func, GS::UniString& str) override;

	virtual	void		PrograminfoReq (GS::UniString* name, UInt32* version, UInt32* keySerialNum, bool* isCommercial) override;

	virtual	void		DimformReq (	short dimKind, short *norm, short *roundInch, short *lenDecimals,
										bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec) override;

	virtual	void		CatnamecodeReq (GS::UniString& name, GS::UniString& code) override;

	virtual	void		PlantitleReq (Int32 nrvals, GS::Array<GS::UniString>& planTitleStrings) override;

	virtual	void		HomestoryReq (	short *index, GS::UniString& storyname,
										bool home_story_of_opening) override;

	virtual	void		StoryReq (short *index, GS::UniString& storyname) override;

	virtual	bool		CleanintersReq (void) override;

	virtual	void		ZonedataReq (	GS::UniString& catname, GS::UniString& catcode,
										GS::UniString& number, GS::UniString& name,
										GS::UniString& catname2, GS::UniString& catcode2,
										GS::UniString& number2, GS::UniString& name2,
										bool fromOwner) override;

	virtual	void		CustomautolabelReq (GS::UniString& name) override;

	virtual	void		ZonecolusareaReq (double *area) override;

	virtual	short		WidoshowdimReq (void) override;

	virtual	short		WindowshowdimReq (void) override;

	virtual	short		DoorshowdimReq (void) override;

	virtual	void		NameOfListedReq (GSHandle globHdl, GS::UniString& name) override;

	virtual	short		WidozonerelevReq (bool fromOwner) override;

	virtual	void		CalcformReq (	short dimKind, short *norm, short *roundInch, short *lenDecimals,
										bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec) override;

	virtual	void		MatchpropReq (	bool ownProp,
										Int32 nrvals, Int32 *retValue,
										GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl) override;

	virtual	GSErr		AssoclpparvalueReq (	const char* parName, Int32 parIndex,
												char *name, Int32 *index,
												short *type, bool *isArray, unsigned char *flags, Int32 *dim1, Int32 *dim2,
												GdlValueRecord *numVal, GS::UniString& strVal,
												GS::Array<GdlValueRecord>& arrayValues, GS::Array<GS::UniString>& stringsHdl, GS::Array<GS::UniString>* numValDescriptions) override;

	virtual	GSErr		AssocelpropReq (	GSHandle globHdl,
											Int32 nrData, char *order, Int32 nrVals, Int32 *retValue,
											GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl) override;

	virtual	void		RefleveldataReq (Int32 nrvals, GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl) override;

	virtual	void		AssoclpnameReq (GS::UniString& name) override;

	virtual	void		StoryinfoReq (	Int32 nrvals, bool allStories, Int32 index,
										Int32 *retValue, GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl) override;

	virtual	void		AncestryinfoReq (	bool getReplacedInfo, Int32 nrvals,
											Int32 *retValue, GS::Array<GS::UniString>& ancestryInfoStrings) override;

	virtual	void		Styleinfo (	const GS::UniString& fontname, short familytype, double face, double slant, double size,
									double *height, double *descent, double *leading)	 override;

	virtual	Int32		ConstrfilldisplayReq (void) override;

	virtual	void		WorkingformReq (	short dimKind, short *norm, short *roundInch, short *lenDecimals,
											bool *show0Whole, char *show0Inch, char *showSmall5, bool *hide0Dec) override;

	virtual	void		TextsizeunitReq (	short workspaceKind,
											GS::UniString& unit) override;

	virtual	GSErr		MaterialinfoReq (	Int32 materIndex,
											Int32 nData, double **data, GSHandle *extraParameters,
											const char *reqStr, Int32 *retValue,
											GS::Array<GdlValueRecord>& values,
											GS::Array<GS::UniString>& stringsHdl,
											RequestValueMode requestValueMode) override;

	virtual	GSErr		TextblockinfoReq (	const GdlTextBlockData*					textBlockData,
											const GS::VAArray<GdlParagraphData>*	paragraphs,
											const GSHandle							tabsHdl,		// double
											const GS::VAArray<GdlStringData>*		stringsData,
											const GSHandle							stringsHdl,		// Layout
											double*									width,
											double*									height) override;

	virtual	void		FontnameslistReq (Int32 nrvals, GS::Array<GdlValueRecord>& values, GS::Array<GS::UniString>& stringsHdl) override;

	virtual	void		HomeDBinfoReq (	Int32			*parentDBIntId,
										GS::UniString&	parenDBUserId,
										GS::UniString&	parenDBName,
										short			*homeContext) override;

	virtual	Int32		FloorplanoptionReq (void) override;

	virtual	double		ViewAngleReq (void) override;

	virtual	void		ElemInfoReq (GS::UniString& name) override;

	virtual	void		FullInfoReq (GS::Array<GS::UniString>& idStrings) override;

	virtual GSErr		SumWithRoundingReq (const Int32 formatReqNr, const GS::Array<double>& numVals, double& result) override;

	virtual	void		ConfigurationNumber (GS::UniString& configurationNumber) override;

	virtual	GSErr		ApplicationQuery (	const GS::UniString&			identifierStr,
											const GS::UniString&			parameterStr,
											Int32							nrvals,
											bool*							storeData,
											Int32*							retValue,
											GS::Array<GdlValueRecord>&		values,
											GS::Array<GS::UniString>&		stringvals,
											IGDLRequests::RequestValueMode	requestValueMode) override;

	class IPropertyCollector	//does whatever is needed, only supports different add methods
	{
	public: 
		virtual ~IPropertyCollector ();

		virtual bool	SendPropertyNameById () = 0;
		virtual bool	SendPropertyValueById () = 0;
		virtual bool	SendPropertyNamesOfParent () = 0;

		virtual const GS::UniString GetPropertyId () = 0;

		virtual bool	AddPropertyName (const GS::UniString& propId, const GS::UniString& propTypeName, const GS::UniString& propGrpName, const GS::UniString& propName) = 0; 
		virtual bool	AddPropertyStringValue (const GS::UniString& propValue) = 0; 
		virtual bool	AddPropertyValue (Property::ValueType valType, const Property::Measure& measure, Int32 dim1, Int32 dim2, const GS::Array<GdlValueRecord>& propValues, const GS::Array<GS::UniString>& propStringVals) = 0; 
		virtual	bool	AddCategoryData (ODB::IdSpace* idSpace, const GS::UniString& propId, const ODB::Id& categoryId, EDB::GeneralElemConstRef elem) = 0;
	};

	static GS::AutoPtr <IPropertyCollector>	NewPropertyAllNamesCollector (const LM::LibrarySet* librarySet,
																		  Int32* retValue,
																		  GS::Array<GdlValueRecord>& values,
																		  GS::Array<GS::UniString>& stringvals); 

	static GS::AutoPtr <IPropertyCollector>	NewPropertyValueCollector (const LM::LibrarySet* librarySet,
																	   const GS::UniString& propertyId,
																	   Int32* retValue, 
																	   GS::Array<GdlValueRecord>& values, 
																	   GS::Array<GS::UniString>& stringvals); 

	static GS::AutoPtr <IPropertyCollector>	NewPropertyNameCollector (const LM::LibrarySet* librarySet,
																	  const GS::UniString& propertyId,
																	  Int32* retValue, 
																	  GS::UniString& propertyType,
																	  GS::UniString& propertyGroupName,
																	  GS::UniString& propertyName); 

	virtual GSErr		PropertiesOfParent (	Int32 reqIndex,
												Int32* retValue,
												GS::Array<GdlValueRecord>& values,
												GS::Array<GS::UniString>& stringvals) override;

	virtual GSErr		PropertyValueOfParent (	const GS::UniString& propertyId,
												Int32* retValue,
												GS::Array<GdlValueRecord>& values,
												GS::Array<GS::UniString>& stringvals) override;

	virtual GSErr		PropertyNameOfParent (	const GS::UniString& propertyId,
												Int32* retValue,
												GS::UniString& propertyType,
												GS::UniString& propertyGroupName,
												GS::UniString& propertyName) override;

protected:
	GSErr				CollectCoreProperties (IPropertyCollector& collector);
	GSErr				CollectClassifications (GDLRequests::IPropertyCollector& collector, const CLS::ClassificationSystemContainerSetConstRef& containerSet);

public:
	virtual	bool		AppQueryEnabledFromParameterScript (const GS::UniString& identifierStr) override;

	virtual	GSErr		LibraryGlobal	(	const GS::UnID&				unID,
											const GS::UniString&		identifierStr,
											const GS::UniString&		parameterStr,
											Int32*						retValue,
											GS::Array<GdlValueRecord>&	values,
											GS::Array<GS::UniString>&	stringvals) override;
	
	virtual	GSErr		BuildMatInfo (	const GS::UniString*			buildMatName,
										Int32							buildMatIndex,
								 		const char*						reqStr,
										Int32*							retValue,
										GS::Array<GdlValueRecord>&		values,
										GS::Array<GS::UniString>&		stringsHdl,
										RequestValueMode				requestValueMode) override;

	virtual	GSErr		ComponentVolume (UInt32 componentIndex, double& volume) override;
	virtual	GSErr		ComponentProjectedArea (UInt32 componentIndex, double& projectedArea) override;
	virtual GSErr		AutoTextList (Int32* retValue,
									  GS::Array<GdlValueRecord>& values,
									  GS::Array<GS::UniString>& stringvals) override;

	virtual GSErr		ProfileComponents (const GS::UniString* profileName, Int32 profileIndex, GS::Array<GdlValueRecord>& componentTypeCodeValues) override;
	virtual GSErr		ProfileBoundingBox (const GS::UniString* profileName, Int32 profileIndex, double width, double height, double* xmin, double* ymin, double* xmax, double* ymax) override;
	virtual GSErr		ProfileGeometry (const GS::UniString* profileName, Int32 profileIndex, double width, double height, GS::Array<GdlValueRecord>& rawGeometryValues) override;
	virtual GSErr		ProfileComponentInfo (const GS::UniString*			profileName,
											  Int32							profileIndex,
											  Int32							componentIndex,
											  Int32							parameterIndex,
											  Int32*						retValue,
											  GS::Array<GdlValueRecord>&	values,
											  GS::Array<GS::UniString>&		stringsHdl,
											  RequestValueMode				requestValueMode) override;

protected:
	bool	WriteAttributesMd5Content (GS::OChannel& oc) const;

	void	StoryReqConst (short *index, GS::UniString& storyname) const;
	void	ElemInfoReqConst (GS::UniString& name) const;
	void	HomestoryReqConst (short *index, GS::UniString& storyname, bool home_story_of_opening) const;
	void	FullInfoReqConst (GS::Array<GS::UniString>& idStrings) const;

	virtual bool	WriteSizeReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteAttrReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WritePrograminfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteDimformReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteCatnamecodeReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WritePlantitleReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteHomestoryReqMd5Content (GS::OChannel& oc, bool home_story_of_opening) const;
	virtual bool	WriteStoryReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteCleanintersReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteZonedataReqMd5Content (GS::OChannel& oc, bool fromOwner) const;
	virtual bool	WriteCustomautolabelReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteZonecolusareaReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteWidoshowdimReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteWindowshowdimReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteDoorshowdimReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteNameOfListedReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteWidozonerelevReqMd5Content (GS::OChannel& oc, bool fromOwner) const;
	virtual bool	WriteCalcformReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteMatchpropReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteAssoclpparvalueReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteAssocelpropReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteRefleveldataReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteAssoclpnameReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteStoryinfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteAncestryinfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteStyleinfoMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteWorkingformReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteTextsizeunitReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteMaterialinfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteTextblockinfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteFontnameslistReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteHomeDBinfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteFloorplanoptionReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteViewAngleReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteElemInfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteSingleApplicationQueryMd5Content (const GS::UniString& applicationQueryName, GS::OChannel& oc) const;
	bool			WriteApplicationQueryMd5Content (	const GS::HashSet<GS::UniString>&	applicationQueryNames, 
												GS::OChannel&						oc,
												GS::HashSet<GS::UniString>*			nonCacheableApplicationQueryNames = nullptr) const;
	virtual bool	WriteBuildMatInfoMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteFullInfoReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteComponentVolumeReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteComponentProjectedReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WritePropertiesOfParentReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WritePropertyValueOfParentReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WritePropertyNameReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteAutoTextListReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteSumWithRoundingReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteConfigurationNumberReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteProfileComponentsReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteProfileDefaultBoundingBoxReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteProfileDefaultGeometryReqMd5Content (GS::OChannel& oc) const;
	virtual bool	WriteProfileComponentInfoReqMd5Content (GS::OChannel& oc) const;

	static bool	ParseApplicationQueryString (const GS::UniString& parameter, GS::UniString& func, Int32& argument);	
	static bool ParseApplicationQueryString (const GS::UniString& parameter, GS::UniString& func, GS::Array<GS::UniString>& arguments);
	static EDB::GeneralElemConstRef GetParentElem (EDB::GeneralElemConstRef elemRef);

	GSErr GetProfileComponentSurface (const ProfileComposite& profileComposite, ULong componentIndex, short& surface);
	GSErr AddProfileComponentEdgeData (const ProfileVectorImage& finalizedImage, const ProfileMultiPolygon& polys, ULong componentIndex, Int32 parameterIndex,
									  GS::Array<GdlValueRecord>& values, ULong& valueCount);

private:
	bool		ParseApplicationQueryString2 (const GS::UniString& parameter, GS::UniString& func, GS::Array<double>& arguments);
};
	
}	// namespace GDLOperations

#endif	// GDLREQUESTS_HPP
