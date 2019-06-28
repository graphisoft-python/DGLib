// *****************************************************************************
//
// Declaration of Polygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RA, RJ
//
// *****************************************************************************

#ifndef GEOMETRY_POLYGON2D_HPP
#define GEOMETRY_POLYGON2D_HPP

#if defined (_MSC_VER)
#pragma once
#endif

// --- Includes ----------------------------------------------------------------
#include "Polygon2DClassDefinition.hpp"

#include "Polyline2DClassDefinition.hpp"
#include "ConvexHull2DCreator.h"

namespace Geometry {

#if defined (DEBUVERS)
#define DEBUVERS_POLY2D
#endif

#if defined(DEBUVERS_POLY2D)
#define DBCHECKPOLYGONINDEX(idx, minIdx, maxIdx) DBASSERT ((idx) >= (minIdx) && (idx) <= (maxIdx))
#else
#define DBCHECKPOLYGONINDEX(idx, minIdx, maxIdx)
#endif

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetPolyContourUserData (void) const
{
	return poly->GetContourUserDataByIdx (index);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetVertexNum (void) const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return to - from;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetVertexIterator (UIndex vertexIdx) const
{
	if (poly == nullptr) {
		DBBREAK ();
		throw GeometryLogicErrorException ("Invalid polygon in CustomPolygon2D::Contour::GetVertexIterator!", __FILE__, __LINE__);
	}
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	DBCHECKPOLYGONINDEX(vertexIdx, poly->polygon->GetVertexBeginIdxInContour (index), poly->polygon->GetVertexEndIdxInContour (index));

	ConstPolyVertexInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, VertexUserData> item (poly, from, to, vertexIdx);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EnumerateVertex (void) const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetVertexIterator (from);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::BeginVertex (void) const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetVertexIterator (from);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EndVertex	(void) const
{
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return GetVertexIterator (to);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEdgeNum (void) const
{
	UIndex from = poly->polygon->GetEdgeBeginIdxInContour (index);
	UIndex to = poly->polygon->GetEdgeEndIdxInContour (index);
	return to - from;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEdgeIterator (UIndex edgeIdx) const
{
	if (poly == nullptr) {
		DBBREAK ();
		throw GeometryLogicErrorException ("Invalid polygon in CustomPolygon2D::Contour::GetEdgeIterator!!", __FILE__, __LINE__);
	}
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	DBCHECKPOLYGONINDEX(edgeIdx, poly->polygon->GetVertexBeginIdxInContour (index), poly->polygon->GetVertexEndIdxInContour (index));

	ConstPolyEdgeInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, EdgeUserData> item (poly, from, to, edgeIdx);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EnumerateEdge (void) const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetEdgeIterator (from);
}
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::BeginEdge (void) const
{
	UIndex from = poly->polygon->GetVertexBeginIdxInContour (index);
	return GetEdgeIterator (from);
}
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::EndEdge	(void) const
{
	UIndex to = poly->polygon->GetVertexEndIdxInContour (index);
	return GetEdgeIterator (to);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == poly->polygon);
	return GetVertexIterator (poly->polygon->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetEndVertex (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == poly->polygon);
	return GetVertexIterator (poly->polygon->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetNextEdge (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == poly->polygon);
	return GetEdgeIterator (poly->polygon->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Contour::GetPrevEdge (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (vertexIterator.GetTarget ()->polygon == poly->polygon);
	return GetEdgeIterator (poly->polygon->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > polygon2D) : polygon (polygon2D)
{
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	if (polygonArray.GetSize() == 0) {
		return;
	}

	UIndex idx;
	for(idx = 0; idx < polygonArray.GetSize(); idx++) {
		if (polygonArray[idx]->IsEmpty ()) {
			DBBREAK ();
			continue;
		}
		if (!polygonArray[idx]->status.isRegularized) {
			DBBREAK ();
			GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > regularizedPolygons;
			typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygonArray[idx]->Regularize (regularizedPolygons);
			switch (polyResult) {
			case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
				for(UIndex polyIdx = 0; polyIdx < regularizedPolygons.GetSize(); polyIdx++) {
					if (!regularizedPolygons [polyIdx]->status.isRegularized || regularizedPolygons [polyIdx]->IsEmpty ()) {
						DBBREAK ();
						continue;
					}
					CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPolygon (regularizedPolygons [polyIdx]);
					result.Push (tmpPolygon);
				}
				break;
			case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
				{
					CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPolygon (polygonArray[idx]);
					result.Push (tmpPolygon);
				}
				break;
			case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
				DBBREAK ();
				break;
			case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
				DBBREAK ();
				break;
			case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
				break;
			default:
				DBBREAK ();
				break;
			}
		} else {
			CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpPolygon (polygonArray[idx]);
			result.Push (tmpPolygon);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Regularize (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>&	irregularPolygon2D,
																								  CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> &			result,
																								  PolyRegularizationMode																			mode /*= PolyRegularizationMode_Default*/)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = irregularPolygon2D.polygon->Regularize (polygonArray, mode);
	if (polyResult == CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (irregularPolygon2D.polygon);
		result.Push (polygon);
	} else if (polyResult == CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon) {
		// do nothing
//		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> emptyPoly (new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*irregularPolygon2D.polygon, true));
//		result.Push (emptyPoly);
	} else {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateResult (typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult, const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> * firstParam, const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
{
	DBASSERT (polygon->status.isRegularized);
	switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*polygon);
				result.Push (newPolygon);
			}
#else
			result.Push (polygon);
#endif
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
			DBASSERT (firstParam != nullptr);
			if (firstParam != nullptr && firstParam->polygon->status.isRegularized && !firstParam->polygon->IsEmpty ()) {
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*(firstParam->polygon));
				result.Push (newPolygon);
#else
				result.Push (firstParam->polygon);
#endif
			}
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
			DBASSERT (firstParam != nullptr);
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				if (polygon->status.isRegularized && !polygon->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon1 = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*polygon);
					result.Push (newPolygon1);
				}
				if (firstParam != nullptr && firstParam->polygon->status.isRegularized && !firstParam->polygon->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon2 = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*(firstParam->polygon));
					result.Push (newPolygon2);
				}
			}
#else
			if (polygon->status.isRegularized && !polygon->IsEmpty ())
				result.Push (polygon);
			if (firstParam != nullptr && firstParam->polygon->status.isRegularized && !firstParam->polygon->IsEmpty ())
				result.Push (firstParam->polygon);
#endif
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
			break;
		default:
			DBBREAK ();
			break;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetResult (typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult, const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& newPoly)
{
	DBASSERT (polygon->status.isRegularized);
	switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			polygon = newPoly;
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData><VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon = new CorePolygon2D (*polygon);
				polygon = newPolygon;
			}
#endif
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
			DBBREAK ();
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
			DBBREAK ();
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
			polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*polygon, true);
			break;
		default:
			DBBREAK ();
			break;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyOnWrite (void)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	if (polygon == nullptr)
		throw GeometryUnexpectedExceptionException ("Polygon can't be nullptr!!!", __FILE__, __LINE__);
	if (polygon->GetRefCount() > 1)
		polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*polygon);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
	CheckPolyFlags (polyFlags);

	if (PolyFlags_IsSameDirEdgeLegal & polyFlags)
		flags.isSameDirEdgeLegal = true;
	if (PolyFlags_NoSameDirEdgeLegal & polyFlags)
		flags.isSameDirEdgeLegal = false;
	if (PolyFlags_Force64BitPrecision & polyFlags)
		flags.force64BitPrecision = true;
	if (PolyFlags_NoForce64BitPrecision & polyFlags)
		flags.force64BitPrecision = false;

	if (PolyFlags_IsVertexUserData & polyFlags)
		flags.isVertexUserData = true;
	if (PolyFlags_NoVertexUserData & polyFlags)
		flags.isVertexUserData = false;
	if (PolyFlags_IsEdgeUserData & polyFlags)
		flags.isEdgeUserData = true;
	if (PolyFlags_NoEdgeUserData & polyFlags)
		flags.isEdgeUserData = false;
	if (PolyFlags_IsContourUserData & polyFlags)
		flags.isContourUserData = true;
	if (PolyFlags_NoContourUserData & polyFlags)
		flags.isContourUserData = false;
	if (PolyFlags_IsPolygonUserData & polyFlags)
		flags.isPolygonUserData = true;
	if (PolyFlags_NoPolygonUserData & polyFlags)
		flags.isPolygonUserData = false;

	return flags;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (void)
{
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags);
#else
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags);
//	polygon = emptyPolygon;
#endif
	DBASSERT (polygon->status.isRegularized);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & source)
{
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*source.polygon);
#else
	polygon = source.polygon;
#endif
	DBASSERT (polygon->status.isRegularized);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (const Box2DData& box)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags, box);
	if (!polygon->status.isRegularized) {
		polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (GS::UInt32 flags /*PolyFlags*/)
{
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (GetFlags (flags));
	DBASSERT (polygon->status.isRegularized);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomPolygon2D (GS::UInt32 flags /*PolyFlags*/, const Box2DData& box)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (GetFlags (flags), box);
	if (!polygon->status.isRegularized) {
		polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (GetFlags (flags));
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::~CustomPolygon2D ()
{
	DBASSERT (polygon->status.isRegularized);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const ContourDescriptionArray& contourDescrArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, contourDescrArray, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (*polyline.polyline, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & irregularPolygon2D, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	if (irregularPolygon2D.polygon->status.isRegularized) {
		if (!irregularPolygon2D.polygon->IsEmpty ()) {
			CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> emptyPoly (irregularPolygon2D.polygon);
			result.Push (emptyPoly);
		}
		return;
	}

	Regularize (irregularPolygon2D, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const ContourDescriptionArray& contourDescrArray, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), contourDescrArray, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), coords, nValuableCoords, nullptr /*arcs*/, 0 /*nValuableArcs*/, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nArcs, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, coords, nValuableCoords, arcs, nArcs, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nArcs, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((nValuableCoords == 0 && coords == nullptr) || (nValuableCoords > 0 && coords != nullptr));

	if (nValuableCoords > 0 && coords != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), coords, nValuableCoords, arcs, nArcs, nullptr /*contourEnds*/, 1 /*nContours*/, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr));

	if (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const Coord* coords, USize nValuableCoords, const PolyArcRec* arcs, USize nValuableArcs, const UIndex* contourEnds, USize nContours, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((nValuableCoords == 0 && nContours == 0) || (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr));

	if (nValuableCoords > 0 && coords != nullptr && nContours > 0 && contourEnds != nullptr) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, coordList, arcList, contourEndList, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, const GS::Array<UIndex>& contourEndList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	DBASSERT ((coordList.IsEmpty () && contourEndList.IsEmpty ()) || (!coordList.IsEmpty () && !contourEndList.IsEmpty ()));

	if (!coordList.IsEmpty () && !contourEndList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		GS::Array<PolyArcRec> arcList;
		GS::Array<UIndex> contourEndList;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, coordList, arcList, contourEndList, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		GS::Array<PolyArcRec> arcList;
		GS::Array<UIndex> contourEndList;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		GS::Array<UIndex> contourEndList;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, coordList, arcList, contourEndList, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const GS::Array<Coord>& coordList, const GS::Array<PolyArcRec>& arcList, GS::UInt32 createFlags /*PolyCreateFlags*/, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	result.Clear ();

	if (!coordList.IsEmpty ()) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
		GS::Array<UIndex> contourEndList;
		CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), coordList, arcList, contourEndList, createFlags, polygonArray);
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	}
}

//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (const Polygon2DData& polygon2DData, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
//		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
//{
//	result.Clear ();
//
//	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
//	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
//	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (flags, polygon2DData, polygonArray);
//	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
//}

//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GS::UInt32 flags /*PolyFlags*/, const Polygon2DData& polygon2DData, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
//		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
//{
//	result.Clear ();
//
//	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
//	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (GetFlags (flags), polygon2DData, polygonArray);
//	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
//}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Convert (ContourDescriptionArray& contourDescrArray) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->Convert (contourDescrArray);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Convert (CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polylines) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (*this, polylines);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Convert (ConstContourIterator contourIterator, CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& polyline) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>::Create (*this, contourIterator, polyline);
}

//template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
//void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Convert (Polygon2DData& polygon2DData) const
//		CAN_THROW ((GS::OutOfMemoryException))
//{
//	DBASSERT (polygon->status.isRegularized);
//	polygon->Convert (polygon2DData);
//}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class VertexUserData1, class EdgeUserData1, class ContourUserData1, class PolygonUserData1>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConvertFromPolygon2D (CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, const CustomPolygon2D<VertexUserData1, EdgeUserData1, ContourUserData1, PolygonUserData1> & fromPolygon)
	CAN_THROW ((GS::OutOfMemoryException))
{
	DBASSERT (fromPolygon.polygon->status.isRegularized);
	result.CopyOnWrite ();
	CorePolygon2D<VertexUserData1, EdgeUserData1, ContourUserData1, PolygonUserData1>::ConvertFromCorePolygon2D (*result.polygon, *fromPolygon.polygon);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (Coord* coords, USize& nValuableCoords, PolyArcRec* arcs, USize& nValuableArcs, UIndex* contourEnds, USize& nContours, const GS::Array<ConstContourIterator>& reversedContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<UIndex> reversedContourIndices;
	for (typename GS::Array <ConstContourIterator>::ConstIterator contourIter = reversedContours.Enumerate (); contourIter != nullptr; ++contourIter) {
		reversedContourIndices.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->CopyPolygonData (coords, nValuableCoords, arcs, nValuableArcs, contourEnds, nContours, reversedContourIndices, createFlags);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CopyPolygonData (GS::Array<Coord>& coords, GS::Array<PolyArcRec>& arcs, GS::Array<UIndex>& contourEnds, const GS::Array<ConstContourIterator>& reversedContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<UIndex> reversedContourIndices;
	for (typename GS::Array <ConstContourIterator>::ConstIterator contourIter = reversedContours.Enumerate (); contourIter != nullptr; ++contourIter) {
		reversedContourIndices.Push (contourIter->GetItem ().GetIndex ());
	}
	polygon->CopyPolygonData (coords, arcs, contourEnds, reversedContourIndices, createFlags);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AllocateAndCopyPolygonData (Coord** coords, USize& nValuableCoords, PolyArcRec** arcs, USize& nValuableArcs, UIndex** contourEnds, USize& nContours, GS::UInt32 createFlags /*PolyCreateFlags*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (coords != nullptr && contourEnds != nullptr && (polygon->nArcs == 0 || arcs != nullptr));

	if (coords == nullptr || contourEnds == nullptr || (polygon->nArcs > 0 && arcs == nullptr))
		throw GeometryUnexpectedExceptionException ("Error in CustomPolygon2D::AllocateAndCopyPolygonData!!!", __FILE__, __LINE__);

	GS::Array<UIndex> reversedContourIndices;

	polygon->CopyPolygonData (nullptr, nValuableCoords, nullptr, nValuableArcs, nullptr, nContours, reversedContourIndices, createFlags);

	if (IsEmpty ())
		return;

	USize coordOffset = (PolyCreateFlags_DummyCoordAtIdxZero & createFlags) ? 1 : 0;
	*coords			= reinterpret_cast<Coord*>(BMAllocatePtr ((nValuableCoords + coordOffset) * sizeof (Coord), ALLOCATE_CLEAR, 0));

	if (arcs != nullptr) {
		USize arcOffset = (PolyCreateFlags_DummyArcAtIdxZero & createFlags) ? 1 : 0;
		*arcs			= reinterpret_cast<PolyArcRec*>(BMAllocatePtr ((nValuableArcs + arcOffset) * sizeof (PolyArcRec), ALLOCATE_CLEAR, 0));
	}

	USize contourEndOffset = (PolyCreateFlags_DummyContourEndAtIdxZero & createFlags) ? 1 : 0;
	*contourEnds	= reinterpret_cast<UIndex*>(BMAllocatePtr ((nContours + contourEndOffset) * sizeof (UIndex), ALLOCATE_CLEAR, 0));

	polygon->CopyPolygonData ((coords != nullptr) ? *coords : nullptr, nValuableCoords, (arcs != nullptr) ? *arcs : nullptr, nValuableArcs,
		(contourEnds != nullptr) ? *contourEnds : nullptr, nContours, reversedContourIndices, createFlags);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> &	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator= (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & source)
{
	if (this == &source)
		return *this;

	DBASSERT (polygon->status.isRegularized);
	if (polygon != source.polygon)
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
		polygon = new <VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*source.polygon);
#else
		polygon = source.polygon;
#endif
	return *this;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator== (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & rightOp) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Compare (*rightOp.polygon);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::operator!= (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & rightOp) const
{
	return !operator== (rightOp);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetSameDirEdgeLegal (bool isSameDirEdgeLegal)
{
	DBASSERT (polygon->status.isRegularized);
	if (polygon->flags.isSameDirEdgeLegal != isSameDirEdgeLegal) {
		CopyOnWrite ();
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->SetSameDirEdgeLegalAndRegularize (isSameDirEdgeLegal, result);
		switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			polygon = result[0];
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
		default:
			DBBREAK ();
			break;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetForce64BitPrecision (bool force64BitPrecision)
{
	DBASSERT (polygon->status.isRegularized);
	if (polygon->flags.force64BitPrecision != force64BitPrecision) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->SetForce64BitPrecision (force64BitPrecision, result);
		switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			polygon = result[0];
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
		default:
			DBBREAK ();
			break;
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSameDirEdgeLegal (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetSameDirEdgeLegal ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetForce64BitPrecision (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetForce64BitPrecision ();
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
	DBASSERT (polygon->status.isRegularized);
	CheckPolyFlags (polyFlags);
	DBASSERT (!((PolyFlags_Force64BitPrecision & polyFlags) && (PolyFlags_NoForce64BitPrecision & polyFlags)));

	if (PolyFlags_IsSameDirEdgeLegal & polyFlags && !polygon->flags.isSameDirEdgeLegal) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetSameDirEdgeLegal (true);
	}
	if (PolyFlags_NoSameDirEdgeLegal & polyFlags && polygon->flags.isSameDirEdgeLegal) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetSameDirEdgeLegal (false);
	}
	if (PolyFlags_Force64BitPrecision & polyFlags && !polygon->flags.force64BitPrecision) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetForce64BitPrecision (true);
	}
	if (PolyFlags_NoForce64BitPrecision & polyFlags && polygon->flags.force64BitPrecision) {
		CopyOnWrite (); //Csak egyszer fog masolni
		SetForce64BitPrecision (false);
	}
	if (PolyFlags_IsVertexUserData & polyFlags && !polygon->flags.isVertexUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsVertexUserData (true);
	}
	if (PolyFlags_NoVertexUserData & polyFlags && polygon->flags.isVertexUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsVertexUserData (false);
	}
	if (PolyFlags_IsEdgeUserData & polyFlags && !polygon->flags.isEdgeUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsEdgeUserData (true);
	}
	if (PolyFlags_NoEdgeUserData & polyFlags && polygon->flags.isEdgeUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsEdgeUserData (false);
	}
	if (PolyFlags_IsContourUserData & polyFlags && !polygon->flags.isContourUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsContourUserData (true);
	}
	if (PolyFlags_NoContourUserData & polyFlags && polygon->flags.isContourUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsContourUserData (false);
	}
	if (PolyFlags_IsPolygonUserData & polyFlags && !polygon->flags.isPolygonUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsPolygonUserData (true);
	}
	if (PolyFlags_NoPolygonUserData & polyFlags && polygon->flags.isPolygonUserData) {
		CopyOnWrite (); //Csak egyszer fog masolni
		polygon->SetIsPolygonUserData (false);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckPolyFlags (GS::UInt32 polyFlags /*PolyFlags*/)
{
#ifdef DEBUVERS
	DBASSERT (!((PolyFlags_IsSameDirEdgeLegal & polyFlags) && (PolyFlags_NoSameDirEdgeLegal & polyFlags)));
	DBASSERT (!(PolyFlags_IsClosed & polyFlags));
	DBASSERT (!(PolyFlags_NoClosed & polyFlags));
	DBASSERT (!(PolyFlags_IsSameCoord & polyFlags));
	DBASSERT (!(PolyFlags_NoSameCoord & polyFlags));
	DBASSERT (!((PolyFlags_IsVertexUserData & polyFlags) && (PolyFlags_NoVertexUserData & polyFlags)));
	DBASSERT (!((PolyFlags_IsEdgeUserData & polyFlags) && (PolyFlags_NoEdgeUserData & polyFlags)));
	DBASSERT (!((PolyFlags_IsContourUserData & polyFlags) && (PolyFlags_NoContourUserData & polyFlags)));
	DBASSERT (!((PolyFlags_IsPolygonUserData & polyFlags) && (PolyFlags_NoPolygonUserData & polyFlags)));
#else
	UNUSED_PARAMETER (polyFlags);
#endif
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::UInt32 CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyFlags () const //PolyFlags
{
	DBASSERT (polygon->status.isRegularized);
	GS::UInt32 flags = 0;

	if (polygon->GetSameDirEdgeLegal ())
		flags |= PolyFlags_IsSameDirEdgeLegal;
	else 
		flags |= PolyFlags_NoSameDirEdgeLegal;

	if (polygon->GetIsVertexUserData ())
		flags |= PolyFlags_IsVertexUserData;
	else 
		flags |= PolyFlags_NoVertexUserData;

	if (polygon->GetIsEdgeUserData ())
		flags |= PolyFlags_IsEdgeUserData;
	else 
		flags |= PolyFlags_NoEdgeUserData;

	if (polygon->GetIsContourUserData ())
		flags |= PolyFlags_IsContourUserData;
	else 
		flags |= PolyFlags_NoContourUserData;

	if (polygon->GetIsPolygonUserData ())
		flags |= PolyFlags_IsPolygonUserData;
	else 
		flags |= PolyFlags_NoPolygonUserData;

	return flags;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIterator (UIndex vertexIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	DBCHECKPOLYGONINDEX(vertexIdx, 1, polygon->GetVertexNum () + 1);

	ConstPolyVertexInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, VertexUserData> item (this, vertexIdx);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexIterator (const Coord& coord) const
{
	DBASSERT (polygon->status.isRegularized);
	return GetVertexIterator(polygon->GetVertexIdx(coord));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateVertex (void) const
{
	return GetVertexIterator(1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginVertex (void) const
{
	return GetVertexIterator (1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndVertex	(void) const
{
	DBASSERT (polygon->status.isRegularized);
	return GetVertexIterator (polygon->GetVertexNum() + 1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateVertex (const VertexUserData& id) const
{
	ConstPolyVertexInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, VertexUserData> item (this, id);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeIterator (UIndex edgeIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	DBCHECKPOLYGONINDEX(edgeIdx, 1, polygon->GetEdgeNum () + 1);

	ConstPolyEdgeInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, EdgeUserData> item (this, edgeIdx);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateEdge (void) const
{
	return GetEdgeIterator (1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginEdge (void) const
{
	return GetEdgeIterator (1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndEdge	(void) const
{
	DBASSERT (polygon->status.isRegularized);
	return GetEdgeIterator (polygon->GetEdgeNum() + 1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateEdge (const EdgeUserData& id) const
{
	ConstPolyEdgeInPolyState<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>, EdgeUserData> item (this, id);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourIterator (UIndex contourIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	DBCHECKPOLYGONINDEX(contourIdx, 1, polygon->GetContourNum () + 1);

	Contour item (this, contourIdx);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateContour (void) const
{
	return GetContourIterator(1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::BeginContour (void) const
{
	return GetContourIterator (1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EndContour	(void) const
{
	DBASSERT (polygon->status.isRegularized);
	return GetContourIterator (polygon->GetContourNum() + 1);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateContour (const ContourUserData& id) const
{
	Contour item (this, id);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EnumerateHoleContour (void) const
{
	DBASSERT (polygon->status.isRegularized);
	Contour item (this, 2, polygon->GetContourNum(), 2);
	return CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstContourIterator (item);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetPolyUserData (const PolygonUserData& polyId)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->SetUserData (&polyId);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const PolygonUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPolyUserData (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return *polygon->GetUserData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexDefaultUserData (const VertexUserData& userData)
{
	CopyOnWrite ();
	polygon->SetVertexDefaultUserData (userData);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResetUserData (void)
{
	CopyOnWrite ();
	polygon->ResetUserData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexDefaultUserData (void) const
{
	return polygon->GetVertexDefaultUserData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexNum (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetVertexNum ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertex (const ConstVertexIterator& vertexIterator, Vertex& vertex) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	vertex.SetCoord (polygon->GetCoord (vertexIterator.GetItem ().GetIndex ()));
	vertex.SetPolyVertexUserData (*polygon->GetVertexUserData (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Coord& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCoord (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return polygon->GetCoord (vertexIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const VertexUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetVertexUserData (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetVertexUserData (vertexIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetVertexUserData (const ConstVertexIterator& vertexIterator, const VertexUserData& vertexId)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetVertexUserData (vertexIterator.GetItem ().GetIndex (), &vertexId);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeDefaultUserData (const EdgeUserData& userData)
{
	CopyOnWrite ();
	polygon->SetEdgeDefaultUserData (userData);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeDefaultUserData (void) const
{
	return polygon->GetEdgeDefaultUserData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeNum (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetEdgeNum ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdge (const ConstEdgeIterator& edgeIterator, Edge& edge) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	edge.SetArcAngle(polygon->GetArcAngle (edgeIterator.GetItem ().GetIndex ()));
	edge.SetPolyEdgeUserData(*polygon->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Sector& sect, GenArc& genArc) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex (), sect, genArc);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetSector (const ConstEdgeIterator& edgeIterator, Coord& begC, Coord& endC, double& angle) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return polygon->GetSector (edgeIterator.GetItem ().GetIndex (), begC, endC, angle);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const EdgeUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEdgeUserData (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetEdgeUserData (edgeIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeUserData (const ConstEdgeIterator& edgeIterator, const EdgeUserData& edgeId)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetEdgeUserData (edgeIterator.GetItem ().GetIndex (), &edgeId);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourDefaultUserData (const ContourUserData& userData)
{
	CopyOnWrite ();
	polygon->SetContourDefaultUserData (userData);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourDefaultUserData (void) const
{
	return polygon->GetContourDefaultUserData ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
USize CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourNum (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetContourNum ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContour (const ConstContourIterator& contourIterator, CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & contour) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	contour.polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*polygon, contourIterator.GetItem ().GetIndex (), true /*keepRegularized*/);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const ContourUserData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetContourUserData (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return *polygon->GetContourUserData (contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetContourUserData (const ConstContourIterator& contourIterator, const ContourUserData& contourId)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	polygon->SetContourUserData (contourIterator.GetItem ().GetIndex (), &contourId);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBeginVertex (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return GetVertexIterator (polygon->GetBeginVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstVertexIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetEndVertex (const ConstEdgeIterator& edgeIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	return GetVertexIterator (polygon->GetEndVertexIdxOfEdge (edgeIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetNextEdge (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return GetEdgeIterator (polygon->GetNextEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
typename CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstEdgeIterator CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPrevEdge (const ConstVertexIterator& vertexIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return GetEdgeIterator (polygon->GetPrevEdgeIdxOfVertex (vertexIterator.GetItem ().GetIndex ()));
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsVertexInContour (UIndex contourIdx, UIndex vertexIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	if (vertexIdx < polygon->GetVertexBeginIdxInContour (contourIdx))
		return false;
	if (vertexIdx >= polygon->GetVertexEndIdxInContour (contourIdx))
		return false;

	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsEdgeInContour (UIndex contourIdx, UIndex edgeIdx) const
{
	DBASSERT (polygon->status.isRegularized);
	if (edgeIdx < polygon->GetEdgeBeginIdxInContour (contourIdx))
		return false;
	if (edgeIdx >= polygon->GetEdgeEndIdxInContour (contourIdx))
		return false;

	return true;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsEmpty (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->IsEmpty ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasArcs (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->nArcs > 0;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clear (void)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->Clear ();
//	polygon = emptyPolygon;
	DBASSERT (polygon->status.isRegularized);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsABox (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->IsABox ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Flags flags;
	polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (flags);
	DBASSERT (polygon->status.isRegularized);
	return polygon->Read (ic);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Write (oc);
}

extern GEOMETRY_DLL_EXPORT const char*		XMLPolygon_Tag_Polygon2D;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::XMLITag tag (ic, XMLPolygon_Tag_Polygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == Polygon2DPrivate::classInfo.GetVersion ());
	}

	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >  newPolygon 
		= CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXMLAndCreate (ic);

	if (newPolygon == nullptr)
		throw GeometryUnexpectedExceptionException ("Can't Read XML file!!!", __FILE__, __LINE__);

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > regularizedPolygons;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = newPolygon->Regularize (regularizedPolygons);
	if (polyResult == CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis) {
		polygon = newPolygon;
	} else if (polyResult == CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon) {
		polygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*newPolygon, true);
	} else {
		DBASSERT (regularizedPolygons.GetSize () <= 1);
		if (regularizedPolygons.GetSize () > 0)
			polygon = regularizedPolygons [0];
		else
			Clear ();
	}

	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, XMLPolygon_Tag_Polygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (Polygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	errCode = polygon->WriteXML (oc);
	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}

//Calculate
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
const Box2DData& CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox (void) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
//	if (polygon->IsEmpty ())
//		return emptyPolygon->GetBoundBox ();
	return polygon->GetBoundBox ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Coord CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCenter (void) const
{
	DBASSERT (polygon->status.isRegularized);
	Box2DData polyBoundBox = polygon->GetBoundBox ();
	Coord centerC  = Geometry::SetCoord ((polyBoundBox.xMin + polyBoundBox.xMax) / 2.0, (polyBoundBox.yMin + polyBoundBox.yMax) / 2.0);
	return centerC;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcArea (void) const
{
	return polygon->CalcArea ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourArea (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcContourArea (contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::HasPositiveOrientation (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->HasPositiveOrientation (contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcPerimeter (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->CalcPerimeter ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcContourPerimeter (const ConstContourIterator& contourIterator) const
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcPerimeter (contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcConvexHull (const ArcDivParams& arcDivParams, GS::Array<Coord>& convexHull) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->CalcConvexHull (arcDivParams, convexHull);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcMaxVertexFillet (const ConstVertexIterator& vertexIterator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	return polygon->CalcMaxVertexFillet (vertexIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::IsCoordOnEdge (const Coord& c, ConstEdgeIterator* edgeIt) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	UIndex edgeIndex;
	bool result = polygon->IsCoordOnEdge (c, edgeIndex);
	if (edgeIt != nullptr) {
		if (result)
			*edgeIt = GetEdgeIterator (edgeIndex);
		else
			*edgeIt = ConstEdgeIterator ();
	}
	return result;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DistanceFromPoint (const Coord& c) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	return polygon->DistanceFromPoint (c);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Coord& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (point, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (sect, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (arc, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (box, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (*poly.polygon, boundaries, detailed);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->GetPosition (*poly.polyline, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentIn (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->SegmentIn (sector, resSectors);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PGPositionExt CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentOut (Sector sector, GS::Array<Sector>* resSectors /*= nullptr*/) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->SegmentOut (sector, resSectors);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const Coord& c, const Vector& dir, GS::Array<Sector>* result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Intersect (c, dir, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetTransformedBoundBox (Coord box[4], const TRANMAT* tr, const TRANMAT* invTr /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->GetTransformedBoundBox (box, tr, invTr);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (ConstVertexVisitor &visitor) const
{
	DBASSERT (polygon->status.isRegularized);
	polygon->Visit (visitor);
}

//Modify polygon
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveHoles (void)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > result;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->RemoveHoles (result);
	SetResult (polyResult, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteHole (const ConstContourIterator& contourIterator)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	CopyOnWrite ();
	DBASSERT (polygon->status.isRegularized);
	polygon = polygon->DeleteHole (contourIterator.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Move (Vector offset)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->Move (offset);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearVertexIds (void)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->ClearVertexUserDatas ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearEdgeIds (void)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->ClearEdgeUserDatas ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ClearContourIds (void)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->ClearContourUserDatas ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RotateVerticeIndicesInContour (const ConstContourIterator& contourToRotate, const ConstVertexIterator& vertexToFirst)
{
	DBASSERT (polygon->status.isRegularized);
	if (contourToRotate->BeginVertex () == vertexToFirst) {
		return;
	}
	
	CopyOnWrite ();
	polygon->RotateVerticeIndicesInContour (contourToRotate.GetItem ().GetIndex (), vertexToFirst.GetItem ().GetIndex ());
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SwapContourOrder (const GS::Array<ConstContourIterator>& newContourOrder)
{
	DBASSERT (polygon->status.isRegularized);
	if (newContourOrder.GetSize () < 2) {
		return;
	}
	bool inOrder = true;
	UInt32 i = 0;
	for (auto cIt = EnumerateContour (); cIt != nullptr && inOrder; ++cIt) {
		inOrder = cIt == newContourOrder [i++];
	}
	if (inOrder) {
		return;
	}

	CopyOnWrite ();

	GS::Array<UIndex> newContourOrderInIdx;
	newContourOrderInIdx.SetCapacity (newContourOrder.GetSize ());
	for (UIndex i = 0; i < newContourOrder.GetSize (); ++i)
		newContourOrderInIdx.Push (newContourOrder[i].GetItem ().GetIndex ());

	polygon->SwapContourOrder (newContourOrderInIdx);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SortArcsByIndices (void)
{
	DBASSERT (polygon->status.isRegularized);
	CopyOnWrite ();
	polygon->SortArcsByIndices ();
}

//Create new polygons
template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Transform (arcDivParams, tran, polygonArray);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & filterWithPolygon, 
						   const ArcDivParams& arcDivParams, 
						   const TRANMAT& tran, 
						   CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, 
						   bool& isTransformedAll) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Transform (*filterWithPolygon.polygon, arcDivParams, tran, polygonArray, isTransformedAll);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (	const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & filterWithPolygon, 
							const ArcDivParams& arcDivParams, 
							const TRANMAT& tran, 
							CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, 
							bool& isTransformedAll) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > filterPolygonArray;
	filterWithPolygon.GetCorePolygon2DArray (filterPolygonArray);
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Transform (filterPolygonArray, arcDivParams, tran, polygonArray, isTransformedAll);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->SegmentUp (arcDivParams, polygonArray);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EliminateArcs (Geometry::CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->EliminateArcs (polygonArray);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetContour (const ConstContourIterator& contourIterator, double offset, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->OffsetContour (contourIterator.GetItem ().GetIndex (), offset, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdge (const ConstEdgeIterator& edgeIterator, double offset, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->OffsetEdge (edgeIterator.GetItem ().GetIndex (), offset, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::OffsetEdgeFixArea (const ConstEdgeIterator& edgeIterator, const ConstVertexIterator& vertexIterator, double offset, double area, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->OffsetEdgeFixArea (edgeIterator.GetItem ().GetIndex (), vertexIterator.GetItem ().GetIndex (), offset, area, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertex (const ConstVertexIterator& vertexIterator, const Coord& newPosition, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->MoveVertex (vertexIterator.GetItem ().GetIndex (), newPosition, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletAllVertex (const double filletRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->FilletAllVertex (filletRadius, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertex (const ConstVertexIterator& vertexIterator, const double filletRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->FilletVertex (vertexIterator.GetItem ().GetIndex (), filletRadius, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::FilletVertexInContour (const ConstContourIterator& contourIterator, const double filletRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->FilletVertexInContour (contourIterator.GetItem ().GetIndex (), filletRadius, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferAllVertex (const double chamferRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->ChamferAllVertex (chamferRadius, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertex (const ConstVertexIterator& vertexIterator, const double chamferRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->ChamferVertex (vertexIterator.GetItem ().GetIndex (), chamferRadius, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ChamferVertexInContour (const ConstContourIterator& contourIterator, const double chamferRadius, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->ChamferVertexInContour (contourIterator.GetItem ().GetIndex (), chamferRadius, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertex (const ConstEdgeIterator& edgeIterator, const Coord& newPosition, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->InsertVertex (edgeIterator.GetItem ().GetIndex (), newPosition, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertVertexOnPolygon (const Coord& newPosition, const ConstEdgeIterator& edgeIterator, CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& result, ConstVertexIterator* vertexIterator /*= nullptr*/) const
CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	
	UIndex vertexIndex = 0;
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>> newPolygon;
	polygon->InsertVertexOnPolygon (newPosition, edgeIterator.GetItem ().GetIndex (), newPolygon, vertexIndex);
	result.polygon = newPolygon;
	if (vertexIterator != nullptr)
		*vertexIterator = result.GetVertexIterator (vertexIndex);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteVertex (const ConstVertexIterator& vertexIterator, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (vertexIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->DeleteVertex (vertexIterator.GetItem ().GetIndex (), polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SetEdgeAngle (const ConstEdgeIterator& edgeIterator, double edgeAngle, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->SetEdgeAngle (edgeIterator.GetItem ().GetIndex (), edgeAngle, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::MoveVertices (const GS::Array<GS::Pair<ConstVertexIterator, Coord>>& newVertexPositions, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);

	GS::HashTable<UIndex, Coord> indexToCoordTable;
	for (const GS::Pair<ConstVertexIterator, Coord>& vertexWithPosition : newVertexPositions) {
		DBASSERT (vertexWithPosition.first.GetTarget ()->polygon == polygon);
		UIndex vertexIndex = vertexWithPosition.first.GetItem ().GetIndex ();
		DBASSERT (!indexToCoordTable.ContainsKey (vertexIndex));
		indexToCoordTable.Add (vertexIndex, vertexWithPosition.second);
	}
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->MoveVertices (indexToCoordTable, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<GenArc>& arcs, const ArcDivParams& arcDivParams, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), arcs, arcDivParams, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReplaceEdge (const ConstEdgeIterator& edgeIterator, const GS::Array<double>& angles, const GS::Array<Coord>& internalVerts, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->ReplaceEdge (edgeIterator.GetItem ().GetIndex (), angles, internalVerts, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::DeleteEdge (const ConstEdgeIterator& edgeIterator, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (edgeIterator.GetTarget ()->polygon == polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	bool success = polygon->DeleteEdge (edgeIterator.GetItem ().GetIndex (), polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
	return success;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::AddHole (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, const ConstContourIterator& contourIterator, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	DBASSERT (contourIterator.GetTarget ()->polygon == poly.polygon);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->AddHole (*poly.polygon, contourIterator.GetItem ().GetIndex (), polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Unify (*poly.polygon, polygonArray);
	CreateResult (polyResult, &poly, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, Boundary boundaries /*= Boundary_Closed*/, RelativePosition* relativePosition /*= nullptr*/, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Intersect (*poly.polygon, polygonArray, boundaries, relativePosition, detailed);
	CreateResult (polyResult, &poly, polygonArray, result);
}


template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& poly, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, Boundary boundaries /*= Boundary_Closed*/, RelativePosition* relativePosition /*= nullptr*/, DetailedRelativePosition* detailed /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Substract (*poly.polygon, polygonArray, boundaries, relativePosition, detailed);
	CreateResult (polyResult, &poly, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const HalfPlane2DData& cutline, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, bool& fullin, GS::Int32& wrcode, bool* degen /*= nullptr*/) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Cut (cutline, true /*regularizeResults*/, polygonArray, fullin, wrcode, degen);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Cut (const GS::Array<HalfPlane2DData>& cutlines, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, bool& fullin, GS::Int32& wrcode, bool* degen /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Cut (cutlines, true /*regularizeResults*/, polygonArray, fullin, wrcode, degen);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Strip (const HalfPlane2DData& cutline1, const HalfPlane2DData& cutline2, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, GS::Int32& wrcode) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Strip (cutline1, cutline2, true /*regularizeResults*/, polygonArray, wrcode);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Clip (const Box2DData& box, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result, GS::Int32& wrcode) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	result.Clear ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = polygon->Clip (box, true /*regularizeResults*/, polygonArray, wrcode);
	CreateResult (polyResult, nullptr, polygonArray, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Visit (VertexVisitor &visitor, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result) const
{
	DBASSERT (polygon->status.isRegularized);

	CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> irregularPolygon (*this);

	irregularPolygon.Visit (visitor);

	Create (irregularPolygon, result);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (sector, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (genArc, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Coord& coord, Boundary cutBoundaries, PointCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (coord, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (bezier, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary cutBoundaries, CustomPolygon2DCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > results;
	polygon->CutElem (poly.polygon, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (results[polyIdx]);
		creator.CreatePolygon2D (polygon);
	}

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary cutBoundaries, CustomPolyline2DCreator<VertexUserData, EdgeUserData, PolygonUserData>& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > > results;
	polygon->CutElem (poly.polyline, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (results[polyIdx]);
		creator.CreatePolyline2D (polyline);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Sector& sector, Boundary cutBoundaries, GS::Array<Sector>& results) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (sector, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const GenArc& genArc, Boundary cutBoundaries, GS::Array<GenArc>& results) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (genArc, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const Coord& coord, Boundary cutBoundaries, GS::Array<Coord>& results) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (coord, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const BezierDetails& bezier, Boundary cutBoundaries, GS::Array<BezierDetails>& results) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->CutElem (bezier, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary cutBoundaries, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & results) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->CutElem (poly.polygon, cutBoundaries, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CutElem (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary cutBoundaries, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& results) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > > polylineArray;
	polygon->CutElem (poly.polyline, cutBoundaries, polylineArray);
	for (typename GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >::Iterator lineIter = polylineArray.Enumerate (); lineIter != nullptr; ++lineIter) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmpPolyline;
		tmpPolyline.polyline = *lineIter;
		results.Push (tmpPolyline);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, SectorCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (sector, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GenArcCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (genArc, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Coord& coord, Boundary cutBoundaries, PointCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (coord, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, SplineCreator& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (bezier, cutBoundaries, creator);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary cutBoundaries, CustomPolygon2DCreator<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > results;
	polygon->ElemPolyDifference (poly.polygon, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> polygon (results[polyIdx]);
		creator.CreatePolygon2D (polygon);
	}

}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary cutBoundaries, CustomPolyline2DCreator<VertexUserData, EdgeUserData, PolygonUserData>& creator) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > > results;
	polygon->ElemPolyDifference (poly.polyline, cutBoundaries, results);
	for (UIndex polyIdx = 0; polyIdx < results.GetSize (); polyIdx++) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> polyline (results[polyIdx]);
		creator.CreatePolyline2D (polyline);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Sector& sector, Boundary cutBoundaries, GS::Array<Sector>& results) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (sector, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const GenArc& genArc, Boundary cutBoundaries, GS::Array<GenArc>& results) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (genArc, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const Coord& coord, Boundary cutBoundaries, GS::Array<Coord>& results) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (coord, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const BezierDetails& bezier, Boundary cutBoundaries, GS::Array<BezierDetails>& results) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	polygon->ElemPolyDifference (bezier, cutBoundaries, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary cutBoundaries, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & results) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	polygon->ElemPolyDifference (poly.polygon, cutBoundaries, polygonArray);
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (polygonArray, results);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemPolyDifference (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary cutBoundaries, CustomMultiPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& results) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > > polylineArray;
	polygon->ElemPolyDifference (poly.polyline, cutBoundaries, polylineArray);
	for (typename GS::Array<GS::SharedPtr<CorePolyline2D<VertexUserData, EdgeUserData, PolygonUserData> > >::Iterator lineIter = polylineArray.Enumerate (); lineIter != nullptr; ++lineIter) {
		CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData> tmpPolyline;
		tmpPolyline.polyline = *lineIter;
		results.Push (tmpPolyline);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Sector& sector, Boundary cutBoundaries) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (sector, cutBoundaries);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const GenArc& genArc, Boundary cutBoundaries) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (genArc, cutBoundaries);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const Coord& coord, Boundary cutBoundaries) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (coord, cutBoundaries);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const BezierDetails& bezier, Boundary cutBoundaries) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (bezier, cutBoundaries);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary cutBoundaries, bool& touching) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (poly.polygon, cutBoundaries, touching);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ElemXPolygon (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary cutBoundaries) const
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->ElemXPolygon (poly.polyline, cutBoundaries);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateCommonEdgeSections (CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly1, CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly2, bool& changed)
		CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CreateCommonEdgeSections (*poly1.polygon, *poly2.polygon, true, result, changed);
	if (changed && DBVERIFY (result.GetSize () == 2)) {
		poly1.polygon = result [0];
		poly2.polygon = result [1];
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template<class EdgeUserDataComparator>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdgesWithSameEdgeUserData (CustomPolygon2D& poly, const EdgeUserDataComparator& comparator)
{
	DBASSERT (poly.polygon->status.isRegularized);
	poly.CopyOnWrite ();
	poly.polygon->RemoveSameDirEdgesOnlyWithSameUserData (comparator);

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = poly.polygon->Regularize (result);
	switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			poly.polygon = result[0];
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
		default:
			DBBREAK ();
			break;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::RemoveSameDirEdgesWithSameEdgeUserData (CustomPolygon2D& poly)
{
	DBASSERT (poly.polygon->status.isRegularized);
	poly.CopyOnWrite ();
	poly.polygon->RemoveSameDirEdgesOnlyWithSameUserData ();

	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = poly.polygon->Regularize (result);
	switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			DBASSERT (result.GetSize () == 1);
			poly.polygon = result[0];
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
		default:
			DBBREAK ();
			break;
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonXLineOnPolygon (double x, bool& changed, const EdgeSplitControl& cntrl)
CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	polygon->InsertCommonXLineOnPolygon (x, changed, cntrl);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::InsertCommonYLineOnPolygon (double y, bool& changed, const EdgeSplitControl& cntrl)
CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	polygon->InsertCommonYLineOpPolygon (y, changed, cntrl);
}

// Debug

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Dump3DGDL (Geometry::Plane * thePlane/* = nullptr*/, GS::OChannel& oc/* = dbChannel*/) const
{
	polygon->Dump3DGDL (thePlane, oc);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
template <class Output>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Print	(Output& oc) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Print (oc);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PrintDebug (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->PrintDebug ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PrintDebugXML (void) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->PrintDebugXML ();
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Check (PolyCheckFlags checkFlags, double coordUpperRange) const
{
	DBASSERT (polygon->status.isRegularized);
	return polygon->Check (checkFlags, nullptr, coordUpperRange);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
PolyRepairResult	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CheckAndRepair (PolyCheckFlags checkFlags, double coordUpperRange )
{
	PolyCheckFlags errorType;
	PolyRepairResult result;
	result.succeeded = true;
	result.modified = false;

	while (!polygon->Check (checkFlags, &errorType, coordUpperRange)) {
		if ((errorType & checkFlags) == 0) {
			result.succeeded = false;
			return result;
		} else {
			CopyOnWrite ();
			PolyRepairResult resultTemp = polygon->Repair (errorType);
			result.modified = (result.modified || resultTemp.modified);
			if (!resultTemp.succeeded) {
				result.succeeded = false;
				return result;
			}
		}
	}

	return result;
}

//************************************** CustomMultiPolygon2D ***********************************

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiPolygon2D () :
	GS::Array<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > ()
{
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiPolygon2D (const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & source) :
	GS::Array<CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > (source)
{
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CustomMultiPolygon2D (const CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & polys)
{
	for (typename Geometry::CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstIterator it = polys.Enumerate (); it != nullptr; ++it) {
		CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> irregularPolygon2D = *it;
		CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmp;
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Create (irregularPolygon2D, tmp);

		for (typename Geometry::CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstIterator it2 = tmp.Enumerate (); it2 != nullptr; ++it2)
			this->Push (*it2);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::~CustomMultiPolygon2D ()
{}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (PolyHoleHandling holeHandling /*= ReturnHoles*/)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > corePolygonArray;
	GetCorePolygon2DArray (corePolygonArray);
	this->Clear ();
	CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Unify (corePolygonArray, holeHandling);
	PushCorePolygon2DArray (corePolygonArray);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::SegmentUp (const ArcDivParams& arcDivParams)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > corePolygonArray;
	GetCorePolygon2DArray (corePolygonArray);
	this->Clear ();
	GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > firstParam;
	for (UIndex polyIdx = 0; polyIdx < corePolygonArray.GetSize (); polyIdx++) {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
		typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = corePolygonArray[polyIdx]->SegmentUp (arcDivParams, result);
		PushResults (polyResult, corePolygonArray[polyIdx], firstParam, result);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Transform (const ArcDivParams& arcDivParams, const TRANMAT& tran)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	if (tran.status & TR_IDENT) {
		return;
	}

	bool isPreserveArc = Geometry::TMIsPreserveArc (tran);
	if (isPreserveArc) {
		CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> irregularPolygons;
		for (UIndex idx = 0; idx < this->GetSize(); idx++) {
			CustomIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> irregularPolygon (this->Get(idx));
			irregularPolygon.CopyOnWrite ();
			irregularPolygon.TransformPreserveArcs (tran);
			irregularPolygons.Push (irregularPolygon);
		}
		this->Clear ();
		for (typename Geometry::CustomMultiIrregularPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstIterator irrPolyIt = irregularPolygons.Enumerate (); irrPolyIt != nullptr; ++irrPolyIt) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> regularizedPolygons;
			irrPolyIt->Regularize (regularizedPolygons);
			for (typename Geometry::CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ConstIterator polyIt = regularizedPolygons.Enumerate (); polyIt != nullptr; ++polyIt)
				this->Push (*polyIt);
		}

	} else {
		GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > corePolygonArray;
		GetCorePolygon2DArray (corePolygonArray);
		this->Clear ();
		GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > firstParam;
		for (UIndex polyIdx = 0; polyIdx < corePolygonArray.GetSize (); polyIdx++) {
			GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > result;
			typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult = corePolygonArray[polyIdx]->Transform (arcDivParams, tran, result);
			PushResults (polyResult, corePolygonArray[polyIdx], firstParam, result);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Read (GS::IChannel& ic)
	CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::NullReferenceException))
{
	NULL_REF_CHECK (ic);

	this->Clear ();

	GS::InputFrame frame (ic, MultiPolygon2DPrivate::classInfo);
	if (frame.GetStatus () != NoError)
		return frame.GetStatus ();

	USize newSize = 0;
	GSErrCode errorCode = ic.Read (newSize);
	if (errorCode == NoError)
		this->SetSize (newSize);

	for (UIndex i = 0; i < newSize && errorCode == NoError; i++)
		errorCode = this->Get (i).Read (ic);

	return errorCode;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Write (GS::OChannel& oc) const
{
	NULL_REF_CHECK (oc);

	GS::OutputFrame frame (oc, MultiPolygon2DPrivate::classInfo);

	GSErrCode errorCode = oc.Write (this->GetSize ());

	for (UIndex i = 0; i < this->GetSize () && errorCode == NoError; i++)
		errorCode = this->Get (i).Write (oc);

	return errorCode;
}

extern	GEOMETRY_DLL_EXPORT const char*		XMLPolygon_Tag_MultiPolygon2D;
extern	GEOMETRY_DLL_EXPORT const char*		XMLPolygon_Attr_PolyNum;

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ReadXML	(GS::XMLIChannel& ic)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tagMultiPolygon2D (ic, XMLPolygon_Tag_MultiPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		GS::ClassVersion currentClassVersion;
		ic.ReadXMLVersionAttr (currentClassVersion);
		//currentClassVersion.ReadXML (ic);
		DBASSERT (currentClassVersion == MultiPolygon2DPrivate::classInfo.GetVersion ());
	}

	USize newSize = 0;
	if (errCode == NoError)
		errCode = ic.ReadXMLAttr (XMLPolygon_Attr_PolyNum, newSize);

	GS::UniString tokenName;
	while (tagMultiPolygon2D.IsNextChildStartTag (tokenName) && (errCode == NoError)) {
		CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> newPoly;
		errCode = newPoly.ReadXML (ic);
		this->Push (newPoly);
	}

	DBASSERT (newSize == this->GetSize ());

	if (errCode != NoError)
		return errCode;
	return ic.GetErrorStatus () == GS::XMLIChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GSErrCode	CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::WriteXML (GS::XMLOChannel& oc) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GSErrCode errCode = NoError;
	GS::XMLTag tagMultiPolygon2D (oc, XMLPolygon_Tag_MultiPolygon2D);
	{
		//RA: Az XML-ben nem kezelunk verzio-t.
		// Azert irjuk ki, hogy ha szukseges, akkor be tudjuk vezetni a verzio kezelest.
		// Ha be akarjuk vezetni a verzio kezelest, akkor azt mindenutt meg kell tenni.
		oc.WriteXMLVersionAttr (MultiPolygon2DPrivate::classInfo.GetVersion ());
		//GetClassVersion ().WriteXML (oc);
	}

	if (errCode == NoError)
		errCode = oc.WriteXMLAttr (XMLPolygon_Attr_PolyNum, this->GetSize ());

	for (UIndex idx = 0; idx < this->GetSize() && errCode == NoError; idx++) {
		errCode = this->Get (idx).WriteXML (oc);
	}

	if (errCode != NoError)
		return errCode;
	return oc.GetErrorStatus () == GS::XMLOChannel::Ok ? NoError : Error;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PopLargest (void)
{
	CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> actPoly;
	if (this->GetSize () == 0) {
		return actPoly;
	}
	else if (this->GetSize () == 1) {
		actPoly = this->Get (0);
		this->Clear ();
		return actPoly;
	}

	double act, max	= -DBL_MAX;
	UIndex argmax	= 0;
	for (UIndex idx = 0; idx < this->GetSize (); idx++) {
		act = ((this->Get (idx)).CalcArea) ();
		DBASSERT (act >= 0.);
		if (max < act) {
			max = act;
			argmax = idx;
		}
	}
	actPoly = this->Get(argmax);
	this->Delete (argmax);
	return actPoly;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
GS::Int32 CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetLargestIdx (void) const
{
	if (this->GetSize () == 0) {
		DBBREAK (); //lehet, hogy ez nem is hiba?
		return -1;
	}
	else if (this->GetSize () == 1) {
		return 0;
	}
	double largestArea = 0.0;
	UIndex largestIdx = 0;
	double currArea = 0.0;
	for (UIndex idx = 0; idx < this->GetSize (); idx++) {
		currArea = this->Get (idx).CalcArea ();
		if (currArea > largestArea) {
			largestArea = currArea;
			largestIdx = idx;
		}
	}
	return largestIdx;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
Box2DData CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetBoundBox (void) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	Box2DData box;
	if (this->GetSize() == 0) {
		DBBREAK (); //lehet, hogy ez nem is hiba?
		InitBox(&box);
		return box;
	}
	else if (this->GetSize() == 1)
		return this->Get (0).GetBoundBox ();

	box = this->Get (0).GetBoundBox ();
	for (UIndex idx = 1; idx < this->GetSize(); idx++) {
		const Box2DData& elemBox = this->Get (idx).GetBoundBox ();
		UnionBox (&elemBox, &box);
	}
	return box;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
double CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcArea (void) const
{
	double area = 0;

	for (UIndex idx = 0; idx < this->GetSize(); idx++) {
		area += this->Get (idx).CalcArea ();
	}
	return area;
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::CalcConvexHull (const ArcDivParams& arcDivParams, GS::Array<Coord>& convexHull) const
{
	ConvexHull2DCreator convexHullCreator;
	
	for (UIndex idx = 0; idx < this->GetSize (); ++idx) {
		const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>& polygon = this->Get (idx);
		if (polygon.HasArcs ()) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> tmpMultiPolygon;
			polygon.SegmentUp (arcDivParams, tmpMultiPolygon);
			for (UIndex polygonIdx = 0; polygonIdx < tmpMultiPolygon.GetSize (); ++polygonIdx) {
				for (UIndex vertexIdx = 1; vertexIdx <= tmpMultiPolygon[polygonIdx].GetVertexNum (); ++vertexIdx) {
					convexHullCreator.AddPoint (tmpMultiPolygon[polygonIdx].GetVertexCoordByIdx (vertexIdx));
				}
			} 
		} else {
			for (UIndex vertexIdx = 1; vertexIdx <= polygon.GetVertexNum (); ++vertexIdx) {
				convexHullCreator.AddPoint (polygon.GetVertexCoordByIdx (vertexIdx));
			}
		}
	}

	GS::PagedArray<Coord3D> convexHull3D = convexHullCreator.CalcConvexHull ();
	convexHull.Clear ();
	for (UIndex i = 0; i < convexHull3D.GetSize (); ++i) {
		convexHull.Push (Coord (convexHull3D[i].x, convexHull3D[i].y));
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Coord& point, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (polygonArray, point, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Sector& sect, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException, GS::AbortException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (polygonArray, sect, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const GenArc& arc, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (polygonArray, arc, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const Box2DData& box, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (polygonArray, box, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (polygonArray, *poly.polygon, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
RelativePosition CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (const CustomPolyline2D<VertexUserData, EdgeUserData, PolygonUserData>& poly, Boundary boundaries, DetailedRelativePosition* detailed /*= nullptr*/) const
	CAN_THROW ((GS::OutOfMemoryException, GeometryException))
{
	GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > > polygonArray;
	GetCorePolygon2DArray (polygonArray);
	return CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetPosition (polygonArray, *poly.polyline, boundaries, detailed);
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
bool CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Substract (const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly1, const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly2, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
{
//		DBASSERT (result.GetSize () == 0);
	result.Insert (result.GetSize (), poly1.Begin ());

	bool	anyThingChanged = false;
	for (GS::UInt32 i = 0; i < poly2.GetSize (); i++) {
		GS::UInt32	oldSize = result.GetSize ();
		for (GS::UInt32 j = 0; j < oldSize; j++) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>		result1;
			RelativePosition	relativePosition;
			result[j].Substract (poly2[i], result1, Boundary_Closed, &relativePosition);
			result.Insert (result.GetSize (), result1.Begin ());
			if (!anyThingChanged && relativePosition != RelativePosition_Disjunct) {
				anyThingChanged = true;
			}
		}
		result.Delete (0, oldSize);
	}
	return anyThingChanged;
	// false means no change happened (result contains the original poly1 anyway)
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::Intersect (const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly1, const CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & poly2, CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> & result)
{
//		DBASSERT (result.GetSize () == 0);

	for (GS::UInt32 i = 0; i < poly2.GetSize (); i++) {
		GS::UInt32	oldSize = poly1.GetSize ();
		for (GS::UInt32 j = 0; j < oldSize; j++) {
			CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>		result1;
			RelativePosition	relativePosition;
			poly1[j].Intersect (poly2[i], result1, Boundary_Closed, &relativePosition);
			result.Insert (result.GetSize (), result1.Begin ());
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::GetCorePolygon2DArray (GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray) const
{
	for (UIndex idx = 0; idx < this->GetSize(); idx++) {
		polygonArray.Push (this->Get(idx).polygon);
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PushCorePolygon2DArray (const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray)
{
	for (UIndex idx = 0; idx < polygonArray.GetSize(); idx++) {
		if (!polygonArray[idx]->IsEmpty ()) {
			CustomPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> poly2D;
			poly2D.polygon = polygonArray[idx];
			this->Push (poly2D);
		}
	}
}

template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData>
void CustomMultiPolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PushResults (	typename CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::PolygonResult polyResult, 
	const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& thisPoly, 
	const GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> >& firstParam,
	const GS::Array<GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > >& polygonArray)
{
	switch (polyResult) {
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::NewPolygons:
			PushCorePolygon2DArray (polygonArray);
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsThis:
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				if (!thisPoly->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*thisPoly);
					this->Push (newPolygon);
				}
			}
#else
			if (!thisPoly->IsEmpty ())
				this->Push (thisPoly);
#endif
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultSameAsFirstParameter:
			DBASSERT (firstParam != nullptr);
			if (firstParam != nullptr && !firstParam->IsEmpty ()) {
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
				{
					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*firstParam);
					this->Push (newPolygon);
				}
#else
				this->Push (firstParam);
#endif
			}
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::ResultThisAndParameter:
			DBASSERT (firstParam != nullptr);
#if defined (DONT_USE_SHARED_COREPOLYGON2D)
			{
				if (!thisPoly->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon1 = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*thisPoly);
					this->Push (newPolygon1);
				}
				if (firstParam != nullptr && !firstParam->IsEmpty ()) {
					GS::SharedPtr<CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> > newPolygon2 = new CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData> (*firstParam);
					this->Push (newPolygon2);
				}
			}
#else
			if (!thisPoly->IsEmpty ())
				this->Push (thisPoly);
			if (firstParam != nullptr && !firstParam->IsEmpty ())
				this->Push (firstParam);
#endif
			break;
		case CorePolygon2D<VertexUserData, EdgeUserData, ContourUserData, PolygonUserData>::EmptyPolygon:
			break;
		default:
			DBBREAK ();
			break;
	}
}



} //Geometry namespace

#endif //GEOMETRY_POLYGON2D_HPP
