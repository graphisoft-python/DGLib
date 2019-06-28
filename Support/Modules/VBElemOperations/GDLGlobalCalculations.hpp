// *********************************************************************************************************************
// Description:		GDL Global handling utilities
//
// Module:			VBElemOperations
// Namespace:
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GDLGLOBALOPERATIONS_HPP
#define	GDLGLOBALOPERATIONS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from GSUtils
#include	"GSUnID.hpp"

// from InputOutput
#include	"FileTypeManager.hpp"

// from Graphics
#include	"GSPix.h"

// from GDL
#include	"GDLDefs.h"
#include	"GDLbits.h"
#include	"SymbSect.h"
#include	"GDLParamInterface.hpp"

// from VectorImage
#include	"ProfileFillData.hpp"

// from ElementManager
#include	"EDBGeneralDefinitions.hpp"
#include	"ElementManagerTypes.hpp"
#include	"ProjectTypes.hpp"
#include	"VBElemSet/ElemSetType.hpp"

// from VBElements
#include	"VBElements/GDLBasedElemTypes.hpp"
#include	"VBElements/LabelTypes.hpp"
#include	"VBElements/OpeningTypes.hpp"
#include	"VBElements/WallOpeningTypes.hpp"
#include	"VBElements/WallTypes.hpp"
#include	"VBElements/ShellTypes.hpp"
#include	"VBElements/StairTypes.hpp"
#include	"VBElements/CrossSectType.hpp"
#include	"VBElements/NumFormat.hpp"

// from LibraryManager
#include	"LibrarySet.hpp"
#include	"FileServices.hpp"

// from VBCalculations
#include	"GDLGlobalCalculations.hpp"

// from VBElemOperations
#include	"CurrentStoryCutLevels.hpp"
#include	"LibraryMVOData.hpp"
#include	"StairModelViewOption.hpp"
#include	"RailingModelViewOption.hpp"
#include	"CurtainWallModelViewOption.hpp"

// from Phasing
#include	"PhasingTypes.hpp"

// from GSModeler
#include	"SunPosition.hpp"


#define	SkinDownPriorityCorr	10100
#define	SkinUpperPriorityCorr	20200
#define	SkinEmptyPriorityCorr	30300

// WDEXPR.H
#define EXPR_THICKGUSED		(1<<0) // Globals used in door/window thick expr
#define EXPR_INSETGUSED		(1<<1) // Globals used in door/window par. wall inset expr
#define EXPR_LFRAMGUSED		(1<<2) // Globals used in door/window wdLeftFram expr
#define EXPR_RFRAMGUSED		(1<<3) // Globals used in door/window wdRighFram expr
#define EXPR_TFRAMGUSED		(1<<4) // Globals used in door/window wdTopFram expr
#define EXPR_BFRAMGUSED		(1<<5) // Globals used in door/window wdBotFram expr
#define EXPR_THICK_STORED	(1<<6) // wdExprBits stored thick values
#define EXPR_INSET_STORED	(1<<7) // wdExprBits stored inset values
#define EXPR_LFRAM_STORED	(1<<8)  // wdExprBits stored left frame values	// FE #23919
#define EXPR_RFRAM_STORED	(1<<9)  // wdExprBits stored right frame values
#define EXPR_TFRAM_STORED	(1<<10) // wdExprBits stored top frame values
#define EXPR_BFRAM_STORED	(1<<11) // wdExprBits stored bottom frame values


class DetailHandler;

namespace LM {
	class LibPart;
	class LibrarySet;
}

namespace EDB {
	class DefaultElem;
	class IElemDefaults;
}

namespace VBElem {
	class WallDefault;
	class WallOpeningDefault;
	class OpeningDefault;
	class SkylightDefault;
	class GDLObjectDefault;
	class SectionBaseDefault;
	class LabelDefault;
	class RoomDefault;
}

namespace WM {
	class Window;
}

namespace ADB {
	class AttributeSet;
	typedef ODB::ConstRef<AttributeSet> AttributeSetConstRef;
}

namespace GDL {
	class ParamList;
}

namespace LPF {
	class SymbolFile;
}

namespace CompInfo {
	class CompositeInfo;
}

namespace VBCalculations {
	struct WallCutPlaneData;
}

class VectorImage;
struct Box2DData;
class LibPartHandlerRegistry;

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace VBCalculations {

struct CW2StructRec;

struct	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGlobalCalcEnvir
{
// private:
// 	GDLGlobalCalcEnvir (const GDLGlobalCalcEnvir&);
// 	GDLGlobalCalcEnvir& operator = (const GDLGlobalCalcEnvir& src);

public:
	EDB::ProjectConstRef			proj;
	Geometry::Vector2d				offset;

	const EDB::IElemDefaults*		currDef;

	double							listLayoutScale;
	double							dScaleLibrItem;
	double							spec_dScale;
	double							currEn_dScale;
	double							northDirection;
	double							longitude;
	double		    				latitude;
	double							altitude;

	// TODO: ezek kozul csak egy csoport kell!
	SunAngleSettings				plan3d_sunAngSets;
	double							plan3d_viewX;
	double							plan3d_viewY;
	double							plan3d_viewZ;
	double							plan3d_objX;
	double							plan3d_objY;
	double							plan3d_objZ;

	SunAngleSettings				symb3d_sunAngSets;
	double							symb3d_viewX;
	double							symb3d_viewY;
	double							symb3d_viewZ;
	double							symb3d_objX;
	double							symb3d_objY;
	double							symb3d_objZ;
	// -----------------------------------------

	GS_RGBColor						bkgColorRGB;
	EffectiveComposite::Structure	structure;

	FileServices*						fileServices;
	LM::LibrarySet::ThreadSafeModifier	librarySetTSModifier;
	const LibPartHandlerRegistry*		libPartHandlerRegistry;

	GS::UniString					archiCADLayerName;
	GS::UnID						wallEndID;
	GS::UnID						zoneStampID;
	GS::UnID						modelElemID;
	GS::UnID						wallDoorID;
	GS::UnID						wallWindowID;
	GS::UnID						lightID;
	GS::UnID						sectionMarkerID;
	GS::UnID						sectElevBaseMarkerID;
	GS::UnID						elevationMarkerID;
	GS::UnID						commonIntElevationMarkerID;
	GS::UnID						intElevationMarkerID;
	GS::UnID						detailMarkerID;
	GS::UnID						worksheetMarkerID;
	GS::UnID						changeMarkerID;
	GS::UnID						labelID;
	GS::UnID						roofOpeningID;
	GS::UnID						propertiesID;
	GS::UnID						libraryGlobalSettingsID;
	GS::UnID						wallExtraWindowID;
	GS::UnID						designStair2DComponentID;
	GS::UnID						pointCloudID;
	GS::UnID						pointCloudReplacementObjectID;
	GS::UnID						windowDoorSkylightMarkerID;
	GS::UnID						windowMarkerID;
	GS::UnID						doorMarkerID;
	GS::UnID						skylightMarkerID;

	GS::Array<GS::UnID>				all2DElementsSubTypeIDs;

	StairModelViewOption			stairMVO;
	RailingModelViewOption			railingMVO;
	GS::UnID						treadSchematicMVOID;
	GS::UnID						riserSchematicMVOID;
	CurtainWallModelViewOption		curtainWallMVO;

	FTM::GroupID					symbolFiles;
	FTM::TypeID						gdlFile;
	FTM::GroupID					allImgFiles;
	FTM::TypeID						listSetupFile;
	FTM::GroupID					allTextFiles;
	FTM::TypeID						binListCritFile;
	FTM::TypeID						iesFile;

	ADB::AttributeSetConstRef		attributes;

	GS::UniString					windRight;
	GS::UniString					windLeft;
	GS::UniString					doorRight;
	GS::UniString					doorLeft;

	FloorPlanCutLevels				floorPlanCutLevels;

	GS::Array<GS::Array<GS::UniString>>		globIssueScheme;
	GS::Array<GS::Array<GS::UniString>>		globChangeScheme;
	GS::Array<GS::Array<GS::UniString>>		layoutRevisionHistory;
	GS::Array<GS::Array<GS::UniString>>		layoutChangeHistory;
	bool									layoutCurrentRevisionOpen;

	short							emptyHatchIndex;
	short							solidHatchIndex;

	bool							pbcConversion;

	ConstLibraryMVODataContainerPtr	libraryMVODataContainer;

	GDLGlobalCalcEnvir (void);
	virtual ~GDLGlobalCalcEnvir ();

	bool EqualForDebug (const GDLGlobalCalcEnvir& rhs) const;
};



enum	VB_ELEM_OPERATIONS_DLL_EXPORT	CompResult {
	Comp_Invalid = 0,
	Comp_Invis   = 1,
	Comp_OK      = 2
};


enum	VB_ELEM_OPERATIONS_DLL_EXPORT	GlobalsMode { PlanMode, LibPartMode };


// --- Function declarations -------------------------------------------------------------------------------------------


void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetFloorGdlGlobals_NoLabels (	GSHandle						globHdl,
																		const LM::LibPart*				libPart,
																		short							idElem,
																		const EDB::GeneralElemConstRef&	elem,
																		GDL_ScriptType					scriptType,
																		GDLContext						context,
																		GlobalsMode						mode,
																		bool							setThickExpr,
																		bool							setInsetExpr,
																		bool							setFrameExpr,
																		const Int32*					globalsBits,
																		const GDLGlobalCalcEnvir&		gdlGlobals,
																		double							viewAngle = 0.0,
																		const EDB::DefaultElem*			slDat = nullptr,
																		short							labelParentIdElem = 0);

class VB_ELEM_OPERATIONS_DLL_EXPORT IGetWallDefault {
public:
	virtual const VBElem::WallDefault* operator () () = 0;
	virtual ~IGetWallDefault ();
};

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCutPlanesInfo (const EDB::GeneralElemConstRef&	elemPtr,
														  const GDLGlobalCalcEnvir&			gdlGlobals,
														  const VBElem::OpeningDefault*		wdDat,
														  const VBElem::GDLObjectDefault*	slDat,
														  IGetWallDefault*					getWallDef,
														  short								symbTyp,
														  double*							height,
														  double*							topLevel,
														  double*							botLevel,
														  double*							absolute);

void 	VB_ELEM_OPERATIONS_DLL_EXPORT	CalcHoleThickness (VBElem::WallConstRef pWall2, const VBElem::WallOpeningConstRef& pHole, const GDLGlobalCalcEnvir& gdlGlobals,
														   double *holeThick);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetWidoHeadHeight (const VBElem::WallOpeningConstRef& pHole,
														   const GDLGlobalCalcEnvir& gdlGlobals,
														   double *headHeight,
														   double *rSideHeadHeight,
														   double *oprSideHeadHeight);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetWidoOrientation (const VBElem::WallOpeningConstRef&	pHole, const LM::LibrarySet* librarySet,
															const GS::UniString& windowRightOrientation, const GS::UniString& windowLeftOrientation,
															const GS::UniString& doorRightOrientation, const GS::UniString& doorLeftOrientation,
															GS::UniString& widoOrientation);	/* Gdl_WIDO_ORIENTATION */

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_Inset (const LM::LibPart*					libPart,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  const VBElem::WallOpeningConstRef&	elem,
														  GSHandle								addParHdl,
														  double*								wdWallInset,
														  GDLContext							context,
														  GlobalsMode							mode);

GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_Frame (const LM::LibPart*					libPart,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  const VBElem::OpeningConstRef&		hole,
														  double*								wdLeftFram,
														  double*								wdRighFram,
														  double*								wdTopFram,
														  double*								wdBotFram,
														  GSHandle								addParHdl = nullptr,
														  GSHandle								globHdl = nullptr,
														  bool									forceRecalculate = false);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_Thick (const LM::LibPart*					libPart,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  const VBElem::WallOpeningConstRef&	elem,
														  GSHandle								addParHdl,
														  double*								wdMirThick);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_ThickByElem (const VBElem::WallOpeningConstRef&	elem,
															    const GDLGlobalCalcEnvir&	gdlGlobals,
																GSHandle					addParHdl,
																double*						wdMirThick);

GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_OpeningFrame (const VBElem::WallOpeningConstRef&	hole,
																 const GDLGlobalCalcEnvir&			gdlGlobals,
																 double*							wdLeftFram,
																 double*							wdRighFram,
																 double*							wdTopFram,
																 double*							wdBotFram);

VBElem::GDLBasedElemConstRef VB_ELEM_OPERATIONS_DLL_EXPORT GetGDLBasedElem (const EDB::GeneralElemConstRef& elem);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLParamWidthHeight (const LM::LibPart*				libPart,
																const GDLGlobalCalcEnvir&		gdlGlobals,
																const EDB::GeneralElemConstRef&	elem,
																double*							parWidth,
																double*							parHeight);


Int32	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLWallCrossSectType (CrossSectType vbElemCrossSectType);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLParamData (const LM::LibPart*					libPart,
														 const GDLGlobalCalcEnvir&			gdlGlobals,
														 const EDB::GeneralElemConstRef&	elem,
														 bool								isProp,
														 GSHandle*							addParHdl,
														 GS::UInt64*						transientId = nullptr,
														 double*							parA = nullptr,
														 double*							parB = nullptr);

Owner<GDLParam::ParamInterface> VB_ELEM_OPERATIONS_DLL_EXPORT CreateAddParInterface (const LM::LibPart*					libPart,
																					 const GDLGlobalCalcEnvir&			gdlGlobals,
																					 const EDB::GeneralElemConstRef&	elem,
																					 const GSHandle&					addParHdl);

VB_ELEM_OPERATIONS_DLL_EXPORT
const LM::LibPart*	GetEffectiveLibpart (const VBElem::GDLBasedElemConstRef& elem, const GDLGlobalCalcEnvir& gdlGlobals, const LM::LibrarySet* librarySet);

VB_ELEM_OPERATIONS_DLL_EXPORT
const LM::LibPart*	GetEffectiveProxyLibpart (const VBElem::GDLBasedElemConstRef& elem, const GDLGlobalCalcEnvir& gdlGlobals, const LM::LibrarySet* librarySet);

VB_ELEM_OPERATIONS_DLL_EXPORT
bool				LibPartOverrideInEffect (const VBElem::GDLBasedElemConstRef& elem, const GDLGlobalCalcEnvir& gdlGlobals);


bool	VB_ELEM_OPERATIONS_DLL_EXPORT	SetActualAddPars (const LM::LibPart*					libPart,
														  const LM::LibPart*					origLibPart,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  VBElem::GDLBasedElemConstRef	gdlElem,
														  GSHandle*						addParHdl,
														  bool*							isReplaced = nullptr,
														  double*						defparA = nullptr,
														  double*						defparB = nullptr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCompositeValues (const GDLGlobalCalcEnvir&				gdlGlobals,
															 short cPat, GS::UniString*		compositeName,
															 short*							nSkins,
															 double*						skinspars,
															 GS::UniChar::Layout**			skins_bmat_names,
															 bool							useCompContourLineTypePen,
															 short							cutContourLinePen,
															 short							cutContourLineType,
															 bool							useCompInnerLineTypePen,
															 short							cutInnerLinePen,
															 short							cutInnerLineType,
															 bool							useCompFillPen,
															 short							cutFillPen,
															 bool							useCompBackgroundPen,
															 short							cutFillBackgroundPen,
															 short							buildingMaterialIndex,
															 bool							useCompSkinSurfaceIndex,
															 short							surfaceIndex,
															 bool							rotSkins,
															 double							thickness);

GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	CalculateShellBaseGlobals (const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals,
																   VBElem::ShellBaseConstRef	shellBase,
																   GS::UniString*				compositName,
																   short*						nSkins,
																   double*						skinspars);

enum InfoBitsMode {
	EmptyGlobalsBitsForVarMacro,
	FillGlobalsBitsForVarmacro
};

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_GetLPGdlInfoBits (GDL::IFileRef*											fileRef,
																	const GDLGlobalCalcEnvir&								gdlGlobals,
																	const LM::LibPart*										libPart,
																	GDL_ScriptType											scriptType,
																	GdlInfoBits*											infoBits,
																	InfoBitsMode											infoBitsMode = EmptyGlobalsBitsForVarMacro,
																	GS::HashSet<GS::Pair<GS::Int32, GS::UniString> >*		requestIDs = nullptr,
																	GS::HashSet<GS::UniString>*								applicationQueryNames = nullptr);


short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetLibPartType (const LM::LibPart* libPart, const GDLGlobalCalcEnvir& gdlGlobals, bool *isText = nullptr);
short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolType_OBSOLETE (const LM::LibPart* libPart, const GDLGlobalCalcEnvir& gdlGlobals, bool *isText = nullptr);

EDB::Tool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetToolFromLibItem (const LM::LibPart* libPart, short idElem, const GDLGlobalCalcEnvir& gdlGlobals);

enum class SkinMergeMode {
	ForScreenDisplay,
	Disabled
};


class VB_ELEM_OPERATIONS_DLL_EXPORT WallSkinMergeStrategy {
public:
	virtual ~WallSkinMergeStrategy ();

	virtual void MergeWallSkins (CW2StructRec* a_plCW2, VBElem::WallConstRef pWall) const = 0;
};

typedef GS::Ref<const WallSkinMergeStrategy> WallSkinMergeStrategyConstRef;


class VB_ELEM_OPERATIONS_DLL_EXPORT WallSkinMergeStrategyFactory {
public:
	enum KeepSkinsT { KeepSkins };

public:
	WallSkinMergeStrategyFactory (KeepSkinsT);
	WallSkinMergeStrategyFactory (bool nOnlyCalc, SkinMergeMode skinMergeMode, const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (bool nOnlyCalc, const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (SkinMergeMode skinMergeMode, const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (SkinMergeMode skinMergeMode, WallSkinMergeStrategyConstRef skinMergeStrategy);

	WallSkinMergeStrategyConstRef GetStrategy () const;
private:
	const WallSkinMergeStrategyConstRef strategy;
};


CompResult	VB_ELEM_OPERATIONS_DLL_EXPORT	MakeWall2PatStruct (const GDLGlobalCalcEnvir&			   gdlGlobals,
																short								   showElemFloor,
																VBCalculations::WallCutPlaneData*	   wCutPlane,
																const bool							   checkWall,
																VBElem::WallConstRef				   pWall,
																CW2StructRec*						   a_plCW2,
																bool								   ghostColor,
																bool								   turnFl,
																bool								   normalTurn,
																WallSkinMergeStrategyConstRef		   skinMergeStrategy,
																Phasing::RenovationStatusType		   wallStatus,
																EffectiveComposite::Structure		   structureDisplay,
																Geometry::IrregularPolygon2D&		   poly);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetWallDefault_Globals (const GDLGlobalCalcEnvir&			gdlGlobals,
																GSHandle							globHdl,
																Int32								globInd,
																IGetWallDefault*					getWallDef,
																const VBElem::WallOpeningDefault*	wdDat = nullptr,
																bool								isWallEnd = false);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetSymbDefault_Globals (GSHandle						globHdl,
																const GDLGlobalCalcEnvir&		gdlGlobals,
																Int32							globInd,
																const EDB::Tool&				tool,
																short							symbTyp,
																const VBElem::OpeningDefault*	wdDat,
																const EDB::DefaultElem*			slDat,
																bool							storyMarker);

 void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetGdlGlobal_NoLabel (GSHandle							globHdl,
															  Int32								globInd,
															  short								symbTyp,
															  const LM::LibPart*				libPart,
															  short								idElem,
															  const EDB::GeneralElemConstRef&	elem,
															  double*							framData,
															  const VBElem::OpeningDefault*		wdDat,
															  const EDB::DefaultElem*			slDat,
															  GDL_ScriptType					scriptType,
															  GDLContext						context,
															  GlobalsMode						mode,
															  short								frameInd,
															  bool								setThickExpr,
															  bool								setInsetExpr,
															  bool								setFrameExpr,
															  EDB::GeneralElemConstRef			owner,
															  bool								placedElem,
															  const GDLGlobalCalcEnvir&			gdlGlobals,
															  IGetWallDefault*					getWallDef,
															  double							viewAngle = 0.0,
															  short								labelParentIdElem = 0,
															  bool								storyMarker = false,
															  EDB::Tool*						actualTool = nullptr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetGlob_Global (GSHandle						globHdl,
														Int32							globInd,
														short							idElem,
														const EDB::GeneralElemConstRef&	elem,
														const VBElem::OpeningDefault*	wdDat,
														const VBElem::GDLObjectDefault*	slDat,
														IGetWallDefault*				getWallDef,
														short							symbTyp,
														GDL_ScriptType					scriptType,
														GDLContext						context,
														GlobalsMode						mode,
														short							frameInd,
														short							labelParentIdElem,
														const GDLGlobalCalcEnvir&		gdlGlobals);


// --- Functions NOT using GDLGlobalCalcEnvir --------------------------------------------------------------------------


GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	ClearGdlGlobals (GSHandle globHdl);

short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCW55SidePat (const ADB::AttributeSetConstRef&	attributes,
														short								wPat,
														bool								firstPat);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	CalcWallResolution (VBElem::WallConstRef pWall,
															double *refRadius,
															short *resolution);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	ConvertDefaultToFixHeight (EDB::DefaultElem* defElem, EDB::FloorStructureConstRef floorStructure);

Int32	VB_ELEM_OPERATIONS_DLL_EXPORT	SetFontStyle2GlobalValue (unsigned char wordFace, Int32 wordEffects);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	ExplodeFontStyleFromGlobalValue (Int32 gdlStyleValue, unsigned char& wordFaceOut, Int32& wordEffectsOut);


EDB::GeneralElemConstRef	VB_ELEM_OPERATIONS_DLL_EXPORT	GetLabeledElem (VBElem::LabelConstRef label, short *idBaseElem = nullptr);

GSErr		VB_ELEM_OPERATIONS_DLL_EXPORT	InitGDLGlobalOperations (void);
void		VB_ELEM_OPERATIONS_DLL_EXPORT	ExitGDLGlobalOperations (void);
GSErr		VB_ELEM_OPERATIONS_DLL_EXPORT	InitGdlGlobals (GSHandle* globHdl);
void		VB_ELEM_OPERATIONS_DLL_EXPORT	InitGdlGlobalsFor3D (GDL::ParamList& gdlGlobs);
GSHandle	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGdlUserGlobals (void);

class VB_ELEM_OPERATIONS_DLL_EXPORT CopyOfGSHandle
{
private:
	GSHandle handle;
public:
	CopyOfGSHandle (GSConstHandle inHandle);
	~CopyOfGSHandle ();

	GSHandle GetHandle (void);
};

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolParametersRef (const LM::LibPart& libPart, GSConstHandle* result);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	CreateDefaultSyParHandle (const GS::UnID&		parentLPFUnID,
																	  const LM::LibrarySet*	librarySet,
																	  GSHandle*		defaultSyParHandle);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetDefaultAddPar (const LM::LibPart* libPart, short symbolType, GSHandle* addParHdl,
														  GS::UnID zoneStampID,
														  GS::UnID modelElemID,
														  const LM::LibrarySet* librarySet);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetDefaultParamsOfMacro (const IO::Location*	fileLoc,
																	 const LM::LibPart*		libPart,
																	 const LM::LibrarySet*	librarySet,
																	 const GS::UnID&		zoneStampID,
																	 const GS::UnID&		modelElemID,
																	 const FTM::TypeID&		gdlFileType,
																	 const FTM::GroupID&	allImgFileType,
																	 GSHandle*				addParHdl);

GSErrCode VB_ELEM_OPERATIONS_DLL_EXPORT GetAddParData (const IO::Location*							fileLoc,
													   const LM::LibPart*							libPart,
													   const LM::LibrarySet::ThreadSafeModifier&	librarySetModifier,
													   const GS::UnID&								zoneStampID,
													   const GS::UnID&								modelElemID,
													   const FTM::TypeID&							gdlFileType,
													   const FTM::GroupID&							allImgFileType,
													   ConstGDLAddParDataPtr&						gdlAddParData);


GDLContext	VB_ELEM_OPERATIONS_DLL_EXPORT	ElemSetToContext (const VBES::ElemSetConstRef& elemSet);
GlobalsMode	VB_ELEM_OPERATIONS_DLL_EXPORT	ElemSetToGlobalsMode (const VBES::ElemSetConstRef& elemSet);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetWDOrientDisp (const LM::LibPart*	libPart,
														 OrientDispRec*		odr);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	SymbolUseScript (const LM::LibPart* libPart, GDL_ScriptType scriptType, const LM::LibrarySet::IThreadSafeModifier& librarySetTSModifier);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetFullGdlScriptHdl (const LPF::SymbolFile& symFile, UInt32 sectType, GSHandle* pFullScript);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSySection (const LM::LibPart*		libPart,
														  UInt32			sectType,
														  unsigned short	subIdent,
														  GSHandle*			sectData);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_GetDefaultObj_Hdls (GSConstHandle*			def_ParHdl,
																  GS::UnID					id,
																  const LM::LibrarySet*		librarySet);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_GetDefaultRoom_Hdls (GSConstHandle*			def_ParHdl,
																   GS::UnID					id,
																   const LM::LibrarySet*	librarySet);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_FreeDefaultObjPar_Hdls (void);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolComponentsRef	(const LM::LibPart* libPart, GSConstHandle* result);
GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolBinary2dRef	(const LM::LibPart* libPart, VectorImage* image, bool* sectionFound = nullptr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolHdl_EqBox (const LM::LibPart*		libPart,
															Box2DData*				syBox);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	CalcSwTill (double			thick,
													CW2StructRec*	a_plCW2);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	TurnSWWall2 (CW2StructRec*	a_plCW2);


void	VB_ELEM_OPERATIONS_DLL_EXPORT	MaskGlobalBitGroups (Int32 *globalsBits);



bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetMacroFile (const LM::LibrarySet* librarySet, const GS::UnID& unID, const GS::UniString& symbName, IO::Location* macroLoc, const LM::LibPart** libPart,
													  bool* message, bool compatibilityMode = false, bool dontCacheMissingMacros = false);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetMacroFile (const LM::LibrarySet::IThreadSafeModifier& librarySetTSModifier, const GS::UniString& symbName, const IO::Location& callerLoc, const LM::LibPart* callerFileLibPart,
													  IO::Location* macroLoc, const LM::LibPart** libPart, bool* message, GS::UnID* foundUnID = nullptr,
													  bool dontCacheMissingMacros = false);


void	VB_ELEM_OPERATIONS_DLL_EXPORT	ResetMissingMacros (bool enabled);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetLibraryGlobalRefs (const GDLGlobalCalcEnvir& gdlGlobals, GSConstHandle globHdl, const LM::LibPart* libPart, GDL::IFileRef* fileRef,
															  GDL_ScriptType scriptType, GS::HashSet<LM::LibPartId>& libraryGlobalRefs);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetExpressionGlobalsBits (const LM::LibPart* libPart, const GDLGlobalCalcEnvir& gdlGolbalCalcEnvir, Int32 *pExprGlobalsBits);

short	VB_ELEM_OPERATIONS_DLL_EXPORT	ElemId_To_GDLEltype (short idElem);

VB_ELEM_OPERATIONS_DLL_EXPORT
GSErrCode WriteLibraryGlobalsChecksum (GS::OChannel& oc,
									   const LM::LibPart* libPart,
									   GDL::IFileRef* fileRef,
									   const GDLGlobalCalcEnvir& gdlGlobalCalcEnv,
									   const GS::Array<LibraryMVOData>& datas,
									   GDL_ScriptType	scriptType);

short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCalcStoryNumber (VBElem::WallOpeningConstRef opening,
															const EDB::FloorStructureConstRef& floorStructure,
															VBCalculations::GDLGlobalCalcEnvir* gdlGlobals = nullptr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailingPostDefaultGlobals (GSHandle gdlGlobals, GSType typeId);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailingPanelDefaultGlobals (GSHandle gdlGlobals);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailDefaultGlobals (GSHandle gdlGlobals, GSType typeId);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailingFinishGDLObjectDefaultGlobals (GSHandle gdlGlobals, GSType connectedRailTypeId);
}	// namespace VBCalculations

#endif	//GDLGLOBALOPERATIONS_HPP
