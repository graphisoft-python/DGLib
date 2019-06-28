// *****************************************************************************
//
// Declaration of CorePolyline2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_COREPOLYLINE2D_CLASSDEFINITION_HPP
#define GEOMETRY_COREPOLYLINE2D_CLASSDEFINITION_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

// from GSRoot
#include "Algorithms.hpp"
#include "DoubleClassification.hpp"

//own
#include "Poly2D.hpp"
#include "Curve2DData.h"
#include "Ellipse2DData.h"		// DivideEllArcToCo, DivideArcToCo 
#include "CutElems.h"
#include "HalfPlane2DData.h"
#include "Cut2DInternal.h"
#include "NurbsCurve2D.hpp"

namespace Geometry {
	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CorePolygon2D;
}

namespace Geometry {


	class GEOMETRY_DLL_EXPORT CorePolyline2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	class GEOMETRY_DLL_EXPORT CorePolyline2DVertexVisitor
	{
	public:
		virtual ~CorePolyline2DVertexVisitor ();

		virtual void operator () (Coord &) = 0;
	};
	class GEOMETRY_DLL_EXPORT CorePolyline2DConstVertexVisitor
	{
	public:
		virtual ~CorePolyline2DConstVertexVisitor ();

		virtual void operator () (const Coord &) = 0;
	};

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CorePolyline2D : public GS::SharedObject
	{
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CorePolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CorePolygon2D;

	public:
		enum PolylineResult {
			NewPolylines,
			EmptyPolyline,
			ResultSameAsThis,
			ResultSameAsFirstParameter
		};

		enum PolylinePointPosition {PointOnRightSide, PointOnPolyline, PointOnLeftSide};

		struct Flags {
			Flags ()
			{
				Clear ();
			}
			void Clear (void)
			{
				BNZeroMemory (this, sizeof (Flags));
				isSameDirEdgeLegal = true;
				isClosed = false;
				isSameCoord = false;
				isVertexUserData = true;
				isEdgeUserData = true;
				isPolygonUserData = true;
			}
			GS::UInt16					isSameDirEdgeLegal		: 1; // Set if two succeeding edge with same direction (two edge in one line) is legal
			GS::UInt16					isClosed				: 1;
			GS::UInt16					isSameCoord				: 1;
			GS::UInt16					isVertexUserData		: 1;
			GS::UInt16					isEdgeUserData			: 1;
			GS::UInt16					isPolygonUserData		: 1;
		};

	private:
		struct NurbsRec {
			UIndex		begIndex;
			NurbsCurve2D		nurbs;

			NurbsRec () : begIndex (0) {};
		};

		Box2DData					boundBox;			// Boundbox of the whole polygon
		Flags						flags;

		GS::Array <PolygonUserData>	inhPolygonInfo;		// Array containing the attached polygon informations (inherited)
		VertexUserData				defaultVertexData;
		EdgeUserData				defaultEdgeData;

		USize						nVertices;			// Total number of all vertices in all contours (equals to num of edges)
		GS::Array <Coord>			vertices;			// Array containing the vertices
		GS::Array <VertexUserData>	vertexInfos;		// Array containing the attached vertex informations (eg. vertID)

		USize						nArcs;				// Total number of curved edges
		GS::Array <PolyArcRec>		arcs;				// the view angle of arcs (sign: + means CCW, - means CW) and the connecting vertices
		GS::Array <EdgeUserData>	inhEdgeInfos;		// Array containing the attached edge informations inherited by all descendant (eg. height)

		USize						nNurbs;				// Total number of Nurbs
		GS::Array <NurbsRec>		nurbs;

		void InitInternalData (void);
		void FreeInternalData (void)																																	CAN_THROW ((GS::OutOfMemoryException));
		void ReallocateInternalDataSizes (USize verticesNum, USize arcsNum, USize nurbsNum, USize verticesCapacity, USize arcsCapacity, USize nurbsCapacity)			CAN_THROW ((GS::OutOfMemoryException));
		void AllocateInternalData (USize verticesNum, USize arcsNum, USize nurbsNum, USize verticesCapacity = 0, USize arcsCapacity = 0, USize nurbsCapacity = 0)		CAN_THROW ((GS::OutOfMemoryException));
		void ReallocateInternalData (USize verticesNum, USize arcsNum, USize nurbsNum, USize verticesCapacity = 0, USize arcsCapacity = 0, USize nurbsCapacity = 0)		CAN_THROW ((GS::OutOfMemoryException));

		void SetInternalDataVertices (const Coord* pCoords, USize coordNum, GS::UInt32 createFlags);
		void SetInternalDataVertices (const GS::Array<Coord>& coordList, USize coordNum, GS::UInt32 createFlags);
		void SetInternalDataArcs (const PolyArcRec* pArcs, USize arcNum, GS::UInt32 createFlags);
		void SetInternalDataArcs (const GS::Array<PolyArcRec>& arcList, USize arcNum, GS::UInt32 createFlags);
		void SetInternalDataNurbs (const NurbsRec* pNnurbs, USize nurbsNum);
		void SetInternalDataNurbs (const GS::Array<NurbsRec>& inNurbs, USize nurbsNum);
		void SetInternalData (const Coord* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const NurbsRec* pNurbs, USize nurbsNum, GS::UInt32 createFlags);
		void SetInternalData (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<NurbsRec>& inNurbs, GS::UInt32 createFlags);

		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		void CopyInternalDataFromWithoutUserData (const CorePolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& source, USize verticesCapacity, USize arcsCapacity, USize nurbsCapacity)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void CopyInternalDataFromClearUserData (void)			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		template <class ContourUserData>
		void CopyInternalDataFromUserData (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex fromVertex, UIndex begVertexIdx, USize newVerticesNum)			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void CopyInternalDataFrom (const CorePolyline2D& source)																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		template <class ContourUserData>
		void CopyInternalDataFrom (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx)															CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void CopyPolygonLevelDataFrom (const CorePolyline2D& source);

		void AddOneVertex (const Coord& coord, const VertexUserData* vertexInfo, const EdgeUserData* edgeInfo, const PolyArcRec* arc = nullptr, const NurbsRec* nurbs = nullptr);

		UIndex GetInternalArcIdx (UIndex edgeIdx) const;
		UIndex GetInternalSector (UIndex edgeIdx, Coord& begC, Coord& endC, Coord& origo, double& angle) const;
		UIndex GetInternalNurbsIdx (UIndex edgeIdx) const;
		void GetCoord (const CutParam& cutParam, Coord *c) const;

		void DeleteVertexFromInternalData (UIndex remIndex);
		void ReplaceEdgeFromInternalData (UIndex insIndex, const GenArc& genArc, const ArcDivParams& arcDivParams);
		void InsertVertexFromInternalData (UIndex insIndex, const Coord& newPosition, bool keepArc = false, bool insArc = false);
		static GS::Int32 LineLineToDeleteEdge (const Sector &prevEdgeLine, const Sector &nextEdgeLine, Coord *result);
		void SetEdgeArcToDeleteEdge (GS::Int32& arcInd, bool& isEdgeArc, GenArc& edgeArc, Coord& edgeArcCentre, double& edgeArcViewAngle, UIndex edgeIdx, const Coord& vertFromPt, const Coord& vertFromTo) const;
		bool PolylineDeleteEdge (UIndex edgeIdx)																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void PolylineFilletChamferContour (double filletChamferRadius, bool doFillet)														CAN_THROW ((GS::LogicErrorException, GS::OutOfMemoryException, GeometryException));
		static double GetMaxMid (bool twocirc, const Circle* ci1, const GenArc*	arc1, const Circle* ci2, const GenArc* arc2, const Sector*	ls);
		void GetMaxVertexFillet (UIndex filletedVertexIdx, double* maxFilletRadius) const;
		void PolylineFilletChamferVertex (UIndex filletChamferVertexIdx, double filletChamferRadius, bool doFillet)							CAN_THROW ((GS::LogicErrorException, GS::OutOfMemoryException, GeometryException));
		void GetOffsetLimit (double *offset) const;
		void OffsetAllEdge (double offset);
		void GetOffsetLimitEdge (double *offset, UIndex edgeId) const;
		void OffsetOneEdge (double offset, UIndex edgeId, bool *degen1, Coord *degenC1, bool *degen2, Coord *degenC2);
		void DropNurbs (void);

		//Cut With half Planes
		void SetInternalData (	const CorePolyline2D&					origPoly,
								const USize								verticesNum,
								const double*							coords,
								const USize								arcsNum,
								const PolyArcRec*						pArcs,
								const USize								nurbsNum,
								const NurbsRec*							inNurbs,
								const GS::Array <const EdgeUserData*>&	customInhEdgeInfo,
								const GS::Int32*						inds,
								const GS::Int32*						indc)																CAN_THROW ((GS::OutOfMemoryException));
		PolylineResult	CutWithHalfPlanes (	const GS::Array<HalfPlane2DData>&			cutlines,		/* -> line params. 			*/
											GS::Array<GS::SharedPtr<CorePolyline2D> >&	respoly, 		/* <- result polygons		*/
											bool										*fullin,		/* <- full inside 			*/
											GS::Int32 									*wrcode) const	/* <- warning error code   	*/		CAN_THROW ((GS::OutOfMemoryException));

		Box2DData CalcBoundBox (void) const;
		void UpdateBoundingBox (void);

		template<class EdgeUserDataComparator, bool checkUserData>
		void RemoveSameDirEdge (const EdgeUserDataComparator& comparator);
		void RemoveSameDirEdge ();

		void Regularize (void);
		void DeleteNearPoints (void);

	public:
		~CorePolyline2D ();

		CorePolyline2D (const CorePolyline2D& source);
		template <class ContourUserData>
		CorePolyline2D (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& source, UIndex contourIdx);

	protected:
		CorePolyline2D (Flags actFlags);
		CorePolyline2D (const CorePolyline2D& source, bool copyPolygonLevelData);

		CorePolyline2D (Flags actFlags, const Box2DData& box);
		CorePolyline2D (Flags actFlags, const Coord* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, GS::UInt32 createFlags);
		CorePolyline2D (Flags actFlags, const Coord* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, UIndex begCoordIdx, UIndex endCoordIdx, GS::UInt32 createFlags);
		CorePolyline2D (Flags actFlags, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		CorePolyline2D (Flags actFlags, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, UIndex begCoordIdx, UIndex endCoordIdx, GS::UInt32 createFlags);
		CorePolyline2D (Flags actFlags, const GenArc genArc, const ArcDivParams& arcDivParams);

		CorePolyline2D (Flags actFlags, const CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData> & contourDesc);

		static void Create (Flags actFlags, const Coord* pCoords, USize coordNum, const PolyArcRec* pArcs, USize arcNum, const UIndex* pContourEnds, USize contourNum, GS::UInt32 createFlags, GS::Array<GS::SharedPtr<CorePolyline2D> >& result)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (Flags actFlags, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex> contourEndList, GS::UInt32 createFlags, GS::Array<GS::SharedPtr<CorePolyline2D> >& result)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		ULong GetRefCount (void) { return SharedObject::GetRefCount (); }

		bool IsFirstLastCoordEqual (void) const;

	private:
		void FillCorePolyline2DFromContourDesc (const CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData>& contourDesc)					CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		bool CopyPolylineDataVertices (Coord* destCoords, USize& coordNum,  GS::UInt32 createFlags) const			CAN_THROW ((GS::OutOfMemoryException));
		bool CopyPolylineDataArcs (PolyArcRec* destArcs, USize& arcNum, GS::UInt32 createFlags) const				CAN_THROW ((GS::OutOfMemoryException));
		bool CopyPolylineDataNurbs (GS::Array<NurbsCurve2D>& destNurbs) const												CAN_THROW ((GS::OutOfMemoryException));
		bool CompareGeometry (const CorePolyline2D& source) const;
	public:
		CorePolyline2D&	operator= (const CorePolyline2D& source);

		bool Compare (const CorePolyline2D& source) const;

		void Convert (CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData >& contourDesc) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		static void ConvertFromCorePolyline2D (CorePolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& result, const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& source)											CAN_THROW ((GS::OutOfMemoryException, GeometryException));	

		void CopyPolylineData (Coord* destCoords, USize& coordNum, PolyArcRec* destArcs, USize& arcNum, GS::Array<NurbsCurve2D>& destNurbs, GS::UInt32 createFlags) const				CAN_THROW ((GS::OutOfMemoryException));
		void CopyPolylineData (GS::Array<Coord>& destCoords, GS::Array<PolyArcRec>& destArcs, GS::Array<NurbsCurve2D>& destNurbsList, GS::UInt32 createFlags) const;

		void ResetUserData (void);

		void SetUserData (const PolygonUserData* userData);
		const PolygonUserData* GetUserData (void) const;

		void SetSameDirEdgeLegal (bool isSameDirEdgeLegal);
		bool GetSameDirEdgeLegal (void) const { return flags.isSameDirEdgeLegal; }

		void SetIsVertexUserData	(bool actIsUserData);
		bool GetIsVertexUserData	() const { return flags.isVertexUserData; }
		void SetIsEdgeUserData		(bool actIsUserData);
		bool GetIsEdgeUserData		() const { return flags.isEdgeUserData; }
		void SetIsPolygonUserData	(bool actIsUserData);
		bool GetIsPolygonUserData	() const { return flags.isPolygonUserData; }

		void SetClosed			(bool closed)																										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		bool GetClosed			(void) const { return flags.isClosed; }
		void DetectAndSetClosed (void);

		void SetIsSameCoord		(bool isSameCoord);
		bool GetIsSameCoord		() const { return flags.isSameCoord; }

		const VertexUserData& GetVertexDefaultUserData (void) const;
		void SetVertexDefaultUserData (const VertexUserData& userData);

		USize GetVertexNum (void) const;
		UIndex GetVertexIdx (const Coord& coord) const;
		const Coord& GetCoord (UIndex vertexIdx) const;
		void SetCoord (UIndex vertexIdx, const Coord& newCoord);
		const VertexUserData* GetVertexUserData (UIndex vertexIdx) const;
		void SetVertexUserData (UIndex vertexIdx, const VertexUserData* userData);

		const EdgeUserData& GetEdgeDefaultUserData (void) const;
		void SetEdgeDefaultUserData (const EdgeUserData& userData);

		USize GetEdgeNum (void) const { return nVertices > 0 ? nVertices - 1 : 0; }
		double GetArcAngle (UIndex edgeIdx) const;
		double GetEdgeLength (UIndex edgeIdx) const;
		NurbsCurve2D GetNurbs (UIndex edgeIdx) const;
		bool GetSector (UIndex edgeIdx, Sector& sect, GenArc& genArc) const;
		bool GetSector (UIndex edgeIdx, Coord& begC, Coord& endC, double& angle) const;
		const EdgeUserData* GetEdgeUserData (UIndex edgeIdx) const;
		void SetEdgeUserData (UIndex edgeIdx, const EdgeUserData* userData);

		UIndex GetNextVertexIndex (UIndex vertexIdx, const VertexUserData* ud) const;
		UIndex GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData* ud) const;
		UIndex GetNextEdgeIndex (UIndex edgeIdx, const EdgeUserData* ud) const;
		UIndex GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData* ud) const;

		UIndex GetBeginVertexIdxOfEdge (UIndex edgeIdx) const;
		UIndex GetEndVertexIdxOfEdge (UIndex edgeIdx) const;

		UIndex GetPrevEdgeIdxOfVertex (UIndex vertexIdx) const;
		UIndex GetNextEdgeIdxOfVertex (UIndex vertexIdx) const;

		bool IsEmpty (void) const { return nVertices == 0; }
		void Clear (void);

		// returns true, if the polyline is a rectangle and its edges are parallel with the X and Y axises
		bool IsABox (void) const;

		void RemoveSmallArcs (void);

	private:
		GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode	ReadVersion1UserData (GS::IChannel& ic);
		GSErrCode	ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode	ReadVersion2UserData (GS::IChannel& ic);
		GSErrCode	ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);

		GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode	WriteVersion1UserData (GS::OChannel& oc) const;
		GSErrCode	WriteVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode	WriteVersion2UserData (GS::OChannel& oc) const;
		GSErrCode	WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

		GSErrCode	WriteXMLContour (GS::XMLOChannel& oc) const																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static GSErrCode ReadXMLCreateContourDesc	(GS::XMLIChannel& ic, GS::XMLITag& tagSegments, Flags actFlags, CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData>& polyContourDesc, bool& isEdgeTag)										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
	public:
		GSErrCode	Read (GS::IChannel& ic);
		GSErrCode	Write (GS::OChannel& oc) const;

		static GS::SharedPtr<CorePolyline2D>	ReadXMLAndCreate	(GS::XMLIChannel& ic)								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		//******************************* Calculate *******************************
		const Box2DData& GetBoundBox (void) const																							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		double CalcArea (bool signedArea = false) const;
		bool IsClockwise (void) const;
		double CalcLength (void) const;
		double CalcMaxVertexFillet (UIndex vertexIdx) const																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		bool IsCoordOnEdge (const Coord& c, GS::Array<UIndex>& edgeIndex) const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		GS::Array<GS::Pair<UIndex, Vector>> GetTangentAtPoint (const Coord& c) const														CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		Coord GetMiddlePoint (void) const																									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void GetTransformedBoundBox (Coord box[4], const TRANMAT* tr, const TRANMAT* invTr = nullptr) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		double DistanceFromPoint (const Coord& co, UIndex& edgeOfMin, GS::Array<bool>* filter) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void Visit (CorePolyline2DConstVertexVisitor &visitor) const;

	private:
		void FillSegmentedArc (const ArcDivParams& arcDivParams, GS::Array< GS::Array<Coord> >& segmentedArcs, USize& numOfSegmentedVertex) const																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void FillSegmentedNurbs (const ArcDivParams& arcDivParams, GS::Array< GS::Array<Coord> >& segmentedNurbs, USize& numOfSegmentedVertex) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void SetSegmentUp (GS::SharedPtr<CorePolyline2D>& result, GS::Array< GS::Array<Coord> >& segmentedArcs, GS::Array< GS::Array<Coord> >& segmentedNurbs) const																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));

	public:
		//******************************* Modify polyline *******************************
		void Move (Vector offset)																											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		//Ha az iveket torzitani kellene, akkor assertal
		void TransformPreserveArcs (const TRANMAT& tran)																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ClearVertexUserDatas (void);
		void ClearEdgeUserDatas (void);
		void Reverse (void);  //Change vertex order

		void Stretch (	const Coord& fixPoint,
						const Coord& draggedPoint,
						const Vector& offsetAxisX,
						const Vector& offsetAxisY = Vector (0.0, 0.0),
						const ArcDivParams& arcDivParams = ArcDivParams (0.0))																CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		class ArrayRangeRotator;	// C++11 legyen a RotateVerticeIndicesInContour fuggvenyben lokalisan definialva
		void RotateVerticeIndices (UIndex iVertexToFirst);
		void SortArcsByIndices (void);

		void Append (const Coord& c, const bool atEnd)																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void Append (const CorePolyline2D& polylineToAppend)																				CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void Visit (CorePolyline2DVertexVisitor &visitor);

		//******************************* Create new polyline(s) *******************************

			//Ha az iveket torzitani kellene, akkor nurbsse konvertalja oket
		void ArcToNurbs ();
		PolylineResult Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::SharedPtr<CorePolyline2D>& result) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		template <class ContourUserData>
		PolylineResult Transform (const CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& filterWithPolygon, const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::SharedPtr<CorePolyline2D>& result, bool& isTransformedAll) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		template <class ContourUserData>
		PolylineResult Transform (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& filterPolygonArray, const ArcDivParams& arcDivParams, const TRANMAT& tran, GS::SharedPtr<CorePolyline2D>& result, bool& isTransformedAll) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult SegmentUp (const ArcDivParams& arcDivParams, GS::SharedPtr<CorePolyline2D>& result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult EliminateArcs (GS::SharedPtr<CorePolyline2D>& result) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void Reverse (GS::SharedPtr<CorePolyline2D>& result) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void OffsetAllEdge (double offset, GS::SharedPtr<CorePolyline2D>& result, double* newOffset) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult OffsetEdge (UIndex edgeIdx, double offset, GS::SharedPtr<CorePolyline2D>& result) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void MoveVertex (UIndex vertexIdx, const Coord& newPosition, GS::SharedPtr<CorePolyline2D>& result) const							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void FilletAllVertex (const double filletRadius, GS::SharedPtr<CorePolyline2D>& result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void FilletVertex (UIndex vertexIdx, const double filletRadius, GS::SharedPtr<CorePolyline2D>& result) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ChamferAllVertex (const double chamferRadius, GS::SharedPtr<CorePolyline2D>& result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ChamferVertex (UIndex vertexIdx, const double chamferRadius, GS::SharedPtr<CorePolyline2D>& result) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
	private:
		void InsertNewVerticesAndDeleteOld  (UIndex filletChamferVertexIdx, const Coord& begFilletChamferPosition, const Coord& endFilletChamferPosition, UIndex begContourIdx, UIndex endContourIdx, UIndex& prevVertIdx, bool isPrevEdgeArc, GS::Int32 arcIndBeg, double newPrevEdgeArcViewAngle, bool isNextEdgeArc, GS::Int32 arcIndEnd, double newNextEdgeArcViewAngle, bool united1, bool united2)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
	public:
		void InsertVertex (UIndex edgeIdx, const Coord& newPosition, GS::SharedPtr<CorePolyline2D>& result) const							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void InsertVertexOnPolyline (const Coord& newPosition, UIndex edgeIndex, GS::SharedPtr<CorePolyline2D>& result, UIndex& vertexIdx) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void DeleteVertex (UIndex vertexIdx, GS::SharedPtr<CorePolyline2D>& result) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void SetEdgeAngle (UIndex edgeIdx, double edgeAngle, GS::SharedPtr<CorePolyline2D>& result) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ReplaceEdge (UIndex edgeIdx,const GenArc& genArc, const ArcDivParams& arcDivParams, GS::SharedPtr<CorePolyline2D>& result) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		bool DeleteEdge (UIndex edgeIdx, GS::SharedPtr<CorePolyline2D>& result) const														CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ShiftPolyline (double length, bool firstEdge, GS::SharedPtr<CorePolyline2D>& result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult CutAtVertices (GS::Array<UIndex>& vertexIdxArray, GS::Array<GS::SharedPtr<CorePolyline2D> >& result) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult Cut (const HalfPlane2DData& cutline, GS::Array<GS::SharedPtr<CorePolyline2D> >& result, bool& fullin, GS::Int32& wrcode) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, GS::Array<GS::SharedPtr<CorePolyline2D> >& result, GS::Int32& wrcode) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult Clip (const Box2DData& box, GS::Array<GS::SharedPtr<CorePolyline2D> >& result, GS::Int32& wrcode) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		PolylineResult CutPiece (const CutParam& t1, const CutParam& t2, GS::SharedPtr<CorePolyline2D>& result) const;
		GS::Array<CutParam> CutPointToCutParam (const Coord& cutPoint) const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		Coord	CutParamToCutPoint (const CutParam& cutParam) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		double	CutParamToDistance (const CutParam& cutParam) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		CutParam	DistanceToCutParam (double distance)	const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		template<class EdgeUserDataComparator>
		void RemoveSameDirEdgesOnlyWithSameUserData (const EdgeUserDataComparator& comparator);
		void RemoveSameDirEdgesOnlyWithSameUserData ();

	private:
		bool	CheckSizes			(void) const;
		bool	CheckVertices		(PolyCheckFlags checkFlags, PolyCheckFlags* errorType, double coordUpperRange) const;
		bool	CheckArcs			(PolyCheckFlags checkFlags, PolyCheckFlags* errorType) const;
		bool	CheckNurbs			() const;

	public:
		PolylinePointPosition	PointPosition (const Coord& sidePoint) const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Debug
		void				Print			(GS::OChannel& oc)	const;
		void				PrintDebug		(void)				const { Check (PolyCheckFlags_All_Polyline, nullptr, MaxCoordValue ()); Print (dbChannel); }
		void				PrintDebugXML	(void)				const { Check (PolyCheckFlags_All_Polyline, nullptr, MaxCoordValue ()); WriteXML (dbXMLChannel); }

		bool				Check			(PolyCheckFlags  checkFlags,
											 PolyCheckFlags* errorType,
											 double			 coordUpperRange) const;
		PolyRepairResult	Repair			(PolyCheckFlags repairType);
	};

}	// namespace Geometry

#endif //GEOMETRY_COREPOLYLINE2D_CLASSDEFINITION_HPP
