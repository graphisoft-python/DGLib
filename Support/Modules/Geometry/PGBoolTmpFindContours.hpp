// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLTMPFINDCONTOURS_H
#define PGBOOLTMPFINDCONTOURS_H

namespace PolygonBoolean {

template<class DInt, class Int, class PolygonSelector>
CmpResult PGBoolTmp<DInt,Int,PolygonSelector>::SortLinksOfNode (const void* p1, const void* p2)
{
	const Link* l1 = *(const Link**) p1;
	const Link* l2 = *(const Link**) p2;
	PGBoolTmp<DInt,Int,PolygonSelector>* pgBoolTmp = l1->pgBoolTmp;
	Node* node = pgBoolTmp->sortLinksOfThisNode;

	Point<DInt,Int> e1 = l1->beg == node ? l1->end->pos : l1->beg->pos;
	Point<DInt,Int> e2 = l2->beg == node ? l2->end->pos : l2->beg->pos;

	if (pgBoolTmp->IsCoincedentLinks (*l1, *l2)) {
		if (l1->beg == node && l2->end == node)
			return -1;
		if (l1->end == node && l2->beg == node)
			return 1;
		if (l1->beg == node)
			return l1 < l2 ? -1 : (l1 == l2 ? 0 : 1);
		return l1 > l2 ? -1 : (l1 == l2 ? 0 : 1);
	}

	bool ccw;
	bool fromBelow[2];

	if (e1 == e2) {
		Arc* a1 = nullptr;
		Arc* a2 = nullptr;
		enum { Right, Center, Left } pl1, pl2;

		if (l1->isLine)
			pl1 = Center;
		else {
			a1 = (Arc*) l1;
			if ((a1->beg == node) ^ a1->positiv)
				pl1 = Left;
			else
				pl1 = Right;
		}

		if (l2->isLine)
			pl2 = Center;
		else {
			a2 = (Arc*) l2;
			if ((a2->beg == node) ^ a2->positiv)
				pl2 = Left;
			else
				pl2 = Right;
		}

		if (pl1 == pl2) {
			if (pl1 != Center) {
				Point<DInt,Int> d = Point<DInt,Int> (node->pos.y - e1.y, e1.x - node->pos.x);
				ccw = (a1->center - node->pos) * d < (a2->center - node->pos) * d;
			} else
				ccw = true;
		} else if (pl1 == Right)
			ccw = true;
		else if (pl1 == Left)
			ccw = false;
		else
			ccw = pl2 == Left;

		if (!l1->isLine && a1->bbox.minX < node->pos.x && pgBoolTmp->ReturnInfiniteLineCrossings (a1, node, fromBelow) == 1)
			ccw = !ccw;
		if (!l2->isLine && a2->bbox.minX < node->pos.x && pgBoolTmp->ReturnInfiniteLineCrossings (a2, node, fromBelow) == 1)
			ccw = !ccw;
	} else {
		Point<DInt,Int> dir1, dir2;
		int q1, q2;

		dir1 = e1 - node->pos;
		dir2 = e2 - node->pos;

		if (dir1.y == 0 && dir1.x < 0)
			q1 = 5;
		else {
			q1 = pgBoolTmp->GetPointQuarter (dir1);
			if (q1 < 2)
				q1 += 4;
		}

		if (dir2.y == 0 && dir2.x < 0)
			q2 = 5;
		else {
			q2 = pgBoolTmp->GetPointQuarter (dir2);
			if (q2 < 2)
				q2 += 4;
		}

		bool crossProdCalced = false;
		DInt crossProd;
		if (q2 > q1)
			ccw = true;
		else if (q2 < q1)
			ccw = false;
		else {
			crossProd = dir1 ^ dir2;
			crossProdCalced = true;
			ccw = crossProd > Int (0);
		}

		if (!l1->isLine) {
			Arc* a1 = (Arc*) l1;

			if (a1->bbox.minX < node->pos.x && pgBoolTmp->ReturnInfiniteLineCrossings (a1, node, fromBelow) == 1)
				ccw = !ccw;

			if (!crossProdCalced) {
				crossProd = dir1 ^ dir2;
				crossProdCalced = true;
			}
			if ((crossProd > Int (0)) ^ (a1->end == node) ^ a1->positiv)
				if ((e2 - a1->center).LenSqr () < Mul (a1->r, a1->r))
					ccw = !ccw;
		}

		if (!l2->isLine) {
			Arc* a2 = (Arc*) l2;

			if (a2->bbox.minX < node->pos.x && pgBoolTmp->ReturnInfiniteLineCrossings (a2, node, fromBelow) == 1)
				ccw = !ccw;

			if (!crossProdCalced) {
				crossProd = dir1 ^ dir2;
			}
			if ((crossProd > Int (0)) ^ (a2->beg == node) ^ a2->positiv)
				if ((e1 - a2->center).LenSqr () < Mul (a2->r, a2->r))
					ccw = !ccw;
		}
	}

	return ccw ? -1 : 1;
}


template<class DInt, class Int, class PolygonSelector>
int PGBoolTmp<DInt,Int,PolygonSelector>::ReturnInfiniteLineCrossings (Link* link, Node* node, bool* fromBelow)
{
	int n = 0;

	if (link->isLine) {
		if (link->bbox.minY >= node->pos.y || link->bbox.maxY < node->pos.y)
			return n;

		const Point<DInt,Int>& beg = link->beg->pos;
		const Point<DInt,Int>& end = link->end->pos;
		DInt x = Mul (beg.x, end.y - beg.y) + Mul (end.x - beg.x, node->pos.y - beg.y);
		if (beg.y < end.y) {
			if (x < Mul (node->pos.x, end.y - beg.y))
				fromBelow[n++] = true;
		} else {
			if (x > Mul (node->pos.x, end.y - beg.y))
				fromBelow[n++] = false;
		}
	} else {
		if (link->bbox.minY > node->pos.y + DInt::nodeGridRound || link->bbox.maxY < node->pos.y - DInt::nodeGridRound)
			return n;

		Arc* arc = (Arc*) link;
		Int centerDist = node->pos.y - arc->center.y;
		if (arc->beg->pos.y == node->pos.y) {
			if (arc->end->pos.y == node->pos.y) {
				if ((arc->beg->pos.x > arc->end->pos.x) ^ arc->positiv) {
					if (arc->beg->pos.x < node->pos.x)
						fromBelow[n++] = false;
					if (arc->end->pos.x < node->pos.x)
						fromBelow[n++] = true;
				}
			} else {
				if (arc->center.x == arc->beg->pos.x) {
					if (arc->beg->pos.x < node->pos.x && centerDist > 0)
						fromBelow[n++] = false;
				} else {
					if (arc->beg->pos.x < node->pos.x && ((arc->center.x < arc->beg->pos.x) ^ arc->positiv))
						fromBelow[n++] = false;
					Point<DInt,Int> p (arc->center.x - arc->beg->pos.x, centerDist);
					if (p.x + arc->center.x < node->pos.x) {
						if (!(arc->beg == node && p.x + arc->center.x + snapDist > node->pos.x)) {
							int qp = GetRelativePointQuarter (arc->right, p, arc->qr);
							if (IsCCW (p, arc->left, qp, arc->ql))
								fromBelow[n++] = (arc->center.x < arc->beg->pos.x) ^ arc->positiv;
						}
					}
				}
			}
		} else if (arc->end->pos.y == node->pos.y) {
			if (arc->center.x == arc->end->pos.x) {
				if (arc->end->pos.x < node->pos.x && centerDist > 0)
					fromBelow[n++] = true;
			} else {
				if (arc->end->pos.x < node->pos.x && ((arc->center.x > arc->end->pos.x) ^ arc->positiv))
					fromBelow[n++] = true;
				Point<DInt,Int> p (arc->center.x - arc->end->pos.x, centerDist);
				if (p.x + arc->center.x < node->pos.x) {
					if (!(arc->end == node && p.x + arc->center.x + snapDist > node->pos.x)) {
						int qp = GetRelativePointQuarter (arc->right, p, arc->qr);
						if (IsCCW (p, arc->left, qp, arc->ql))
							fromBelow[n++] = (arc->center.x < arc->end->pos.x) ^ arc->positiv;
					}
				}
			}
		} else {
			DInt dSqr = Mul (arc->r, arc->r) - Mul (centerDist, centerDist);
			if (dSqr > Int (0)) {
				Int d = Sqrt (dSqr);
				if (arc->center.x - d < node->pos.x) {
					Point<DInt,Int> p (-d, centerDist);
					int qp = GetRelativePointQuarter (arc->right, p, arc->qr);
					if (IsCCW (p, arc->left, qp, arc->ql))
						fromBelow[n++] = !arc->positiv;
					if (arc->center.x + d < node->pos.x) {
						Point<DInt,Int> p (d, centerDist);
						int qp = GetRelativePointQuarter (arc->right, p, arc->qr);
						if (IsCCW (p, arc->left, qp, arc->ql))
							fromBelow[n++] = arc->positiv;
					}
				}
			}
		}
	}

	return n;
}


template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::CalcOverlapAsPassingLink (PolygonSelector& polygonSelector, bool passingLeftToRight, WhichPoly whichPoly)
{	
	if (whichPoly < origPolys.GetSize ()) {
		Int32 overlap = polygonSelector.GetPolyOverlap (whichPoly);
		if (passingLeftToRight) {
			--overlap;
		} else {
			++overlap;
		}
		polygonSelector.SetPolyOverlap (whichPoly, overlap);
	}	
}


template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::CalcOverlapAsPassingLinkOfNode (PolygonSelector& polygonSelector, Node* node, Int32 linkIndex)
{
	Link* link = node->links[linkIndex];

	WhichPoly prevWhichPoly = polygonSelector.GetSelectedPoly ();		

	if (link->beg == node) {
		link->leftPoly	= prevWhichPoly;
	} else {
		link->rightPoly	= prevWhichPoly;
	}

	if (link->whichPoly < origPolys.GetSize ()) {
		CalcOverlapAsPassingLink (polygonSelector, link->beg == node, link->whichPoly);
	}	
	
	WhichPoly actWhichPoly = polygonSelector.GetSelectedPoly ();
	
	if (link->beg == node) {		
		link->rightPoly = actWhichPoly;
	} else {		
		link->leftPoly = actWhichPoly;
	}

}

template<class DInt, class Int, class PolygonSelector>
struct PGBoolTmp<DInt,Int,PolygonSelector>::NodeOverlapData {
	Node* node;
	Link* startLinkPtr;

	Int32 startLink;
	Int32 i;

	PGBoolTmp* pgBoolTmp;

	bool	first;

	Int32 firstA;
	Int32 firstB;
	Int32 prevA;
	Int32 prevB;

	bool touchesA, touchesB;


 #if defined (DEBUG_PGBOOL)
	PolygonSelector savedSelector; 	
 #endif
	//lint -save -e1401 [member symbol 'Symbol' (Location) not initialized by constructor]	
	NodeOverlapData () {} //don't initialize members (speed)
	//lint -restore

	void Init (Node* node, Link* startLinkPtr, PGBoolTmp* pgBoolTmp)
	{
		this->node = node;
		this->startLinkPtr = startLinkPtr;
		startLink = -1;
		i = -1;
		this->pgBoolTmp = pgBoolTmp;
		first = true;
		firstA = 0;
		firstB = 0;
		prevA = 0;
		prevB = 0;
		touchesA = false;
		touchesB = false;
	}

	GS_FORCE_INLINE void UpdateStatus (Int32 prevCountA, Int32 prevCountB, Int32 countA, Int32 countB)
	{
		if (pgBoolTmp->isPolyRegular != nullptr) {
			if (countA < 0 || countA > 1) {
				*pgBoolTmp->isPolyRegular = false;
			}
		}

		if (countA > 0) {
			pgBoolTmp->polyAHasZeroArea = false;
		}

		if (countB > 0) {
			pgBoolTmp->polyBHasZeroArea = false;
		}

		if (countA > 0 && countB <= 0) {
			pgBoolTmp->polyACovered = false;
		}

		if (countB > 0 && countA <= 0) {
			pgBoolTmp->polyBCovered = false;
		}

		if (countA > 0 && countB > 0) {
			pgBoolTmp->polysDisjoint = false;
		}

		const bool edgeTouchesA = (countA > 0) != (prevCountA > 0);
		const bool edgeTouchesB = (countB > 0) != (prevCountB > 0);

		if (edgeTouchesA && edgeTouchesB) {
			pgBoolTmp->edgeTouch = true;
		}

		touchesA |= edgeTouchesA;
		touchesB |= edgeTouchesB;

		if (touchesA && touchesB) {
			pgBoolTmp->nodeTouch = true;
		}
	}

	GS_FORCE_INLINE void SetABCount (const PolygonSelector& polygonSelector)
	{
		const Int32 countA = polygonSelector.GetPolyCount (0);
		const Int32 countB = polygonSelector.GetPolyCount (1);

		Int32 nextLinkIndex = i == 0 ? node->links.GetSize () - 1 : i - 1;

		bool isLast = (i == nextLinkIndex || !pgBoolTmp->IsCoincedentLinks (*node->links [i], *node->links [nextLinkIndex]));

		if (isLast) {
			if (first) {
				firstA = countA;
				firstB = countB;
				first = false;
			} else {
				UpdateStatus (prevA, prevB, countA, countB);
			}
			prevA = countA;
			prevB = countB;
		}

		if (!isLast && pgBoolTmp->isPolyRegular != nullptr) {
			*pgBoolTmp->isPolyRegular = false;
		}

		if (nextLinkIndex == startLink) {
			UpdateStatus (prevA, prevB, firstA, firstB);
		}
	}
};


template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::ProcessNode (Node* node)
{
	if (node->links.IsEmpty ()) {
		node->processed = true;
		return;
	}

	polygonSelector.Reset ();

	// iterative depth-first enumeration of nodes

	GS::ArrayFB<NodeOverlapData, 64> stack;
	UInt32 stackSize = 1;
	stack.SetSize (1);
	stack [0].Init (node, nullptr, this);	

	while (stackSize != 0) {
		NodeOverlapData& stackData = stack [stackSize - 1];

		Node* node = stackData.node;

		const Int32 linkNum = node->links.GetSize ();

		if (!stackData.node->processed) {
			stackData.node->processed = true;
			sortLinksOfThisNode = node;
			qsort ((Link**) node->links.GetContent (), node->links.GetSize (), sizeof (Link*), SortLinksOfNode);
			if (stackData.startLinkPtr != nullptr) {
				for (Int32 i = 0; i < linkNum; ++i) {
					if (node->links [i] == stackData.startLinkPtr) {
						stackData.startLink = i;
						break;
					}
				}
			} else {
				const Int32 allLinksNum = allLinks.GetSize ();
				for (Int32 i = 0; i < allLinksNum && allLinks[i]->bbox.minX < node->pos.x; i++) {					
					if (allLinks [i]->whichPoly < origPolys.GetSize ()) {
						bool fromBelow[2];
						Int32 n = ReturnInfiniteLineCrossings (allLinks[i], node, fromBelow);
						for (Int32 j = 0; j < n; j++) {
							CalcOverlapAsPassingLink (polygonSelector, fromBelow [j], allLinks [i]->whichPoly);					
						}
					}
				}
				stackData.startLink = linkNum - 1;
				CalcOverlapAsPassingLinkOfNode (polygonSelector, node, stackData.startLink);				
			}
			DBASSERT (stackData.startLink >= 0);

			stackData.i = stackData.startLink;
			stackData.SetABCount (polygonSelector);
			
			stackData.i = (stackData.startLink + linkNum - 1) % linkNum;
#if defined (DEBUG_PGBOOL)
 			stackData.savedSelector = pgBoolean->polygonSelector;
#endif
		}

		Node* otherNode = node->links [stackData.i]->beg == node ? node->links [stackData.i]->end : node->links [stackData.i]->beg;
		if (!otherNode->processed) {			
			if (stackSize == stack.GetSize ()) {
				stack.SetSize (stackSize + 1);
			}
			stack [stackSize].Init (otherNode, node->links [stack [stackSize - 1].i], this); // stackData ref might be invalid at this point because of SetSize
			++stackSize;
		} else {					
			if (stackData.i == stackData.startLink) {
				CalcOverlapAsPassingLink (polygonSelector, node->links [stackData.startLink]->beg == node, node->links [stackData.startLink]->whichPoly);
#if defined (DEBUG_PGBOOL)
 				DBASSERT (pgBoolean->polygonSelector == stackData.savedSelector);
#endif
				--stackSize;				
			} else {
				CalcOverlapAsPassingLinkOfNode (polygonSelector, node, stackData.i);
				stackData.SetABCount (polygonSelector);
				stackData.i = (stackData.i + linkNum - 1) % linkNum;
			}
		}
	}

}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::CalcLinkSideOverlaps ()
{
	const Int32 nodeNum = allNodes.GetSize ();

	if (!linksSorted) {
		qsort ((Link**) allLinks.GetContent (), allLinks.GetSize (), sizeof (Link*), CompareLinks);
		linksSorted = true;
	}
	

	polyACovered = true;
	polyBCovered = true;
	polysDisjoint = true;
	polyAHasZeroArea = true;
	polyBHasZeroArea = true;
	edgeTouch = false;
	nodeTouch = false;

	for (Int32 i = 0; i < nodeNum; ++i) {		
		if (!allNodes [i]->processed) {
			ProcessNode (allNodes [i]);
		}
	}
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::IsCoincedentLinks (const Link& l1, const Link&l2)
{
	if ((l1.beg == l2.beg && l1.end == l2.end) || (l1.beg == l2.end && l1.end == l2.beg)) {
		if (l1.isLine && l2.isLine)
			return true;
		else if (!l1.isLine && !l2.isLine) {
			if (((const Arc*) &l1)->center == ((const Arc*) &l2)->center)
				return (l1.beg == l2.beg) ^ (((const Arc*) &l1)->positiv != ((const Arc*) &l2)->positiv);
		}
	}

	return false;
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::ReverseLink (Link* link)
{
	if (!link->isLine)
		((Arc*)link)->positiv = !((Arc*)link)->positiv;
	Node* n = link->beg;
	link->beg = link->end;
	link->end = n;
}

template<class DInt, class Int, class PolygonSelector>
PGRelPolyPosExt PGBoolTmp<DInt,Int,PolygonSelector>::SelectGoodLinks ()
{


	Int32 linkNum = allLinks.GetSize ();
	for (Int32 i = 0; i < linkNum; i++) {
		if (breaker != nullptr && breaker->ShouldAbort ())
			throw GS::AbortException ();

		if (allLinks[i]->markForDelete || allLinks[i]->markForKeep)
			continue;

		Node* begNode = allLinks[i]->beg;
		Int32 nodeLinksNum = begNode->links.GetSize ();
		Int32 firstSameLink = 0, lastSameLink;
		while (!IsCoincedentLinks (*allLinks[i], *begNode->links[firstSameLink]))
			firstSameLink++;
		if (firstSameLink == 0) {
			firstSameLink = nodeLinksNum - 1;
			while (firstSameLink >= 0 && IsCoincedentLinks (*allLinks[i], *begNode->links[firstSameLink]))
				firstSameLink--;
			firstSameLink = (firstSameLink + 1) % nodeLinksNum;
			lastSameLink = 0;
		} else
			lastSameLink = firstSameLink;
		while ((lastSameLink + 1) % nodeLinksNum != firstSameLink &&
			IsCoincedentLinks (*allLinks[i], *begNode->links[(lastSameLink + 1) % nodeLinksNum]))
				lastSameLink++;
		
		lastSameLink = lastSameLink % nodeLinksNum;

		Link* lastLink = begNode->links[lastSameLink];
		Link* firstLink = begNode->links[firstSameLink];


		WhichPoly left	= lastLink->beg == begNode ? lastLink->leftPoly : lastLink->rightPoly;
		WhichPoly right = firstLink->beg == begNode ? firstLink->rightPoly : firstLink->leftPoly;

		if (lastSameLink < firstSameLink)
			lastSameLink += nodeLinksNum;
		if (left == right) {
			for (Int32 j = firstSameLink; j <= lastSameLink; j++)
				begNode->links[j % nodeLinksNum]->markForDelete = true;
			noChange = false;
		} else {
			WhichPoly primaryPoly = GS::Min (left, right);
			WhichPoly secondaryPoly = GS::Max (left, right);

			Int32 pFw = -1, pRev = -1, sFw = -1, sRev = -1, oFw = -1, oRev = -1;
			UInt32 oFwMin	= MaxUInt32;
			UInt32 oRevMin	= MaxUInt32;

			Int32 j;
			for (j = firstSameLink; j <= lastSameLink; j++) {
				Link* curr = begNode->links[j % nodeLinksNum];				
				if (curr->*(left == primaryPoly ? &Link::beg : &Link::end) == begNode) {
					if (curr->whichPoly == primaryPoly) {
						pFw = j;
					} else if (curr->whichPoly == secondaryPoly) {
						sFw = j;
					} else if (curr->whichPoly < oFwMin) {
						oFw = j;
						oFwMin = curr->whichPoly;
					}
				} else {
					if (curr->whichPoly == primaryPoly) {
						pRev = j;
					} else if (curr->whichPoly == secondaryPoly) {
						sRev = j;
					} else if (curr->whichPoly < oRevMin){
						oRev = j;
						oRevMin = curr->whichPoly;
					}
				}				
			}
			bool reverse = false;
			
			if (pFw >= 0) {
				j = pFw;
			} else if (sFw >= 0) {
				j = sFw;
			} else if (pRev >= 0) {
				j = pRev;
				reverse = true;
			} else if (sRev >= 0) {
				j = sRev;
				reverse = true;
			} else if (oFw >= 0) {
				j = oFw;
			} else {
				DBASSERT(oRev >= 0);
				j = oRev;
				reverse = true;
			}			

			if (reverse) {
				ReverseLink (begNode->links[j % nodeLinksNum]);
			}

			if (sRev >= 0 && j != sRev) {
				begNode->links[j % nodeLinksNum]->origRightEdge = begNode->links[sRev % nodeLinksNum]->origEdge;
			}

			for (Int32 k = firstSameLink; k <= lastSameLink; k++) {
				if (k == j) {
					Int32 ind = (k % nodeLinksNum);
					begNode->links[ind]->markForKeep = true;
					begNode->links[ind]->leftPoly = primaryPoly;
					begNode->links[ind]->rightPoly = secondaryPoly;
				} else {
					begNode->links[k % nodeLinksNum]->markForDelete = true;
					noChange = false;
				}
			}
		}
	}

	if (polyAHasZeroArea)
		return Poly1HasZeroArea;
	if (polyBHasZeroArea)
		return Poly2HasZeroArea;
	if (polysDisjoint) {
		if (edgeTouch)
			return PolysDisjunct_Edge;
		if (nodeTouch)
			return PolysDisjunct_Node;
		return PolysDisjunct;
	}
	if (polyBCovered && polyACovered)
		return PolysEqual;
	if (polyBCovered && (pgBoolean->polyPosition || (!edgeTouch && !nodeTouch)))
		return Poly1CoversPoly2;
	if (polyACovered && (pgBoolean->polyPosition || (!edgeTouch && !nodeTouch)))
		return Poly2CoversPoly1;
	return PolysOverlap;
}

template<class DInt, class Int, class PolygonSelector>
PGPositionExt PGBoolTmp<DInt,Int,PolygonSelector>::ReturnGoodSegments (const CircleArc* arc, ResultSegmentPos::Et pos,
													   PGRESSECTOREXT* newSectors, GS::Array<CircleArc>* newArcs)
{
	bool inside = false;
	bool outside = false;
	bool on = false;

	Int32 linkNum = allLinks.GetSize ();
	for (Int32 i = 0; i < linkNum; i++) {
		if (allLinks[i]->whichPoly != SoloSegment)
			continue;

		Node* begNode = allLinks[i]->beg;
		Int32 nodeLinksNum = begNode->links.GetSize ();
		Int32 firstSameLink = 0, lastSameLink;
		while (!IsCoincedentLinks (*allLinks[i], *begNode->links[firstSameLink]))
			firstSameLink++;
		if (firstSameLink == 0) {
			firstSameLink = nodeLinksNum - 1;
			while (firstSameLink >= 0 && IsCoincedentLinks (*allLinks[i], *begNode->links[firstSameLink]))
				firstSameLink--;
			firstSameLink = (firstSameLink + 1) % nodeLinksNum;
			lastSameLink = 0;
		} else
			lastSameLink = firstSameLink;
		while ((lastSameLink + 1) % nodeLinksNum != firstSameLink &&
			IsCoincedentLinks (*allLinks[i], *begNode->links[(lastSameLink + 1) % nodeLinksNum]))
				lastSameLink++;
		lastSameLink = lastSameLink % nodeLinksNum;

		bool left, right;

		Link* lastLink = begNode->links[lastSameLink];
		Link* firstLink = begNode->links[firstSameLink];
		if (lastLink->beg == begNode) {
			left = (lastLink->leftPoly != None);
		} else {
			left = (lastLink->rightPoly != None);
		}
		if (firstLink->beg == begNode) {
			right = (firstLink->rightPoly != None);
		} else {
			right = (firstLink->leftPoly != None);
		}

		if (left != right)
			on = true;
		else if (left && right)
			inside = true;
		else
			outside = true;

		if ((left != right && (pos & ResultSegmentPos::OnEdge)) ||
			(left && right && (pos & ResultSegmentPos::Inside)) ||
			(!left && !right && (pos & ResultSegmentPos::Outside)))
		{
			if (newSectors != nullptr) {
				Sector s;
				s.c1 = PointToCoord (allLinks[i]->beg->pos);
				s.c2 = PointToCoord (allLinks[i]->end->pos);
				if (Geometry::DistSqr (s.c1, s.c2) > Eps * Eps) {
					if (newSectors->newSector == nullptr)
						((GS::VAArray<Sector>*) newSectors->sectorsData)->Push (s);
					else
						newSectors->newSector (newSectors, s);
				}
			} else if (newArcs != nullptr) {
				CircleArc ca;
				ca.begC = PointToCoord (allLinks[i]->beg->pos);
				ca.endC = PointToCoord (allLinks[i]->end->pos);
				if (!((Arc*)allLinks[i])->positiv)
					GS::Swap (ca.begC, ca.endC);
				ca.origo = arc->origo;
				newArcs->Push (ca);
			}
		}
	}

	return inside && !outside && !on ? PGInsidePoly : !inside && outside && !on ? PGOutsidePoly : PGOnPolyEdge;
}

template<class DInt, class Int, class PolygonSelector>
bool PGBoolTmp<DInt,Int,PolygonSelector>::IsNodeInsideContour (Node* node, const Contour& contour)
{
	if (node->pos.x < contour.bbox.minX || 
		contour.bbox.maxX < node->pos.x || 
		node->pos.y < contour.bbox.minY || 
		contour.bbox.maxY < node->pos.y)
	{
		return false;
	}

	Link* link = contour.startLink;
	Int32 crossCount = 0;

	do {		
		if (link->beg == node || link->end == node)
			return false;

		bool fromBelow[2];
		if (link->bbox.minX < node->pos.x)
			crossCount += ReturnInfiniteLineCrossings (link, node, fromBelow);

		link = GetContourNextLink (link, contour);
	} while (link != contour.startLink);

	return (crossCount & 1) == 1;
}

template<class DInt, class Int, class PolygonSelector>
DInt PGBoolTmp<DInt,Int,PolygonSelector>::GetLinkSweepArea2 (Link* link)
{
	DInt area2;

	area2 = link->beg->pos ^ link->end->pos;
	if (!link->isLine) {
		Arc* arc = (Arc*) link;
		DInt crossProd = arc->right ^ arc->left;
		DInt add = -crossProd;

		double angle = arc->r > 0 ? atan2 (double (crossProd / arc->r), double ((arc->right * arc->left) / arc->r)) : 0;
		if (angle < 0)
			angle += 2 * PI;

		Int alpha = Int (angle * DInt::angleCalcPrecision);

		add += Mul (Mul (alpha, arc->r) / DInt::angleCalcPrecision, arc->r);
		area2 += arc->positiv ? add : -add;
	}

	return area2;
}

template<class DInt, class Int, class PolygonSelector>
DInt PGBoolTmp<DInt,Int,PolygonSelector>::GetLinkSweepArea2 (Link* link, WhichPoly whichPoly)
{
	DInt area2 = GetLinkSweepArea2 (link);

	if (whichPoly == link->rightPoly) {
		area2 = -area2;
	}
#if defined (DEBUVERS)
	else {
		DBASSERT (whichPoly == link->leftPoly);
	}
#endif

	return area2;
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::CollectContours (Contour* insideOf, Int32 startLinkIndex)
{
	Int32 linkNum = allLinks.GetSize ();

	WhichPoly outsidePoly = None;

	if (insideOf == nullptr) {
		polygonSelector.Reset ();
		outsidePoly = polygonSelector.GetSelectedPoly ();
	}

	for (Int32 i = startLinkIndex; i < linkNum; i++) {
		if (insideOf != nullptr && allLinks[i]->bbox.minX > insideOf->bbox.maxX)
			return;

		for (UInt32 polySide = 0; polySide < 2; ++polySide)
		{
			if (!allLinks [i]->markForKeep) {
				break;
			}

			WhichPoly  whichPoly;
			if (polySide == 0) {
				if (allLinks [i]->leftContourId > 0) {
					continue;
				}
				whichPoly = allLinks [i]->leftPoly;
			} else {
				if (allLinks [i]->rightContourId > 0) {
					continue;
				}
				whichPoly = allLinks [i]->rightPoly;
			}

			if (whichPoly >= origPolys.GetSize ()) {
				continue;
			}

			if (insideOf != nullptr && whichPoly != insideOf->whichPoly) {
				continue;
			}

			if (insideOf == nullptr || IsNodeInsideContour (allLinks[i]->beg, *insideOf))
			{
				Link* startLink = allLinks[i];
				if (withoutHoles) {
					if (startLink->bbox.minX == startLink->beg->pos.x || startLink->bbox.minX == startLink->end->pos.x) {
						Node* startNode = startLink->bbox.minX == startLink->beg->pos.x ? startLink->beg : startLink->end;
						for (ULong j = 0; j < startNode->links.GetSize (); j++) {
							if (startNode->links[j]->markForKeep && 
								(startNode->links [j]->leftPoly == whichPoly && startNode->links [j]->leftContourId == 0 ||
								 startNode->links [j]->rightPoly == whichPoly && startNode->links [j]->rightContourId == 0))
							{
								startLink = startNode->links[j];
								break;
							}
						}
					}
				}

				numContours++;

				Contour contour;
				contour.whichPoly = whichPoly;
				contour.contourId = numContours;
				contour.numVertex = 0;
				contour.numArc = 0;
				contour.startLink = startLink;
				contour.bbox = startLink->bbox;
				contour.area2 = Int (0);

				contour.positiv = (insideOf == nullptr && whichPoly != outsidePoly) || (insideOf != nullptr && !insideOf->positiv);

				bool contourStartLinkAgain = false;
				bool hasInvalidLink = false;
				Link* link = startLink;
				do {
					Link* nextLink = GetContourNextLink (link, contour);
					if (link == nextLink) {
						hasInvalidLink = true;
						break;
					}
					if (!pgBoolean->isSameDirEdgeLegal && (link->leftPoly == whichPoly ? link->rightContourId: link->leftContourId) == 0) {
						Link* prevLink = GetContourPrevLink (link, contour);

						Int32 infCycleWatch = 0;
						Point<DInt,Int>& beg = link->leftPoly == whichPoly ? link->beg->pos : link->end->pos;
						const PGEDGEEXT* linkOrigEdge = nullptr;
						if (!polyEdges.IsEmpty ())
							linkOrigEdge = &polyEdges [polyEdgeOffsets [link->whichPoly] + link->origEdge];						

						Link* prevNextLink = nullptr;
						for (;;) {
							if (link->isLine != nextLink->isLine)
								break;
							if (nextLink == prevLink)
								break;

							ULong keptLinksNum = 0;

							if (nextLink->leftPoly == whichPoly) {
								for (ULong j = 0; j < nextLink->beg->links.GetSize (); j++) {
									if (nextLink->beg->links[j]->markForKeep) {
										keptLinksNum++;
									}
								}
							} else {
								for (ULong j = 0; j < nextLink->end->links.GetSize (); j++) {
									if (nextLink->end->links[j]->markForKeep) {
										keptLinksNum++;
									}
								}
							}

							if (keptLinksNum > 2) {
								break;
							}

							if (DBERROR (link->leftPoly != nextLink->leftPoly || link->rightPoly != nextLink->rightPoly)) {
								break;
							}

							if ((nextLink->leftPoly == whichPoly ? nextLink->rightContourId : nextLink->leftContourId) != 0) {
								break;
							}

							if (link->isLine) {
								if (!polyEdges.IsEmpty ()) {
									const PGEDGEEXT* nextLinkOrigEdge = &polyEdges [polyEdgeOffsets [nextLink->whichPoly] + nextLink->origEdge];									
									if (linkOrigEdge->status.isInvisible != nextLinkOrigEdge->status.isInvisible ||
										linkOrigEdge->status.isSplitLine != nextLinkOrigEdge->status.isSplitLine)
										break;
								}

								Point<DInt,Int> relEnd = (nextLink->leftPoly == whichPoly ? nextLink->end->pos : nextLink->beg->pos) - beg;
								Link* lk = link;
								for (; lk != nextLink; lk = GetContourNextLink (lk, contour)) {
									Point<DInt,Int> p = lk->end->pos - beg;

									if (p.x <= GS::Min (relEnd.x, Int (0)) - snapDist4 || p.x >= GS::Max (relEnd.x, Int (0)) + snapDist4 ||
										p.y <= GS::Min (relEnd.y, Int (0)) - snapDist4 || p.y >= GS::Max (relEnd.y, Int (0)) + snapDist4)
										break;

									Int arx = Abs (relEnd.x);
									Int ary = Abs (relEnd.y);
									if (arx < ary) {
										DInt a = Mul (p.x, ary);
										a += relEnd.y > 0 ? -Mul (relEnd.x, p.y) : Mul (relEnd.x, p.y);
										if (Abs (a) >= Mul (snapDist4, ary))
											break;
									} else {
										DInt a = Mul (p.y, arx);
										a += relEnd.x > 0 ? -Mul (relEnd.y, p.x) : Mul (relEnd.y, p.x);
										if (Abs (a) >= Mul (snapDist4, arx))
											break;
									}
								}

								if (lk != nextLink)
									break;

							} else if (link->whichPoly != nextLink->whichPoly || link->origEdge != nextLink->origEdge) {
								break;
							}

							prevNextLink = nextLink;
							nextLink = GetContourNextLink (nextLink, contour);

							if (prevNextLink == startLink) {
								contourStartLinkAgain = true;
								contour.numVertex--;
								contour.startLink = link;
								contour.area2 -= GetLinkSweepArea2 (startLink, whichPoly);
								startLink = link;
								break;
							}

							if (++infCycleWatch > linkNum) {
								throw GeometryAlgorithmErrorException ("Infinite Cycle", __FILE__, __LINE__);
							}
						}

						if (prevNextLink != nullptr) {
							noChange = false;
							for (Link* lk = GetContourNextLink (link, contour); lk != nextLink; lk = GetContourNextLink (lk, contour)) {
								lk->markForDelete	= true;
								lk->markForKeep		= false;
							}

							if (nextLink->leftPoly == whichPoly) {
								for (ULong j = 0; j < nextLink->beg->links.GetSize (); j++) {
									if (nextLink->beg->links[j] == prevNextLink) {
										nextLink->beg->links[j] = link;
										break;
									}
								}
								DBASSERT (link->leftPoly == whichPoly);
								link->end = nextLink->beg;
							} else {
								DBASSERT (nextLink->rightPoly == whichPoly);
								for (ULong j = 0; j < nextLink->end->links.GetSize (); j++) {
									if (nextLink->end->links[j] == prevNextLink) {
										nextLink->end->links[j] = link;
										break;
									}
								}
								DBASSERT (link->rightPoly == whichPoly);
								link->beg = nextLink->end;
							}
							FillLineStruct ((Line*) link);
						}
					}

					if (link->leftPoly == whichPoly) {
						link->leftContourId = numContours;
					} else {
						DBASSERT (link->rightPoly == whichPoly);
						link->rightContourId = numContours;
					}

					contour.numVertex++;
					if (contour.numVertex > linkNum)
						throw GeometryAlgorithmErrorException ("Infinite Cycle", __FILE__, __LINE__);
					if (!link->isLine)
						contour.numArc++;
					contour.bbox.minX = GS::Min (contour.bbox.minX, link->bbox.minX);
					contour.bbox.maxX = GS::Max (contour.bbox.maxX, link->bbox.maxX);
					contour.bbox.minY = GS::Min (contour.bbox.minY, link->bbox.minY);
					contour.bbox.maxY = GS::Max (contour.bbox.maxY, link->bbox.maxY);
					contour.area2 += GetLinkSweepArea2 (link, whichPoly);
					link = nextLink;
				} while (link != startLink && !contourStartLinkAgain);

				if (hasInvalidLink) {
					numContours--;
					continue;
				}

				DBASSERT (Abs (contour.area2) <= area2Minimum || contour.positiv == contour.area2 > Int (0));

				CollectContours (&contour, i);

				if (contour.positiv)
					positivContours.Push (contour);
				else if (insideOf != nullptr)
					insideOf->holes.Push (contour);

				if (insideOf == nullptr && withoutHoles) {
					Contour outsideContour;
					outsideContour.whichPoly = contour.whichPoly;
					outsideContour.contourId = contour.contourId;
					outsideContour.numVertex = 0;
					outsideContour.numArc = 0;
					outsideContour.startLink = startLink;
					outsideContour.bbox = startLink->bbox;
					outsideContour.area2 = Int (0);
					outsideContour.positiv = true;

					Link* link = startLink;
					do {
						outsideContour.numVertex++;
						if (outsideContour.numVertex > linkNum)
							throw GeometryAlgorithmErrorException ("Infinite Cycle", __FILE__, __LINE__);
						if (!link->isLine)
							outsideContour.numArc++;
						outsideContour.bbox.minX = GS::Min (outsideContour.bbox.minX, link->bbox.minX);
						outsideContour.bbox.maxX = GS::Max (outsideContour.bbox.maxX, link->bbox.maxX);
						outsideContour.bbox.minY = GS::Min (outsideContour.bbox.minY, link->bbox.minY);
						outsideContour.bbox.maxY = GS::Max (outsideContour.bbox.maxY, link->bbox.maxY);
						outsideContour.area2 += GetLinkSweepArea2 (link);
						link = GetOutsideContourNextLink (link, contour);
					} while (link != startLink);

					if (outsideContour.numVertex != contour.numVertex || contour.holes.GetSize () != 0)
						noChange = false;

					outsideContours.Push (outsideContour);
				}
			}
		}
	}
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Link* PGBoolTmp<DInt,Int,PolygonSelector>::GetContourPrevLink (Link* link, const Contour& contour)
{
	DBASSERT (link->leftPoly == contour.whichPoly || link->rightPoly == contour.whichPoly);

	const bool positivContour = contour.positiv;
	Node* n = link->leftPoly == contour.whichPoly ? link->beg : link->end;
	Int32 j;

	Int32 linkNum = n->links.GetSize ();
	for (j = 0; j < linkNum && n->links[j] != link; j++)
		;

	if (!positivContour) {
		j += linkNum;
	}
	do {
		if (positivContour)
			j++;
		else
			j--;
	} while (!n->links[j % linkNum]->markForKeep || n->links [j % linkNum]->leftPoly != contour.whichPoly && n->links [j % linkNum]->rightPoly != contour.whichPoly);
	return n->links[j % linkNum];
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Link* PGBoolTmp<DInt,Int,PolygonSelector>::GetContourNextLink (Link* link, const Contour& contour)
{
	DBASSERT (link->leftPoly == contour.whichPoly || link->rightPoly == contour.whichPoly);

	static GS::InfoLogLine log ("GetContourNextLink", "Geometry");

	const bool positivContour = contour.positiv;
	Node* n = link->leftPoly == contour.whichPoly ? link->end : link->beg;
	Int32 j;

	Int32 linkNum = n->links.GetSize ();
	for (j = 0; j < linkNum && n->links[j] != link; j++)
		;

	if (positivContour) {
		j += linkNum;
	}
	do {
		if (positivContour)
			j--;
		else
			j++;
		if ((j < -linkNum) || (j > 3 * linkNum)) {
			GS::logger.Append (log, "Infinite Cycle in GetContourNextLink");	// biztos hogy korbeertunk (a hatarok nagyvonaluan vannak beallitva, de ez itt mindegy)-> exeption
			throw GeometryAlgorithmErrorException ("Infinite Cycle in GetContourNextLink", __FILE__, __LINE__);
		}
	} while (!n->links[j % linkNum]->markForKeep || n->links [j % linkNum]->leftPoly != contour.whichPoly && n->links [j % linkNum]->rightPoly != contour.whichPoly);
	return n->links[j % linkNum];
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Link* PGBoolTmp<DInt,Int,PolygonSelector>::GetOutsideContourPrevLink (Link* link, const Contour& contour)
{	
	DBASSERT (link->leftPoly == contour.whichPoly || link->rightPoly == contour.whichPoly);

	Node* n = link->leftPoly == contour.whichPoly ? link->beg : link->end;
	Int32 j;

	Int32 linkNum = n->links.GetSize ();
	for (j = 0; j < linkNum && n->links[j] != link; j++)
		;

	j += linkNum;
	do {
		j--;
	} while (n->links[j % linkNum]->leftContourId != contour.contourId && n->links[j % linkNum]->rightContourId != contour.contourId);
	return n->links[j % linkNum];
}

template<class DInt, class Int, class PolygonSelector>
typename PGBoolTmp<DInt,Int,PolygonSelector>::Link* PGBoolTmp<DInt,Int,PolygonSelector>::GetOutsideContourNextLink (Link* link, const Contour& contour)
{	
	DBASSERT (link->leftPoly == contour.whichPoly || link->rightPoly == contour.whichPoly);

	Node* n = link->leftPoly == contour.whichPoly ? link->end : link->beg;
	Int32 j;

	Int32 linkNum = n->links.GetSize ();
	for (j = 0; j < linkNum && n->links[j] != link; j++)
		;

	do {
		j++;
	} while (n->links[j % linkNum]->leftContourId != contour.contourId && n->links[j % linkNum]->rightContourId != contour.contourId);
	return n->links[j % linkNum];
}


}

#endif
