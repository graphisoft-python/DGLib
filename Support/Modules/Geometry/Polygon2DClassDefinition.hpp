// *****************************************************************************
//
// Declaration of Polygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA
//
// *****************************************************************************

#ifndef GEOMETRY_POLYGON2D_CLASSDEFINITION_HPP
#define GEOMETRY_POLYGON2D_CLASSDEFINITION_HPP

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
#include "CorePolygon2D.hpp"

#include "CutElems.h"

namespace Geometry {

	class GEOMETRY_DLL_EXPORT Polygon2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
	class CustomPolygon2D
	{
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomMultiPolyline2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomMultiIrregularPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomPolygon2D;

		friend class ConstPolyVertexInPolyState<CustomPolygon2D, VertexUserData>;
		friend class ConstPolyEdgeInPolyState<CustomPolygon2D, EdgeUserData>;
		friend class ConstPolyVertexInPoly<CustomPolygon2D, VertexUserData>;
		friend class ConstPolyEdgeInPoly<CustomPolygon2D, EdgeUserData>;

	public:
		typedef VertexUserData		VertexUserDataType;
		typedef EdgeUserData		EdgeUserDataType;
		typedef ContourUserData		ContourUserDataType;
		typedef PolygonUserData		PolygonUserDataType;

		typedef CorePolygon2DVertexVisitor		VertexVisitor;
		typedef CorePolygon2DConstVertexVisitor	ConstVertexVisitor;

		typedef CustomPolyVertex<VertexUserData>	Vertex;
		typedef CustomPolyEdge<EdgeUserData>		Edge;

		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolygon2D, ConstPolyVertexInPolyState<CustomPolygon2D, VertexUserData>, ConstPolyVertexInPoly<CustomPolygon2D, VertexUserData> > ConstVertexIterator;
		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolygon2D, ConstPolyEdgeInPolyState<CustomPolygon2D, EdgeUserData>, ConstPolyEdgeInPoly<CustomPolygon2D, EdgeUserData> > ConstEdgeIterator;

		class Contour
		{
			friend class CustomPolygon2D;
		private:
			enum FilterType
			{
				Filter_None			= 0x00,
				Filter_Range		= 0x01,
				Filter_PolyId		= 0x02
			};
		private:
			const CustomPolygon2D*		poly;
			UIndex					index;

			FilterType				filterType;
			UIndex					from;
			UIndex					to;
			ContourUserData			polyId;

			ConstVertexIterator		GetVertexIterator (UIndex vertexIdx) const;
			ConstEdgeIterator		GetEdgeIterator (UIndex edgeIdx) const;

		public:
			Contour (void) : poly (nullptr), index (0), filterType (Filter_None), from (0), to (0)
			{
			}
			Contour (const CustomPolygon2D* poly2D, UIndex idx) : poly (poly2D), index (idx), filterType (Filter_None), from (0), to (0)
			{
			}
			Contour (const CustomPolygon2D* poly2D, UIndex fromIdx, UIndex toIdx, UIndex idx) : poly (poly2D), index (idx), filterType (Filter_Range), from (fromIdx), to (toIdx)
			{
			}
			Contour (const CustomPolygon2D* poly2D, const ContourUserData& id) : poly (poly2D), index (0), filterType (Filter_PolyId), from (0), to (0), polyId (id)
			{
				index = poly->GetNextContourIndex (0, polyId);
			}
			Contour (const Contour& source) : 
				poly (source.poly), 
				index (source.index), 
				filterType (source.filterType), 
				from (source.from), 
				to (source.to), 
				polyId (source.polyId)
			{
			}

			Contour&  GetCurrent (void) { return *this; }
			const Contour&  GetCurrent (void) const { return *this; }
			void Next (void)
			{
				if (filterType & Filter_PolyId) {
					index = poly->GetNextContourIndex (index, polyId);
					return;
				}
				index++;
			}
			void Prev (void)
			{
				if (filterType & Filter_PolyId) {
					index = poly->GetPrevContourIndex (index, polyId);
					return;
				}
				index--;
			}
			UIndex GetIndex (void) const { return index; }
			bool IsEqual (const Contour& contour) const { return (poly == contour.poly && index == contour.index); }
			bool IsBegin (void) const
			{
				if (filterType & Filter_Range) {
					return (index < from);
				}
				return (index <= 0);
			}
			bool IsEnd (void) const
			{
				if (filterType & Filter_Range) {
					return (index >= to);
				}
				return (index > poly->GetContourNum ());
			}
			bool IsValid (void) const { return poly != nullptr; }
			bool CheckType (const Contour& contour) const { return poly == contour.poly; }
			const CustomPolygon2D* GetTarget (void) const { return poly; }

		public:
			const ContourUserData& GetPolyContourUserData (void) const;

			USize					GetVertexNum (void) const;
			ConstVertexIterator		EnumerateVertex (void) const;
			ConstVertexIterator		BeginVertex (void) const;
			ConstVertexIterator		EndVertex	(void) const;

			USize					GetEdgeNum (void) const;
			ConstEdgeIterator		EnumerateEdge (void) const;
			ConstEdgeIterator		BeginEdge (void) const;
			ConstEdgeIterator		EndEdge	(void) const;

			ConstVertexIterator		GetBeginVertex (const ConstEdgeIterator& edgeIterator) const;
			ConstVertexIterator		GetEndVertex (const ConstEdgeIterator& edgeIterator) const;

			ConstEdgeIterator		GetNextEdge (const ConstVertexIterator& vertexIterator) const;
			ConstEdgeIterator		GetPrevEdge (const ConstVertexIterator& vertexIterator) const;
		};

		typedef GS::ConstBidirectionalItemIteratorBase <CustomPolygon2D, Contour, Contour> ConstContourIterator;

		typedef CustomPolySegment<VertexUserData, EdgeUserData> Segment;
		typedef CustomPolyContourDescription<VertexUserData, EdgeUserData, ContourUserData> ContourDescription;
		typedef GS::Array<ContourDescription> ContourDescriptionArray;

	protected:

		GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >	polygon;

	protected:
		CustomPolygon2D (GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > polygon2D);

		static void Create (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result);
		static void Regularize (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> &	irregularPolygon2D,
								CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> &				result,
								PolyRegularizationMode																				mode = PolyRegularizationMode_Default)								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void CreateResult (typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult, const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>* firstParam, const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const;
		void SetResult (typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult, const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& newPoly);

		void CopyOnWrite (void)																										CAN_THROW ((GS::OutOfMemoryException, GeometryException));

	protected:
		const Coord& GetVertexCoordByIdx (UIndex vertexIdx) const
		{
			return polygon->GetCoord (vertexIdx);
		}
		const VertexUserData& GetVertexUserDataByIdx (UIndex vertexIdx) const
		{
			return *polygon->GetVertexUserData (vertexIdx);
		}
		UIndex GetNextVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polygon->GetNextVertexIndex (vertexIdx, &id);
		}
		UIndex GetPrevVertexIndex (UIndex vertexIdx, const VertexUserData& id) const
		{
			return polygon->GetPrevVertexIndex (vertexIdx, &id);
		}
		double GetEdgeArcAngleByIdx (UIndex edgeIdx) const
		{
			return polygon->GetArcAngle (edgeIdx);
		}
		double GetEdgeLengthByIdx (UIndex edgeIdx) const
		{
			return polygon->GetEdgeLength (edgeIdx);
		}
		bool GetSectorById (UIndex edgeIdx, Sector& sect, GenArc& genArc) const
		{
			return polygon->GetSector (edgeIdx, sect, genArc);
		}
		const EdgeUserData& GetEdgeUserDataByIdx (UIndex edgeIdx) const
		{
			return *polygon->GetEdgeUserData (edgeIdx);
		}
		UIndex GetNextEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polygon->GetNextEdgeIndex (edgeIdx, &id);
		}
		UIndex GetPrevEdgeIndex (UIndex edgeIdx, const EdgeUserData& id) const
		{
			return polygon->GetPrevEdgeIndex (edgeIdx, &id);
		}
		UIndex GetNextContourIndex (UIndex contourIdx, const ContourUserData& id) const
		{
			return polygon->GetNextContourIndex (contourIdx, &id);
		}
		UIndex GetPrevContourIndex (UIndex contourIdx, const ContourUserData& id) const
		{
			return polygon->GetPrevContourIndex (contourIdx, &id);
		}
		const ContourUserData& GetContourUserDataByIdx (UIndex contourIdx) const
		{
			return *polygon->GetContourUserData (contourIdx);
		}

		static typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags GetFlags (GS::UInt32 flags /*PolyFlags*/);
		static void CheckPolyFlags (GS::UInt32 flags /*PolyFlags*/);
	public:

		// Constructs an empty Polygon, where all sizes (number of vertices, arcs and contours) are 0 and corresponding data is uninitialized, PolyFlags all set to true values
		// For info on PolyFlags please, check Poly2D.hpp
		CustomPolygon2D (void);
		CustomPolygon2D (const CustomPolygon2D& source);
		// Constructs a rectangle Polygon with the box parameter as bounds, PolyFlags all set to true values
		CustomPolygon2D (const Box2DData& box)																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Constructs an empty Polygon, where all sizes (number of vertices, arcs and contours) are 0 and corresponding data is uninitialized, PolyFlags provided by caller
		// For info on PolyFlags please, check Poly2D.hpp
		explicit CustomPolygon2D (GS::UInt32 flags /*PolyFlags*/);
		// Constructs a rectangle Polygon with the box parameter as bounds, PolyFlags provided by caller
		CustomPolygon2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		~CustomPolygon2D ();

		GS::ClassVersion	GetClassVersion (void) const {return Polygon2DPrivate::classInfo.GetVersion ();}

		// First creates an irregular Polygon from a contour description array by using the first contour in the array as the main contour and the rest as holes, then regularizes the
		// result, which then may fall to pieces resulting in multiple regularized Polygons
		// If the result of creation is empty we get an empty MultiPolygon
		static void Create (const ContourDescriptionArray& contourDescrArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// First creates an irregular Polygon using the vertices and edges of the input Polyline sequentially, then regularizes the result
		static void Create (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Simply regularizes the inpult irregular Polygon
		static void Create (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)												CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next six methods create a CustomMultiPolygon2D from a list of coordinates, PolyArcs and contour end indices using several flags to determine the input format
		// See Poly2D.hpp for detailed info on PolyCreateFlags
		static void Create (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of contours in the resulting Polygon
		static void Create (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// First creates an irregular Polygon from a contour description array by using the first contour in the array as the main contour and the rest as holes, then regularizes the
		// result, which then may fall to pieces resulting in multiple regularized Polygons, PolyFlags provided by caller
		// If the result of creation is empty we get an empty CustomMultiPolygon2D
		static void Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescriptionArray& contourDescrArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next six methods create a CustomMultiPolygon2D from a list of coordinates, PolyArcs and contour end indices using several flags to determine the input format, PolyFlags provided by caller
		// See Poly2D.hpp for detailed info on PolyFlags and PolyCreateFlags
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// nValuableCoords indicates the number of coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the number of arcs not counting the possible initial dummy blank arc
		// nContours indicates the number of contours in the resulting Polygon
		static void Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		static void Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Converts the Polygon to an array of contour descriptions moving contour by contour starting with the main contour
		void Convert (ContourDescriptionArray& contourDescrArray) const															CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Converts the Polygon to an array of Polylines moving contour by contour starting with the main contour
		void Convert (CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polylines) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Converts the contour of the Polygon specified by the iterator to a Polyline
		void Convert (ConstContourIterator contourIterator, CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		static void ConvertFromPolygon2D (CustomPolygon2D& result, const CustomPolygon2D<VertexUserData1, EdgeUserData1, ContourUserData1, PolygonUserData1>& source);

		// Copies the Polygon's vertices into a coord list, its curved edges into a PolyArcRec list and its vertex indices that are on contour ends into an index list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The reversedContours iterator list specifies which contours in the polygon should be copied as a reversed order contour (starting from the same vertex)
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// nContours indicates the expected number of resulting contour ends not counting the possible initial dummy 0 index, this should match the number of contours in the Polygon
		// If the caller specifies either coords, arcs or contourEnds as nullptr, the corresponding size will still be returned but no copying will be done
		// If the caller specifies either nValuableCoords, nValuableArcs or nContours as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void CopyPolygonData (Coord* coords, USize& nValuableCoords, PolyArcRec* arcs, USize& nValuableArcs, UIndex* contourEnds, USize& nContours, const GS::Array<ConstContourIterator>& reversedContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Similar to previous but uses GS::Arrays instead of pointers
		// Copies the Polygon's vertices into a coord list, its curved edges into a PolyArcRec list and its vertex indices that are on contour ends into an index list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The reversedContours iterator list specifies which contours in the polygon should be copied as a reversed order contour
		void CopyPolygonData (GS::Array<Coord>& coords, GS::Array<PolyArcRec>& arcs, GS::Array<UIndex>& contourEnds, const GS::Array<ConstContourIterator>& reversedContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const;

		// Copies the Polygon's vertices into a coord list, its curved edges into a PolyArcRec list and its vertex indices that are on contour ends into an index list
		// where the caller must specify several flags to indicate the output format - See Poly2D.hpp for detailed info on PolyCreateFlags
		// The memory for the lists is allocated within the method
		// nValuableCoords indicates the expected number of resulting coords not counting the possible initial dummy blank coord
		// nValuableArcs indicates the expected number of resulting arcs not counting the possible initial dummy blank arc
		// nContours indicates the expected number of resulting contour ends not counting the possible initial dummy 0 index, this should match the number of contours in the Polygon
		// If the caller specifies either nValuableCoords, nValuableArcs or nContours as a smaller number than the actual corresponding size but does actually expect a result
		// (pointer not nullptr) then an OutOfMemoryException is thrown
		void AllocateAndCopyPolygonData (Coord** coords, USize& nValuableCoords, PolyArcRec** arcs, USize& nValuableArcs, UIndex** contourEnds, USize& nContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		CustomPolygon2D&	operator= (const CustomPolygon2D& source);

		bool	operator== (const CustomPolygon2D& rightOp) const;
		bool	operator!= (const CustomPolygon2D& rightOp) const;

		// Enables or disables the possibility of two succeeding edges with the same direction (two edges in one line)
		// calling with false parameter ensures that there are none of these edges by regularizing - which may remove edges and vertices
		void SetSameDirEdgeLegal (bool isSameDirEdgeLegal);
		void SetForce64BitPrecision (bool force64BitPrecision);

		// Returns whether it is possible for two succeeding edges to have the same direction (two edges in one line)
		bool GetSameDirEdgeLegal (void) const;

		bool GetForce64BitPrecision (void) const;

		// For info on PolyFlags please, check Poly2D.hpp
		void SetPolyFlags (GS::UInt32 flags /*PolyFlags*/);
		// For info on PolyFlags please, check Poly2D.hpp
		GS::UInt32 GetPolyFlags () const; //PolyFlags

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

		ConstContourIterator	GetContourIterator (UIndex contourIdx) const;
		ConstContourIterator	EnumerateContour (void) const;
		// Same as previous
		ConstContourIterator	BeginContour (void) const;
		ConstContourIterator	EndContour	(void) const;
		ConstContourIterator	EnumerateContour (const ContourUserData& id) const;
		// Get first hole iterator
		ConstContourIterator	EnumerateHoleContour (void) const;

		void SetPolyUserData (const PolygonUserData& polyId)																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		const PolygonUserData& GetPolyUserData (void) const;

		const VertexUserData& GetVertexDefaultUserData (void) const;
		void SetVertexDefaultUserData (const VertexUserData& userData);

		void ResetUserData (void);

		USize GetVertexNum (void) const;
		// Returns the vertex data (Coord and VertexUserData) of the vertex at vertexIterator into the vertex parameter
		void GetVertex (const ConstVertexIterator& vertexIterator, Vertex& vertex) const;
		// Returns the coordinates of the vertex at vertexIterator
		const Coord& GetCoord (const ConstVertexIterator& vertexIterator) const;

		// Returns the VertexUserData of the vertex at vertexIterator
		const VertexUserData& GetVertexUserData (const ConstVertexIterator& vertexIterator) const;
		// Sets vertex user data
		void SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId)								CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		const EdgeUserData& GetEdgeDefaultUserData (void) const;
		void SetEdgeDefaultUserData (const EdgeUserData& userData);

		USize GetEdgeNum (void) const;
		// Returns the edge data (angle and EdgeUserData) of the edge at edgeIterator into the edge parameter
		void GetEdge (const ConstEdgeIterator& edgeIterator, Edge& edge) const;
		// Gives back a Sector and a GenArc that correspond with the beginning, the end and the angle of the edge at edgeIterator
		// Returns true if the edge at edgeIterator is curved
		bool GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const;
		// Gives back the beginning coord, the end coord and the angle of the edge at edgeIterator
		// Returns true if the edge at edgeIterator is curved
		bool GetSector (const ConstEdgeIterator& edgeIterator, Coord& begC, Coord& endC, double& angle) const;

		// Returns the EdgeUserData of the edge at edgeIterator
		const EdgeUserData& GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const;
		// Sets edge user data
		void SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId)										CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		const ContourUserData& GetContourDefaultUserData (void) const;
		void SetContourDefaultUserData (const ContourUserData& userData);

		USize GetContourNum (void) const;
		// Returns the contour data of the contour at contourIterator as a CustomPolygon2D
		void GetContour (const ConstContourIterator& contourIterator, CustomPolygon2D& contour) const;

		// Returns the ContourUserData of the contour at contourIterator
		const ContourUserData& GetContourUserData (const ConstContourIterator& contourIterator) const;
		// Sets contour user data
		void SetContourUserData (const ConstContourIterator& contourIterator, const ContourUserData& contourId)							CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Returns a vertex iterator pointing to the beginning vertex of the edge at edgeIterator
		ConstVertexIterator GetBeginVertex (const ConstEdgeIterator& edgeIterator) const;
		// Returns a vertex iterator pointing to the end vertex of the edge at edgeIterator
		ConstVertexIterator GetEndVertex (const ConstEdgeIterator& edgeIterator) const;

		// Returns an edge iterator pointing to the edge originating from the vertex at vertexIterator
		ConstEdgeIterator GetNextEdge (const ConstVertexIterator& vertexIterator) const;
		// Returns an edge iterator pointing to the edge terminating in the vertex at vertexIterator
		ConstEdgeIterator GetPrevEdge (const ConstVertexIterator& vertexIterator) const;

	protected:
		bool IsVertexInContour (UIndex contourIdx, UIndex vertexIdx) const;
		bool IsEdgeInContour (UIndex contourIdx, UIndex edgeIdx) const;

	public:
		// Returns true if the Polygon is an empty Polygon
		bool IsEmpty (void) const;
		// Returns true if the Polygon has at least one curved edge
		bool HasArcs (void) const;
		// Returns the Polygon becomes an empty Polygon
		void Clear (void);

		// Returns true, if the polygon is a rectangle and its edges are parallel with the X and Y axises
		bool IsABox (void) const;

		GSErrCode	Read (GS::IChannel& ic)																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		GSErrCode	Write (GS::OChannel& oc) const;
		GSErrCode	ReadXML	(GS::XMLIChannel& ic)																				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		//******************************* Calculate *******************************
		// Returns the bounding box of the Polygon
		const Box2DData& GetBoundBox (void) const																							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the center of the bounding box of the Polygon
		Coord GetCenter (void) const;
		// Returns the signed area of the Polygon
		double CalcArea (void) const;
		// Returns the signed area of the contour at contourIterator
		double CalcContourArea (const ConstContourIterator& contourIterator) const;
		// Returns true if the Polygon's orientation is positive (CCW)
		bool HasPositiveOrientation (const ConstContourIterator& contourIterator) const;
		// Returns the perimeter of the Polygon
		double CalcPerimeter (void) const;
		// Returns the perimeter of the contour at contourIterator
		double CalcContourPerimeter (const ConstContourIterator& contourIterator) const;
		// Calculates the convex hull of the polygon
		void CalcConvexHull (const ArcDivParams& arcDivParams, GS::Array<Coord>& convexHull) const;
		// Returns the maximum fillet radius that can belong to the vertex at vertexIterator
		double CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns wether the given coordinate is on the polygon's contour
		bool IsCoordOnEdge (const Coord& c, ConstEdgeIterator* edgeIt) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the distance of the polygon's contour from the given coordinate  
		double DistanceFromPoint (const Coord& c) const																					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the relative position of the Polygon and the point parameter
		// Find RelativePosition definitions in GeometricDefinitions.h
		RelativePosition GetPosition (const Coord& point, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the relative position of the Polygon and the sector parameter
		RelativePosition GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		// Returns the relative position of the Polygon and the GenArc parameter
		RelativePosition GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the relative position of the Polygon and the box parameter
		RelativePosition GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the relative position of the Polygon and the Polygon parameter
		RelativePosition GetPosition (const CustomPolygon2D& poly, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the relative position of the Polygon and the Polyline parameter
		RelativePosition GetPosition (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the disposition of the sector parameter relative to the Polygon, if the resSectors parameter is not nullptr,
		// it also returns the pieces of the sector that are inside the Polygon
		PGPositionExt SegmentIn (Sector sector, GS::Array<Sector>* resSectors = nullptr) const;
		// Returns the disposition of the sector parameter relative to the Polygon, if the resSectors parameter is not nullptr,
		// it also returns the pieces of the sector that are outside the Polygon
		PGPositionExt SegmentOut (Sector sector, GS::Array<Sector>* resSectors = nullptr) const;
		// Returns the parts of a line - given by one of its points and its direction - that are inside the Polygon
		bool Intersect (const Coord& c, const Vector& dir, GS::Array<Sector>* result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the bounding box of the Polygon we would get if we applied tr as a transformation matrix on this Polygon
		// if invTr is not nullptr then invTr will be applied to the box result
		void GetTransformedBoundBox (Coord box[4], const TRANMAT* tr, const TRANMAT* invTr = nullptr) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void Visit (ConstVertexVisitor &visitor) const;

		//******************************* Modify polygon *******************************
		// Removes all holes from the Polygon
		void RemoveHoles (void)																									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Deletes the hole at contourIterator
		void DeleteHole (const ConstContourIterator& contourIterator)															CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Moves the Polygon with the offset
		void Move (Vector offset)																								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// The next three clear user data
		void ClearVertexIds (void);
		void ClearEdgeIds (void);
		void ClearContourIds (void);

		void RotateVerticeIndicesInContour (const ConstContourIterator& contourToRotate, const ConstVertexIterator& vertexToFirst);
		void SwapContourOrder (const GS::Array<ConstContourIterator>& newContourOrder);
		void SortArcsByIndices (void);

		//******************************* Create new polygons *******************************
		// Transforms the Polygon with tran - if the transformation does not preserve arcs then arcDivParams is used as granulation to segment up the Polygon,
		// in this case the Polygon may fall to pieces after regularization
		void Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Same as previous but only transforms the parts of the Polygon that intersect with the filter Polygon or is on its edge
		void Transform (const CustomPolygon2D& filterWithPolygon, 
						const ArcDivParams& arcDivParams, 
						const TRANMAT& tran, 
						CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, 
						bool& isTransformedAll) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Same as first transform but only transforms the parts of the Polygon that intersect with any of the filter Polygons or is on the edge of any
		void Transform (const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & filterWithPolygon, 
						const ArcDivParams& arcDivParams, 
						const TRANMAT& tran, 
						CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, 
						bool& isTransformedAll) const																			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Segments up the Polygon - i.e. replaces all curves with line sections - using arcDivParams as granulation for the segmentation
		void SegmentUp (const ArcDivParams& arcDivParams, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Makes all curved edges straight - this is not segmentation, number of edges and vertices remain the same!
		void EliminateArcs (Geometry::CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const																CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Offsets the edge at edgeIterator with the given offset preserving area
		void OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Offsets the edge at edgeIterator with the given offset preserving connecting edge angles then regularizes the result
		void OffsetEdgeFixArea (const ConstEdgeIterator& edgeIterator, const ConstVertexIterator& vertexIterator, double offset, double area, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Offsets all edges in the contour at contourIterator with the given offset preserving edge angles then regularizes the result
		void OffsetContour (const ConstContourIterator& contourIterator, double offset, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Moves the vertex at vertexIterator to newPosition then regularizes the result
		void MoveVertex (const ConstVertexIterator& vertexIterator, const Coord& newPosition, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates fillets with given radius at all vertices in the Polygon then regularizes the result
		void FilletAllVertex (const double filletRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a fillet with given radius at the vertex at vertexIterator then regularizes the result
		void FilletVertex (const ConstVertexIterator& vertexIterator, const double filletRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates fillets with given radius at all vertices in the contour at contourIterator then regularizes the result
		void FilletVertexInContour (const ConstContourIterator& contourIterator, const double filletRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates chamfers with given radius at all vertices in the Polygon then regularizes the result
		void ChamferAllVertex (const double chamferRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const										CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates a chamfer with given radius at the vertex at vertexIterator then regularizes the result
		void ChamferVertex (const ConstVertexIterator& vertexIterator, const double chamferRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Creates chamfers with given radius at all vertices in the contour at contourIterator then regularizes the result
		void ChamferVertexInContour (const ConstContourIterator& contourIterator, const double chamferRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Inserts a vertex on the edge at edgeIterator to newPosition then regularizes the result
		void InsertVertex (const ConstEdgeIterator& edgeIterator, const Coord& newPosition, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void InsertVertexOnPolygon (const Coord& newPosition, const ConstEdgeIterator& edgeIterator, CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result, ConstVertexIterator* vertexIterator = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Deletes the vertex at vertexIterator, connects the neighboring vertices then regularizes the result
		void DeleteVertex (const ConstVertexIterator& vertexIterator, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Sets the angle of the curve of the edge at edgeIterator to edgeAngle then regularizes the result
		void SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Replace more vertices
		void MoveVertices (const GS::Array<GS::Pair<ConstVertexIterator, Coord>>& newVertexPositions, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Replace edge at edgeIterator to genArc definition then regularizes the result
		void ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<GenArc>& arcs, const ArcDivParams& arcDivParams, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<double>& angles, const GS::Array<Coord>& internalVerts, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Deletes the edge at edgeIterator, connects the neighboring edges (the intersection creates a new Polygon vertex) then regularizes the result
		bool DeleteEdge (const ConstEdgeIterator& edgeIterator, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Adds the hole at contourIterator from poly then regularizes the result
		void AddHole (const CustomPolygon2D& poly, const ConstContourIterator& contourIterator, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the union of the two Polygons
		void Unify (const CustomPolygon2D& poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const														CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the intersections of the two Polygons
		void Intersect (const CustomPolygon2D& poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, Boundary boundaries = Boundary_Closed, RelativePosition* relativePosition = nullptr, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Substracts poly from the Polygon
		void Substract (const CustomPolygon2D& poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, Boundary boundaries = Boundary_Closed, RelativePosition* relativePosition = nullptr, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Returns the parts of the Polygon that are on the given half plane, determines whether it is cut or not
		void Cut (const HalfPlane2DData& cutline, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, bool& fullin, GS::Int32& wrcode, bool* degen = nullptr) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the parts of the Polygon that are on the given half planes, determines whether it is cut or not
		void Cut (const GS::Array<HalfPlane2DData>& cutlines, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, bool& fullin, GS::Int32& wrcode, bool* degen = nullptr) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the parts of the Polygon that are on the given half planes
		void Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, GS::Int32& wrcode) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Returns the parts of the Polygon that are in the clip box
		void Clip (const Box2DData& box, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, GS::Int32& wrcode) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		void Visit (VertexVisitor &visitor, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const;

		// Stores the intersections of the given sector and the Polygon in the creator
		// See creator interfaces in Poly2D.hpp
		void CutElem (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		// Stores the intersections of the given GenArc and the Polygon in the creator
		void CutElem (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the given coord in the creator if it is inside the Polygon
		void CutElem (const Coord& coord, Boundary cutBoundaries, PointCreator& creator) const									CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the intersections of the given spline and the Polygon in the creator
		void CutElem (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the intersections of the given Polygon and the host Polygon in the creator
		void CutElem (const CustomPolygon2D& polygon, Boundary cutBoundaries, CustomPolygon2DCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& creator) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the intersections of the given Polyline and the Polygon in the creator
		void CutElem (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, Boundary cutBoundaries, CustomPolyline2DCreator<VertexUserData, EdgeUserData, PolygonUserData>& creator) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Stores the intersections of the given sector and the Polygon in results
		void CutElem (const Sector& sector, Boundary cutBoundaries, GS::Array<Sector>& results) const							CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		// Stores the intersections of the given GenArc and the Polygon in results
		void CutElem (const GenArc& genArc, Boundary cutBoundaries, GS::Array<GenArc>& results) const							CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the given coord in results if it is inside the Polygon
		void CutElem (const Coord& coord, Boundary cutBoundaries, GS::Array<Coord>& results) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the intersections of the given spline and the Polygon in results
		void CutElem (const BezierDetails& bezier, Boundary cutBoundaries, GS::Array<BezierDetails>& results) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the intersections of the given Polygon and the host Polygon in results
		void CutElem (const CustomPolygon2D& poly, Boundary cutBoundaries, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & results) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the intersections of the given Polyline and the Polygon in results
		void CutElem (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary cutBoundaries, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& results) const							CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Stores the substraction results of the given sector and the Polygon in the creator
		// See creator interfaces in Poly2D.hpp
		void ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		// Stores the substraction results of the given GenArc and the Polygon in the creator
		void ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the given coord in the creator if it is not inside the Polygon
		void ElemPolyDifference (const Coord& coord, Boundary cutBoundaries, PointCreator& creator) const						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the substraction results of the given spline and the Polygon in the creator
		void ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the substraction results of the given Polygon and the host Polygon in the creator
		void ElemPolyDifference (const CustomPolygon2D& polygon, Boundary cutBoundaries, CustomPolygon2DCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& creator) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the substraction results of the given Polyline and the Polygon in results
		void ElemPolyDifference (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, Boundary cutBoundaries, CustomPolyline2DCreator<VertexUserData, EdgeUserData, PolygonUserData>& creator) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Stores the substraction results of the given sector and the Polygon in the creator
		// See creator interfaces in Poly2D.hpp
		void ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, GS::Array<Sector>& results) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		// Stores the substraction results of the given GenArc and the Polygon in the creator
		void ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GS::Array<GenArc>& results) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the given coord in the creator if it is not inside the Polygon
		void ElemPolyDifference (const Coord& coord, Boundary cutBoundaries, GS::Array<Coord>& results) const					CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the substraction results of the given spline and the Polygon in the creator
		void ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, GS::Array<BezierDetails>& results) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the substraction results of the given Polygon and the host Polygon in the creator
		void ElemPolyDifference (const CustomPolygon2D& polygon, Boundary cutBoundaries, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & results) const				CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Stores the substraction results of the given Polyline and the Polygon in results
		void ElemPolyDifference (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, Boundary cutBoundaries, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& results) const			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Determines whether the given sector overlaps with the Polygon
		bool ElemXPolygon (const Sector& sector, Boundary cutBoundaries) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		// Determines whether the given GenArc overlaps with the Polygon
		bool ElemXPolygon (const GenArc& genArc, Boundary cutBoundaries) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Determines whether the given Coord is inside the Polygon
		bool ElemXPolygon (const Coord& coord, Boundary cutBoundaries) const													CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Determines whether the given spline overlaps with the Polygon
		bool ElemXPolygon (const BezierDetails& bezier, Boundary cutBoundaries) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Determines whether the given Polygon overlaps with the Polygon
		bool ElemXPolygon (const CustomPolygon2D& polygon, Boundary cutBoundaries, bool& touching) const								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Determines whether the given Polyline overlaps with the Polygon
		bool ElemXPolygon (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, Boundary cutBoundaries) const											CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Inserts vertices into the given Polygons' edges where the two intersect
		static void CreateCommonEdgeSections (CustomPolygon2D& poly1, CustomPolygon2D& poly2, bool& changed)								CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Removes same directional edges from polygon if EdgeUserData is equal or comparable with a comparator
		template<class EdgeUserDataComparator>
		static void RemoveSameDirEdgesWithSameEdgeUserData (CustomPolygon2D& poly, const EdgeUserDataComparator& comparator);
		static void RemoveSameDirEdgesWithSameEdgeUserData (CustomPolygon2D& poly);
		// Inserts vertices into the given Polygons' edges where the x line intersect
		void InsertCommonXLineOnPolygon (double x, bool& changed, const EdgeSplitControl& cntrl = EdgeSplitControl ())			CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		// Inserts vertices into the given Polygons' edges where the x line intersect
		void InsertCommonYLineOnPolygon (double y, bool& changed, const EdgeSplitControl& cntrl = EdgeSplitControl ())			CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Debug
		void				Dump3DGDL		(Geometry::Plane * thePlane = nullptr, GS::OChannel& oc = dbChannel) const;
		template <class Output>
		void				Print			(Output& oc)	const;
		void				PrintDebug		(void)				const;
		void				PrintDebugXML	(void)				const;
		bool				Check			(PolyCheckFlags checkFlags,
											 double			coordUpperRange) const;
		PolyRepairResult	CheckAndRepair	(PolyCheckFlags checkFlags,
											 double			coordUpperRange);
	};

	typedef CustomPolygon2D<PolyId, PolyId, PolyId, PolyId> Polygon2D;

	template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
	inline GSErrCode	Read (GS::IChannel& ic, CustomPolygon2D<VertexUserData1, EdgeUserData1, ContourUserData1, PolygonUserData1> & polygon)			{ return polygon.Read (ic); }
	template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
	inline GSErrCode	Write (GS::OChannel& oc, const CustomPolygon2D<VertexUserData1, EdgeUserData1, ContourUserData1, PolygonUserData1> & polygon)	{ return polygon.Write (oc); }

	class GEOMETRY_DLL_EXPORT MultiPolygon2DPrivate {
	public:
		static GS::ClassInfo	classInfo;
	};

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
	class CustomMultiPolygon2D : public GS::Array<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >
	{
		template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
		friend class CustomPolygon2D;
		template <class VertexUserData1, class EdgeUserData1, class PolygonUserData1>
		friend class CustomPolyline2D;
	public:
		typedef CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> PolyType;

		CustomMultiPolygon2D ();
		CustomMultiPolygon2D (const CustomMultiPolygon2D& source);

		CustomMultiPolygon2D (const CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polys);

		virtual ~CustomMultiPolygon2D ();

		void Unify (PolyHoleHandling holeHandling = ReturnHoles)																CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		void SegmentUp (const ArcDivParams& arcDivParams)																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		void Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran)													CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		GSErrCode	Read (GS::IChannel& ic)																						CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::NullReferenceException));
		GSErrCode	Write (GS::OChannel& oc) const;
		
		GSErrCode	ReadXML	(GS::XMLIChannel& ic);
		GSErrCode	WriteXML (GS::XMLOChannel& oc) const																		CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Returns the largest area Polygon and deletes it from the MultiPolygon
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> PopLargest (void);
		// Returns the index of the largest area Polygon in the MultiPolygon
		GS::Int32 GetLargestIdx (void) const;
		// Returns overall bounding box
		Box2DData GetBoundBox (void) const																						CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		double CalcArea (void) const;
		void CalcConvexHull (const ArcDivParams& arcDivParams, GS::Array<Coord>& convexHull) const;

		RelativePosition GetPosition (const Coord& point, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		RelativePosition GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException));
		RelativePosition GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const		CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		RelativePosition GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		RelativePosition GetPosition (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));
		RelativePosition GetPosition (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed = nullptr) const	CAN_THROW ((GS::OutOfMemoryException, GeometryException));

		// Substracts all poly2 Polygons from all poly1 Polygons
		// returns false if the result is the same as poly1
		static bool Substract (const CustomMultiPolygon2D& poly1, const CustomMultiPolygon2D& poly2, CustomMultiPolygon2D& result);
		// Intersects all poly1 Polygons with all poly2 Polygons
		// if poly1 and poly2 are disjunct, the result will also be disjunct and will be the intersection of the disjunct areas
		static void Intersect (const CustomMultiPolygon2D& poly1, const CustomMultiPolygon2D& poly2, CustomMultiPolygon2D& result);

	protected:
		void GetCorePolygon2DArray (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray) const;
		void PushCorePolygon2DArray (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray);

		void PushResults (	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult, 
							const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& thisPoly, 
							const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& firstParam,
							const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray);
	};

	typedef CustomMultiPolygon2D<PolyId, PolyId, PolyId, PolyId> MultiPolygon2D;

} //Geometry namespace

#endif //GEOMETRY_POLYGON2D_CLASSDEFINITION_HPP
