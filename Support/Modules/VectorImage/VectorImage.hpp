#ifndef VECTORIMAGE_HPP
#define VECTORIMAGE_HPP

#pragma once

// from GSRoot
#include "GSRoot.hpp"
#include "UniString.hpp"
#include "AutoPtr.hpp"

// from Geometry
#include "Polygon2D.hpp"
#include "IrregularPolygon2D.hpp"
#include "Polyline2D.hpp"

// from VectorImage
#include "VectorImageExport.h"
#include "ISymbol.hpp"
#include "SyHead.hpp"
#include "SyEnd.hpp"
#include "SyHot.hpp"
#include "SyLine.hpp"
#include "SyPolyLine.hpp"
#include "SyArc.hpp"
#include "SyText.hpp"
#include "SyRichText.hpp"
#include "SyHatch.hpp"
#include "SySpline.hpp"
#include "SyFont.hpp"
#include "SyPicture.hpp"
#include "SyPixMap.hpp"
#include "SyPointCloud.hpp"
#include "VectorImageObject.hpp" 
#include "SyHatchObject.hpp" 

// from Pattern
#include "PolygonDrawingDirection.hpp"


namespace GS {
	class XMLOChannel;
	class XMLIChannel;
}

class IVectorImagePartialCopy;
class VI2DGeometryInterface;
class ReIDMapCollector;
class PointCloudObject;
class ConstVectorImageIterator;
class VectorImageIterator;

namespace VI {
	class Transformer;
	class IAttributeModifier;
}

namespace VI {
namespace HatchGeometryPriority {
	class HatchGeometryPriorityComparer;
}
}

class VI_DLL_CLASS_EXPORT VectorImage
{
	DECLARE_ROOT_CLASS_INFO

private:
	friend class ConstVectorImageIterator;
	friend class VectorImageIterator;

	char*	imageData;
	ULong	imageDataLen;
	ULong	allocatedBytes;

	ULong	nElements;
	ULong	nHots;
	ULong	nLine;
	ULong	nPolyLine;
	ULong	nArc;
	ULong	nText;
	ULong	nHatc;
	ULong	nSpline;
	ULong	nFonts;
	ULong	nPicture;
	ULong	nPixMap;
	ULong	nRichText;
	ULong	nPointCloud;

	Int32	defScale;

	mutable Box2DData boundingBox;

	mutable bool	isBoundBoxValid			:1;
	mutable bool	hangOutOfBox			:1;
	bool			useDrawQueue			:1;
	bool			sortDrawQueue			:1;

	bool			fontsMapped				:1;
	bool			generatedWithOverrides	:1;

	GS::Array<GS::AutoPtr<VectorImageObject>>	objects;
	GS::HashTable<GS::Guid, HatchObject>		hatchObjects;

private:
	Sy_EndType*				Element (ULong offset);
	const Sy_EndType*		Element (ULong offset) const;
	void					CalcBounds () const;

	enum AllocationType { Standard = 0, ExactAllocSize = 1, CanDecrease = 2, MakeACopy = 4, SetImageDataLen = 8 };
	void					ReallocBytes (ULong bytes, AllocationType allocType);				// can throw

	GSErrCode				DeleteRecord (Sy_EndType* itemPtr);
	Sy_EndType*				AddRecord (const void*		rec,									// can throw
									   const char*		block1 = nullptr,
									   ULong			offset1 = 0,
									   ULong			length1 = 0,
									   const char*		block2 = nullptr,
									   ULong			offset2 = 0,
									   ULong			length2 = 0);

	GSErrCode				GetItemPoints_Common (const Box2DData* frame, GS::Array<Coord>& points, SyEnum typeID, bool withoutHotspots) const;

	GSErrCode				Write_TextStyleIndices (GS::OChannel& oc) const;
	GSErrCode				Write_SyObjects (GS::OChannel& oc) const;
	GSErrCode				Write_SyObjectsXML (GS::XMLOChannel& oc) const;
	GSErrCode				Write_Version8_9 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

	void					Clear_TextStyleIndices (void);
	GSErrCode				Read_TextStyleIndices (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode				Read_SyObjects (GS::IChannel& ic);
	GSErrCode				Read_SyObjectsXML (GS::XMLIChannel& ic);
	GSErrCode				ReadVersion1_7 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode				ReadVersion8_9 (GS::IChannel& ic, const GS::InputFrame& frame);

	void					EmptyVectorImage ();
	void					FillSy_2DHeadType (Sy_2DHeadType* head) const;
	void					SetConvertedEndOffset (Sy_2DHeadType& head) const;
	void					FillFromSy_2DHeadType (const Sy_2DHeadType& head) ;
	void					SetElements (GS::IChannel& channel, ULong dataLen);					// can throw


	void					TransformSyPolyLine    (const TRANMAT*				tran,
													const Sy_PolyLinType*		srcPolyLinePtr,
													Sy_PolyLinType*				myPolyLinePtr,
													Coord**						myPolyCoordsHdl,
													PolyArcRec**				myPolyArcsHdl) const;

	void					TransformSyHatch   (const TRANMAT*				tran,
												bool						changeHatchTypeToKeepAppearance,
												const HatchObject&			srcHatchPtr,
												HatchObject&				myHatchPtr,
												IGetGradientFillType*		getFillType) const;

public:
	VectorImage ();
	VectorImage (const VectorImage& source);						// can throw
	virtual ~VectorImage ();

	const VectorImage&	operator= (const VectorImage& source);		// can throw

	bool				operator== (const VectorImage& op) const;
	bool				operator!= (const VectorImage& op) const;
	virtual bool		Compare (const VectorImage& op) const;

	void				Copy (VectorImage& target, IVectorImagePartialCopy& callback) const;

	GSErrCode			CheckAndRepair (void);

	GSHandle			GetElements () const;						// can throw
	void				SetSymbolHandle (GSConstHandle imageHdl);	// can throw

	void				SetCapacity (ULong capacity);				// can throw
	void				GrowCapacity (ULong capacity);				// can throw

	Int32				GetScale () const;
	void				SetScale (Int32 defScale);

	GSErrCode			GetBounds (Box2DData* bounds, bool withoutHotspots = false) const;

	bool				IsUsingDrawQueue () const;
	bool				IsUsingSortQueue () const;
	bool				AreThereAnyHotspotsOutOfModel () const;
	bool				WasGeneratedWithOverrides () const;

	void				SetDrawQueueUsing ();
	void				SetSortQueueUsing ();
	void				SetGeneratedWithOverrides (bool generatedWithOverrides);

	bool				IsFontsMapped () const;
	void				SetFontMappingComplete ();

	bool				IsEmpty () const;
	ULong				GetItemCount (bool withoutHotspots = false) const;
	ULong				GetItemCountOfType (SyEnum typeID) const;

	void				Clear ();
	void				DeleteItemsOfType (SyEnum typeID);

	void				Append (const VectorImage&				oper,							// can throw
								IGetGradientFillType*			getFillType,
								const VI::IAttributeModifier&	attrModifier,
								const VI::Transformer&			transformer,
								short							donorLayer		= 0,
								double							dScale			= 100.0);

	GSErrCode			WriteContentForChecksum (GS::OChannel& channel) const;
	GSErrCode			Write (GS::OChannel& channel) const;
	GSErrCode			Read (GS::IChannel& channel);
	GSErrCode			WriteXML (GS::XMLOChannel& channel) const;
	GSErrCode			ReadXML (GS::XMLIChannel& channel);

	void				ExportToHandle (GSHandle handle) const;			// Used in AC API // can throw 
	void				ImportFromHandle (GSConstHandle handle);			// Used in AC API // can throw

	void				OffsetImage (const Geometry::Vector2d& offset);

	GSErrCode			GetItemFramePoints (const Box2DData& frame, GS::Array<Coord>& points, bool withoutHotspots = false) const;
	GSErrCode			GetItemPointsOfType (SyEnum typeID, GS::Array<Coord>& points) const;

	void				AddHotspotRec	(const Sy_HotType&			hotspot);							// can throw

	void				AddLineRec		(const Sy_LinType&			line);								// can throw

	void				AddPolyLineRec	(const Sy_PolyLinType&		polyLine,							// can throw
										const char*					pCoordPtr,
										const char*					pArcsPtr);

	void				AddPolyLine		(const Sy_PolyLinType&		syPolyLine,							// can throw
										const Geometry::Polyline2D&	polyline);

	void				AddWholeGenArc (const VBAttr::ExtendedPen&	pen,								// can throw
										short						pattern,
										short						layer,
										DrawIndex					drwIndex,
										const Coord&				origo,
										double						r,
										double						ratio,
										double						mainAxisDir,
										short						determine = 0,
										char						specFor3D = SySymbolic);

	void				AddArcRec (const Sy_ArcType&	arc);								// can throw

	void				AddTextRec (const Sy_TextType&	text,								// can throw
									const char*			conPtr,
									const char*			lstPtr);

	void				AddText	(	short				pen,								// can throw
									short				layer,
									DrawIndex			drwIndex,
									Int32				styleind,
									const Coord&		loc,
									unsigned char		paramInd,
									const char*			text);

	void				AddRichTextRec (const Sy_RichTextType*	richtext);					// can throw

	GSErrCode			AddHatchRec (Sy_HatchType& hatchRef, HatchObject& hatchObj);

	GSErrCode			AddHatchRec (Sy_HatchType&							hatchRef,		// can throw
									 HatchObject&							hatchObj,
									 const Geometry::IrregularPolygon2D&	polygon,
									 const IPolygonDrawingDirection*		drawingDirection);

	GS::Guid			AddHatch (	bool						contVis,					// can throw
									const VBAttr::ExtendedPen&	contPen,
									const VBAttr::ExtendedPen&	fillPen,
									short						fillind,
									Int32						nCoords,
									double*						coords,
									double*						angles,
									UInt32						displayOrder);

	GS::Guid			AddHatchWhole (														// can throw
									bool						contVis,
									const VBAttr::ExtendedPen&	contPen,
									short						contLTyp,
									const VBAttr::ExtendedPen&	fillPen,
									short						bkgPen,
									short						fragmentIdx,
									DrawIndex					drwIndex,
									GX::Pattern::HatchTran		hatchTrafo,
									short						fillind,
									Int32						npb,
									const UInt32*				boends,
									Int32						npc,
									const Coord*				coords,
									const double*				angles,
									const PlaneEq&				plane,
									UInt32						displayOrder,
									short						fillTypeDetermination = 0,
									const GS_RGBColor*			bkgColorRGB = nullptr,
									const GS_RGBColor*			fgColorRGB = nullptr,
									char						renovationStatus = VI::SyUndefinedRenovationStatus,
									char						specFor3D = SySymbolic, 
									SyHatchIsForSelection		isSel = SyNormalHatch);

	GS::Guid			AddHatchWhole (														// can throw
									bool							contVis,
									const VBAttr::ExtendedPen&		contPen,
									short							contLTyp,
									short							buildMatIdx,
									short							fillind,
									VBAttr::OverriddenExtendedPen	fillPen,
									VBAttr::OverriddenPen			bkgPen,
									short							fragmentIdx,
									DrawIndex						drwIndex,
									GX::Pattern::HatchTran			hatchTrafo,
									Int32							npb,
									const UInt32*					boends,
									Int32							npc,
									const Coord*					coords,
									const double*					angles,
									const PlaneEq&					plane,
									UInt32							displayOrder,
									short							fillTypeDetermination = 0,
									char							renovationStatus = VI::SyUndefinedRenovationStatus,
									char							specFor3D = SySymbolic);


	void				AddSplineRec (const Sy_SplineType&		spline,							// can throw
									  char*						pCoordPtr,
									  char*						pSDirsPtr);

	void				AddSplineRecConst (const Sy_SplineType&			spline,							// can throw
										   const char*					pCoordPtr,
										   const char*					pSDirsPtr,
										   const Geometry::Vector2d*	offsCo);
	
	void				AddPixMapRec (	const Sy_PixMapType&	pixHeader,					// can throw
										GSConstHandle			pixMemoHdl,
										const char*				mimeType = nullptr);

	void				AddPixMap (	DrawIndex			drwIndex,							// can throw
									GSPixMapHandle		pict,
									Box2DData*			drawnBox,
									bool				mirrored,
									bool				transparent,
									double				rotAngle);

	void				AddFontRec (const Sy_FontType&	font,								// can throw
									const GS::UniString& fontName);

	void				AddSyElement (const Sy_EndType&	elem);								// can throw

	void				AddPointCloudRec (const Sy_PointCloudType&			pointCloudRec,
										  PointCloudObject*					pointCloudObjectPtr);							// can throw

	void					AddPointCloud (PointCloudObject* object, DrawIndex drwIndex, short sy_fragmentIdx);					// can throw
	PointCloudObject*		GetPointCloud (const ConstVectorImageIterator& it);
	const PointCloudObject*	GetPointCloud (const ConstVectorImageIterator& it) const;

	const HatchObject&		GetHatchObject (const Sy_HatchType& hatchRef) const;
	HatchObject&			GetHatchObject (const Sy_HatchType& hatchRef);
	bool					AddHatchObject (const HatchObject& hatch);
	const Sy_HatchType*		GetSyHatchType (const GS::Guid& hatchUniqueId) const;
	
	const GS::HashTable<GS::Guid, HatchObject>&	GetConstHatchObjects (void) const;
	const HatchObject*							GetHatchObject (const GS::Guid& hatchId) const;

	bool					GetContinousPolylines (GS::Array<Geometry::Polyline2D>& resultPolylines) const;
	
	void				Strip (const Geometry::IrregularPolygon2D& cutPoly, VectorImage* resultingImage, const Geometry::Boundary cutWithBoundary = Geometry::Boundary_Opened, bool stripHotspots = false) const;				// can throw
	void				Sort (GS::CmpFunction* sortFunc, VectorImage* resultingImage) const;								// can throw

	void				Transform (const VI::Transformer& transformer);															// can throw
	void				Transform (const VI::Transformer& transformer, VectorImage* resultingImage) const;						// can throw

	USize				GetSizeInBytes (void) const;

	void				ExportTo (VI2DGeometryInterface& dest) const;
	void				ImportFrom (VI2DGeometryInterface& src, const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer);

	static void			MarkPolyEdgesVerts (Geometry::IrregularPolygon2D& poly);
	static void			MarkPolyEdgesVerts (Geometry::IrregularPolygon2D& poly, const GS::Guid& polyGUID, ReIDMapCollector& reID);
private:
	static void			MarkPolyEdgesVerts (Geometry::IrregularPolygon2D& poly, const GS::Guid& polyGUID, ReIDMapCollector* reID);
};

/*	Implement this interface to specify which elements in the VectorImage
	should be copied to the new VectorImage.
	- CopyCurrent(): return true if should copy; false if shouldn't
*/
class VI_DLL_CLASS_EXPORT IVectorImagePartialCopy {
public:
	virtual bool CopyCurrent (const ConstVectorImageIterator& currentElem) = 0;
	virtual ~IVectorImagePartialCopy ();
};



#include "VectorImageInline.hpp"

#endif
