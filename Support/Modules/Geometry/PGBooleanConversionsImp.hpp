// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#include "PGBoolean.hpp"
#include "PGBoolTmp.hpp"
#include "PGBoolTmpConversions.hpp"

namespace PolygonBoolean {

template<class PolygonSelector>
void PGBoolean<PolygonSelector>::GetEdgesOfPoly (WhichPoly whichPoly)
{
	if (polyEdgeOffsets.GetSize () <= whichPoly || polyEdgeOffsets [whichPoly] == MaxUInt32) {
		while (polyEdgeOffsets.GetSize () <= whichPoly) {
			polyEdgeOffsets.Push (MaxUInt32);
		}

		const UInt32 polyEdgeOffset = polyEdges.GetSize ();
		polyEdgeOffsets [whichPoly] = polyEdgeOffset;

		const PGPOLYEXT* poly = origPolys [whichPoly];
		polyEdges.SetSize (polyEdgeOffset + poly->nEdges + 1);		

		if (poly->nEdges == 0) {
			return;
		}

		for (Int32 i = 1; i <= poly->nEdges; i++) {
			polyEdges [polyEdgeOffset + i] = poly->getEdge (poly, i);
		}

		DBASSERT (polyEdges.GetLast ().status.isEndContour);
		polyEdges.GetLast ().status.isEndContour = true;

		const UInt32 lastPolyEdgeIndex = polyEdges.GetSize () - 1;
		Int32 contourEndIndex = lastPolyEdgeIndex;
		for (Int32 i = 1; i < poly->nEdges; ++i) {
			if (polyEdges [lastPolyEdgeIndex - i].status.isEndContour) {
				contourEndIndex = lastPolyEdgeIndex - i;
			} else {
				polyEdges [lastPolyEdgeIndex - i].contourData = (GSPtr)(GS::IntPtr)(contourEndIndex);
			}
		}
	}
}

#ifdef DEBUVERS
inline void CheckBox (const Box2DData& calculatedBox, const Box2DData& storedBox)
{
	DBASSERT (Geometry::IsEmptyBox (calculatedBox) || Geometry::BoxInBox (calculatedBox, storedBox, Geometry::Boundary_Closed, MEDEPS));
}
#endif

template<class PolygonSelector>
Box2DData PGBoolean<PolygonSelector>::GetBoundBox (WhichPoly whichPoly)
{
	const PGPOLYEXT* poly = origPolys[whichPoly];

	if (poly->getEdge == nullptr) {
		const Polygon2DData* polydata = (const Polygon2DData*)poly->data;
		if (polydata->status.isBoundBoxValid) {
			GS_DEBUG_ONLY (CheckBox (CalcBoundBox (whichPoly), polydata->boundBox));
			return polydata->boundBox;
		}
	} else {
		GS_DEBUG_ONLY (CheckBox (CalcBoundBox (whichPoly), poly->boundBox));
		return poly->boundBox;
	}
	return CalcBoundBox (whichPoly);
}

template<class PolygonSelector>
Box2DData PGBoolean<PolygonSelector>::CalcBoundBox (WhichPoly whichPoly)
{
	const PGPOLYEXT* poly = origPolys[whichPoly];

	Box2DData b, d;
	InitBox (&b);

	if (poly->getEdge != nullptr) {		
		GetEdgesOfPoly (whichPoly);

		const UInt32 polyEdgeOffet = polyEdgeOffsets [whichPoly];

		for (Int32 i = 1; i <= poly->nEdges; ) {
			Int32 contourBeg = i;

			do {
				Int32 nextEdge = polyEdges [polyEdgeOffet + i].status.isEndContour ? contourBeg : i + 1;

				if (polyEdges [polyEdgeOffet + i].status.isArc == 0)
					CoordToBox (polyEdges [polyEdgeOffet + i].begPt, &d);
				else if (polyEdges [polyEdgeOffet + i].status.isArcRevoriented)
					ArcToBox (&d, &polyEdges [polyEdgeOffet + nextEdge].begPt, &polyEdges [polyEdgeOffet + i].begPt, &polyEdges [polyEdgeOffet + i].center);
				else
					ArcToBox (&d, &polyEdges [polyEdgeOffet + i].begPt, &polyEdges [polyEdgeOffet + nextEdge].begPt, &polyEdges [polyEdgeOffet + i].center);
				UnionBox (&d, &b);
				i++;
			} while (polyEdges [polyEdgeOffet + i - 1].status.isEndContour == 0 && i <= poly->nEdges);
		}
	} else {
		const Polygon2DData* polyData = (const Polygon2DData*) poly->data;
		for (ULong i = 1; i <= polyData->nVertices; i++) {
			CoordToBox ((*polyData->vertices)[i], &d);
			UnionBox (&d, &b);
		}

		for (ULong i = 1; i <= polyData->nArcs; i++) {
			const Coord& beg = (*polyData->vertices)[(*polyData->arcs)[i].begIndex];
			const Coord& end = (*polyData->vertices)[(*polyData->arcs)[i].endIndex];
			Coord arcOrig;
			if (ArcGetOrigo (&beg, &end, (*polyData->arcs)[i].arcAngle, &arcOrig)) {
				if ((*polyData->arcs)[i].arcAngle > 0)
					ArcToBox (&d, &beg, &end, &arcOrig);
				else
					ArcToBox (&d, &end, &beg, &arcOrig);
				UnionBox (&d, &b);
			}
		}
	}

	return b;
}

template<class PolygonSelector>
void PGBoolean<PolygonSelector>::AddArcCenters (Box2DData* bbox, WhichPoly whichPoly)
{
	const PGPOLYEXT* poly = origPolys [whichPoly];		
	Box2DData b;

	Coord c = SetCoord (boundBox.xMin, boundBox.yMin);
	double maxDist = GS::Max (GS::Max (GS::Max (boundBox.xMax - boundBox.xMin, boundBox.yMax - boundBox.yMin), poly->epsilon * 8),
		SmallEps * 8) * 1000.0;

	if (poly->getEdge != nullptr) {
		GetEdgesOfPoly (whichPoly);

		const UInt32 polyEdgeOffet = polyEdgeOffsets [whichPoly];

		for (Int32 i = 1; i <= poly->nEdges; i++) {
			if (!polyEdges [polyEdgeOffet + i].status.isArc)
				continue;

			containsArc = true;
			if (Dist (polyEdges [polyEdgeOffet + i].center, c) < maxDist) {
				CoordToBox (polyEdges [polyEdgeOffet + i].center, &b);
				UnionBox (&b, bbox);
			}
		}
	} else {
		const Polygon2DData* polyData = (const Polygon2DData*) poly->data;
		if (polyDatas.GetSize () <= whichPoly) {
			polyDatas.SetSize (whichPoly + 1);
		}
		polyDatas [whichPoly] = polyData;		

		for (ULong i = 1; i <= polyData->nArcs; i++) {
			const Coord& beg = (*polyData->vertices)[(*polyData->arcs)[i].begIndex];
			const Coord& end = (*polyData->vertices)[(*polyData->arcs)[i].endIndex];
			Coord center;
			if (ArcGetOrigo (&beg, &end, (*polyData->arcs)[i].arcAngle, &center)) {
				containsArc = true;
				if (Dist (center, c) < maxDist) {
					CoordToBox (center, &b);
					UnionBox (&b, bbox);
				}
			}
		}
	}
}

template<class PolygonSelector>
void PGBoolean<PolygonSelector>::PrintPolygon (GS::OChannel& outChannel, WhichPoly whichPoly)
{
	const PGPOLYEXT* poly = origPolys [whichPoly];		

	if (poly->getEdge != nullptr) {
		GetEdgesOfPoly (whichPoly);

		const UInt32 polyEdgeOffet = polyEdgeOffsets [whichPoly];

		Int32 lines = poly->nEdges;
		for (Int32 i = 1; i <= poly->nEdges; i++) {
			if (polyEdges [polyEdgeOffet + i].status.isEndContour)
				lines++;
			if (polyEdges [polyEdgeOffet + i].status.isArc)
				lines += 2;
		}

		outChannel << "\nPOLY2_   " << lines << ",  7,\n";

		for (Int32 i = 1; i <= poly->nEdges; ) {
			Int32 contourBeg = i;

			do {
				outChannel << polyEdges [polyEdgeOffet + i].begPt.x << ",  " << polyEdges [polyEdgeOffet + i].begPt.y << ",   1, \n";

				if (polyEdges [polyEdgeOffet + i].status.isArc) {
					outChannel << polyEdges [polyEdgeOffet + i].center.x << ",  " << polyEdges [polyEdgeOffet + i].center.y << ",  900, \n";
					outChannel << "  0, " << CalcRotFi (polyEdges [polyEdgeOffet + i].fi1, polyEdges [polyEdgeOffet + i].fi2, polyEdges [polyEdgeOffet + i].status.isArcRevoriented) * 180.0 / PI <<
						", 4001, \n";
				}
				i++;
			} while (polyEdges [polyEdgeOffet + i - 1].status.isEndContour == 0 && i <= poly->nEdges);
			outChannel << polyEdges [polyEdgeOffet + contourBeg].begPt.x << ",  " << polyEdges [polyEdgeOffet + contourBeg].begPt.y << ",  -1";
			if (i < poly->nEdges)
				outChannel << ",\n";
		}
		outChannel << "\n\n";

	} else {
		const Polygon2DData* polyData = (const Polygon2DData*) poly->data;
		const PolyArcRec* arcs = polyData->arcs != nullptr ? (*polyData->arcs) + 1 : nullptr;

		outChannel << "\nPOLY2_   " << (polyData->nVertices + 2 * polyData->nArcs) << ",  7,\n";

		for (Int32 i = 1, j = 1; i <= Int32 (polyData->nContours); i++) {
			while (Int32 ((*polyData->contourEnds)[i]) != j) {
				outChannel << (*polyData->vertices)[j].x << ",  " << (*polyData->vertices)[j].y << ",   1, \n";

				Int32 arcInd = FindArc (arcs, polyData->nArcs, j);
				if (arcInd >= 0) {
					Coord center;
					if (ArcGetOrigo (&(*polyData->vertices)[j], &(*polyData->vertices)[j + 1], arcs[arcInd].arcAngle, &center)) {
						outChannel << center.x << ",  " << center.y << ",  900, \n";
						outChannel << "  0, " << (arcs[arcInd].arcAngle * 180.0 / PI) << ", 4001, \n";
					}
				}
				j++;
			}
			j++;

			Coord& c = (*polyData->vertices)[(*polyData->contourEnds)[i - 1] + 1];
			outChannel << c.x << ",  " << c.y << ",  -1";
			if (i < Int32 (polyData->nContours))
				outChannel << ",\n";
		}
		outChannel << "\n\n";
	}
}

template<class PolygonSelector>
void PGBoolean<PolygonSelector>::PrintReport (const char* opName, PGRelPolyPosExt status, GS::OChannel& outChannel)
{
	if (stage == 0)
		return;

	outChannel << "\n! ------------ START Boolean Operation: " << opName << "\n";

	for (UInt32 i = 0; i < origPolys.GetSize (); ++i) {
		outChannel << "\n! Polygon In "<< i <<":";
		PrintPolygon (outChannel, i);
	}

	outChannel << "\n! ReturnStatus:" << int (status) << "\n";
	outChannel << "\nPEN 3\n\n";
	outChannel << "!  Polygons Out:";

	if (stage > 2) {
		if (b64BitPrecision)
			pgBoolean64.PrintResult (outChannel);
		else
			pgBoolean32.PrintResult (outChannel);
	}

	outChannel << "\n! --------- END Boolean Operation Report \n\n\n";
}

}
