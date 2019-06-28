// *****************************************************************************
//
// Declaration of Polyline2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *****************************************************************************

#ifndef GEOMETRY_POLYLINE2D_CLASSDEFINITION_HPP
#define GEOMETRY_POLYLINE2D_CLASSDEFINITION_HPP

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
// from GSRoot
#include "Definitions.hpp"
#include "Array.hpp"

// from Geometry
#include "Poly2DTypes.hpp"

#include "Poly2D.hpp"
#include "Poly2DIterator.hpp"
#include "CorePolyline2D.hpp"

#include "IrregularPolygon2DClassDefinition.hpp"

#include "CutElems.h"

namespace Geometry {

	class GEOMETRY_DLL_EXPORT Polyline2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomPolyline2D
	{
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomMultiPolyline2D;

		friend class ConstPolyVertexInPolyState<CustomPolyline2D, VertexUserData>;
		friend class ConstPolyEdgeInPolyState<CustomPolyline2D, EdgeUserData>;
		friend class ConstPolyVertexInPoly<CustomPolyline2D, VertexUserData>;
		friend class ConstPolyEdgeInPoly<CustomPolyline2D, EdgeUserData>;

	public:
		typedef VertexUserData		VertexUserDataType;
		typedef EdgeUserData		EdgeUserDataType;
		typedef PolygonUserData		PolylineUserDataType;

		enum PolylinePointPosition {PointOnRightSide, PointOnPolyline, PointOnLeftSide};

		typedef CorePolyline2DVertexVisitor			VertexVisitor;
		typedef CorePolyline2DConstVertexVisitor	ConstVertexVisitor;
		
		typedef CustomPolyVertex<VertexUserData>	Vertex;
		typedef CustomPolyEdge<EdgeUserData>		Edge;

		typedef CustomPolySegment<VertexUserData, EdgeUserData> Segment;
		typedef CustomPolyContourDescription<VertexUserData, EdgeUserData, PolygonUserData> ContourDescription;

		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolyline2D, ConstPolyVertexInPolyState<CustomPolyline2D, VertexUserData>, ConstPolyVertexInPoly<CustomPolyline2D, VertexUserData> > ConstVertexIterator;
		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolyline2D, ConstPolyEdgeInPolyState<CustomPolyline2D, EdgeUserData>, ConstPolyEdgeInPoly<CustomPolyline2D, EdgeUserData> > ConstEdgeIterator;

	protected:

		GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >		polyline;

	protected:

		CustomPolyline2D (GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > polyline2D);
		static void Create(const GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& polylineArray, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result);
		void CreateResult (typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult polyResult, const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& newPolyline, CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result) const;
		void CreateResult (typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult polyResult, const GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& polylineArray, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result) const;

		void CopyOnWrite (void)																										CAN_THROW ((GS::OutOfMemoryException, GeometryException));

	protected:
		const Coord& GetVertexCoordByIdx (UIndex vertexIdx) const
		{
			return const_cast<const CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>*> (&*polyline)->GetCoord (vertexIdx);
		}
		const VertexUserData& GetVertexUserDataByIdx (UIndex vertexIdx) const
		{
			return *polyline->GetVertexUserData (vertexIdx);
		}
		UIndex GetNextVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polyline->GetNextVertexIndex (vertexIdx, &id);
		}
		UIndex GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polyline->GetPrevVertexIndex (vertexIdx, &id);
		}

		double GetEdgeArcAngleByIdx (UIndex edgeIdx) const
		{
			return polyline->GetArcAngle (edgeIdx);
		}
		double GetEdgeLengthByIdx (UIndex edgeIdx) const
		{
			return polyline->GetEdgeLength (edgeIdx);
		}
		bool GetSectorById (UIndex edgeIdx, Sector& sect, GenArc& genArc) const
		{
			return polyline->GetSector (edgeIdx, sect, genArc);
		}
		const EdgeUserData& GetEdgeUserDataByIdx (UIndex edgeIdx) const
		{
			return *polyline->GetEdgeUserData (edgeIdx);
		}
		UIndex GetNextEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polyline->GetNextEdgeIndex (edgeIdx, &id);
		}
		UIndex GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polyline->GetPrevEdgeIndex (edgeIdx, &id);
		}

		static typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Flags GetFlags (GS::UInt32 flags /*PolyFlags*/);
	public:

		// Constructs an empty Polyline, where all sizes (number of vertices and arcs) are 0 and corresponding data is uninitialized, PolyFlags all set to true values
		// For info on PolyFlags please, check Poly2D.hpp
		CustomPolyline2D (void);
		CustomPolyline2D (const CustomPolyline2D& source)																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next two construct a Polyline from a Polygon contour
		template <class ContourUserData>
		CustomPolyline2D (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polygon, typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator contourIterator)									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		template <class ContourUserData>
		CustomPolyline2D (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& polygon, typename CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator contourIterator)				CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Constructs a rectangle Polyline with the box parameter as bounds, PolyFlags all set to true values
		explicit CustomPolyline2D (const Box2DData& box)																				CAN_THROW ((GS::OutOfMemoryException, GeometryException));		
		// Constructs a Polyline from a contour description, PolyFlags all set to true values
		// If the result of creation is empty then we get an empty Polyline
		explicit CustomPolyline2D (const ContourDescription& contourDesc)																CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next four methods construct a Polyline from a list of coordinates and PolyArcs using several flags to determine the input format
		// See Poly2D.hpp for detailed info on PolyCreateFlag
		CustomPolyline2D (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/)					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		CustomPolyline2D (const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/)									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		CustomPolyline2D (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		CustomPolyline2D (const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Constructs a Polyline by segmenting up a GenArc - i.e. replaces the curve with line sections - using arcDivParams as granulation for the segmentation
		CustomPolyline2D (const GenArc genArc, const ArcDivParams& arcDivParams)														CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Constructs an empty Polyline, where all sizes (number of vertices and arcs) are 0 and corresponding data is uninitialized, PolyFlags provided by caller
		// For info on PolyFlags please, check Poly2D.hpp
		explicit CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/);
		// Constructs a rectangle Polyline with the box parameter as bounds, PolyFlags provided by caller
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Constructs a Polyline from a contour description, PolyFlags provided by caller
		// If the result of creation is empty then we get an empty Polyline
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const ContourDescription& contourDesc)			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next four methods create a Polyline from a list of coordinates and PolyArcs using several flags to determine the input format, PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags and PolyCreateFlags
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/)			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Constructs a Polyline by segmenting up a GenArc - i.e. replaces the curve with line sections - using arcDivParams as granulation for the segmentation, PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags
		CustomPolyline2D (GS::UInt32 flags /*PolyFlags*/, const GenArc genArc, const ArcDivParams& arcDivParams)						CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		~CustomPolyline2D ();

		GS::ClassVersion	GetClassVersion (void) const {return Polyline2DPrivate::classInfo.GetVersion ();}

		// See corresponding constructor (same parameter list without the last)
		static void Create (const ContourDescription& contourDesc, CustomPolyline2D& result)											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (const GenArc genArc, const ArcDivParams& arcDivParams, CustomPolyline2D& result)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a Polyline from a contour description array
		// If the result of creation is empty then we get an empty MultiPolyline
		static void Create (const GS::Array<ContourDescription>& contourDesc, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next two methods create a MultiPolyline2D from a list of coordinates, PolyArcs and contour end indices (one contour - one Polyline) using several flags to determine the input format
		// See Poly2D.hpp for detailed info on PolyCreateFlags
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of resulting Polylines
		static void Create (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// See corresponding constructor (same parameter list without the last)
		template <class ContourUserData>
		static void Create (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polygon, typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator contourIterator, CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a Polyline from each contour of the input Polygon
		template <class ContourUserData>
		static void Create (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polygon, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		template <class ContourUserData>
		static void Create (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& polygon, typename CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator contourIterator, CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a Polyline from each contour of the input Polygon
		template <class ContourUserData>
		static void Create (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& polygon, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)											CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// See corresponding constructor (same parameter list without the last)
		static void Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescription& contourDesc, CustomPolyline2D& result)										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomPolyline2D& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// See corresponding constructor (same parameter list without the last)
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GenArc genArc, const ArcDivParams& arcDivParams, CustomPolyline2D& result)						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a Polyline from a contour description array, PolyFlags provided by caller
		// If the result of creation is empty then we get an empty MultiPolyline
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<ContourDescription>& contourDesc, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next two methods create a MultiPolyline2D from a list of coordinates, PolyArcs and contour end indices (one contour - one Polyline) using several flags to determine the input format,
		// PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags and PolyCreateFlags
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of resulting Polylines
		static void Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Converts the Polyline to a contour description
		void Convert (ContourDescription& contourDesc) const																	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ArcToNurbs ();
		// Converts the Polyline to an array of Polygons (if the Polyline is self intersecting it will result in more than one Polygon)
		template <class ContourUserData>
		void Convert (CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polygons) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		static void ConvertFromPolyline2D (CustomPolyline2D& result, const CustomPolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& source);

		// Copies the Polyline's vertices into a coord list and its curved edges into a PolyArcRec list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// If the caller specifies either coords or arcs as nullptr, the corresponding size will still be returned but no copying will be done
		// If the caller specifies either nValuableCoords or nValuableArcs as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void CopyPolylineData (Coord* coords, USize& nValuableCoords, PolyArcRec* arcs, USize& nValuableArcs, GS::Array<NurbsCurve2D>& nurbs, GS::UInt32 createFlags /*PolyCreateFlags*/) const				CAN_THROW ((GS::OutOfMemoryException));
		// Similar to previous but uses GS::Arrays instead of pointers
		// Copies the Polygon's vertices into a coord list and its curved edges into a PolyArcRec list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		void CopyPolylineData (GS::Array<Coord>& coords, GS::Array<PolyArcRec>& arcs, GS::Array<NurbsCurve2D>& nurbs, GS::UInt32 createFlags /*PolyCreateFlags*/) const;

		// Copies the Polyline's vertices into a coord list and its curved edges into a PolyArcRec list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The memory for the lists is allocated within the method
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// If the caller specifies either nValuableCoords or nValuableArcs as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void AllocateAndCopyPolylineData (Coord** coords, USize& nValuableCoords, PolyArcRec** arcs, USize& nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		CustomPolyline2D&	operator= (const CustomPolyline2D& source);

		bool	operator== (const CustomPolyline2D& rightOp) const;
		bool	operator!= (const CustomPolyline2D& rightOp) const;

		// Enables or disables the possibility of two succeeding edges with the same direction (two edges in one line)
		// calling with false parameter ensures that there are none of these edges by removing edges and vertices if needed
		void SetSameDirEdgeLegal (bool isSameDirEdgeLegal);
		// Returns whether it is possible for two succeeding edges to have the same direction (two edges in one line)
		bool GetSameDirEdgeLegal (void) const;
		// For info on PolyFlags please, check Poly2D.hpp
		void SetPolyFlags (GS::UInt32 flags /*PolyFlags*/);
		// For info on PolyFlags please, check Poly2D.hpp
		GS::UInt32 GetPolyFlags () const; //PolyFlags

		// Opens or closes the Polyline
		void SetClosed (bool isClosed)																							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns true if the Polyline is closed
		bool GetClosed (void) const;
		// Closes the Polyline if the first and last coordinates are equal and it was not already closed
		void DetectAndSetClosed (void)																							CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		ConstVertexIterator	GetVertexIterator (UIndex vertexIdx) const;
		ConstVertexIterator	GetVertexIterator (const Coord& coord) const;
		ConstVertexIterator	EnumerateVertex (void) const;
		// Same as previous
		ConstVertexIterator	BeginVertex (void) const;
		ConstVertexIterator	EndVertex	(void) const;
		ConstVertexIterator	EnumerateVertex (const VertexUserData& id) const;

		ConstEdgeIterator	GetEdgeIterator (UIndex edgeIdx) const;
		ConstEdgeIterator	EnumerateEdge (void) const;
		// Same as previous
		ConstEdgeIterator	BeginEdge (void) const;
		ConstEdgeIterator	EndEdge	(void) const;
		ConstEdgeIterator	EnumerateEdge (const EdgeUserData& id) const;

		void ResetUserData (void);

		void SetPolyUserData (const PolygonUserData& polyId)																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		const PolygonUserData& GetPolyUserData (void) const;

		const VertexUserData& GetVertexDefaultUserData (void) const;
		void SetVertexDefaultUserData (const VertexUserData& userData);

		USize GetVertexNum (void) const;
		// Returns the vertex data (Coord and PolyId) of the vertex at vertexIterator into the vertex parameter
		void GetVertex (const ConstVertexIterator& vertexIterator, Vertex& vertex) const;
		// Returns the coordinates of the vertex at vertexIterator
		const Coord& GetCoord (const ConstVertexIterator& vertexIterator) const;

		// Sets vertex user data
		void SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId);
		// Returns the PolyId of the vertex at vertexIterator
		const VertexUserData& GetVertexUserData (const ConstVertexIterator& vertexIterator) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		const EdgeUserData& GetEdgeDefaultUserData (void) const;
		void SetEdgeDefaultUserData (const EdgeUserData& userData);

		USize GetEdgeNum (void) const;
		// Returns the edge data (angle and PolyId) of the edge at edgeIterator into the edge parameter
		void GetEdge (const ConstEdgeIterator& edgeIterator, Edge& edge) const;
		// Gives back a Sector and a GenArc that correspond with the beginning, the end and the angle of the edge at edgeIterator
		// Returns true if the edge at edgeIterator is curved
		bool GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const;
		// Gives back the beginning coord, the end coord and the angle of the edge at edgeIterator
		// Returns true if the edge at edgeIterator is curved
		bool GetSector (const ConstEdgeIterator& edgeIterator, Coord& begC, Coord& endC, double& angle) const;

		// Sets edge user data
		void SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId);
		// Returns the PolyId of the edge at edgeIterator
		const EdgeUserData& GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const 												CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Returns a vertex iterator pointing to the beginning vertex of the edge at edgeIterator
		ConstVertexIterator GetBeginVertex (const ConstEdgeIterator& edgeIterator) const;
		// Returns a vertex iterator pointing to the end vertex of the edge at edgeIterator
		ConstVertexIterator GetEndVertex (const ConstEdgeIterator& edgeIterator) const;

		// Returns an edge iterator pointing to the edge originating from the vertex at vertexIterator
		ConstEdgeIterator GetNextEdge (const ConstVertexIterator& vertexIterator) const;
		// Returns an edge iterator pointing to the edge terminating in the vertex at vertexIterator
		ConstEdgeIterator GetPrevEdge (const ConstVertexIterator& vertexIterator) const;

		// Returns true if the Polyline is an empty Polyline
		bool IsEmpty (void) const;
		// Returns true if the Polyline has at least one curved edge
		bool HasArcs (void) const;
		// Returns the Polyline becomes an empty Polyline
		void Clear (void);

		// Returns true, if the polygon is a rectangle and its edges are parallel with the X and Y axises
		bool IsABox (void) const;

		GSErrCode	Read (GS::IChannel& ic)																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		GSErrCode	Write (GS::OChannel& oc) const;
		GSErrCode	ReadXML	(GS::XMLIChannel& ic)																				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		//******************************* Calculate *******************************
		// Returns the bounding box of the Polyline
		const Box2DData& GetBoundBox (void) const																				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the center of the bounding box of the Polyline
		Coord GetCenter (void) const;
		// Returns the signed area of the Polyline (if it is not closed the area is calculated by closing it by a straight edge)
		double CalcArea (void) const;
		// IsClockwise == IsNegativeOrder
		bool IsClockwise (void) const;
		// Returns the accumulated length of the Polyline segments
		double CalcLength (void) const;
		// Returns the maximum fillet radius that can belong to the vertex at vertexIterator
		double CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns wether the given coordinate is on the polyline
		bool IsCoordOnEdge (const Coord& c, GS::Array<ConstEdgeIterator>* edgeIt = nullptr) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the tangent of the polyline at the given point, throws exception if point not on polyline
		GS::Array<GS::Pair<ConstEdgeIterator, Vector>> GetTangentAtPoint (const Coord& c) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the middle point of a polyine, throws exception if empty
		Coord GetMiddlePoint (void) const																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the bounding box of the Polyline we would get if we applied tr as a transformation matrix on this Polyline
		// if invTr is not nullptr then invTr will be applied to the box result
		void GetTransformedBoundBox (Coord box[4], const TRANMAT* tr, const TRANMAT* invTr = nullptr) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the distance from polyline, throws exception if empty
		double DistanceFromPoint (const Coord& co, ConstEdgeIterator* edgeItOfMin = nullptr, GS::Array<bool>* filter = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void Visit (ConstVertexVisitor &visitor) const;

		//******************************* Modify polyline *******************************
		// Moves the Polyline with the offset
		void Move (Vector offset)																								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Transforms the Polyline with tran - the transformation should preserve arcs
		void TransformPreserveArcs (const TRANMAT& tran)																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next two clear user data
		void ClearVertexIds (void);
		void ClearEdgeIds (void);
		// Reverses the direction of the Polyline (goes from last vertex to first vertex; in closed case last = first)
		void Reverse (void);  //Change vertex order

		void Stretch (	const Coord& fixPoint,
						const Coord& draggedPoint,
						const Vector& offsetAxisX,
						const Vector& offsetAxisY = Vector (0.0, 0.0),
						const ArcDivParams& arcDivParams = ArcDivParams (0.0))													CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void RotateVerticeIndices (const ConstVertexIterator& vertexToFirst);
		void SortArcsByIndices (void);
		void Append (const CustomPolyline2D& polylineToAppend)																	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void Append (const Coord& c, const bool atEnd = true)																	CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void Visit (VertexVisitor &visitor);

		//******************************* Create new polylines *******************************
		// Transforms the Polyline with tran - if the transformation does not preserve arcs then arcDivParams is used as granulation to segment up the Polyline
		void Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran, CustomPolyline2D& result) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Same as previous but only transforms the parts of the Polyline that intersect with the filter Polygon or is on its edge
		template <class ContourUserData>
		void Transform (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & filterWithPolygon, const ArcDivParams& arcDivParams, const TRANMAT& tran, CustomPolyline2D& result, bool& isTransformedAll) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Same as first transform but only transforms the parts of the Polyline that intersect with any of the filter Polygons or is on the edge of any
		template <class ContourUserData>
		void Transform (const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & filterWithPolygon, const ArcDivParams& arcDivParams, const TRANMAT& tran, CustomPolyline2D& result, bool& isTransformedAll) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Segments up the Polyline - i.e. replaces all curves with line sections - using arcDivParams as granulation for the segmentation
		void SegmentUp (const ArcDivParams& arcDivParams, CustomPolyline2D& result) const												CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Makes all curved edges straight - this is not segmentation, number of edges and vertices remain the same!
		void EliminateArcs (CustomPolyline2D& result) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		//Change vertex order
		// Reverses the direction of the Polyline (goes from last vertex to first vertex; in closed case last = first) into a copy
		void Reverse (CustomPolyline2D& result) const																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Offsets all edges in the Polyline with the given offset preserving edge angles
		void OffsetAllEdge (double offset, CustomPolyline2D& result, double* newOffset =  nullptr) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Offsets the edge at edgeIterator with the given offset preserving connecting edge angles
		void OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset, CustomPolyline2D& result) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Moves the vertex at vertexIterator to newPosition
		void MoveVertex (const ConstVertexIterator& vertexIterator, const Coord& newPosition, CustomPolyline2D& result) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Creates fillets with given radius at all vertices in the Polyline
		void FilletAllVertex (const double filletRadius, CustomPolyline2D& result) const												CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a fillet with given radius at the vertex at vertexIterator
		void FilletVertex (const ConstVertexIterator& vertexIterator, const double filletRadius, CustomPolyline2D& result) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates chamfers with given radius at all vertices in the Polyline
		void ChamferAllVertex (const double chamferRadius, CustomPolyline2D& result) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a chamfer with given radius at the vertex at vertexIterator
		void ChamferVertex (const ConstVertexIterator& vertexIterator, const double chamferRadius, CustomPolyline2D& result) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Inserts a vertex on the edge at edgeIterator to newPosition
		void InsertVertex (const ConstEdgeIterator& edgeIterator, const Coord& newPosition, CustomPolyline2D& result) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Inserts a vertex if vertex is on polyline, otherwise exception
		void InsertVertexOnPolyline (const Coord& newPosition, const ConstEdgeIterator& edgeIterator, CustomPolyline2D& result, ConstVertexIterator* vertexIterator = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Deletes the vertex at vertexIterator, connects the neighboring vertices
		void DeleteVertex (const ConstVertexIterator& vertexIterator, CustomPolyline2D& result) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Sets the angle of the curve of the edge at edgeIterator to edgeAngle
		void SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle, CustomPolyline2D& result) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Replace edge at edgeIterator to genArc definition
		void ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GenArc& genArc, const ArcDivParams& arcDivParams, CustomPolyline2D& result) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Deletes the edge at edgeIterator, connects the neighboring edges (the intersection creates a new Polyline vertex)
		bool DeleteEdge (const ConstEdgeIterator& edgeIterator, CustomPolyline2D& result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// lengthens the first (last) edge while shortens the last (first) edge, so the total length of the polyline is preserved
		void ShiftPolyline (double length, bool firstEdge, CustomPolyline2D& result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Cut the Polyline at given vertices
		void CutAtVertices (const GS::Array<ConstVertexIterator>& vertexIteratorArray, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Gives back the parts of the Polyline that are on the given half plane, determines whether it is cut or not
		void Cut (const HalfPlane2DData& cutline, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result, bool& fullin, GS::Int32& wrcode) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Gives back the parts of the Polyline that are on the given half planes
		void Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result, GS::Int32& wrcode) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Gives back the parts of the Polyline that are in the clip box
		void Clip (const Box2DData& box, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& result, GS::Int32& wrcode) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Cuts out one part of the Polyline between param t1..t2 and gives it back
		void CutPiece (const CutParam& t1, const CutParam& t2, CustomPolyline2D& result) const;
		// cutPoint to CutParam, throws exception if point not on polyline
		GS::Array<CutParam>	CutPointToCutParam (const Coord& cutPoint) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// CutParam  to cutPoint, throws exception if invalid cutParam
		Coord	CutParamToCutPoint (const CutParam& cutParam) const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// calculates the distance of the cutPoint from the start
		double	CutParamToDistance (const CutParam& cutParam) const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// calculates the cutPoint from the start
		CutParam	DistanceToCutParam (double distance)	const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Returns whether the Coord parameter is on the left or on the right side of the Polyline
		PolylinePointPosition	PointPosition (const Coord& sidePoint) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Removes same directional edges from polygon if EdgeUserData is equal or comparable with a comparator
		template<class EdgeUserDataComparator>
		static void RemoveSameDirEdgesOnlyWithSameUserData (CustomPolyline2D& poly, const EdgeUserDataComparator& comparator);
		static void RemoveSameDirEdgesOnlyWithSameUserData (CustomPolyline2D& poly);

		// Debug
		void				Print			(GS::OChannel& oc)	const;
		void				PrintDebug		(void)				const;
		void				PrintDebugXML	(void)				const;
		bool				Check			(PolyCheckFlags checkFlags,
											 double			coordUpperRange) const;
		PolyRepairResult	CheckAndRepair	(PolyCheckFlags checkFlags,
											 double			coordUpperRange);
	};

	typedef CustomPolyline2D<PolyId, PolyId, PolyId> Polyline2D;

	template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
	inline GSErrCode	Read (GS::IChannel& ic, CustomPolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& polyline)			{ return polyline.Read (ic); }
	template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
	inline GSErrCode	Write (GS::OChannel& oc, const CustomPolyline2D<VertexUserData1, EdgeUserData1, PolygonUserData1>& polyline)	{ return polyline.Write (oc); }

	class GEOMETRY_DLL_EXPORT MultiPolyline2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomMultiPolyline2D : public GS::Array<CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >
	{
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
	public:
		typedef CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> PolyType;

		virtual ~CustomMultiPolyline2D ();
		
		void SegmentUp (const ArcDivParams& arcDivParams)																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran)													CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		GSErrCode	Read (GS::IChannel& ic)																						CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::NullReferenceException));
		GSErrCode	Write (GS::OChannel& oc) const;
		
		GSErrCode	ReadXML	(GS::XMLIChannel& ic);
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Returns the largest area Polyline and deletes it from the MultiPolyline
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> PopLargest (void);
		// Returns overall bounding box
		Box2DData GetBoundBox (void) const																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		
	protected:
		void GetCorePolyline2DArray (GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >& polylineArray) const;
		void PushResults (	typename CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::PolylineResult polyResult, 
							const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& thisPoly, 
							const GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> >& newPolyline);
	};

	typedef CustomMultiPolyline2D<PolyId, PolyId, PolyId> MultiPolyline2D;

} //Geometry namespace

#endif //GEOMETRY_POLYLINE2D_CLASSDEFINITION_HPP
