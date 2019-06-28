// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLTMP_H
#define PGBOOLTMP_H

namespace PolygonBoolean {

template<class DInt, class Int, class PolygonSelector>
PGBoolTmp<DInt,Int,PolygonSelector>::PGBoolTmp (PGBoolean<PolygonSelector>* pgObj) :
	polyEdges (pgObj->polyEdges),
	polyEdgeOffsets (pgObj->polyEdgeOffsets),
	origPolys (pgObj->origPolys),
	polyDatas (pgObj->polyDatas),
	withoutHoles (pgObj->withoutHoles),
	origBBSide (pgObj->origBBSide),
	origBBOffset (pgObj->origBBOffset),
	isBSplitLine (pgObj->isBSplitLine),
	isPolyRegular (pgObj->isPolyRegular),
	polygonSelector (pgObj->polygonSelector),
	polyACovered (false),
	polyBCovered (false),
	polysDisjoint (false),
	polyAHasZeroArea (false),
	polyBHasZeroArea (false),
	edgeTouch (false),
	nodeTouch (false),
	generatedNodeIdCounter (0),
#if defined (DEBUG_PGBOOL)
	idCounter (0),
#endif
	breaker (pgObj->breaker)
{
	pgBoolean = pgObj;

	numContours = 0;
}

template<class DInt, class Int, class PolygonSelector>
inline PGBoolTmp<DInt,Int,PolygonSelector>::~PGBoolTmp ()
{
	ULong linkNum = allLinks.GetSize ();
	ULong nodeNum = allNodes.GetSize ();

	for (ULong i = 0; i < linkNum; i++)
		DeleteLink (allLinks[i]);
	for (ULong i = 0; i < nodeNum; i++)
		DeleteNode (allNodes[i]);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::Reinitialize ()
{
	ULong linkNum = allLinks.GetSize ();
	ULong nodeNum = allNodes.GetSize ();

	for (ULong i = 0; i < linkNum; i++)
		DeleteLink (allLinks[i]);
	for (ULong i = 0; i < nodeNum; i++)
		DeleteNode (allNodes[i]);

	allLinks.Clear ();
	allNodes.Clear ();
	positivContours.Clear ();

	numContours = 0;
}

template<class DInt, class Int, class PolygonSelector>
PGRelPolyPosExt PGBoolTmp<DInt,Int,PolygonSelector>::DoOperationStages (bool allStages)
{
	if (pgBoolean->stage == 3) {
		double pgEps = origPolys [0]->epsilon;
		for (UInt32 i = 1; i < origPolys.GetSize (); ++i) {
			pgEps = GS::Min (pgEps, origPolys [i]->epsilon);
		}
		pgEps = GS::Max (pgEps, SmallEps);
		
		Int intPgEps = DistanceToInt (pgEps);
		const Int minSnapDist = DInt::minSnapDist;
		snapDist = GS::Max (minSnapDist, intPgEps / 8);
		snapDist4 = snapDist / 4;
		area2Minimum = Mul (intPgEps, intPgEps * 2);
		noChange = true;

		bool bigEnough = ConvertPoly (0);

		pgBoolean->stage++;

		if (!allStages && !bigEnough) {
			noChange = false;
			if (isPolyRegular != nullptr)
				*isPolyRegular = false;
			return Poly1HasZeroArea;
		}
	}

	if (pgBoolean->stage == 4) {		
		bool poly2HasZeroArea = false;
		for (UInt32 i = 1; i < origPolys.GetSize (); ++i) {
			bool bigEnough = ConvertPoly (i);
			if (i == 1 &&  !bigEnough)
				poly2HasZeroArea = true;				
		}

		pgBoolean->stage++;

		if (!allStages && poly2HasZeroArea)
			return Poly2HasZeroArea;
	}

	PGRelPolyPosExt retVal = UnknownStatus;
	if (pgBoolean->stage == 5) {
		nodesSorted = linksSorted = false;

		bool b1 = NodeToNodeSnap ();
		if (isPolyRegular != nullptr && b1)
			*isPolyRegular = false;

		bool b2 = LinkToNodeSnap ();
		if (isPolyRegular != nullptr && b2)
			*isPolyRegular = false;

		bool b3 = CreateLinkIntersections ();
		if (isPolyRegular != nullptr && b3)
			*isPolyRegular = false;

		if (b1 || b2 || b3)
			noChange = false;

		for (int infiniteCycleCount = 1; ; infiniteCycleCount++) {
			if (!b3)
				break;

			if (infiniteCycleCount % 10 == 0) {
				snapDist /= 2;
				snapDist4 /= 2;
				if (snapDist < DInt::minSnapDist / 2) {
					DBBREAK ();
					break;
				}
			}

			b1 = NodeToNodeSnap ();

			if (!b1 && !b3)
				break;
			b2 = LinkToNodeSnap ();
			if (isPolyRegular != nullptr && b2)
				*isPolyRegular = false;

			if (!b2 && !b1)
				break;
			b3 = CreateLinkIntersections ();
			if (isPolyRegular != nullptr && b3)
				*isPolyRegular = false;
		}

		CalcLinkSideOverlaps ();
		retVal = SelectGoodLinks ();

		pgBoolean->stage++;
	}

	return retVal;
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::GetResultPolygons (PGRESPOLYEXT* newPolygons)
{
	if (pgBoolean->stage == 6) {
		if (!linksSorted) {
			qsort ((Link**) allLinks.GetContent (), allLinks.GetSize (), sizeof (Link*), CompareLinks);
			linksSorted = true;
		}
		CollectContours (nullptr, 0);		

		pgBoolean->stage++;
	}

	ReturnResult (newPolygons);
}

template<class DInt, class Int, class PolygonSelector>
PGPositionExt PGBoolTmp<DInt,Int,PolygonSelector>::SegmentInPoly (const Sector* sector, const CircleArc* arc, ResultSegmentPos::Et pos,
												  PGRESSECTOREXT* newSectors, GS::Array<CircleArc>* newArcs)
{
	double pgEps = GS::Max (origPolys [0]->epsilon, SmallEps);
	Int intPgEps = DistanceToInt (pgEps);
	const Int minSnapDist = DInt::minSnapDist;
	snapDist = GS::Max (minSnapDist, intPgEps / 8);
	snapDist4 = snapDist / 4;
	area2Minimum = Mul (intPgEps, intPgEps * 2);

	bool bigEnough = ConvertPoly (0);
	if (!bigEnough) {
		if (pos & ResultSegmentPos::Outside) {
			if (newSectors != nullptr) {
				if (newSectors->newSector == nullptr)
					((GS::VAArray<Sector>*) newSectors->sectorsData)->Push (*sector);
				else
					newSectors->newSector (newSectors, *sector);
			}
			if (newArcs != nullptr)
				newArcs->Push (*arc);
		}
		return PGOutsidePoly;
	}

	Node* begNode = InsertNewNode (sector != nullptr ? sector->c1 : arc->begC, SoloSegment, 0);
	if (sector != nullptr)
		InsertNewLine (begNode, sector->c2);
	else
		InsertNewArc (begNode, arc->endC, arc->origo, false);

	nodesSorted = linksSorted = false;

	bool b1;
	bool b2;
	/*b1 =*/ NodeToNodeSnap ();
	/*b2 =*/ LinkToNodeSnap ();
	bool b3 = CreateLinkIntersections ();

	for (int infiniteCycleCount = 1; ; infiniteCycleCount++) {
		if (!b3)
			break;

		if (infiniteCycleCount % 10 == 0) {
			snapDist /= 2;
			snapDist4 /= 2;
			if (snapDist < DInt::minSnapDist / 2) {
				DBBREAK ();
				break;
			}
		}

		b1 = NodeToNodeSnap ();

		if (!b1 && !b3)
			break;
		b2 = LinkToNodeSnap ();

		if (!b2 && !b1)
			break;
		b3 = CreateLinkIntersections ();
	}

	CalcLinkSideOverlaps ();
	return ReturnGoodSegments (arc, pos, newSectors, newArcs);
}

template<class DInt, class Int, class PolygonSelector>
inline void PGBoolTmp<DInt,Int,PolygonSelector>::FillLineStruct (Line* line)
{
	line->bbox.minX = GS::Min (line->beg->pos.x, line->end->pos.x);
	line->bbox.maxX = GS::Max (line->beg->pos.x, line->end->pos.x);
	line->bbox.minY = GS::Min (line->beg->pos.y, line->end->pos.y);
	line->bbox.maxY = GS::Max (line->beg->pos.y, line->end->pos.y);
}

template<class DInt, class Int, class PolygonSelector>
void PGBoolTmp<DInt,Int,PolygonSelector>::FillArcStruct (Arc* arc)
{
	const Point<DInt,Int> begPos = arc->beg->pos;
	const Point<DInt,Int> endPos = arc->end->pos;

	const Point<DInt,Int> diff = (endPos - begPos) / 2;

	Int diffMax = GS::Max (Abs (diff.x), Abs (diff.y));
	if (diffMax > 0) {
		const DInt dSqr = diff.LenSqr ();
		const Int d = Sqrt (dSqr);

		if (arc->r < d)
			arc->r = CeilToRadiusGrid (d);

		const DInt mSqr = Mul (arc->r, arc->r) - dSqr;
		Int m = mSqr > Int (0) ? Sqrt (mSqr) : 0;

		if (((arc->center - begPos) ^ diff) < Int (0))
			m = -m;

		Point<DInt,Int> diff2 (Mul (diff.x, DInt::maxCoordVal - DInt::minCoordVal) / diffMax,
							   Mul (diff.y, DInt::maxCoordVal - DInt::minCoordVal) / diffMax);
		Int d2 = diff2.Len ();

		arc->center.x = begPos.x + diff.x + Mul (diff2.y, m) / d2;
		arc->center.y = begPos.y + diff.y + Mul (-diff2.x, m) / d2;
	} else {
		arc->center = begPos;
		arc->r = 0;
	}

	if (arc->positiv) {
		arc->right = begPos - arc->center;
		arc->left = endPos - arc->center;
	} else {
		arc->right = endPos - arc->center;
		arc->left = begPos - arc->center;
	}

	arc->qr = GetPointQuarter (arc->right);
	arc->ql = GetRelativePointQuarter (arc->right, arc->left, arc->qr);

	arc->bbox.minX = GS::Min (begPos.x, endPos.x);
	arc->bbox.maxX = GS::Max (begPos.x, endPos.x);
	arc->bbox.minY = GS::Min (begPos.y, endPos.y);
	arc->bbox.maxY = GS::Max (begPos.y, endPos.y);

	for (int i = arc->qr; i < arc->ql; i++) {
		switch (i % 4)
		{
			case 0:
				arc->bbox.maxY = GS::Max (arc->bbox.maxY, arc->center.y + arc->r);
				break;
			case 1:
				arc->bbox.minX = GS::Min (arc->bbox.minX, arc->center.x - arc->r);
				break;
			case 2:
				arc->bbox.minY = GS::Min (arc->bbox.minY, arc->center.y - arc->r);
				break;
			case 3:
				arc->bbox.maxX = GS::Max (arc->bbox.maxX, arc->center.x + arc->r);
				break;
		}
	}
}

template<class DInt, class Int, class PolygonSelector>
inline int PGBoolTmp<DInt,Int,PolygonSelector>::GetPointQuarter (const Point<DInt,Int>& p)
{
	if (p.y > 0) {
		if (p.x > 0)
			return 0;
		else
			return 1;
	} else if (p.x > 0)
		return 3;
	else
		return 2;
}

template<class DInt, class Int, class PolygonSelector>
inline bool PGBoolTmp<DInt,Int,PolygonSelector>::IsCCWInQuarter (const Point<DInt,Int>& v, const Point<DInt,Int>& w)
{
	if (Abs (v.x) > Abs (v.y)) {
		if (Abs (w.x) > Abs (w.y))
			return v.x > 0 ? w.y > v.y || (w.y == v.y && w.x < v.x) : w.y < v.y || (w.y == v.y && w.x > v.x);
		else
			return !((v.x > 0) ^ (v.y > 0));
	} else {
		if (Abs (w.x) > Abs (w.y))
			return (v.x > 0) ^ (v.y > 0);
		else
			return v.y > 0 ? w.x < v.x || (w.x == v.x && w.y > v.y) : w.x > v.x || (w.x == v.x && w.y < v.y);
	}
}

template<class DInt, class Int, class PolygonSelector>
inline int PGBoolTmp<DInt,Int,PolygonSelector>::GetRelativePointQuarter (const Point<DInt,Int>& beg, const Point<DInt,Int>& p, int qb)
{
	int qp = GetPointQuarter (p);

	if (qp == qb)
		return IsCCWInQuarter (beg, p) ? qp : qp + 4;

	return qp > qb ? qp : qp + 4;
}

template<class DInt, class Int, class PolygonSelector>
inline bool PGBoolTmp<DInt,Int,PolygonSelector>::IsCCW (const Point<DInt,Int>& mid, const Point<DInt,Int>& end, int qm, int qe)
{
	if (qm != qe)
		return qm < qe;

	return IsCCWInQuarter (mid, end);
}

template<class DInt, class Int, class PolygonSelector>
CmpResult PGBoolTmp<DInt,Int,PolygonSelector>::CompareNodes (const void* p1, const void* p2)
{
	const Node* n1 = *(Node**) p1;
	const Node* n2 = *(Node**) p2;

	if (n1 == nullptr)
		return n2 == nullptr ? 0 : 1;
	if (n2 == nullptr)
		return -1;

	if (n1->pos.x < n2->pos.x)
		return -1;
	else if (n1->pos.x == n2->pos.x)
		return 0;
	else
		return 1;
}

template<class DInt, class Int, class PolygonSelector>
CmpResult PGBoolTmp<DInt,Int,PolygonSelector>::CompareLinks (const void* p1, const void* p2)
{
	const Link* l1 = *(Link**) p1;
	const Link* l2 = *(Link**) p2;

	if (l1->markForDelete)
		return l2->markForDelete ? 0 : 1;
	if (l2->markForDelete)
		return -1;

	if (l1->bbox.minX < l2->bbox.minX)
		return -1;
	else if (l1->bbox.minX == l2->bbox.minX)
		return 0;
	else
		return 1;
}

template<class DInt, class Int, class PolygonSelector>
CmpResult PGBoolTmp<DInt,Int,PolygonSelector>::CompareNodeSnapToLineData (const void* p1, const void* p2)
{
	const NodeSnapToLineData& snapData1 = *(NodeSnapToLineData*) p1;
	const NodeSnapToLineData& snapData2 = *(NodeSnapToLineData*) p2;

	if (snapData1.sortVal < snapData2.sortVal)
		return -1;
	else if (snapData1.sortVal == snapData2.sortVal)
		return 0;
	else
		return 1;
}

template<class DInt, class Int, class PolygonSelector>
CmpResult PGBoolTmp<DInt,Int,PolygonSelector>::CompareNodeSnapToArcDataPositiv (const void* p1, const void* p2)
{
	const NodeSnapToArcData& snapData1 = *(NodeSnapToArcData*) p1;
	const NodeSnapToArcData& snapData2 = *(NodeSnapToArcData*) p2;

	if (IsCCW (snapData1.p, snapData2.p, snapData1.qnode, snapData2.qnode))
		return -1;
	else if (snapData1.p == snapData2.p && snapData1.qnode == snapData2.qnode)
		return 0;
	else
		return 1;
}

template<class DInt, class Int, class PolygonSelector>
CmpResult PGBoolTmp<DInt,Int,PolygonSelector>::CompareNodeSnapToArcDataNegativ (const void* p1, const void* p2)
{
	const NodeSnapToArcData& snapData1 = *(NodeSnapToArcData*) p1;
	const NodeSnapToArcData& snapData2 = *(NodeSnapToArcData*) p2;

	if (IsCCW (snapData2.p, snapData1.p, snapData2.qnode, snapData1.qnode))
		return -1;
	else if (snapData1.p == snapData2.p && snapData1.qnode == snapData2.qnode)
		return 0;
	else
		return 1;
}

template<class DInt, class Int, class PolygonSelector>
inline typename PGBoolTmp<DInt,Int,PolygonSelector>::Node* PGBoolTmp<DInt,Int,PolygonSelector>::NewNode ()
{
	Node* n = pgBoolean->memAlloc.template Allocate<Node> ();
	new (n) Node (
#if defined (DEBUG_PGBOOL)
		++idCounter
#endif
		);
	return n;
}

template<class DInt, class Int, class PolygonSelector>
inline typename PGBoolTmp<DInt,Int,PolygonSelector>::Line* PGBoolTmp<DInt,Int,PolygonSelector>::NewLine ()
{
	Line* ln = pgBoolean->memAlloc.template Allocate<Line> ();
	new (ln) Line (this
#if defined (DEBUG_PGBOOL)
		, ++idCounter
#endif
		);
	return ln;
}

template<class DInt, class Int, class PolygonSelector>
inline typename PGBoolTmp<DInt,Int,PolygonSelector>::Line* PGBoolTmp<DInt,Int,PolygonSelector>::NewLine (const Line& source)
{
	Line* ln = pgBoolean->memAlloc.template Allocate<Line> ();
	new (ln) Line (source);
#if defined (DEBUG_PGBOOL)
	ln->linkId = ++idCounter;
#endif
	return ln;
}

template<class DInt, class Int, class PolygonSelector>
inline typename PGBoolTmp<DInt,Int,PolygonSelector>::Arc* PGBoolTmp<DInt,Int,PolygonSelector>::NewArc ()
{
	Arc* a = pgBoolean->memAlloc.template Allocate<Arc> ();
	new (a) Arc (this
#if defined (DEBUG_PGBOOL)
		, ++idCounter
#endif
		);
	return a;
}

template<class DInt, class Int, class PolygonSelector>
inline typename PGBoolTmp<DInt,Int,PolygonSelector>::Arc* PGBoolTmp<DInt,Int,PolygonSelector>::NewArc (const Arc& source)
{
	Arc* a = pgBoolean->memAlloc.template Allocate<Arc> ();
	new (a) Arc (source);
#if defined (DEBUG_PGBOOL)
	a->linkId = ++idCounter;
#endif
	return a;
}

template<class DInt, class Int, class PolygonSelector>
GS_FORCE_INLINE void PGBoolTmp<DInt,Int,PolygonSelector>::DeleteNode (Node* n)
{
	if (n == nullptr)
		return;

	n->~Node ();
	pgBoolean->memAlloc.Free (n);
}

template<class DInt, class Int, class PolygonSelector>
inline void PGBoolTmp<DInt,Int,PolygonSelector>::DeleteLink (Link* link)
{
	if (link == nullptr)
		return;

	if (link->isLine) {
		Line* ln = (Line*) link;
		ln->~Line ();
		pgBoolean->memAlloc.Free (ln);
	} else {
		Arc* a = (Arc*) link;
		a->~Arc ();
		pgBoolean->memAlloc.Free (a);
	}
}

}

#endif
