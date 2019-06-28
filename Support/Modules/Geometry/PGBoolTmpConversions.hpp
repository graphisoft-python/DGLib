// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLTMPCONVERSIONS_H
#define PGBOOLTMPCONVERSIONS_H

namespace PolygonBoolean {

template<class DInt, class Int, class PolygonSelector>
inline Point<DInt,Int> PGBoolTmp<DInt,Int,PolygonSelector>::RoundToNodeGrid (const Point<DInt,Int>& p)
{
	Point<DInt,Int> q;

	q.x = (p.x + DInt::nodeGridRound) & DInt::nodeGridMask;
	q.y = (p.y + DInt::nodeGridRound) & DInt::nodeGridMask;

	return q;
}

template<class DInt, class Int, class PolygonSelector>
GS_FORCE_INLINE Int PGBoolTmp<DInt,Int,PolygonSelector>::RoundToRadiusGrid (Int r)
{
	return (r + DInt::radiusGridRound) & DInt::radiusGridMask;
}

template<class DInt, class Int, class PolygonSelector>
GS_FORCE_INLINE Int PGBoolTmp<DInt,Int,PolygonSelector>::CeilToRadiusGrid (Int r)
{
	return (r + DInt::radiusGridCeil) & DInt::radiusGridMask;
}

template<class DInt, class Int, class PolygonSelector>
inline Point<DInt,Int> PGBoolTmp<DInt,Int,PolygonSelector>::CoordToPoint (const Coord& c)
{
	Point<DInt,Int> p;

	p.x = Int ((c.x - origBBOffset.x) / origBBSide * (DInt::maxCoordVal - DInt::minCoordVal)) + DInt::minCoordVal;
	p.y = Int ((c.y - origBBOffset.y) / origBBSide * (DInt::maxCoordVal - DInt::minCoordVal)) + DInt::minCoordVal;
	return p;
}

template<class DInt, class Int, class PolygonSelector>
inline Coord PGBoolTmp<DInt,Int,PolygonSelector>::PointToCoord (const Point<DInt,Int>& p)
{
	Coord c;

	c.x = double (p.x - DInt::minCoordVal) / (DInt::maxCoordVal - DInt::minCoordVal) * origBBSide + origBBOffset.x;
	c.y = double (p.y - DInt::minCoordVal) / (DInt::maxCoordVal - DInt::minCoordVal) * origBBSide + origBBOffset.y;
	return c;
}

template<class DInt, class Int, class PolygonSelector>
inline Int PGBoolTmp<DInt,Int,PolygonSelector>::DistanceToInt (double d)
{
	return Int (d / origBBSide * (DInt::maxCoordVal - DInt::minCoordVal));
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::ConvertPoly (WhichPoly whichPoly)
{
	const PGPOLYEXT* poly = origPolys [whichPoly];		

	GS::ArrayFB<CheckPositivContourData, 10> checkPosContour;

	Node* polygonFirstNode = nullptr;
	Node* contourFirstNode;
	Node* lastNode;

	if (poly->getEdge != nullptr) {
		const PGEDGEEXT* edges = polyEdges.GetContent () + polyEdgeOffsets [whichPoly];			
		const PGEDGEEXT* lastEdge;
		const PGEDGEEXT* currEdge;
		bool newPolygon = true;
		Int32 polyFirstLinkIndex = 0;

		for (Int32 i = 1; i <= poly->nEdges; ) {
			lastEdge = edges + i;
			contourFirstNode = lastNode = InsertNewNode (lastEdge->begPt, whichPoly, i);
			if (newPolygon) {
				polygonFirstNode = contourFirstNode;
				polyFirstLinkIndex = allLinks.GetSize ();
				newPolygon = false;
			}

			i++;
			do {
				currEdge = edges + i;
				if (lastEdge->status.isArc == 0)
					lastNode = InsertNewLine (lastNode, currEdge->begPt);
				else
					lastNode = InsertNewArc (lastNode, currEdge->begPt, lastEdge->center, lastEdge->status.isArcRevoriented == 1);
				lastEdge = currEdge;
				i++;
			} while (currEdge->status.isEndContour == 0 && i <= poly->nEdges);
			if (lastEdge->status.isArc == 0)
				CloseContourWithLine (lastNode, contourFirstNode);
			else
				CloseContourWithArc (lastNode, contourFirstNode, lastEdge->center, Dist (lastEdge->begPt, lastEdge->center),
					lastEdge->status.isArcRevoriented == 1);

			if (i > poly->nEdges || currEdge->status.isEndPolygon) {
				CheckPositivContourData ch;
				ch.polygonFirstNode = polygonFirstNode;
				ch.firstLinkIndex = polyFirstLinkIndex;
				ch.endLinkIndex = allLinks.GetSize ();
				checkPosContour.Push (ch);
				newPolygon = true;
			}
		}
	} else {
		const Polygon2DData* polyData = (const Polygon2DData*) poly->data;

		const PolyArcRec* arcs = polyData->arcs != nullptr ? (*polyData->arcs) + 1 : nullptr;
		Int32 polyFirstLinkIndex = allLinks.GetSize ();
		for (Int32 i = 1, j = 1; i <= Int32 (polyData->nContours); i++) {
			Int32 arcInd;
			contourFirstNode = lastNode = InsertNewNode ((*polyData->vertices)[j], whichPoly, j);
			if (i == 1)
				polygonFirstNode = contourFirstNode;

			j++;
			while (j != Int32 ((*polyData->contourEnds)[i]) && j <= Int32 (polyData->nVertices)) {
				arcInd = FindArc (arcs, polyData->nArcs, j - 1);
				if (arcInd < 0)
					lastNode = InsertNewLine (lastNode, (*polyData->vertices)[j]);
				else {
					Coord center;
					if (ArcGetOrigo (&(*polyData->vertices)[j - 1], &(*polyData->vertices)[j], arcs[arcInd].arcAngle, &center))
						lastNode = InsertNewArc (lastNode, (*polyData->vertices)[j], center, arcs[arcInd].arcAngle < 0);
					else
						lastNode = InsertNewLine (lastNode, (*polyData->vertices)[j]);
				}
				j++;
			}
			arcInd = FindArc (arcs, polyData->nArcs, j - 1);
			if (arcInd < 0)
				CloseContourWithLine (lastNode, contourFirstNode);
			else {
				Coord center;
				if (ArcGetOrigo (&(*polyData->vertices)[j - 1], &(*polyData->vertices)[j], arcs[arcInd].arcAngle, &center))
					CloseContourWithArc (lastNode, contourFirstNode, center, Dist ((*polyData->vertices)[j], center),
						arcs[arcInd].arcAngle < 0);
				else
					CloseContourWithLine (lastNode, contourFirstNode);
			}
			j++;
		}

		if (polygonFirstNode != nullptr) {
			CheckPositivContourData ch;
			ch.polygonFirstNode = polygonFirstNode;
			ch.firstLinkIndex = polyFirstLinkIndex;
			ch.endLinkIndex = allLinks.GetSize ();
			checkPosContour.Push (ch);
		}
	}

	DInt area2Sum = Int (0);
	bool bigEnough = false;
	for (ULong i = 0; i < checkPosContour.GetSize (); i++) {
		DInt area2 = Int (0);
		lastNode = polygonFirstNode = checkPosContour[i].polygonFirstNode;
		if (!lastNode->links.IsEmpty ()) {
			do {
				Link* link = lastNode->links[lastNode->links[0]->beg == lastNode ? 0 : 1];
				area2 += GetLinkSweepArea2 (link);
				lastNode = link->end;
			} while (lastNode != polygonFirstNode);
		}
		if (area2 < Int (0)) {
			Int32 endLinkIndex = checkPosContour[i].endLinkIndex;
			for (Int32 j = checkPosContour[i].firstLinkIndex; j < endLinkIndex; j++)
				ReverseLink (allLinks[j]);
			area2 = -area2;
			noChange = false;
		}

		if (!bigEnough) {
			area2Sum += area2;
			if (area2Sum >= area2Minimum)
				bigEnough = true;
		}
	}

	return bigEnough;
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Node* PGBoolTmp<DInt,Int,PolygonSelector>::InsertNewNode (const Coord& c, WhichPoly whichPoly, Int32 origVertex)
{
	Node* newNode = NewNode ();
	try { allNodes.Push (newNode); }
	catch (const GS::Exception&) { DeleteNode (newNode); throw; }

	newNode->pos = RoundToNodeGrid (CoordToPoint (c));
	newNode->origVertex = origVertex;
	newNode->whichPoly = whichPoly;
	return newNode;
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Node* PGBoolTmp<DInt,Int,PolygonSelector>::InsertNewLine (Node* begNode, const Coord& endCo)
{
	Node* endNode = NewNode ();
	try { allNodes.Push (endNode); }
	catch (const GS::Exception&) { DeleteNode (endNode); throw; }

	Line* newLine = NewLine ();
	try { allLinks.Push (newLine); }
	catch (const GS::Exception&) { DeleteLink (newLine); throw; }

	endNode->pos = RoundToNodeGrid (CoordToPoint (endCo));
	endNode->origVertex = begNode->origVertex + 1;
	endNode->whichPoly = begNode->whichPoly;

	newLine->beg = begNode;
	newLine->end = endNode;
	newLine->origEdge = begNode->origVertex;
	newLine->whichPoly = begNode->whichPoly;
	newLine->uniqOrigEdge = true;

	begNode->links.Push (newLine);
	endNode->links.Push (newLine);
	FillLineStruct (newLine);

	return endNode;
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Node* PGBoolTmp<DInt,Int,PolygonSelector>::InsertNewArc (Node* begNode, const Coord& endCo, const Coord& center,
																	   bool revOriented)
{
	Node* endNode = NewNode ();
	try { allNodes.Push (endNode); }
	catch (const GS::Exception&) { DeleteNode (endNode); throw; }

	endNode->pos = RoundToNodeGrid (CoordToPoint (endCo));
	endNode->origVertex = begNode->origVertex + 1;
	endNode->whichPoly = begNode->whichPoly;

	if (IsBoxPointIntersect (pgBoolean->boundBox, center, Boundary_Closed, 0)) {
		Arc* newArc = NewArc ();
		try { allLinks.Push (newArc); }
		catch (const GS::Exception&) { DeleteLink (newArc); throw; }

		newArc->beg = begNode;
		newArc->end = endNode;
		newArc->origEdge = begNode->origVertex;
		newArc->whichPoly = begNode->whichPoly;
		newArc->uniqOrigEdge = true;
		newArc->center = CoordToPoint (center);
		newArc->positiv = !revOriented;
		newArc->r = RoundToRadiusGrid (DistanceToInt (Dist (endCo, center)));

		begNode->links.Push (newArc);
		endNode->links.Push (newArc);
		FillArcStruct (newArc);
	} else
		SegmentArcToLines (begNode, endNode, center, revOriented);

	return endNode;
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::CloseContourWithLine (Node* begNode, Node* endNode)
{
	if (begNode == endNode)
		return;

	Line* newLine = NewLine ();
	try { allLinks.Push (newLine); }
	catch (const GS::Exception&) { DeleteLink (newLine); throw; }

	newLine->beg = begNode;
	newLine->end = endNode;
	newLine->origEdge = begNode->origVertex;
	newLine->whichPoly = begNode->whichPoly;
	newLine->uniqOrigEdge = true;

	begNode->links.Push (newLine);
	endNode->links.Push (newLine);
	FillLineStruct (newLine);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::CloseContourWithArc (Node* begNode, Node* endNode, const Coord& center, double r, bool revOriented)
{
	if (begNode == endNode)
		return;

	if (IsBoxPointIntersect (pgBoolean->boundBox, center, Boundary_Closed, 0)) {
		Arc* newArc = NewArc ();
		try { allLinks.Push (newArc); }
		catch (const GS::Exception&) { DeleteLink (newArc); throw; }

		newArc->beg = begNode;
		newArc->end = endNode;
		newArc->origEdge = begNode->origVertex;
		newArc->whichPoly = begNode->whichPoly;
		newArc->uniqOrigEdge = true;
		newArc->center = CoordToPoint (center);
		newArc->positiv = !revOriented;
		newArc->r = RoundToRadiusGrid (DistanceToInt (r));

		begNode->links.Push (newArc);
		endNode->links.Push (newArc);
		FillArcStruct (newArc);
	} else
		SegmentArcToLines (begNode, endNode, center, revOriented);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::SegmentArcToLines (Node* beg, Node* end, const Coord& center, bool revOriented)
{
	Coord b = PointToCoord (beg->pos);
	Coord e = PointToCoord (end->pos);
	Geometry::Vector2d b2 = b - center;
	Geometry::Vector2d e2 = e - center;

	double alpha = atan2 (MulvVectors (b2, e2), MulsVectors (b2, e2));
	if (alpha < 0)
		alpha += 2 * PI;
	if (revOriented)
		alpha = 2 * PI - alpha;

	double eps = GS::Max (SmallEps, beg->whichPoly < origPolys.GetSize () ? origPolys [beg->whichPoly]->epsilon : origPolys [0]->epsilon);		
	double r = LenVector (b2);

	Int32 nSegments = 1;
	if (r > eps) {
		double q = sqrt (2.0 * r * eps - eps * eps) / r;
		if (q <= 1.0) {
			if (q < SmallEps)
				nSegments = 1000;
			else {
				nSegments = Int32 (alpha / (2.0 * asin (q))) + 1;
				if (nSegments > 1000)
					nSegments = 1000;
			}
		}
	}

	Vector x = b2;
	Vector y (-x.y, x.x);

	double beta = (alpha / nSegments) * (revOriented ? -1.0 : 1.0);
	Node* last = beg;

	for (Int32 i = 1; i < nSegments; i++) {
		Node* n = NewNode ();
		try { allNodes.Push (n); }
		catch (const GS::Exception&) { DeleteNode (n); throw; }

		Line* newLine = NewLine ();
		try { allLinks.Push (newLine); }
		catch (const GS::Exception&) { DeleteLink (newLine); throw; }

		Coord s = center + (MulVector (x, cos (beta * i)) + MulVector (y, sin (beta * i)));
		n->pos = RoundToNodeGrid (CoordToPoint (s));
		n->origVertex = -1;
		n->whichPoly = None;

		newLine->beg = last;
		newLine->end = n;
		newLine->origEdge = beg->origVertex;
		newLine->whichPoly = beg->whichPoly;
		newLine->uniqOrigEdge = false;

		last->links.Push (newLine);
		n->links.Push (newLine);
		FillLineStruct (newLine);

		last = n;
	}

	Line* newLine = NewLine ();
	try { allLinks.Push (newLine); }
	catch (const GS::Exception&) { DeleteLink (newLine); throw; }

	newLine->beg = last;
	newLine->end = end;
	newLine->origEdge = beg->origVertex;
	newLine->whichPoly = beg->whichPoly;
	newLine->uniqOrigEdge = true;

	last->links.Push (newLine);
	end->links.Push (newLine);
	FillLineStruct (newLine);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::ReturnContourProc (const Contour& contour, PGPOLYEXT* createdPoly)
{
	bool firstEdgeDone = false;

	Link* link = contour.startLink;
	
	Int32 contourEdgeIndex = -1;

	do {
		WhichPoly	linkOrigPoly;
		Int32		linkOrigEdge;		

		if (link->rightPoly == contour.whichPoly && link->origRightEdge >= 0) {
			linkOrigPoly = link->rightPoly;
			linkOrigEdge = link->origRightEdge;
		} else {
			linkOrigPoly = link->whichPoly;
			linkOrigEdge = link->origEdge;
		}

		DBASSERT (linkOrigPoly >= origPolys.GetSize () || linkOrigEdge <= static_cast<Int32> (origPolys [linkOrigPoly]->nEdges));

		if (linkOrigPoly < origPolys.GetSize ()) {
			const PGEDGEEXT& origEdge = polyEdges[polyEdgeOffsets [linkOrigPoly] + linkOrigEdge];

			Int32 actContourEdgeIndex;

			if (origEdge.status.isEndContour) {
				actContourEdgeIndex = polyEdgeOffsets [linkOrigPoly] + linkOrigEdge;
			} else {
				actContourEdgeIndex = (Int32)TruncateTo32Bit ((GS::IntPtr)origEdge.contourData);
			}

			if (contourEdgeIndex < 0) {
				contourEdgeIndex = actContourEdgeIndex;
			} else if (contourEdgeIndex != actContourEdgeIndex) {
				contourEdgeIndex = -1;
				break;
			}
		} else {
			contourEdgeIndex = -1;
			break;
		}		

		link = !withoutHoles ? GetContourNextLink (link, contour) : GetOutsideContourNextLink (link, contour);
	} while (link != contour.startLink);


	link = contour.startLink;
	const Link* lastLink = !withoutHoles ? GetContourPrevLink (link, contour) : GetOutsideContourPrevLink (link, contour);

	do {
		PGEDGEEXT edge;
		memset (&edge, 0, sizeof (edge));

		DBASSERT (contour.whichPoly == link->leftPoly || contour.whichPoly == link->rightPoly);
		const bool left = contour.whichPoly == link->leftPoly;
		Node* begNode = left ? link->beg : link->end;

		if (begNode->generatedNodeId == 0) {
			begNode->generatedNodeId = ++generatedNodeIdCounter;
		}
		edge.generatedVertexId = begNode->generatedNodeId;
		edge.begPt = PointToCoord (begNode->pos);
		Coord end = PointToCoord (left ? link->end->pos : link->beg->pos);

		edge.contourData = createdPoly->defaultContourData;

		if (begNode->whichPoly < origPolys.GetSize ()) {
			edge.vertexData = polyEdges[polyEdgeOffsets [begNode->whichPoly] + begNode->origVertex].vertexData;
		} else {
			edge.vertexData = origPolys [contour.whichPoly]->defaultVertexData;
		}

		WhichPoly	linkOrigPoly;
		Int32		linkOrigEdge;		

		if (link->rightPoly == contour.whichPoly && link->origRightEdge >= 0) {
			linkOrigPoly = link->rightPoly;
			linkOrigEdge = link->origRightEdge;
		} else {
			linkOrigPoly = link->whichPoly;
			linkOrigEdge = link->origEdge;
		}

		DBASSERT (linkOrigPoly >= origPolys.GetSize () || linkOrigEdge <= static_cast<Int32> (origPolys [linkOrigPoly]->nEdges));			

		if (linkOrigPoly < origPolys.GetSize ()) {
			const PGEDGEEXT& origEdge = polyEdges[polyEdgeOffsets [linkOrigPoly] + linkOrigEdge];			
			edge.inhEdgeData = origEdge.inhEdgeData;
			edge.contourData = origEdge.contourData;
			edge.status.isSplitLine = (isBSplitLine && linkOrigPoly == 1) || origEdge.status.isSplitLine;
			edge.status.isInvisible = origEdge.status.isInvisible;
		}

		edge.contourData = contourEdgeIndex < 0 ? origPolys [contour.whichPoly]->defaultContourData : polyEdges [contourEdgeIndex].contourData;

		if (link->uniqOrigEdge) {
			if (link->whichPoly < origPolys.GetSize ()) {
				const PGEDGEEXT& origEdge = polyEdges[polyEdgeOffsets [link->whichPoly] + link->origEdge];
				edge.uniqEdgeData = origEdge.uniqEdgeData;
			}
		} else {
			edge.uniqEdgeData = createdPoly->defaultUniqEdgeData;
		}

		if (!link->isLine) {
			Arc* arc = (Arc*) link;
			edge.center = PointToCoord (arc->center);
			edge.radius = LenVector (edge.begPt - edge.center);
			edge.status.isArc = true;
			edge.status.isArcRevoriented = (left != arc->positiv);
			edge.fi1 = ComputeFi (edge.center, edge.begPt);
			edge.fi2 = ComputeFi (edge.center, end);
		}
		double d = Dist (edge.begPt, end);
		if (d > SmallEps)
			edge.invlen = 1.0 / d;

		if (!firstEdgeDone) {
			if (!contour.positiv)
				edge.status.isBegHole = true;
			firstEdgeDone = true;
		}

		if (link == lastLink) {
			edge.status.isEndContour = true;
		}
		if ((*createdPoly->newEdge) (createdPoly, &edge) != NoError)
			throw GS::GeneralException ("Cannot create edge", __FILE__, __LINE__);

		link = !withoutHoles ? GetContourNextLink (link, contour) : GetOutsideContourNextLink (link, contour);
	} while (link != contour.startLink);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::ReturnContourData (const Contour& contour, Polygon2DData* poly)
{
	Int32 firstVertex = 0;
	bool firstEdgeDone = false;
	Box2DData bb;

	Link* link = contour.startLink;
	Int32		contourInd = -1;
	WhichPoly	contourPoly = None;

	do {
		DBASSERT (contour.whichPoly == link->leftPoly || contour.whichPoly == link->rightPoly);
		const bool left = contour.whichPoly == link->leftPoly;
		const Node* begNode = left ? link->beg : link->end;
		poly->nVertices++;
		(*poly->vertices)[poly->nVertices] = PointToCoord (begNode->pos);
		CoordToBox ((*poly->vertices)[poly->nVertices], &bb);

		const WhichPoly nodePoly = begNode->whichPoly;
		if (nodePoly < polyDatas.GetSize ()) {
			const Polygon2DData* polyData = polyDatas[nodePoly];
			if (poly->sizeOfVertexInfo > 0 && poly->sizeOfVertexInfo == polyData->sizeOfVertexInfo) {
				const Int32 origVertex = begNode->origVertex;
				memcpy (*poly->vertexInfos + poly->nVertices * poly->sizeOfVertexInfo,
						*polyData->vertexInfos + origVertex * polyData->sizeOfVertexInfo, polyData->sizeOfVertexInfo);
			}
		}

		if (link->whichPoly < polyDatas.GetSize ()) {
			WhichPoly	linkOrigPoly;
			Int32		linkOrigEdge;		

			if (link->rightPoly == contour.whichPoly && link->origRightEdge >= 0) {
				linkOrigPoly = link->rightPoly;
				linkOrigEdge = link->origRightEdge;
			} else {
				linkOrigPoly = link->whichPoly;
				linkOrigEdge = link->origEdge;
			}			

			const Polygon2DData* polyData = polyDatas[linkOrigPoly];
			DBASSERT (linkOrigEdge <= static_cast<Int32> (polyData->nVertices));

			if (poly->sizeOfInhEdgeInfo > 0 && poly->sizeOfInhEdgeInfo == polyData->sizeOfInhEdgeInfo) {
					memcpy (*poly->inhEdgeInfos + poly->nVertices * poly->sizeOfInhEdgeInfo,
						    *polyData->inhEdgeInfos + linkOrigEdge * polyData->sizeOfInhEdgeInfo, polyData->sizeOfInhEdgeInfo);
			}
			if (contourInd < 0 || contourPoly == linkOrigPoly) {
				contourPoly = linkOrigPoly;
				for (Int32 i = 1; i <= Int32 (polyData->nContours); i++) {
					if (linkOrigEdge <= (Int32)(*polyData->contourEnds)[i]) {
						if (contourInd > 0 && contourInd != i) {
							contourPoly = None;
						}
						contourInd = i;
						break;
					}
				}			
			} else {
				contourPoly = None;
			}
		}


		if (link->uniqOrigEdge) {
			if (link->whichPoly < polyDatas.GetSize ()) {
				const Polygon2DData* polyData = polyDatas[link->whichPoly];
				if (poly->sizeOfUniqEdgeInfo > 0 && poly->sizeOfUniqEdgeInfo == polyData->sizeOfUniqEdgeInfo) {
					memcpy (*poly->uniqEdgeInfos + poly->nVertices * poly->sizeOfUniqEdgeInfo,
							*polyData->uniqEdgeInfos + link->origEdge * polyData->sizeOfUniqEdgeInfo, polyData->sizeOfUniqEdgeInfo);
				}
			}
		}

		if (!link->isLine) {
			Arc* arc = (Arc*) link;

			poly->nArcs++;
			(*poly->arcs)[poly->nArcs].begIndex = poly->nVertices;
			(*poly->arcs)[poly->nArcs].endIndex = poly->nVertices + 1;
			Coord center = PointToCoord (arc->center);
			Coord end = PointToCoord (left ? arc->end->pos : arc->beg->pos);
			Geometry::Vector2d a = UnitVector ((*poly->vertices)[poly->nVertices] - center);
			Geometry::Vector2d b = UnitVector (end - center);			
			if (left != arc->positiv) {
				GS::Swap (a, b);
			}
			(*poly->arcs)[poly->nArcs].arcAngle = atan2 (MulvVectors (a, b), MulsVectors (a, b));
			if ((*poly->arcs)[poly->nArcs].arcAngle < 0)
				(*poly->arcs)[poly->nArcs].arcAngle += 2 * PI;
			if (!arc->positiv)
				(*poly->arcs)[poly->nArcs].arcAngle *= -1;

			if (arc->positiv)
				ArcToBox (&bb, &(*poly->vertices)[poly->nVertices], &end, &center);
			else
				ArcToBox (&bb, &end, &(*poly->vertices)[poly->nVertices], &center);
		}
		UnionBox (&bb, &poly->boundBox);

		if (!firstEdgeDone) {
			firstVertex = poly->nVertices;
			firstEdgeDone = true;
		}

		link = !withoutHoles ? GetContourNextLink (link, contour) : GetOutsideContourNextLink (link, contour);
	} while (link != contour.startLink);

	poly->nVertices++;
	(*poly->vertices)[poly->nVertices] = (*poly->vertices)[firstVertex];

	if (poly->sizeOfVertexInfo > 0)
		memcpy (*poly->vertexInfos + poly->nVertices * poly->sizeOfVertexInfo,
			*poly->vertexInfos + firstVertex * poly->sizeOfVertexInfo, poly->sizeOfVertexInfo);
	if (poly->sizeOfInhEdgeInfo > 0)
		memcpy (*poly->inhEdgeInfos + poly->nVertices * poly->sizeOfInhEdgeInfo,
			*poly->inhEdgeInfos + firstVertex * poly->sizeOfInhEdgeInfo, poly->sizeOfInhEdgeInfo);
	if (poly->sizeOfUniqEdgeInfo > 0)
		memcpy (*poly->uniqEdgeInfos + poly->nVertices * poly->sizeOfUniqEdgeInfo,
			*poly->uniqEdgeInfos + firstVertex * poly->sizeOfUniqEdgeInfo, poly->sizeOfUniqEdgeInfo);

	poly->nContours++;
	(*poly->contourEnds)[poly->nContours] = poly->nVertices;

	if (poly->sizeOfContourInfo > 0) {		
		if (contourPoly != None && contourInd >= 0 && poly->sizeOfContourInfo == polyDatas [contourPoly]->sizeOfContourInfo) {
			const Polygon2DData* polyData = polyDatas [contourPoly];
			memcpy (*poly->contourInfos + poly->nContours * poly->sizeOfContourInfo,
				    *polyData->contourInfos + contourInd * polyData->sizeOfContourInfo, polyData->sizeOfContourInfo);
		} else {
			memcpy (*poly->contourInfos + poly->nContours * poly->sizeOfContourInfo,
				    *poly->defaultContourInfo, poly->sizeOfContourInfo);
		}
	}
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::ReturnResult (PGRESPOLYEXT* newPolygons)
{
	GS::ArrayFB<Contour, 10>& mainContours = !withoutHoles ? positivContours : outsideContours;

	if (newPolygons->newPolygon == nullptr) {
		GS::VAArray<Polygon2DData>*	resultPolys = (GS::VAArray<Geometry::Polygon2DData>*) newPolygons->polygonsData;
		Polygon2DData poly;
		const Polygon2DData* polyData;

		if (noChange && origPolys.GetSize () < 2 && mainContours.GetSize () == 1) {
			if (InitPolygon2DData (&poly) != NoError)
				throw GS::GeneralException ("Cannot initialize new polygon", __FILE__, __LINE__);
			if (CopyPolygon2DData (&poly, *polyDatas [0]) != NoError) {
				FreePolygon2DData (&poly);
				throw GS::GeneralException ("Cannot copy new polygon", __FILE__, __LINE__);
			}
			try { resultPolys->Push (poly); }
			catch (const GS::Exception&)
			{
				FreePolygon2DData (&poly);
				throw;
			}
		} else {
			GSSize sizeOfVertexInfo				= polyDatas [0]->sizeOfVertexInfo;
			GSHandle defaultVertexInfo			= polyDatas [0]->defaultVertexInfo;
			GSSize sizeOfInhEdgeInfo			= polyDatas [0]->sizeOfInhEdgeInfo;
			GSHandle defaultInhEdgeInfo			= polyDatas [0]->defaultInhEdgeInfo;
			GSSize sizeOfUniqEdgeInfo			= polyDatas [0]->sizeOfUniqEdgeInfo;
			GSHandle defaultUniqEdgeInfo		= polyDatas [0]->defaultUniqEdgeInfo;
			GSSize sizeOfContourInfo			= polyDatas [0]->sizeOfContourInfo;
			GSHandle defaultContourInfo			= polyDatas [0]->defaultContourInfo;
			GSSize sizeOfInhPolygonInfo			= polyDatas [0]->sizeOfInhPolygonInfo;
			GSHandle defaultInhPolygonInfo		= polyDatas [0]->inhPolygonInfo;
			GSSize sizeOfUniqPolygonInfo		= polyDatas [0]->sizeOfUniqPolygonInfo;
			GSHandle defaultUniqPolygonInfo		= polyDatas [0]->defaultUniqPolygonInfo;

			for (UInt32 i = 1; i < polyDatas.GetSize (); ++i) {
				if (sizeOfVertexInfo < polyDatas [i]->sizeOfVertexInfo) {
					defaultVertexInfo	= polyDatas [i]->defaultVertexInfo;
					sizeOfVertexInfo	= polyDatas [i]->sizeOfVertexInfo;
				}
				if (sizeOfInhEdgeInfo < polyDatas [i]->sizeOfInhEdgeInfo) {
					defaultInhEdgeInfo	= polyDatas [i]->defaultInhEdgeInfo;
					sizeOfInhEdgeInfo	= polyDatas [i]->sizeOfInhEdgeInfo;
				}
				if (sizeOfUniqEdgeInfo < polyDatas [i]->sizeOfUniqEdgeInfo) {
					defaultUniqEdgeInfo	= polyDatas [i]->defaultUniqEdgeInfo;
					sizeOfUniqEdgeInfo	= polyDatas [i]->sizeOfUniqEdgeInfo;
				}
				if (sizeOfContourInfo < polyDatas [i]->sizeOfContourInfo) {
					defaultContourInfo	= polyDatas [i]->defaultContourInfo;
					sizeOfContourInfo	= polyDatas [i]->sizeOfContourInfo;
				}
				if (sizeOfInhPolygonInfo < polyDatas [i]->sizeOfInhPolygonInfo) {
					defaultInhPolygonInfo	= polyDatas [i]->inhPolygonInfo;
					sizeOfInhPolygonInfo	= polyDatas [i]->sizeOfInhPolygonInfo;
				}
				if (sizeOfUniqPolygonInfo < polyDatas [i]->sizeOfUniqPolygonInfo) {
					defaultUniqPolygonInfo	= polyDatas [i]->defaultUniqPolygonInfo;
					sizeOfUniqPolygonInfo	= polyDatas [i]->sizeOfUniqPolygonInfo;
				}
			}	

			GS::ArrayFB<bool, 10> polyFound;
			polyFound.SetSize (polyDatas.GetSize ()); // set to false

			for (Int32 i = 0; i < Int32 (mainContours.GetSize ()); i++) {
				if (breaker != nullptr && breaker->ShouldAbort ())
					throw GS::AbortException ();

				const WhichPoly whichPoly = mainContours [i].whichPoly;

				if (DBERROR (whichPoly >= polyDatas.GetSize ())) {
					continue;
				}

				if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].area2) < area2Minimum)
					continue;

				try {
					memset (&poly, 0, sizeof (poly));
					poly.status.isBoundBoxValid = 1;
					poly.status.isOrientationCorrect = 1;
					poly.status.isSameDirEdgeLegal = polyDatas [0]->status.isSameDirEdgeLegal;
					poly.status.force64BitPrecision = polyDatas [0]->status.force64BitPrecision;
					InitBox (&poly.boundBox);

					Int32 numVertex = mainContours[i].numVertex + 1;
					Int32 numArc = mainContours[i].numArc;
					Int32 numContours = 1;
					for (Int32 j = 0; j < Int32 (mainContours[i].holes.GetSize ()); j++) {
						if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].holes[j].area2) < area2Minimum)
							continue;

						numVertex += mainContours[i].holes[j].numVertex + 1;
						numArc += mainContours[i].holes[j].numArc;
						numContours++;
					}
					poly.vertices = (Coord**) BMXhAll (sizeof (Coord) * (numVertex + 1));
					poly.arcs = (PolyArcRec**) BMXhAll (sizeof (PolyArcRec) * (numArc + 1));
					poly.contourEnds = (UIndex**) BMXhAll (sizeof (UIndex) * (numContours + 1));
					memset (*poly.vertices, 0, sizeof (Coord));
					memset (*poly.arcs, 0, sizeof (PolyArcRec));
					(*poly.contourEnds)[0] = 0;

					polyData = polyDatas [whichPoly];

					poly.sizeOfVertexInfo = sizeOfVertexInfo;
					if (poly.sizeOfVertexInfo != 0) {
						poly.vertexInfos = BMXhAllClear (poly.sizeOfVertexInfo * (numVertex + 1));
						poly.defaultVertexInfo = BMXhAll (poly.sizeOfVertexInfo);
						memcpy (*poly.defaultVertexInfo, *defaultVertexInfo, poly.sizeOfVertexInfo);
						for (Int32 j = 0; j <= numVertex; j++)
							memcpy (*poly.vertexInfos + j * poly.sizeOfVertexInfo, *defaultVertexInfo, poly.sizeOfVertexInfo);
					}
					
					poly.sizeOfInhEdgeInfo = sizeOfInhEdgeInfo;
					if (poly.sizeOfInhEdgeInfo != 0) {
						poly.inhEdgeInfos = BMXhAllClear (poly.sizeOfInhEdgeInfo * (numVertex + 1));
						poly.defaultInhEdgeInfo = BMXhAll (poly.sizeOfInhEdgeInfo);
						memcpy (*poly.defaultInhEdgeInfo, *defaultInhEdgeInfo, poly.sizeOfInhEdgeInfo);
						for (Int32 j = 0; j <= numVertex; j++)
							memcpy (*poly.inhEdgeInfos + j * poly.sizeOfInhEdgeInfo, *defaultInhEdgeInfo, poly.sizeOfInhEdgeInfo);
					}

					poly.sizeOfUniqEdgeInfo = sizeOfUniqEdgeInfo;
					if (poly.sizeOfUniqEdgeInfo != 0) {
						poly.uniqEdgeInfos = BMXhAllClear (poly.sizeOfUniqEdgeInfo * (numVertex + 1));
						poly.defaultUniqEdgeInfo = BMXhAll (poly.sizeOfUniqEdgeInfo);
						memcpy (*poly.defaultUniqEdgeInfo, *defaultUniqEdgeInfo, poly.sizeOfUniqEdgeInfo);
						for (Int32 j = 0; j <= numVertex; j++)
							memcpy (*poly.uniqEdgeInfos + j * poly.sizeOfUniqEdgeInfo, *defaultUniqEdgeInfo, poly.sizeOfUniqEdgeInfo);
					}

					poly.sizeOfContourInfo = sizeOfContourInfo;
					if (poly.sizeOfContourInfo != 0) {
						poly.contourInfos = BMXhAllClear (poly.sizeOfContourInfo * (numContours + 1));
						poly.defaultContourInfo = BMXhAll (poly.sizeOfContourInfo);
						memcpy (*poly.defaultContourInfo, *defaultContourInfo, poly.sizeOfContourInfo);
						for (Int32 j = 0; j <= numContours; j++)
							memcpy (*poly.contourInfos + j * poly.sizeOfContourInfo, *defaultContourInfo, poly.sizeOfContourInfo);
					}

					poly.sizeOfInhPolygonInfo = sizeOfInhPolygonInfo;
					if (poly.sizeOfInhPolygonInfo != 0) {
						poly.inhPolygonInfo = BMXhAll (poly.sizeOfInhPolygonInfo);
						if (poly.sizeOfInhPolygonInfo == polyData->sizeOfInhPolygonInfo) {
							memcpy (*poly.inhPolygonInfo, *polyData->inhPolygonInfo, poly.sizeOfInhPolygonInfo);
						} else {
							memcpy (*poly.inhPolygonInfo, *defaultInhPolygonInfo, poly.sizeOfInhPolygonInfo);
						}
					}

					poly.sizeOfUniqPolygonInfo = sizeOfUniqPolygonInfo;
					if (poly.sizeOfUniqPolygonInfo != 0) {
						poly.uniqPolygonInfo = BMXhAll (poly.sizeOfUniqPolygonInfo);
						poly.defaultUniqPolygonInfo = BMXhAll (poly.sizeOfUniqPolygonInfo);
						memcpy (*poly.defaultUniqPolygonInfo, *defaultUniqPolygonInfo, poly.sizeOfUniqPolygonInfo);
						if ((poly.sizeOfUniqPolygonInfo == polyData->sizeOfUniqPolygonInfo) && !polyFound [whichPoly]) {
							memcpy (*poly.uniqPolygonInfo, *polyData->uniqPolygonInfo, poly.sizeOfUniqPolygonInfo);
						} else {
							memcpy (*poly.uniqPolygonInfo, *defaultUniqPolygonInfo, poly.sizeOfUniqPolygonInfo);
						}
					}

					polyFound [whichPoly] = true;

					ReturnContourData (mainContours[i], &poly);
					for (Int32 j = 0; j < Int32 (mainContours[i].holes.GetSize ()); j++) {
						if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].holes[j].area2) < area2Minimum)
							continue;

						ReturnContourData (mainContours[i].holes[j], &poly);
					}

					BMXhSetSize ((GSHandle) poly.vertices, sizeof (Coord) * (poly.nVertices + 1));

					resultPolys->Push (poly);
				}
				catch (const GS::Exception&)
				{
					FreePolygon2DData (&poly);
					for (i--; i >= 0; i--)
						if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].area2) >= area2Minimum) {
							poly = resultPolys->Pop ();
							FreePolygon2DData (&poly);
						}

					throw;
				}
			}
		}
	} else {
		PGPOLYEXT* createdPoly = nullptr;
		
		bool  noChangeOneContour = false; 
		if (noChange && origPolys.GetSize () < 2 && mainContours.GetSize () == 1) {
			const UInt32 polyEdgeOffset = polyEdgeOffsets [0];
			for (Int32 i = 1; i <= origPolys [0]->nEdges; i++) {
				if (polyEdges[polyEdgeOffset + i].status.isEndContour) {
					noChangeOneContour = (i == origPolys [0]->nEdges);
					break;
				}
			}
		}

		if (noChangeOneContour) {
			PGPOLYEXT newPoly = *(origPolys [0]);
			newPoly.nContours = 1;
			if ((*newPolygons->newPolygon) (newPolygons, &newPoly, &createdPoly) != NoError)
				throw GS::GeneralException ("Cannot create new polygon", __FILE__, __LINE__);

			PGEDGEEXT edge;
			const UInt32 polyEdgeOffset = polyEdgeOffsets [0];
			for (Int32 i = 1; i <= origPolys [0]->nEdges; i++) {
				edge = polyEdges[polyEdgeOffset + i];
				
				if (!edge.status.isEndContour) {
					const Int32 contourEdgeIndex = (Int32)TruncateTo32Bit ((GS::IntPtr)edge.contourData);
					DBASSERT (polyEdges[contourEdgeIndex].status.isEndContour);
					edge.contourData = polyEdges[contourEdgeIndex].contourData;
				}

				edge.generatedVertexId = ++generatedNodeIdCounter;
				edge.status.isEndPolygon = false;
				if ((*createdPoly->newEdge) (createdPoly, &edge) != NoError)
					throw GS::GeneralException ("Cannot create edge", __FILE__, __LINE__);
			}
			edge.generatedVertexId = 0;
			edge.status.isEndPolygon = true;
			if ((*createdPoly->newEdge) (createdPoly, &edge) != NoError)
				throw GS::GeneralException ("Cannot finish polygon", __FILE__, __LINE__);
		} else {
			PGPOLYEXT newPoly = *origPolys [0];
			
			for (Int32 i = 0; i < Int32 (mainContours.GetSize ()); i++) {
				if (DBERROR (mainContours [i].whichPoly >= origPolys.GetSize ())) {
					continue;
				}

				if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].area2) < area2Minimum)
					continue;

				WhichPoly whichPoly = mainContours [i].whichPoly;

				newPoly.defaultVertexData	= origPolys [whichPoly]->defaultVertexData;
				newPoly.defaultInhEdgeData	= origPolys [whichPoly]->defaultInhEdgeData;
				newPoly.defaultUniqEdgeData = origPolys [whichPoly]->defaultUniqEdgeData;
				newPoly.defaultContourData	= origPolys [whichPoly]->defaultContourData;
				newPoly.inhPolygonData		= origPolys [whichPoly]->inhPolygonData;


				Point<DInt,Int> pMin (mainContours[i].bbox.minX, mainContours[i].bbox.minY);
				Point<DInt,Int> pMax (mainContours[i].bbox.maxX, mainContours[i].bbox.maxY);

				Coord cMin = PointToCoord (pMin);
				Coord cMax = PointToCoord (pMax);

				newPoly.boundBox.xMin = cMin.x;
				newPoly.boundBox.xMax = cMax.x;
				newPoly.boundBox.yMin = cMin.y;
				newPoly.boundBox.yMax = cMax.y;

				newPoly.nContours = 1;
				newPoly.nEdges = mainContours[i].numVertex;
				newPoly.nArcs  = mainContours[i].numArc;
				for (Int32 j = 0; j < Int32 (mainContours[i].holes.GetSize ()); j++) {
					if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].holes[j].area2) < area2Minimum)
						continue;

					newPoly.nContours += 1;
					newPoly.nEdges += mainContours[i].holes[j].numVertex;
					newPoly.nArcs  += mainContours[i].holes[j].numArc;
				}

				if ((*newPolygons->newPolygon) (newPolygons, &newPoly, &createdPoly) != NoError)
					throw GS::GeneralException ("Cannot create new polygon", __FILE__, __LINE__);

				ReturnContourProc (mainContours[i], createdPoly);
				for (Int32 j = 0; j < Int32 (mainContours[i].holes.GetSize ()); j++) {
					if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].holes[j].area2) < area2Minimum)
						continue;

					ReturnContourProc (mainContours[i].holes[j], createdPoly);
				}

				PGEDGEEXT e;
				e.generatedVertexId = 0;
				e.status.isEndPolygon = true;
				if ((*createdPoly->newEdge) (createdPoly, &e) != NoError)
					throw GS::GeneralException ("Cannot finish polygon", __FILE__, __LINE__);
			}
		}
	}
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::PrintContour (const Contour& contour, GS::OChannel& outChannel)
{
	Link* link = contour.startLink;
	do {
		Coord beg = PointToCoord (link->beg->pos);
		outChannel << beg.x << ",  " << beg.y << ",   1, \n";

		if (!link->isLine) {
			Arc* arc = (Arc*) link;
			Coord center = PointToCoord (arc->center);
			Coord end = PointToCoord (arc->end->pos);
			double fi1 = ComputeFi (center, beg);
			double fi2 = ComputeFi (center, end);
			outChannel << center.x << ",  " << center.y << ",  900, \n";
			outChannel << "  0, " << CalcRotFi (fi1, fi2, !arc->positiv) * 180.0 / PI << ", 4001, \n";
		}

		link = !withoutHoles ? GetContourNextLink (link, contour) : GetOutsideContourNextLink (link, contour);
	} while (link != contour.startLink);

	Coord beg = PointToCoord (link->beg->pos);
	outChannel << beg.x << ",  " << beg.y << ",   -1";
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::PrintResult (GS::OChannel& outChannel)
{
	GS::ArrayFB<Contour, 10>& mainContours = !withoutHoles ? positivContours : outsideContours;

	for (Int32 i = 0; i < Int32 (mainContours.GetSize ()); i++) {
		if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].area2) < area2Minimum)
			continue;

		Int32 lines = mainContours[i].numVertex + 2 * mainContours[i].numArc + 1;
		for (Int32 j = 0; j < Int32 (mainContours[i].holes.GetSize ()); j++) {
			if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].holes[j].area2) < area2Minimum)
				continue;
			lines += mainContours[i].holes[j].numVertex + 2 * mainContours[i].holes[j].numArc + 1;
		}

		outChannel << "\nPOLY2_   " << lines << ",  7,\n";

		PrintContour (mainContours[i], outChannel);
		for (Int32 j = 0; j < Int32 (mainContours[i].holes.GetSize ()); j++) {
			if (pgBoolean->resultPolygonHandling == PGBoolean<PolygonSelector>::SkipSmallPolygons && Abs (mainContours[i].holes[j].area2) < area2Minimum)
				continue;

			outChannel << ",\n";
			PrintContour (mainContours[i].holes[j], outChannel);
		}

		outChannel << "\n\n";
	}
}

}

#endif
