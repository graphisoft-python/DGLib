// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLTMPINTERSECTLINKS_H
#define PGBOOLTMPINTERSECTLINKS_H

#include "Approx.hpp"

namespace PolygonBoolean {

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::NodeToNodeSnap ()
{
	bool retVal = false;

	if (!pgBoolean->containsArc && allNodes.GetSize () < 25) {
		bool markForDeleteWas = false;
		Int32 i, j;

		for (i = 0; i < Int32 (allNodes.GetSize ()); i++) {
			Node* iNode = allNodes[i];
			for (j = i + 1; j < Int32 (allNodes.GetSize ()); j++) {
				Node* jNode = allNodes[j];
				if (Abs (iNode->pos.x - jNode->pos.x) < snapDist && Abs (iNode->pos.y - jNode->pos.y) < snapDist) {
					nodesSorted = linksSorted = false;
					retVal = true;

					for (Int32 k = 0; k < Int32 (jNode->links.GetSize ()); ) {
						Link* lk = jNode->links[k];
						if (lk->beg == iNode || lk->end == iNode) {
							if (k < Int32 (jNode->links.GetSize ()) - 1)
								jNode->links[k] = jNode->links.GetLast ();
							jNode->links.Pop ();
						} else
							k++;
					}

					for (Int32 k = 0; k < Int32 (iNode->links.GetSize ()); k++) {
						Link* lk = iNode->links[k];
						if (lk->beg == jNode || lk->end == jNode)
							markForDeleteWas = lk->markForDelete = true;
						else {
							jNode->links.Push (lk);
							lk->*(lk->beg == iNode ? &Link::beg : &Link::end) = jNode;
							FillLineStruct ((Line*) lk);
						}
					}

					if (jNode->whichPoly > iNode->whichPoly) {
						jNode->origVertex = iNode->origVertex;
						jNode->whichPoly = iNode->whichPoly;
					}

					if (jNode->links.GetSize () == 0) {
						DeleteNode (jNode);
						if (j < Int32 (allNodes.GetSize ()) - 1)
							allNodes[j] = allNodes.GetLast ();
						allNodes.Pop ();
					}
					if (i < Int32 (allNodes.GetSize ()) - 1)
						allNodes[i] = allNodes.GetLast ();
					allNodes.Pop ();
					DeleteNode (iNode);
					i--;
					break;
				}
			}
		}

		if (markForDeleteWas) {
			Int32 linksNum = allLinks.GetSize ();
			for (Int32 i = 0; i < linksNum;) {
				if (allLinks[i]->markForDelete) {
					if (i < linksNum - 1)
						allLinks[i] = allLinks.GetLast ();
					allLinks.Pop ();
					linksNum--;
				} else
					i++;
			}
		}

		return retVal;
	} else {
		if (!nodesSorted) {
			qsort ((Node**) allNodes.GetContent (), allNodes.GetSize (), sizeof (Node*), CompareNodes);
			nodesSorted = true;
		}

		for (int infiniteCycleCount = 0; ; infiniteCycleCount++) {
			if (infiniteCycleCount == 300)
				throw GeometryAlgorithmErrorException ("Infinite Cycle", __FILE__, __LINE__);

			bool snapWas = false;
			bool newNodeAdded = false;
			const Int32 origNodesNum = allNodes.GetSize ();

			for (Int32 i = 1, lastWatch = 0; i < origNodesNum; i++) {
				if (breaker != nullptr && breaker->ShouldAbort ())
					throw GS::AbortException ();

				Node* const iNode = allNodes[i];
				while (lastWatch < i && (allNodes[lastWatch] == nullptr || allNodes[lastWatch]->pos.x + snapDist <= iNode->pos.x))
					lastWatch++;

				for (Int32 j = i - 1; j >= lastWatch; j--) {
					Node* const jNode = allNodes[j];

					if (jNode != nullptr && Abs (jNode->pos.y - iNode->pos.y) < snapDist) {
						snapWas = true;

						for (Int32 k = 0; k < Int32 (jNode->links.GetSize ()); ) {
							Link* lk = jNode->links[k];
							bool deleteLink = false;

							if (lk->beg == iNode || lk->end == iNode) {
								deleteLink = true;
								if (!lk->isLine) {
									Arc* arc = (Arc*) lk;
									Point<DInt,Int> othSide = arc->center - jNode->pos;
									if (IsCCW (othSide, arc->left, GetRelativePointQuarter (arc->right, othSide, arc->qr), arc->ql)) {
										othSide = RoundToNodeGrid (othSide * 2);
										if (Abs (othSide.x) >= snapDist || Abs (othSide.y) >= snapDist) {
											newNodeAdded = true;
											deleteLink = false;

											Node* nNode = nullptr;
											Arc* nArc = nullptr;

											try {
												nNode = NewNode ();
												nNode->pos = othSide + jNode->pos;
												nNode->origVertex = -1;
												nNode->whichPoly = None;

												nArc = NewArc (*arc);
												nArc->uniqOrigEdge = false;
												if (arc->beg == iNode)
													nArc->beg = arc->end = nNode;
												else
													nArc->end = arc->beg = nNode;

												nNode->links.Push (arc);
												nNode->links.Push (nArc);

												jNode->links[k] = nArc;

												FillArcStruct (arc);
												FillArcStruct (nArc);

												allNodes.Push (nNode);
												nNode = nullptr;
												allLinks.Push (nArc);
											}
											catch (const GS::Exception&)
											{
												DeleteNode (nNode);
												DeleteLink (nArc);
												throw;
											}
										}
									}
								}
							}

							if (deleteLink) {
								if (k < Int32 (jNode->links.GetSize ()) - 1)
									jNode->links[k] = jNode->links.GetLast ();
								jNode->links.Pop ();
							} else
								k++;
						}

						for (Int32 k = 0; k < Int32 (iNode->links.GetSize ()); k++) {
							Link* lk = iNode->links[k];
							if (lk->beg == jNode || lk->end == jNode)
								lk->markForDelete = true;
							else {
								jNode->links.Push (lk);
								lk->*(lk->beg == iNode ? &Link::beg : &Link::end) = jNode;
								if (lk->isLine) {
									FillLineStruct ((Line*) lk);
								} else {
									FillArcStruct ((Arc*) lk);
								}
							}
						}

						if (jNode->whichPoly > iNode->whichPoly) {
							jNode->origVertex = iNode->origVertex;
							jNode->whichPoly = iNode->whichPoly;
						}

						DeleteNode (iNode);
						allNodes[i] = nullptr;
						if (jNode->links.GetSize () == 0) {
							DeleteNode (jNode);
							allNodes[j] = nullptr;
						}
						break;
					}
				}
			}

			if (snapWas) {
				qsort ((Node**) allNodes.GetContent (), allNodes.GetSize (), sizeof (Node*), CompareNodes);
				for (Int32 i = allNodes.GetSize () - 1; i >= 0 && allNodes[i] == nullptr; i--)
					allNodes.Pop ();

				retVal = true;
			}

			if (!newNodeAdded) {
				if (retVal) {
					qsort ((Link**) allLinks.GetContent (), allLinks.GetSize (), sizeof (Link*), CompareLinks);
					linksSorted = true;
					for (Int32 i = allLinks.GetSize () - 1; i >= 0 && allLinks[i]->markForDelete; i--)
						DeleteLink (allLinks.Pop ());
				}
				return retVal;
			}
		}
	}
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::AddNodeIfNearToLine (Line* line, Node* node, NodeSnapToLineDataArray& snapNodes)
{
	Point<DInt,Int> p = node->pos;

	p -= line->beg->pos;
	Point<DInt,Int> end = line->end->pos - line->beg->pos;

	Int aex = Abs (end.x);
	Int aey = Abs (end.y);
	if (aex < aey) {
		DInt a = Mul (p.x, aey);
		a += end.y > 0 ? -Mul (end.x, p.y) : Mul (end.x, p.y);
		if (Abs (a) < Mul (snapDist, aey)) {
			NodeSnapToLineData snapData;
			snapData.node = node;
			snapData.sortVal = end.y > 0 ? p.y : -p.y;
			snapNodes.Push (snapData);
			return true;
		} else
			return false;
	} else {
		DInt a = Mul (p.y, aex);
		a += end.x > 0 ? -Mul (end.y, p.x) : Mul (end.y, p.x);
		if (Abs (a) < Mul (snapDist, aex)) {
			NodeSnapToLineData snapData;
			snapData.node = node;
			snapData.sortVal = end.x > 0 ? p.x : -p.x;
			snapNodes.Push (snapData);
			return true;
		} else
			return false;
	}
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::AddNodeIfNearToArc (Arc* arc, Node* node, NodeSnapToArcDataArray& snapNodes)
{
	Point<DInt,Int> p = node->pos - arc->center;
	if (Abs (p.Len () - arc->r) >= snapDist)
		return false;

	int qp = GetRelativePointQuarter (arc->right, p, arc->qr);
	if (!IsCCW (p, arc->left, qp, arc->ql))
		return false;

	NodeSnapToArcData snapData;
	snapData.node = node;
	snapData.p = p;
	snapData.qnode = qp;
	snapNodes.Push (snapData);
	return true;
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::LinkToNodeSnap ()
{
	GS::HashTable<Line*, NodeSnapToLineDataArray> insertLineNodes;
	GS::HashTable<Arc*, NodeSnapToArcDataArray> insertArcNodes;
	NodeSnapToLineDataArray newLineSnapNodes;
	NodeSnapToArcDataArray newArcSnapNodes;

	const Int32 nodesNum = allNodes.GetSize ();
	const Int32 linksNum = allLinks.GetSize ();

	if (!pgBoolean->containsArc && nodesNum < 70 && linksNum < 70 && nodesNum * linksNum < 70) {
		for (Int32 j = 0; j < linksNum; j++) {
			Link* jLink = allLinks[j];
			BoundBox<Int> bb;
			bb.minX = jLink->bbox.minX - snapDist;
			bb.minY = jLink->bbox.minY - snapDist;
			bb.maxX = jLink->bbox.maxX + snapDist;
			bb.maxY = jLink->bbox.maxY + snapDist;

			for (Int32 i = 0; i < nodesNum; i++) {
				Node* iNode = allNodes[i];
				Point<DInt,Int>& p = iNode->pos;
				if (jLink->beg != iNode && jLink->end != iNode && p.x > bb.minX && p.x < bb.maxX && p.y > bb.minY && p.y < bb.maxY ) {
					Line* line = (Line*) jLink;
					NodeSnapToLineDataArray* snapNodes;
					if (insertLineNodes.Get (line, &snapNodes))
						AddNodeIfNearToLine (line, iNode, *snapNodes);
					else {
						newLineSnapNodes.Clear ();
						if (AddNodeIfNearToLine (line, iNode, newLineSnapNodes))
							insertLineNodes.Add (line, newLineSnapNodes);
					}
				}
			}
		}
	} else {
		if (!nodesSorted) {
			qsort ((Node**) allNodes.GetContent (), allNodes.GetSize (), sizeof (Node*), CompareNodes);
			nodesSorted = true;
		}

		if (!linksSorted) {
			qsort ((Link**) allLinks.GetContent (), allLinks.GetSize (), sizeof (Link*), CompareLinks);
			linksSorted = true;
		}

		const int statAlloc = sizeof (linkPtrArr) / sizeof (linkPtrArr[0]);
		typedef Link* LinkPtr;
		Link** currLinksArray;

		if (linksNum <= statAlloc)
			currLinksArray = linkPtrArr;
		else
			currLinksArray = new LinkPtr[linksNum];

		Int32 firstLinkIndex = 0;
		Int32 lastLinkIndex = -1;

		try {
			for (Int32 i = 0, nextWatch = 0; i < nodesNum; i++) {
				if (breaker != nullptr && breaker->ShouldAbort ())
					throw GS::AbortException ();

				const Point<DInt,Int>& p = allNodes[i]->pos;

				while (firstLinkIndex <= lastLinkIndex && currLinksArray[firstLinkIndex]->bbox.maxX + snapDist <= p.x)
					firstLinkIndex++;

				while (nextWatch < linksNum && allLinks[nextWatch]->bbox.minX - snapDist < p.x) {
					Int32 j;
					for (j = lastLinkIndex; j >= firstLinkIndex; j--) {
						if (allLinks[nextWatch]->bbox.maxX >= currLinksArray[j]->bbox.maxX)
							break;
						currLinksArray[j + 1] = currLinksArray[j];
					}
					currLinksArray[j + 1] = allLinks[nextWatch];
					lastLinkIndex++;

					nextWatch++;
				}

				for (Int32 j = firstLinkIndex; j <= lastLinkIndex; j++) {
					if (p.y < currLinksArray[j]->bbox.maxY + snapDist &&
						p.y > currLinksArray[j]->bbox.minY - snapDist &&
						currLinksArray[j]->beg != allNodes[i] &&
						currLinksArray[j]->end != allNodes[i])
					{
						if (currLinksArray[j]->isLine) {
							Line* line = (Line*) currLinksArray[j];
							NodeSnapToLineDataArray* snapNodes;
							if (insertLineNodes.Get (line, &snapNodes))
								AddNodeIfNearToLine (line, allNodes[i], *snapNodes);
							else {
								newLineSnapNodes.Clear ();
								if (AddNodeIfNearToLine (line, allNodes[i], newLineSnapNodes))
									insertLineNodes.Add (line, newLineSnapNodes);
							}
						} else {
							Arc* arc = (Arc*) currLinksArray[j];
							NodeSnapToArcDataArray* snapNodes;
							if (insertArcNodes.Get (arc, &snapNodes))
								AddNodeIfNearToArc (arc, allNodes[i], *snapNodes);
							else {
								newArcSnapNodes.Clear ();
								if (AddNodeIfNearToArc (arc, allNodes[i], newArcSnapNodes))
									insertArcNodes.Add (arc, newArcSnapNodes);
							}
						}
					}
				}
			}

			if (linksNum > statAlloc)
				delete [] currLinksArray;
			currLinksArray = nullptr;
		}
		catch (const GS::Exception&)
		{
			if (linksNum > statAlloc && currLinksArray != nullptr)
				delete [] currLinksArray;
			throw;
		}
	}

	{
		typename GS::HashTable<Line*, NodeSnapToLineDataArray>::PairIterator iter = insertLineNodes.EnumeratePairs ();
		while (iter != nullptr) {
			InsertNodesToLine (*iter->key, *iter->value);
			++iter;
		}
	}

	{
		typename GS::HashTable<Arc*, NodeSnapToArcDataArray>::PairIterator iter = insertArcNodes.EnumeratePairs ();
		while (iter != nullptr) {
			InsertNodesToArc (*iter->key, *iter->value);
			++iter;
		}
	}

	if (!insertLineNodes.IsEmpty () || !insertArcNodes.IsEmpty ()) {
		linksSorted = false;
		return true;
	} else
		return false;
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::InsertNodesToLine (Line* line, NodeSnapToLineDataArray& nodesToInsert)
{
	const Int32 nodesNum = nodesToInsert.GetSize ();
	qsort ((NodeSnapToLineData*) nodesToInsert.GetContent (), nodesToInsert.GetSize (), sizeof (NodeSnapToLineData),
		CompareNodeSnapToLineData);

	Node* end = line->end;
	Line* currLine = line;
	for (Int32 i = 0; i < nodesNum; i++) {
		Line* nextLine = NewLine (*currLine);
		nextLine->beg = currLine->end = nodesToInsert[i].node;
		nextLine->uniqOrigEdge = false;
		try { allLinks.Push (nextLine); }
		catch (const GS::Exception&) { DeleteLink (nextLine); throw; }

		nextLine->beg->links.Push (currLine);
		nextLine->beg->links.Push (nextLine);
		FillLineStruct (currLine);
		currLine = nextLine;
	}
	for (Int32 i = 0; i < Int32 (end->links.GetSize ()); i++) {
		if (end->links[i] == line) {
			end->links[i] = currLine;
			break;
		}
	}
	FillLineStruct (currLine);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::InsertNodesToArc (Arc* arc, NodeSnapToArcDataArray& nodesToInsert)
{
	const Int32 nodesNum = nodesToInsert.GetSize ();
	qsort ((NodeSnapToArcData*) nodesToInsert.GetContent (), nodesToInsert.GetSize (), sizeof (NodeSnapToArcData),
		arc->positiv ? CompareNodeSnapToArcDataPositiv : CompareNodeSnapToArcDataNegativ);

	Node* end = arc->end;
	Arc* currArc = arc;
	for (Int32 i = 0; i < nodesNum; i++) {
		Arc* nextArc = NewArc (*currArc);
		nextArc->beg = currArc->end = nodesToInsert[i].node;
		nextArc->uniqOrigEdge = false;
		try { allLinks.Push (nextArc); }
		catch (const GS::Exception&) { DeleteLink (nextArc); throw; }

		nextArc->beg->links.Push (currArc);
		nextArc->beg->links.Push (nextArc);
		FillArcStruct (currArc);
		currArc = nextArc;
	}
	for (Int32 i = 0; i < Int32 (end->links.GetSize ()); i++) {
		if (end->links[i] == arc) {
			end->links[i] = currArc;
			break;
		}
	}
	FillArcStruct (currArc);
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::ApproxLineToLineIntersection (Line* l1, Line* l2)
{
	// Approximate intersection
	// The function returns false if intersection surely does not occur,
	// otherwise it returns true
	
	const Int dx1Int (l1->end->pos.x - l1->beg->pos.x);
	const Int dy1Int (l1->end->pos.y - l1->beg->pos.y);
	const Int dx2Int (l2->end->pos.x - l2->beg->pos.x);
	const Int dy2Int (l2->end->pos.y - l2->beg->pos.y);
	const Int bxInt (l2->beg->pos.x - l1->beg->pos.x);
	const Int byInt (l2->beg->pos.y - l1->beg->pos.y);

	const Approx dx1 (dx1Int, dx1Int);
	const Approx dy1 (dy1Int, dy1Int);
	const Approx dx2 (dx2Int, dx2Int);
	const Approx dy2 (dy2Int, dy2Int);
	const Approx bx (bxInt, bxInt);
	const Approx by (byInt, byInt);

	Approx p = by * dx2 - bx * dy2;
	if (p.CanBeNull ())
		return true;

	const Approx t = dx1 * dy2 - dy1 * dx2;
	Approx q = p + t;
	if (q.CanBeNull ())
		return true;

	if (p.Sgn () == q.Sgn ())
		return false;

	p = bx * dy1 - by * dx1;
	if (p.CanBeNull ())
		return true;

	q = p - t;
	if (q.CanBeNull ())
		return true;

	if (p.Sgn () == q.Sgn ())
		return false;

	return true;
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::AddLineToLineIntersection (Line* l1, Line* l2, NodeSnapToLineDataArray& snapNodes1,
										   NodeSnapToLineDataArray& snapNodes2)
{
	typedef QXTools::Integer<Int> Integer;

	bool canIntersect = ApproxLineToLineIntersection (l1, l2);
#ifndef DEBUVERS
	if (!canIntersect)
		return false;
#endif

	const Integer dx1 (l1->end->pos.x - l1->beg->pos.x);
	const Integer dy1 (l1->end->pos.y - l1->beg->pos.y);
	const Integer dx2 (l2->end->pos.x - l2->beg->pos.x);
	const Integer dy2 (l2->end->pos.y - l2->beg->pos.y);
	const Integer bx (l2->beg->pos.x - l1->beg->pos.x);
	const Integer by (l2->beg->pos.y - l1->beg->pos.y);

	Integer p = by * dx2 - bx * dy2;
	if (p.IsZero ())
		return false;

	const Integer t = dx1 * dy2 - dy1 * dx2;
	Integer q = p + t;
	if (q.IsZero () || p.IsNegative () == q.IsNegative ())
		return false;

	p = bx * dy1 - by * dx1;
	if (p.IsZero ())
		return false;

	q = p - t;
	if (q.IsZero () || p.IsNegative () == q.IsNegative ())
		return false;

	DBASSERT (canIntersect);

	Integer x = Integer (l2->beg->pos.x) + dx2 * p / t;
	Integer y = Integer (l2->beg->pos.y) + dy2 * p / t;

	Node* node = NewNode ();
	node->pos = RoundToNodeGrid (Point<DInt,Int> (x.ConvertToInt (), y.ConvertToInt ()));
	node->origVertex = -1;
	node->whichPoly = None;
	try { allNodes.Push (node); }
	catch (const GS::Exception&) { DeleteNode (node); throw; }

	NodeSnapToLineData snapData;
	snapData.node = node;
	if (dx1.CompareAbs (dy1) < 0)
		snapData.sortVal = Abs (node->pos.y - l1->beg->pos.y);
	else
		snapData.sortVal = Abs (node->pos.x - l1->beg->pos.x);
	snapNodes1.Push (snapData);

	if (dx2.CompareAbs (dy2) < 0)
		snapData.sortVal = Abs (node->pos.y - l2->beg->pos.y);
	else
		snapData.sortVal = Abs (node->pos.x - l2->beg->pos.x);
	snapNodes2.Push (snapData);

	return true;
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::AddLineToArcIntersections (Line* line, Arc* arc, NodeSnapToLineDataArray& snapNodes1,
										   NodeSnapToArcDataArray& snapNodes2)
{
	int common = 0;

	if (line->beg == arc->beg || line->beg == arc->end)
		common = 1;
	if (line->end == arc->beg || line->end == arc->end) {
		if (common == 1)
			return false;
		common = 2;
	}

	Point<DInt,Int> begPos = line->beg->pos;
	Point<DInt,Int> endPos = line->end->pos;
	Point<DInt,Int> w = arc->center - begPos;
	Point<DInt,Int> v = endPos - begPos;

	Int vMax = GS::Max (Abs (v.x), Abs (v.y));
	v = Point<DInt,Int> (Mul (v.x, DInt::maxCoordVal - DInt::minCoordVal) / vMax, Mul (v.y, DInt::maxCoordVal - DInt::minCoordVal) / vMax);

	Int vLen = v.Len ();
	Int f = v * w / vLen;
	Point<DInt,Int> proj (begPos.x + Mul (v.x, f) / vLen, begPos.y + Mul (v.y, f) / vLen);

	Point<DInt,Int> p[2];
	int numX = 0;

	DInt distSqr = (proj - arc->center).LenSqr ();
	if (distSqr >= Mul (arc->r + snapDist, arc->r + snapDist))
		return false;
	else {
		DInt kSqr = Mul (arc->r, arc->r) - distSqr;
		if (kSqr < Int (0)) {
			p[0] = proj;
			numX = 1;
		} else {
			Int k = Sqrt (kSqr);
			Point<DInt,Int> d (Mul (v.x, k) / vLen, Mul (v.y, k) / vLen);
			p[0] = proj + d;
			p[1] = proj - d;
			numX = 2;
		}
	}

	Point<DInt,Int> q[2];
	int k = 0;

	for (int i = 0; i < numX; i++) {
		if (common == 1 && Abs (p[i].x - begPos.x) < snapDist && Abs (p[i].y - begPos.y) < snapDist)
			continue;

		if (common == 2 && Abs (p[i].x - endPos.x) < snapDist && Abs (p[i].y - endPos.y) < snapDist)
			continue;

		if (p[i].x > line->bbox.maxX || p[i].x < line->bbox.minX || p[i].y > line->bbox.maxY || p[i].y < line->bbox.minY)
			continue;

		Point<DInt,Int> s = p[i] - arc->center;
		if (!IsCCW (s, arc->left, GetRelativePointQuarter (arc->right, s, arc->qr), arc->ql))
			continue;

		q[k++] = p[i];
	}

	if (k == 2 && Abs (q[0].x - q[1].x) < snapDist && Abs (q[0].y - q[1].y) < snapDist) {
		q[0] = (q[0] + q[1]) / 2;
		k = 1;
	}

	for (int i = 0; i < k; i++) {
		Node* node = NewNode ();
		node->pos = RoundToNodeGrid (q[i]);
		node->origVertex = -1;
		node->whichPoly = None;
		try { allNodes.Push (node); }
		catch (const GS::Exception&) { DeleteNode (node); throw; }

		NodeSnapToLineData snapData;
		snapData.node = node;
		if (Abs (begPos.x - endPos.x) < Abs (begPos.y - endPos.y))
			snapData.sortVal = Abs (q[i].y - begPos.y);
		else
			snapData.sortVal = Abs (q[i].x - begPos.x);
		snapNodes1.Push (snapData);

		NodeSnapToArcData snapArcData;
		snapArcData.node = node;
		snapArcData.p = q[i] - arc->center;
		snapArcData.qnode = GetRelativePointQuarter (arc->right, snapArcData.p, arc->qr);
		snapNodes2.Push (snapArcData);
	}

	return k > 0;
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::AddArcToArcIntersections (Arc* a1, Arc* a2, NodeSnapToArcDataArray& snapNodes1,
													NodeSnapToArcDataArray& snapNodes2)
{
	int common = 0;

	if (Abs (a1->center.x - a2->center.x) < snapDist4 && Abs (a1->center.y - a2->center.y) < snapDist4)
		return false;

	if (a1->beg == a2->beg || a1->beg == a2->end)
		common = 1;
	if (a1->end == a2->beg || a1->end == a2->end) {
		if (common == 1)
			return false;
		common = 2;
	}

	Point<DInt,Int> p[2];
	int numX = 0;
	DInt distSqr = (a1->center - a2->center).LenSqr ();
	Int dist = Sqrt (distSqr);

	Point<DInt,Int> cDir = a2->center - a1->center;
	Int cMax = GS::Max (Abs (cDir.x), Abs (cDir.y));
	cDir = Point<DInt,Int> (Mul (cDir.x, DInt::maxCoordVal - DInt::minCoordVal) / cMax,
							Mul (cDir.y, DInt::maxCoordVal - DInt::minCoordVal) / cMax);
	Int cDirLen = cDir.Len ();

	if (dist >= a1->r + a2->r + snapDist)
		return false;
	else if (a1->r >= dist + a2->r + snapDist)
		return false;
	else if (a2->r >= dist + a1->r + snapDist)
		return false;
	else {
		DInt a1rSqr = Mul (a1->r, a1->r);
		DInt s = a1rSqr - Mul (a2->r, a2->r) + distSqr;
		Int a = s / (dist * 2);

		p[0].x = a1->center.x + Mul (cDir.x, a) / cDirLen;
		p[0].y = a1->center.y + Mul (cDir.y, a) / cDirLen;

		DInt mSqr = a1rSqr - Mul (a, a);
		if (mSqr > Int (0)) {
			Int m = Sqrt (mSqr);
			Point<DInt,Int> mVect (Mul (cDir.y, m) / cDirLen, Mul (-cDir.x, m) / cDirLen);
			p[1] = p[0] + mVect;
			p[0] -= mVect;
			numX = 2;
		} else
			numX = 1;
	}

	Point<DInt,Int> q[2];
	int k = 0;

	for (int i = 0; i < numX; i++) {
		if (common == 1 && Abs (p[i].x - a1->beg->pos.x) < snapDist && Abs (p[i].y - a1->beg->pos.y) < snapDist)
			continue;

		if (common == 2 && Abs (p[i].x - a1->end->pos.x) < snapDist && Abs (p[i].y - a1->end->pos.y) < snapDist)
			continue;

		Point<DInt,Int> p1 = p[i] - a1->center;
		int qp1 = GetRelativePointQuarter (a1->right, p1, a1->qr);
		if (!IsCCW (p1, a1->left, qp1, a1->ql))
			continue;

		Point<DInt,Int> p2 = p[i] - a2->center;
		int qp2 = GetRelativePointQuarter (a2->right, p2, a2->qr);
		if (!IsCCW (p2, a2->left, qp2, a2->ql))
			continue;

		q[k++] = p[i];
	}

	if (k == 2 && Abs (q[0].x - q[1].x) < snapDist && Abs (q[0].y - q[1].y) < snapDist) {
		q[0] = (q[0] + q[1]) / 2;
		k = 1;
	}

	for (int i = 0; i < k; i++) {
		Node* node = NewNode ();
		node->pos = RoundToNodeGrid (q[i]);
		node->origVertex = -1;
		node->whichPoly = None;
		try { allNodes.Push (node); }
		catch (const GS::Exception&) { DeleteNode (node); throw; }

		NodeSnapToArcData snapData;
		snapData.node = node;
		snapData.p = q[i] - a1->center;
		snapData.qnode = GetRelativePointQuarter (a1->right, snapData.p, a1->qr);
		snapNodes1.Push (snapData);

		snapData.p = q[i] - a2->center;
		snapData.qnode = GetRelativePointQuarter (a2->right, snapData.p, a2->qr);
		snapNodes2.Push (snapData);
	}

	return k > 0;
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::CreateLinkIntersections ()
{
	GS::HashTable<Line*, NodeSnapToLineDataArray> insertLineNodes;
	GS::HashTable<Arc*, NodeSnapToArcDataArray> insertArcNodes;
	NodeSnapToLineDataArray localLineSnapNodes1, localLineSnapNodes2;
	NodeSnapToArcDataArray localArcSnapNodes1, localArcSnapNodes2;

	const Int32 linksNum = allLinks.GetSize ();

	if (!pgBoolean->containsArc && linksNum < 12) {
		for (Int32 i = 0; i < linksNum; i++) {
			Link* iLink = allLinks[i];
			BoundBox<Int> bb;
			bb.minX = iLink->bbox.minX - snapDist;
			bb.minY = iLink->bbox.minY - snapDist;
			bb.maxX = iLink->bbox.maxX + snapDist;
			bb.maxY = iLink->bbox.maxY + snapDist;
			for (Int32 j = i + 1; j < linksNum; j++) {
				Link* jLink = allLinks[j];
				if (jLink->bbox.maxX > bb.minX && jLink->bbox.minX < bb.maxX && jLink->bbox.maxY > bb.minY && jLink->bbox.minY < bb.maxY &&
					iLink->beg != jLink->beg && iLink->beg != jLink->end && iLink->end != jLink->beg && iLink->end != jLink->end)
				{
					Line* l1 = (Line*) iLink;
					NodeSnapToLineDataArray* snapNodes1;
					localLineSnapNodes1.Clear ();
					if (!insertLineNodes.Get (l1, &snapNodes1))
						snapNodes1 = &localLineSnapNodes1;

					Line* l2 = (Line*) jLink;
					NodeSnapToLineDataArray* snapNodes2;
					localLineSnapNodes2.Clear ();
					if (!insertLineNodes.Get (l2, &snapNodes2))
						snapNodes2 = &localLineSnapNodes2;

					AddLineToLineIntersection (l1, l2, *snapNodes1, *snapNodes2);

					if (!localLineSnapNodes2.IsEmpty ())
						insertLineNodes.Add (l2, localLineSnapNodes2);

					if (!localLineSnapNodes1.IsEmpty ())
						insertLineNodes.Add (l1, localLineSnapNodes1);
				}
			}
		}
	} else {
		if (pgBoolean->containsArc) {
			for (ULong i = 0; i < allNodes.GetSize (); i++) {
				if (breaker != nullptr && breaker->ShouldAbort ())
					throw GS::AbortException ();
				const Node* iNode = allNodes[i];
				for (ULong j = 0; j < iNode->links.GetSize (); j++) {
					if (!iNode->links[j]->isLine) {
						const Arc* jArc = (const Arc*) iNode->links[j];
						for (ULong k = j + 1; k < iNode->links.GetSize (); k++) {
							if (!iNode->links[k]->isLine) {
								Arc* kArc = (Arc*) iNode->links[k];
								if ((jArc->beg == kArc->beg && jArc->end == kArc->end && jArc->positiv == kArc->positiv) ||
									(jArc->beg == kArc->end && jArc->end == kArc->beg && jArc->positiv != kArc->positiv))
								{
									Point<DInt,Int> vj = jArc->end->pos - jArc->beg->pos;
									DInt lenSqr = (vj / 2).LenSqr ();
									DInt djSqr = Mul (jArc->r, jArc->r) - lenSqr;
									Int dj = 0;
									if (djSqr > Int (0))
										dj = Sqrt (djSqr);
									if (((vj ^ (jArc->center - jArc->beg->pos)) > Int (0)) ^ jArc->positiv)
										dj = jArc->r + dj;
									else
										dj = jArc->r - dj;

									DInt dkSqr = Mul (kArc->r, kArc->r) - lenSqr;
									Int dk = 0;
									if (dkSqr > Int (0))
										dk = Sqrt (dkSqr);
									if (((vj ^ (kArc->center - jArc->beg->pos)) > Int (0)) ^ jArc->positiv)
										dk = kArc->r + dk;
									else
										dk = kArc->r - dk;

									if (Abs (dj - dk) < snapDist) {
										kArc->bbox = jArc->bbox;
										kArc->r = jArc->r;
										kArc->center = jArc->center;
										kArc->right = jArc->right;
										kArc->left = jArc->left;
										kArc->qr = jArc->qr;
										kArc->ql = jArc->ql;
										linksSorted = false;
									}
								}
							}
						}
					}
				}
			}
		}

		if (!linksSorted) {
			qsort ((Link**) allLinks.GetContent (), allLinks.GetSize (), sizeof (Link*), CompareLinks);
			linksSorted = true;
		}

		const int statAlloc = sizeof (linkPtrArr) / sizeof (linkPtrArr[0]);
		typedef Link* LinkPtr;
		Link** currLinksArray;

		if (linksNum <= statAlloc)
			currLinksArray = linkPtrArr;
		else
			currLinksArray = new LinkPtr[linksNum];

		Int32 firstLinkIndex = 0;
		Int32 lastLinkIndex = -1;

		try {
			for (Int32 i = 0; i < linksNum; i++) {
				if (breaker != nullptr && breaker->ShouldAbort ())
					throw GS::AbortException ();

				while (firstLinkIndex <= lastLinkIndex && currLinksArray[firstLinkIndex]->bbox.maxX + snapDist <= allLinks[i]->bbox.minX)
					firstLinkIndex++;

				Int32 j;
				for (j = firstLinkIndex; j <= lastLinkIndex; j++) {
					if (allLinks[i]->isLine && currLinksArray[j]->isLine &&
						(allLinks[i]->beg == currLinksArray[j]->beg || allLinks[i]->beg == currLinksArray[j]->end ||
						allLinks[i]->end == currLinksArray[j]->beg || allLinks[i]->end == currLinksArray[j]->end))
						continue;

					if (allLinks[i]->bbox.minY < currLinksArray[j]->bbox.maxY + snapDist &&
						allLinks[i]->bbox.maxY > currLinksArray[j]->bbox.minY - snapDist)
					{
						if (allLinks[i]->isLine) {
							Line* l1 = (Line*) allLinks[i];
							NodeSnapToLineDataArray* snapNodes1;
							localLineSnapNodes1.Clear ();
							if (!insertLineNodes.Get (l1, &snapNodes1))
								snapNodes1 = &localLineSnapNodes1;

							if (currLinksArray[j]->isLine) {
								Line* l2 = (Line*) currLinksArray[j];
								NodeSnapToLineDataArray* snapNodes2;
								localLineSnapNodes2.Clear ();
								if (!insertLineNodes.Get (l2, &snapNodes2))
									snapNodes2 = &localLineSnapNodes2;

								AddLineToLineIntersection (l1, l2, *snapNodes1, *snapNodes2);

								if (!localLineSnapNodes2.IsEmpty ())
									insertLineNodes.Add (l2, localLineSnapNodes2);
							} else {
								Arc* a2 = (Arc*) currLinksArray[j];
								NodeSnapToArcDataArray* snapNodes2;
								localArcSnapNodes2.Clear ();
								if (!insertArcNodes.Get (a2, &snapNodes2))
									snapNodes2 = &localArcSnapNodes2;

								AddLineToArcIntersections (l1, a2, *snapNodes1, *snapNodes2);

								if (!localArcSnapNodes2.IsEmpty ())
									insertArcNodes.Add (a2, localArcSnapNodes2);
							}

							if (!localLineSnapNodes1.IsEmpty ())
								insertLineNodes.Add (l1, localLineSnapNodes1);
						} else {
							Arc* a1 = (Arc*) allLinks[i];
							NodeSnapToArcDataArray* snapNodes1;
							localArcSnapNodes1.Clear ();
							if (!insertArcNodes.Get (a1, &snapNodes1))
								snapNodes1 = &localArcSnapNodes1;

							if (currLinksArray[j]->isLine) {
								Line* l2 = (Line*) currLinksArray[j];
								NodeSnapToLineDataArray* snapNodes2;
								localLineSnapNodes2.Clear ();
								if (!insertLineNodes.Get (l2, &snapNodes2))
									snapNodes2 = &localLineSnapNodes2;

								AddLineToArcIntersections (l2, a1, *snapNodes2, *snapNodes1);

								if (!localLineSnapNodes2.IsEmpty ())
									insertLineNodes.Add (l2, localLineSnapNodes2);
							} else {
								Arc* a2 = (Arc*) currLinksArray[j];
								NodeSnapToArcDataArray* snapNodes2;
								localArcSnapNodes2.Clear ();
								if (!insertArcNodes.Get (a2, &snapNodes2))
									snapNodes2 = &localArcSnapNodes2;

								AddArcToArcIntersections (a1, a2, *snapNodes1, *snapNodes2);

								if (!localArcSnapNodes2.IsEmpty ())
									insertArcNodes.Add (a2, localArcSnapNodes2);
							}

							if (!localArcSnapNodes1.IsEmpty ())
								insertArcNodes.Add (a1, localArcSnapNodes1);
						}
					}
				}

				for (j = lastLinkIndex; j >= firstLinkIndex; j--) {
					if (allLinks[i]->bbox.maxX >= currLinksArray[j]->bbox.maxX)
						break;
					currLinksArray[j + 1] = currLinksArray[j];
				}
				currLinksArray[j + 1] = allLinks[i];
				lastLinkIndex++;
			}

			if (linksNum > statAlloc)
				delete [] currLinksArray;
			currLinksArray = nullptr;
		}
		catch (const GS::Exception&)
		{
			if (linksNum > statAlloc && currLinksArray != nullptr)
				delete [] currLinksArray;
			throw;
		}
	}

	{
		typename GS::HashTable<Line*, NodeSnapToLineDataArray>::PairIterator iter = insertLineNodes.EnumeratePairs ();
		while (iter != nullptr) {
			InsertNodesToLine (*iter->key, *iter->value);
			++iter;
		}
	}

	{
		typename GS::HashTable<Arc*, NodeSnapToArcDataArray>::PairIterator iter = insertArcNodes.EnumeratePairs ();
		while (iter != nullptr) {
			InsertNodesToArc (*iter->key, *iter->value);
			++iter;
		}
	}

	if (!insertLineNodes.IsEmpty () || !insertArcNodes.IsEmpty ()) {
		nodesSorted = linksSorted = false;
		return true;
	} else
		return false;
}

}

#endif
