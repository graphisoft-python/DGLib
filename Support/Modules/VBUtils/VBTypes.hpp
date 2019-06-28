// *********************************************************************************************************************
// Basic definitions for the Virtual Building data stuctures
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (VBTYPES_H)
#define VBTYPES_H

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "VBUtilsExport.hpp"

#include "HashTable.hpp"
#include "HashSet.hpp"
#include "Pair.hpp"
#include "ODBObject.hpp"
#include "ODBReference.hpp"
#include "ODBConversionData.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace EDB {
	class ChangedDefaultRegDataTable;
	class ChangedElemRegDataTable;
	class DBUnId;
	class IElemDatabase;
	class Project;
}

namespace EDBAC17 {
	class DBUnId;
}

namespace VBElem {
	class WallConnectionsMap;
	class BeamConnectionsMap;
}

struct VerticalLinkData {
	char linkType;
	short floorNum;
};

namespace VBUtil {

enum FillOrientationType {
	ProjectOrigin	= 0,
	ElementOrigin	= 1,
	FitToSkin		= 2
};

// =============================================================================
// WriteConversionInfo
//
// Use this class to give information to the old Write functions
// =============================================================================
//fi021029, hibajav: #19151

class VBUTILS_DLL_EXPORT ObjectConversionData
{
public:
	ObjectConversionData ();
	virtual ~ObjectConversionData ();
};

class VBUTILS_DLL_EXPORT AttrConversionData : public GS::HasReadWriteMethods<AttrConversionData> {
public:
	short				cutFillIndex;			// cut fill index
	short				cutFillPen;				// cut fill pen index
	short				cutFillBackgroundPen;	// cut fill background pen index
	FillOrientationType	orientationBits;		// fill orientation as set in composite < 17 skins
	Int32				connPriority;			// connection priority
	short				cutMaterial;			// material index
	bool				generateAlways;			// always generate building material from this data - no override available

	AttrConversionData ();
	virtual ~AttrConversionData ();

	bool	operator== (const AttrConversionData& other) const	{ return cutFillIndex == other.cutFillIndex &&
																		 cutFillPen == other.cutFillPen && cutFillBackgroundPen == other.cutFillBackgroundPen &&
																		 orientationBits == other.orientationBits && connPriority == other.connPriority &&
																		 cutMaterial == other.cutMaterial && generateAlways == other.generateAlways; }
	bool	operator!= (const AttrConversionData& right) const	{ return !operator== (right); }
			operator GS::HashValue () const;

	GS::UniString	GetBuildingMaterialNamePostFix (GS::UniString* name2PostFix = nullptr) const;
	GS::UniString	GenerateConvertedName (GS::UniString& namePrefix, GS::UniString* name2PostFix = nullptr) const;

	GSErrCode	Write (GS::OChannel& oc) const;
	GSErrCode	Read  (GS::IChannel& ic);
};

class VBUTILS_DLL_EXPORT OverriddenAttributeData : public GS::HasReadWriteMethods<OverriddenAttributeData> {
public:
	short		attrIndex;	
	Int32		connPriority;
	short		cutContourLineType;
	short		cutContourLinePen;
	short		cutInnerLineType;
	short		cutInnerLinePen;

	short		elementMaterial;			// material coming from element (Column)
	bool		useElementMaterial;

		OverriddenAttributeData ();
	virtual ~OverriddenAttributeData ();

	void	Fill (short _attrIndex,
				  bool useCompConnPriority, Int32 _connPriority,
				  bool useCompContourLineTypePen, short _cutContourLineType, short _cutContourLinePen,
				  bool useCompInnerLineTypePen, short _cutInnerLineType, short _cutInnerLinePen,
				  bool _useElementMaterial = false, short _elementMaterial = 0)
	{
		attrIndex = _attrIndex;
		if (!useCompConnPriority) {
			connPriority = _connPriority;
		}
		if (!useCompContourLineTypePen) {
			cutContourLineType = _cutContourLineType;
			cutContourLinePen = _cutContourLinePen;
		}
		if (!useCompInnerLineTypePen) {
			cutInnerLineType = _cutInnerLineType;
			cutInnerLinePen = _cutInnerLinePen;
		}
		useElementMaterial = _useElementMaterial;
		elementMaterial = _elementMaterial;
	}

	bool	operator== (const OverriddenAttributeData& other) const	{ return attrIndex == other.attrIndex && connPriority == other.connPriority && 
																		 cutContourLineType == other.cutContourLineType && cutContourLinePen == other.cutContourLinePen &&
																		 cutInnerLineType == other.cutInnerLineType && cutInnerLinePen == other.cutInnerLinePen &&
																		 useElementMaterial == other.useElementMaterial && elementMaterial == other.elementMaterial; }
	bool	operator!= (const OverriddenAttributeData& right) const	{ return !operator== (right); }
			operator GS::HashValue () const;

	GS::UniString	GenerateConvertedName (GS::UniString namePrefix, GS::UniString* name2PostFix = nullptr) const;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct VBUTILS_DLL_EXPORT OwnProfiledData : public GS::HasReadWriteMethods<OwnProfiledData> {
	Int32	hatchPositionIndex;
	short	cutContourLineType;
	short	cutContourLinePen;
	short	cutInnerLineType;
	short	cutInnerLinePen;

	OwnProfiledData ();
	virtual ~OwnProfiledData ();

	void	Fill (short _hatchPositionIndex,
				  bool useCompContourLineTypePen, short _cutContourLineType, short _cutContourLinePen,
				  bool useCompInnerLineTypePen, short _cutInnerLineType, short _cutInnerLinePen)
	{
		hatchPositionIndex = _hatchPositionIndex;
		if (!useCompContourLineTypePen) {
			cutContourLineType = _cutContourLineType;
			cutContourLinePen = _cutContourLinePen;
		}
		if (!useCompInnerLineTypePen) {
			cutInnerLineType = _cutInnerLineType;
			cutInnerLinePen = _cutInnerLinePen;
		}
	}

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct VBUTILS_DLL_EXPORT OwnProfiledObjectRefData  : public GS::HasReadWriteMethods<OwnProfiledObjectRefData> {
	ODB::Ref<ODB::Object>	objRef;
	OwnProfiledData			profiledData;
	bool					updated;

	OwnProfiledObjectRefData () :
		updated (false)
	{
	}
	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct VBUTILS_DLL_EXPORT DefaultToolData : public GS::HasReadWriteMethods<DefaultToolData> {
	short	idElem;
	short	idVariation;

	DefaultToolData () :
		idElem (0),
		idVariation (0)
	{
	}

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct VBUTILS_DLL_EXPORT OwnProfiledDefaultData  : public GS::HasReadWriteMethods<OwnProfiledDefaultData> {
	DefaultToolData		defaultToolData;
	OwnProfiledData		profiledData;
	bool				updated;

	OwnProfiledDefaultData () :
		updated (false)
	{
	}

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct VBUTILS_DLL_EXPORT AttrConversionSkinData  : public GS::HasReadWriteMethods<AttrConversionSkinData> {
	short		attrIndex;
	short		skinIndex;
	bool		updated;

	AttrConversionSkinData () :
		attrIndex (0),
		skinIndex (0),
		updated (false)
	{
	}

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct VBUTILS_DLL_EXPORT AttrConversionProfileData : public GS::HasReadWriteMethods<AttrConversionProfileData> {
	short		profileIndex;
	Int32		hatchPositionIndex;
	bool		updated;

	AttrConversionProfileData () :
		profileIndex (0),
		hatchPositionIndex (0),
		updated (false)
	{
	}

	bool		operator== (const AttrConversionProfileData& source) const { return profileIndex == source.profileIndex && hatchPositionIndex == source.hatchPositionIndex; }
	bool		operator!= (const AttrConversionProfileData& source) const { return profileIndex != source.profileIndex || hatchPositionIndex != source.hatchPositionIndex; }

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

enum AttributeIndexType {
	Basic			= 0,
	BasicCore		= 1,
	BasicVeneer		= 2,
	BasicFrame		= 3,
	BasicPanel		= 4,
	Composite		= 5,
	Profile			= 6
};

struct ObjectWithIndexType : public GS::HasReadWriteMethods<ObjectWithIndexType> {
	ObjectWithIndexType () :
		indexType (Basic),
		updated (false)
	{
	}

	ObjectWithIndexType (ODB::Ref<ODB::Object> objectRef, AttributeIndexType indexType) :
		objectRef (objectRef),
		indexType (indexType),
		updated (false)
	{
	}

	ODB::Ref<ODB::Object>	objectRef;
	AttributeIndexType		indexType;
	bool					updated;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};

struct DefaultToolDataWithIndexType : public GS::HasReadWriteMethods<DefaultToolDataWithIndexType> {
	DefaultToolDataWithIndexType ():
		indexType (Basic),
		updated (false)
	{
	}

	DefaultToolDataWithIndexType (DefaultToolData defaultToolData, AttributeIndexType indexType) :
		defaultToolData (defaultToolData),
		indexType (indexType),
		updated (false)
	{
	}

	DefaultToolData		defaultToolData;
	AttributeIndexType	indexType;
	bool				updated;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};


struct VBUTILS_DLL_EXPORT AttrConversionElements : public GS::HasReadWriteMethods<AttrConversionElements> {
	GS::Array<ObjectWithIndexType>			objectRefList;				// placed objects & favorites
	GS::Array<OwnProfiledObjectRefData>		profiledObjectRefList;		// placed objects & favorites with embedded profile
	GS::Array<DefaultToolDataWithIndexType>	defaultElemList;			// default elements for tools
	GS::Array<OwnProfiledDefaultData>		profiledDefaultList;		// default elements for tools with embedded profile

	GS::Array<AttrConversionSkinData>		compositeList;				// composite attributes to generate
	GS::Array<AttrConversionProfileData>	profileList;				// profile attributes to generate

	bool		wasGenerated;
	short		attrIndex;

	AttrConversionElements () :
		wasGenerated (false),
		attrIndex (0)
	{
	}

	AttrConversionElements&	operator+= (const AttrConversionElements& conversionElements);
	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;
};


class VBUTILS_DLL_EXPORT AttributeConversionInfo : public GS::Object {
	ODB::Ref<ODB::Object>							favoriteRef;
	DefaultToolData									defaultToolData;
	GS::HashTable<AttrConversionData, AttrConversionElements>*		attrConversionTable;	// new BuildingMaterial attributes with elements to update the index 
	GS::HashTable<OverriddenAttributeData, AttrConversionElements>*	compositeDataTable;		// new CompWall attributes with elements to update the index 
	GS::HashTable<OverriddenAttributeData, AttrConversionElements>*	profileDataTable;		// new Profile attributes with elements to update the index 
	GS::Array<AttrConversionElements>*								attrConvertedTable;		// elements using not overridden attributes

	bool useOwnTables;

	DECLARE_DYNAMIC_CLASS_INFO (AttributeConversionInfo);

public:
	AttributeConversionInfo ();
	virtual ~AttributeConversionInfo ();
	AttributeConversionInfo (const AttributeConversionInfo& source);

	void						CreateOwnTables (void);

	void						SetFavoriteRef (ODB::Ref<ODB::Object> actFavoriteRef) { favoriteRef = actFavoriteRef; }
	ODB::Ref<ODB::Object>		GetFavoriteRef (void){ return favoriteRef; }

	void					SetDefaultToolData (DefaultToolData actDefaultToolData) { defaultToolData = actDefaultToolData; }
	DefaultToolData			GetDefaultToolData (void) { return defaultToolData; }

	void					AddAttrConversionData (const AttrConversionData& data, ODB::Ref<ODB::Object> object, AttributeIndexType indexType);
	void					AddAttrConversionData (const AttrConversionData& data, OwnProfiledObjectRefData& profiledObjectData);
	void					AddAttrConversionData (const AttrConversionData& data, short idElem, short idVariation, AttributeIndexType indexType);
	void					AddAttrConversionData (const AttrConversionData& data, OwnProfiledDefaultData& profiledDefaultData);
	void					AddAttrConversionData (const AttrConversionData& data, AttrConversionSkinData& skinData);
	void					AddAttrConversionData (const AttrConversionData& data, AttrConversionProfileData& skinData);

	void					AddDefaultAttrConversionData (const AttrConversionData& data, AttributeIndexType indexType);
	void					AddDefaultAttrConversionData (const AttrConversionData& data, const OwnProfiledData& profiledData);

	GS::HashTable<AttrConversionData, AttrConversionElements>*	GetAttrConversionDataTable (void)	{return attrConversionTable; }
	void					SetAttrConversionDataTable (GS::HashTable<AttrConversionData, AttrConversionElements>* _attrConversionTable)	{attrConversionTable = _attrConversionTable; }

	void					AddOverriddenCompositeData (const OverriddenAttributeData& data, ODB::Ref<ODB::Object> object);
	void					AddOverriddenCompositeData (const OverriddenAttributeData& data, short idElem, short idVariation);
	void					AddDefaultOverriddenCompositeData (const OverriddenAttributeData& data);
	GS::HashTable<OverriddenAttributeData, AttrConversionElements>*	GetOverriddenCompositeDataTable (void)	{return compositeDataTable; }
	void					SetOverriddenCompositeDataTable (GS::HashTable<OverriddenAttributeData, AttrConversionElements>* _compositeDataTable)	{compositeDataTable = _compositeDataTable; }

	void					AddOverriddenProfileData (const OverriddenAttributeData& data, ODB::Ref<ODB::Object> object);
	void					AddOverriddenProfileData (const OverriddenAttributeData& data, short idElem, short idVariation);
	void					AddDefaultOverriddenProfileData (const OverriddenAttributeData& data);
	GS::HashTable<OverriddenAttributeData, AttrConversionElements>*	GetOverriddenProfileDataTable (void)	{return profileDataTable; }
	void					SetOverriddenProfileDataTable (GS::HashTable<OverriddenAttributeData, AttrConversionElements>* _profileDataTable)	{profileDataTable = _profileDataTable; }

	void					AddCompositeConvertedData (ODB::Ref<ODB::Object> object);
	void					AddDefaultCompositeConvertedData (void);
	void					AddProfileConvertedData (ODB::Ref<ODB::Object> object);
	void					AddDefaultProfileConvertedData (void);
	GS::Array<AttrConversionElements>*	GetAttrConvertedTable (void)	{return attrConvertedTable; }
	void					SetAttrConvertedTable (GS::Array<AttrConversionElements>* _attrConvertedTable)	{attrConvertedTable = _attrConvertedTable; }


	virtual GSErrCode		Read (GS::IChannel& ic) override;
	virtual GSErrCode		Write (GS::OChannel& oc) const override;
	virtual GS::Object*		Clone (void) const override;

	GSErrCode				Merge (const AttributeConversionInfo& source);

private:
	void	DeleteTables (void);
};

// =============================================================================
// ElemDefaultReadConversionInfo
//
// Use this class to give information to the old Read functions (ElemDefault)
// =============================================================================
class AttributeConversionInfo;

class VBUTILS_DLL_EXPORT ElemDefaultReadConversionInfo : public ODB::ConversionData {

	DECLARE_DYNAMIC_CLASS_INFO (ElemDefaultReadConversionInfo);

	AttributeConversionInfo	attributeConversionInfo;

	// data members
public:
	ElemDefaultReadConversionInfo ();
	ElemDefaultReadConversionInfo (const ElemDefaultReadConversionInfo& source);
	virtual ~ElemDefaultReadConversionInfo ();

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
	virtual GS::Object* Clone (void) const override;

	const AttributeConversionInfo&	GetAttributeConversionInfo (void) const { return attributeConversionInfo; }
	AttributeConversionInfo&		GetAttributeConversionInfo (void)		{ return attributeConversionInfo; }
};

// =============================================================================
// ElemDefaultWriteConversionInfo
//
// Use this class to give information to the old Write functions (ElemDefault)
// =============================================================================

class VBUTILS_DLL_EXPORT ElemDefaultWriteConversionInfo {

};


// =============================================================================	/* sm390 EDU */
// ReadConversionInfo
//
// Use this class to give information to the old Read functions
// =============================================================================

typedef GS::HashTable<ODB::ConstRef<ODB::Object>, ObjectConversionData*> ObjectConversionDataTable;
typedef GS::HashSet<ODB::ConstRef<ODB::Object> >	ObjectList;


class VBUTILS_DLL_EXPORT ReadConversionInfo {		// additional information block for reading old version
private:
	bool				layoutMerge;
	bool				frozen;
	short				parentType;
	Int32				actCamSetIdx;
	Int32				ownIndex;
	Int32				plVersion;
	EDB::IElemDatabase* readDatabase;
	EDB::Project*		readProject;
	bool				specialBaseOnSection;							// old specialOnSection in BaseType
	GS::HashTable<EDBAC17::DBUnId, short>*								oldSideWdIDs;		// Ebben azok a sideWdID-k vannak amiket 11 elotti file-ok S/E elemeibol olvas.
	GS::HashTable<ODB::Ref<ODB::Object>, short>*					derivedElems;
	GS::HashTable<GS::Guid, UIndex>*								oldDrawingOrder;
	ObjectConversionDataTable										objectConversionDataTable;
	AttributeConversionInfo											attributeConversionInfo;
	bool															convertWallConnPriority;
	Int32															wallConnPriority;
	GS::HashTable<ODB::ConstRef<ODB::Object>, VerticalLinkData>*	verticalLinksTable;

	Int32				currentPlanVersion;

public:
	ReadConversionInfo (Int32	currentPlanVersion);
   ~ReadConversionInfo ();

	void	SetLayoutMerge			(bool a)		{ layoutMerge = a;		}
	bool	IsLayoutMerge			(void) const	{ return layoutMerge;	}
	void	SetFrozen				(bool frzn)		{ frozen = frzn;		}
	bool	IsFrozen				(void) const	{ return frozen;		}
	void	SetParentType			(short p)		{ parentType = p;		}
	short	GetParentType			(void) const	{ return parentType;	}
	Int32	GetActCamSetIdx			(void) const	{ return actCamSetIdx;	}
	void	SetActCamSetIdx			(Int32 idx)		{ actCamSetIdx = idx;	}
	void	SetElemOwnIndex			(Int32 idx)		{ ownIndex = idx;	}
	Int32	GetElemOwnIndex			(void) const	{ return ownIndex;	}
	void	SetPlanVersion			(Int32 ver)		{ plVersion = ver;	}
	Int32	GetPlanVersion			(void) const	{ return plVersion;	}
	void	SetSpecialBaseOnSection	(bool b)		{ specialBaseOnSection = b;		}
	bool	GetSpecialBaseOnSection	(void) const	{ return specialBaseOnSection;	}

	GS::HashTable<EDBAC17::DBUnId, short>*	GetOldSideWdIDs (void) const	{return oldSideWdIDs; }
	void									SetOldSideWdIDs (GS::HashTable<EDBAC17::DBUnId, short>* hashTable)	{ oldSideWdIDs = hashTable; }

	GS::HashTable<ODB::Ref<ODB::Object>, short>*	GetDerivedElems (void)							{ return derivedElems; }
	void											SetDerivedElems (GS::HashTable<ODB::Ref<ODB::Object>, short>* _derivedElems)	{ derivedElems = _derivedElems; }

	GS::HashTable<GS::Guid, UIndex>*	GetOldDrawingOrder (void)												{ return oldDrawingOrder; }
	void								SetOldDrawingOrder (GS::HashTable<GS::Guid, UIndex>* _oldDrawingOrder)	{ oldDrawingOrder = _oldDrawingOrder; }

	ObjectConversionData*	GetObjectConversionData			(ODB::ConstRef<ODB::Object> object) const;
	void					AddObjectConversionData			(ODB::ConstRef<ODB::Object> object, ObjectConversionData* data);
	bool					ContainsObjectConversionData	(ODB::ConstRef<ODB::Object> object) const;

	GS::HashTable<ODB::ConstRef<ODB::Object>, VerticalLinkData>*	GetVerticalLinksTable (void)							{ return verticalLinksTable; }
	void					SetVerticalLinksTable (GS::HashTable<ODB::ConstRef<ODB::Object>, VerticalLinkData>* _verticalLinkTable)	{ verticalLinksTable = _verticalLinkTable; }

	EDB::IElemDatabase*		GetReadDatabase (void) const;
	EDB::Project*			GetReadProject	(void) const;
	void					SetReadDatabase (EDB::IElemDatabase* db);
	void					SetReadProject (EDB::Project* project);

	AttributeConversionInfo&		GetAttributeConversionInfo (void)		 { return attributeConversionInfo; }							
	const AttributeConversionInfo&	GetAttributeConversionInfo (void) const	 { return attributeConversionInfo; }							

	void					SetConvertWallConnPriority (void) { convertWallConnPriority = true; }
	bool					GetConvertWallConnPriority (void) { return convertWallConnPriority; }
	void					SetWallConnPriority (Int32 _wallConnPriority) { wallConnPriority = _wallConnPriority; }
	Int32					GetWallConnPriority (void) { return wallConnPriority; }

	Int32					GetCurrentPlanVersion (void) const { return currentPlanVersion; }
};		// ReadConversionInfo


enum MemoCheckResult {
	Ok,
	Modified,
	Deleted,
	Error
};

}	// namespace VBUtil

#endif
