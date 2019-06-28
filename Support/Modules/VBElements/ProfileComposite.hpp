// *********************************************************************************************************************
// Description:		ProfileComposite wrapper class
//
// Module:			VBElements
// Namespace:		TPL
// Contact person:	PT, FGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PROFILECOMPOSITE_HPP)
#define PROFILECOMPOSITE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "Array.hpp"

// from Geometry
#include	"basicgeometry.h"

// from VBAttributes
#include "profileAttrTypes.hpp"

// from VBElements
#include	"VBElementsEnv.hpp"
#include	"ProfileFillData.hpp"

#include	"EffectiveComposite.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------


class ProfileVectorImage;
class IUsedAttrCollection;
class Sy_HotType;
class Sy_LinType;
class Sy_ArcType;
class Sy_SplineType;
class Sy_PixMapType;
class Sy_RichTextType;


namespace ADB {
	class IAttributeNewIndexTable;
}


namespace PVI {
	class StretchData;
}


// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

struct StretchZone {
	double	min;
	Sector	minLine;
	double	max;
	Sector	maxLine;
};

struct VBELEMENTS_DLL_EXPORT StretchZones {

	enum OrigoHorizontalPosition {
		Horizontal_Invalid,
		Outside_Left,
		Outside_Right,
		OnBoundary_Left,
		OnBoundary_Right,
		Horizontal_Inside
	};

	enum OrigoVerticalPosition {
		Vertical_Invalid,
		Outside_Bottom,
		Outside_Top,
		OnBoundary_Bottom,
		OnBoundary_Top,
		Vertical_Inside
	};

	struct OrigoPosition {
		OrigoHorizontalPosition		horizontal;
		OrigoVerticalPosition		vertical;
	};

	StretchZone		horizontal;
	StretchZone		vertical;

	StretchZones () { Clear (); }

	void	Clear (void);
	void	ClearVertical (void);
	void	ClearHorizontal (void);
	void	Print (void) const;

	bool	HasHorizontalZone (void) const { return Geometry::IsLessOrNear (horizontal.min, horizontal.max); }
	bool	HasVerticalZone (void) const { return Geometry::IsLessOrNear (vertical.min, vertical.max); }

	OrigoPosition	GetOrigoPosition (void) const;
};


class VBELEMENTS_DLL_EXPORT VectorImagePlaceholder {
private:
	ProfileVectorImage*		m_Image;
public:

	VectorImagePlaceholder ();
	VectorImagePlaceholder (const VectorImagePlaceholder& source);
	VectorImagePlaceholder (const ProfileVectorImage& profileImageIn);
	~VectorImagePlaceholder ();
	VectorImagePlaceholder& operator= (const VectorImagePlaceholder& source);

	bool IsVectorImageConstructed () const;
	void DestructVectorImage ();
	const ProfileVectorImage& GetProfileImage () const;
	ProfileVectorImage& GetConstructedProfileImage ();
};


class VBELEMENTS_DLL_EXPORT ProfileComposite
{
public:
	enum FixMode {
		Normal = 0,
		DelStretchLines = 1,
		DelOpeningLines = 2,
		DelHotSpots = 3,
		FixStretchLines = 4
	};

	enum LineRole {
		WindowLine		= 0,
		HelperLine		= 2,
		HStretchLine	= 3,
		VStretchLine	= 4
	};

	struct OrigProfileSkin {
		short		priority;
		CutSurface	cutSurface;
		short		skinFlags;
		short		contourPenIndex;
		bool		globalFillOrient;
	};

	struct CrossSectSkin {
		double		xBeg, xEnd;
		double		width;
		short		priority;
		CutSurface	cutSurface;
		short		skinFlags;
		short		upperLinePenIndex;
		short		lowerLinePenIndex;
		short		upperLineType;
		short		lowerLineType;
		short		endFacePenIndex;
		bool		globalFillOrient;
	};

	struct TransformData {
		double	width;
		double	height;
		double	angle;
		bool	mirrorX;
		bool	mirrorY;
	};

private:

	VectorImagePlaceholder	profileImagePlaceholder;

public:
				ProfileComposite ();
				ProfileComposite (const ProfileVectorImage& profileImageIn);
				ProfileComposite (VBAttr::ProfileConstRef& profile);
				~ProfileComposite (void);

	bool		IsValid () const;
	void		MakeInvalid ();

	const		ProfileVectorImage&	GetProfileVectorImageConstRef () const;
	void		Set (const ProfileVectorImage& profileImageIn);
	void		Clear ();
	void		ReindAttr	(ADB::IAttributeNewIndexTable* newIndexTable);
	void		CollectUsedAttrsOfProfile (IUsedAttrCollection& usedAttrCollection) const;
	bool		HasMarkedAttribute (ADB::IAttributeSelTable* attrIndexTbl, GS::HashSet<ADB::IDAttribute>* markedAttributes);

	short		GetHighestCorePriority (ADB::AttributeSetConstRef	attrSet) const;

	Box2DData	GetBuildingBounds (void) const;
	Box2DData	GetWholeBounds (void) const;

	void		GetPolygons (const ADB::AttributeSetConstRef&					attributeSet,
							 ProfileMultiPolygon*					polys,
							 EffectiveComposite::Structure			structure = EffectiveComposite::EntireStructure) const;

	bool		GetCrossSectionParameters (ADB::AttributeSetConstRef	attrSet,
											double						height,
											double						position,
											double						slantAngle,
											double*						minimalX,
											double*						maximalX,
											double*						crossSectionWidth,
											GS::Array<CrossSectSkin>*	crossSectionParams) const;
	bool		GetAllSkinsParameters (ADB::AttributeSetConstRef						attrSet,
										GS::Array<ProfileComposite::OrigProfileSkin>*	skinsParams,
									   EffectiveComposite::Structure					structure = EffectiveComposite::EntireStructure) const;
	void		GetStretchZones (StretchZones* stretchZones) const;
	void		SetStretchZones (const PVI::StretchData& stretchData);
	ULong		GetNumberOfProfileComponents (void) const;

	GS::Array<const HatchObject*>	GetProfileComponent (short componentIndex) const;
	short							GetProfileComponentBuildMatIdx (short componentIndex) const;
	void							Offset (const Vector& offsetVector);
	
	void		AddHotspot (const Sy_HotType& syHotspot);
	void		AddHotspot (double x, double y, UIndex unIdInProfile, short subtype = 0);

	void		AddLine (const Sy_LinType& syLine);
	void		AddLine (LineRole role, const Coord& begC, const Coord& endC);
	void		AddLine (LineRole role, double xBeg, double yBeg, double xEnd, double yEnd);

	void		AddArc (const Sy_ArcType& syArc);

	void		AddSpline (
						const Sy_SplineType& spline,
						const GSConstPtr	pCoordPtr,
						const GSConstPtr	pSDirsPtr);


	void		AddHatch (const ProfilePolygon& poly);	// throws exception

	void		AddHatch (bool									contVis,
						  short									contPen,
						  short									contLTyp,
						  short									buildingMaterialIdx,
						  const VBAttr::OverriddenExtendedPen&	fillPen,
						  const VBAttr::OverriddenPen&			bkgPen,
						  short									fillind,
						  Int32									npb,
						  const UInt32*							contourEnds,
						  Int32									npc,
						  const Coord*							coords,
						  const double*							angles,
						  bool									globalOffset,
						  const GSHandle						addInfo);

	void		AddPixMap (
						const Sy_PixMapType&	syPixmap,
						GSHandle				pixMemoHdl,
						const char*				mimeType = nullptr);

	void		AddRichText (
						const Sy_RichTextType&	syRichText);

static GSErrCode	HatchToPoly (const UIndex hatchIndex_init, const Sy_HatchType& syHatchRef, const HatchObject& hatchPtr, const ADB::AttributeSetConstRef& attributeSet, ProfilePolygon* poly);

static void			Resize (
						const ProfileComposite&	origProfile,
						const ADB::AttributeSetConstRef&	attributeSet,
						ProfileComposite* 		resultProfile,
						double 					newWidth,
						double 					newHeight);

static void			Rotate (const ProfileComposite& src,
							ProfileComposite* dst,
							double angle);

static void			Transform (ADB::AttributeSetConstRef attrSet,
								const ProfileComposite& src,
							   ProfileComposite* dst,
							   const TransformData* transform);

static void			FixProfile (const ProfileComposite& multiProfile, const ADB::AttributeSetConstRef& attributeSet, ProfileComposite& result, short fixMode = Normal, bool* isChanged = nullptr);

#ifdef DEBUVERS
static void			DumpGDLProfileComposite (const ADB::AttributeSetConstRef attrSet, const ProfileComposite* profCompPtr);
#endif

};


#endif
