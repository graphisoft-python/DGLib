// *****************************************************************************
// Composite Info for elem connections
//
// Namespaces:			Contact person:
//		CompInfo			PT
//
// [SG compatible]
// *****************************************************************************

#if !defined (COMPOSITEINFO_HPP)
#define COMPOSITEINFO_HPP

#include	"Array.hpp"
#include	"CurrentStoryCutLevels.hpp"
#include	"ProfileFillData.hpp"
#include	"attributeset.hpp"
#include	"BuildingMaterial.hpp"
#include	"compwall.hpp"

#include	"VBElemOperationsExport.hpp"


#define		MaxComp		127

class StructureDisplay;

namespace CompInfo {

class SkinFaceLine {
private:
	short	lineType;	// line type index of the skin face line
	short	pen;		// pen index of the skin face line
	bool	skip;		// skip this line

public:
	SkinFaceLine ();
	SkinFaceLine (short	inLineType, short inPen, bool toSkip = false);

	inline	short	GetLineTypeIndex (void) const	{ return lineType;	}
	inline	short	GetPenIndex (void) const		{ return pen;		}
	inline	bool	IsLineToSkip (void) const		{ return skip;		}

	void			SetLineTypeIndex (short newLineType);
	void			SetPenIndex (short newPen);
	void			SetToSkip (bool toSkip);
};


enum SkinFlags {
	SFHatchAngle	= 1,
	SFCore			= 2,
	SFFinish		= 32,
	SFHatchFit		= 64
};


enum SkinType {
	Skin_Normal = 0,
	Skin_Upper  = 1,
	Skin_Down   = 2,
	Skin_Empty	= 3
};


class Skin {
private:
	CutSurface		cutSurface;
	short			endLinePen;		// Index of the outside frame pen
	short			endLineType;	// Index of the outside frame linetype
	short			flagBits;		// skin flags
	double			fillThick;		// absolute thickness of the skin in m
	Int32			connPriority;	// skin connection priority
	SkinType		skinType;		// Skin_Normal, Skin_Upper, Skin_Down, Skin_Empty

public:
	Skin ();
	Skin	(VBAttr::BuildingMaterialConstRef buildMatRef,
			 const VBAttr::OverriddenPen& inFillPen,
			 const VBAttr::OverriddenPen& inFillBkgPen,
			 short inEndLinePen, short inEndLineType,
			 short inFlagBits, double inFillThick, Int32 inConnPriority, SkinType inSkinType);

	Skin (
		const CutSurface & cutSurface_init,
		short inEndLinePen, short inEndLineType,
		short inFlagBits, double inFillThick, Int32 inConnPriority, CompInfo::SkinType inSkinType);

	inline	short		GetPatternIndex (void) const		{ return cutSurface.GetFillIndex ();				}
	inline	short		GetBuildMatIndex (void) const		{ return cutSurface.GetBuildingMaterialIndex ();	}
	inline	void		GetCutSurface (CutSurface& actCutSurface) const		{ actCutSurface = cutSurface;		}
	inline	short		GetEndFacePenIndex (void) const 	{ return endLinePen;	}
	inline	short		GetEndFaceLTIndex (void) const 		{ return endLineType;	}
	inline	short		GetFlags (void) const				{ return flagBits;		}
	inline	double		GetFillThickness (void) const		{ return fillThick;		}
	inline	Int32		GetConnPriority (void) const		{ return connPriority;	}
	inline	SkinType	GetSkinType (void) const			{ return skinType;		}

	inline	VBAttr::OverriddenExtendedPen	GetFillExtendedPen (void) const		{ return cutSurface.GetOverridenFgExtendedPen ();	}
	inline	VBAttr::OverriddenPen			GetFillBGPenIndex (void) const		{ return cutSurface.GetOverridenBkgPen ();	}

	inline	bool	IsCoreSkin		 (void) const		{ return (flagBits & SFCore) > 0; }
	inline	bool	IsHatchAngleSkin (void) const		{ return (flagBits & SFHatchAngle) > 0; }
	inline	bool	IsFinishSkin	 (void) const		{ return (flagBits & SFFinish) > 0; }
	inline	bool	IsHatchFitSkin	 (void) const		{ return (flagBits & SFHatchFit) > 0; }

	inline	bool	IsSkinNormal (void) const			{ return (skinType == CompInfo::Skin_Normal);	}
	inline	bool	IsSkinUpper (void) const			{ return (skinType == CompInfo::Skin_Upper);	}
	inline	bool	IsSkinDown (void) const				{ return (skinType == CompInfo::Skin_Down);	}
	inline	bool	IsSkinEmpty (void) const			{ return (skinType == CompInfo::Skin_Empty);	}

	inline	bool	HasProperty (short feature) const	{ return (flagBits & feature) > 0; }

	void			SetEndFacePenIndex (short newEndFacePenIndex);
	void			SetEndFaceLTIndex (short newEndFaceLTIndex);
	void			SetFillFgExtendedPenIndex (const VBAttr::ExtendedPen& newFillPenIndex);
	void			SetFillBGPenIndex (short newFillBGPenIndex);
	void			SetFlags (short newFlags);
	void			SetFillThickness (double newFillThickness);
	void			SetConnPriority (Int32 newConnPriority);
	void			SetSkinType (SkinType newSkinType);
	void			SetOpaqueCutFill ();
};


class VB_ELEM_OPERATIONS_DLL_EXPORT CompositeInfo {
private:
	double					totalThick;				// thickness of the whole wall
	double					maxX;					// min X of the first skin
	short					nSkins;					// number of skins
	GS::Array<Skin>			skins;					// skin array
	GS::Array<SkinFaceLine>	skinFaceLines;			// skin face line array

public:
	CompositeInfo ();

	CompositeInfo (
		const VBAttr::CompWallConstRef& compWall,
		const VBAttr::OverriddenPen& fillPen,
		const VBAttr::OverriddenPen& fillBkgPen);
	
	CompositeInfo (
		const VBElem::WallConstRef& pWall,
		const VBCalculations::CurrentStoryCutLevels& floorCut,
		const VBElem::ElemDisplayOptions& displayOption,
		const VBElem::ElemViewDepthLimitations& viewDepth,
		const EffectiveComposite::Structure& structureDisplay,
		double relLevel);

	CompositeInfo (const CompositeInfo&);

	inline	double				GetTotalThickness (void) const		{ return totalThick;	}
	inline	double				GetMaxX (void) const				{ return maxX;			}
	inline	short				GetSkinNumber (void) const			{ return nSkins;		}
	inline	short				GetSkinFaceLineNumber (void) const	{ return nSkins + 1;	}

	const Skin*					GetSkin (short skinNumber) const;
	const SkinFaceLine*			GetSkinFaceLine (short skinFaceLineNumber) const;

	Skin*						GetSkin (short skinNumber);
	SkinFaceLine*				GetSkinFaceLine (short skinFaceLineNumber);

	CompositeInfo&				operator = (const CompositeInfo&);
};

}		// namespace CompInfo

bool IsTransparentInCutPlane (VBAttr::BuildingMaterialConstRef & buildMatRef, const CutSurface & cutSurf);

#endif		// COMPOSITEINFO_HPP
