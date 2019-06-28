// *********************************************************************************************************************
// Description:		QuantityTakeoff common utility functions
//
// Module:			QuantityTakeoff
// Namespace:
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef QUANTITYCALCULATOR_HPP
#define QUANTITYCALCULATOR_HPP

#define LISTTEXTLEN	256

// from GDL
#include	"GDL.h"
#include	"GDLbits.h"
#include	"GDLGres.h"
#include	"GDLProc.h"

// from VBElements
#include	"VBElements/RoomTypes.hpp"
#include	"VBElements/RailingSegmentTypes.hpp"

// from VBTo3DConverter
#include	"ElemListSEOConverter.hpp"
#include	"ModelUpdater.hpp"
#include	"VBTo3D.hpp"

// from VBElemOperations
#include	"WallFloorPlanCalculations.hpp"

// from ModelCalculations
#include	"ModelCalculationsDefinitions.hpp"

// from QuantityTakeoff
#include	"QuantityTakeoffMain.hpp"
#include	"QuantityTakeoffExport.hpp"
#include	"CalculationRules.hpp"
#include	"QuantityTakeoffTypes.hpp"

//======================================================================================================================
//											structs to replace API structures
//======================================================================================================================

struct QT_RoofQuantity {
	double							bottomSurface;
	double							topSurface;
	double							edgeSurface;
	double							bottomSurface_cond;
	double							topSurface_cond;
	double							volume;
	double							volume_cond;
	double							perimeter;
	double							holesSurf;
	double							holesPrm;
	double							grossBotSurf;
	double							grossTopSurf;
	double							grossEdgeSurf;
	double							contourArea;
	double							grossVolume;
	double							insuThickness;
	double							ridgesLength;
	double							valleysLength;
	double							gablesLength;
	double							hipsLength;
	double							eavesLength;
	double							peaksLength;
	double							sideWallConLength;
	double							endWallConLength;
	double							domeConLength;
	double							hollowConLength;
	double							openingSurf;
	Int32							numOfHoles;
	Int32							numOfSkylight;
	Int32							filler_1;
	Int32							filler_2;
};

struct QT_MorphQuantity {
	double							surface;
	double							volume;
	double							floorPlanArea;
	double							floorPlanPerimeter;
	double							baseLevel;
	double							baseHeight;
	double							wholeHeight;
	UInt32							nodesNr;
	UInt32							edgesNr;
	UInt32							hiddenEdgesNr;
	UInt32							softEdgesNr;
	UInt32							visibleEdgesNr;
	UInt32							facesNr;
	double							filler_1[8];
};

struct QT_CompositeQuantity {
	double							volumes;
	double							projectedArea;
	short							buildMatIndices;
	short							flags;
	Int32							filler_1;
};

struct QT_ElemPartId {
	UInt32							main;
	UInt32							sub;
	Int32							floor;

	QT_ElemPartId () : main (0), sub (0), floor (0) {}
	bool	operator==	(const QT_ElemPartId& right) const		{ return (main == right.main && sub == right.sub && floor == right.floor); }
	bool	operator!=	(const QT_ElemPartId& right) const		{ return !operator== (right); }
	operator GS::HashValue () const	{ return (main ^ sub) + floor * 65599; }
};

union QT_ElementQuantity {
	QT_RoofQuantity		roof;
	QT_MorphQuantity	morph;
	char				filler[1160];	// The size of the biggest API_ElementQuantity, to make sure memcpy in ListSel wont fail.
};

//======================================================================================================================
//												  CONV2LISTREC factory
//======================================================================================================================

enum CalculationModelType {
	NormalFinalModel,
	DetailedFinalModel
};

QUANTITYTAKEOFF_DLL_EXPORT
CONV2LISTREC	CreateListParams (CalculationModelType calculationModelType);

//======================================================================================================================
//												Utility function prototypes
//======================================================================================================================

const LM::LibPart*	GetLibPart (VBElem::GDLBasedElemConstRef gdlElem, const LM::LibrarySet* librarySet);

void		CutOneElem (GS::ProcessControl&				processControl,
						Modeler::ConstElemPtr			elem,
						const GS::Array<CUT_RECORD>		&cutrecs,
						Modeler::ConstElemPtr			&cutElem,
						Modeler::Attributes::Modifier	&attrModifier);

void		GetProfileSkinParams (	GS::ProcessControl&				processControl,
									Modeler::ConstElemPtr			elem,
									Modeler::Attributes::Modifier	&attrModifier,
									const ProfileVectorImage		&profileImage,
									const PlaneEq					&plane,
									const Vector3D					&dir,
									const TRANMAT					&tm,
									Int32							*skinNumber,
									short							**skinBuildMatIndices,
									double							**skinVolumes,
									short							**skinFlags);

Modeler::ConstElemPtr	GetPolyRoofSinglePlanes (GS::ProcessControl&	processControl,
												 const Modeler::Elem&	fullRoof,
												 Modeler::AttributesPtr	attribs,
												 Modeler::ConstElemPtr	perBodyElem,
												 const LM::LibrarySet*	librarySet,
												 bool					separateComponents = false);

QT_ElementQuantity*	GetPolyRoofQuantity (const Modeler::MeshBody& body, GS::HashTable<QT_ElemPartId, QT_ElementQuantity>& quantitiesTable);


QUANTITYTAKEOFF_DLL_EXPORT
Int32 GetMultiStoryElemInd (EDB::GeneralElemConstRef pElem, const EDB::FloorStructureConstRef& floorStructure);

QUANTITYTAKEOFF_DLL_EXPORT
void	 CalcPoly (	const Geometry::IrregularPolygon2D&	poly,
					double								thick,
					double								*length,
					double								*surf,
					double								*vol,
					double								*holesSurf,
					Int32								*segmentsNr,
					double								*holesPrm);

QUANTITYTAKEOFF_DLL_EXPORT
Geometry::MultiPolygon2D	CalcFreeShapeFloorPlanPolygon (const VBElem::FreeShapeConstRef&	freeShape, 
														   const QT::QuantityModelConstPtr&	quantityModel, 
														   const GS::Optional<GSIndex>&		floorIndex = GS::NoValue);

QUANTITYTAKEOFF_DLL_EXPORT
ModelCalculations::MeshBodyCuttingResult	CalcFreeShapeOneFloorBodies (const VBElem::FreeShapeConstRef&	freeShape,
																		 const QT::QuantityModelConstPtr&	quantityModel,
																		 const GSIndex						floorIndex);

double CalcPolyActLength (const Geometry::IrregularPolygon2D&	poly,
						  Int32*								segmentsNr,
						  double*								holesPrm);

typedef		GS::HashTable<VBEO::ModelElemComponentId, double>	ComponentVolumeMap;
typedef		GS::HashTable<VBEO::ModelElemComponentId, double>	ComponentProjectedAreaMap;

void	FillSkinVolumes (const ComponentVolumeMap& componentVolumes, double*& skinVolumes, GSSize expectedComponentNumber);
void	FillSkinProjectedAreas (const ComponentProjectedAreaMap& componentProjectedAreas, double*& skinProjectedAreas, GSSize expectedComponentNumber);

template <typename T>
void		FillArrayWithZeros (GS::Array<T> *arr, ULong size) {
	if (arr == nullptr)
		return;

	arr->SetSize (size);
	arr->Fill (T (0));
}

CONV2LISTREC GenerateGrossModelListParamsForObjects ();

enum RailingEnumerationMode
{
	AllSubElements,
	OnlyLeafSubElements
};

void EnumerateStairModelElemSubelems	(const VBElem::StairConstRef& stair, const std::function<void (const VBElem::ModelElementConstRef& subElem)>& processor);
void EnumerateStairModelElemVisibleSubelems (const VBElem::StairConstRef& stair, const std::function<void (const VBElem::ModelElementConstRef& subElem)>& processor);
void EnumerateRailingModelElemSubelems	(const VBElem::RailingConstRef& railing, RailingEnumerationMode mode, const std::function<void (const VBElem::ModelElementConstRef& subElem)>& processor);
void EnumerateRailingSegmentModelElemSubelems (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::ModelElementConstRef& subElem)>& processor);

#endif

