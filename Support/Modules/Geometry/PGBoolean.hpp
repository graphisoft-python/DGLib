// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLEAN_H
#define PGBOOLEAN_H

//#include <search.h>

#include "Algorithms.hpp"
#include "Array.hpp"
#include "Channel.hpp"
#include "HashTable.hpp"

#include "Polygon2DOperations.h"
#include "Polygon2DData.h"
#include "PGInternalRepresentation.hpp"
#include "GenArc2DData.h"
#include "AngleData.h"

#include "PGBooleanOperations.hpp"
#include "PGBooleanInternal.hpp"
#include "MemAlloc.hpp"

#include "BTree.hpp"

using namespace QXTools;

#if defined (DEBUVERS)
#define DEBUG_PGBOOL 1
#endif

namespace PolygonBoolean {

static const UInt32	SoloSegment = MaxUInt32 - 1;
static const UInt32 None		= MaxUInt32;
typedef UInt32 WhichPoly;

template <class PolygonSelector>
class PGBoolean;

class PGBooleanOp;
class PGBooleanClip;

template<class DInt, class Int, class PolygonSelector>
class PGBoolTmp
{
	struct NodeOverlapData;
	
	template <class>
	friend class PGBoolean;

	friend class PGBooleanOp;
	friend class PGBooleanClip;

	PGBoolTmp (PGBoolean<PolygonSelector>*);
	~PGBoolTmp ();

	PGBoolTmp& operator= (const PGBoolTmp&);

	struct Link;
	struct Node
	{
		Point<DInt,Int>			pos;
		Int32					origVertex;
		WhichPoly				whichPoly;
		GS::ArrayFB<Link*,8>	links;		
		bool					processed;
		UInt32					generatedNodeId;

#if defined (DEBUG_PGBOOL)
		Int32			nodeId;
#endif

		Node (
#if defined (DEBUG_PGBOOL) 
			UInt32		nodeId
#endif
			) :
					
			processed (false),
			generatedNodeId (0)
#if defined (DEBUG_PGBOOL)
			, nodeId (nodeId)
#endif
		{
		}
	};

	struct Link
	{
		Node*			beg;
		Node*			end;
		BoundBox<Int>	bbox;
		Int32			origEdge;
		WhichPoly		whichPoly;

		Int32			origRightEdge; // orig edge from rightPoly.

		bool			uniqOrigEdge;		
		
		bool			markForDelete, markForKeep;

		WhichPoly		leftPoly;
		WhichPoly		rightPoly;

		Int32			leftContourId;
		Int32			rightContourId;

		PGBoolTmp<DInt, Int, PolygonSelector>* const	pgBoolTmp;
		const bool	isLine;

#if defined (DEBUG_PGBOOL)
		UInt32			linkId;
#endif

		Link (bool inIsLine, PGBoolTmp<DInt,Int, PolygonSelector>* inPGBoolTmp
#if defined (DEBUG_PGBOOL)
			, UInt32 linkId
#endif		
			) :
			pgBoolTmp (inPGBoolTmp),
			isLine (inIsLine),
			markForDelete (false),
			markForKeep (false),
			leftPoly (None),
			rightPoly (None),
			leftContourId (0),
			rightContourId (0),
			origRightEdge (-1)
#if defined (DEBUG_PGBOOL)
			, linkId (linkId)
#endif
		{
		}

		Link& operator= (const Link&);		// Not implemented. To avoid compiler warning caused by the const data member.
	};

	struct Line : Link
	{
		Line (PGBoolTmp<DInt,Int,PolygonSelector>* inPGBoolTmp
#if defined (DEBUG_PGBOOL)
			, UInt32 linkId
#endif
			) : Link (true, inPGBoolTmp
#if defined (DEBUG_PGBOOL)
			, linkId
#endif
			) {}
	};

	struct Arc : Link
	{
		Int				r;
		bool			positiv;
		Point<DInt,Int>	center;
		Point<DInt,Int>	right;
		Point<DInt,Int>	left;
		int				qr;
		int				ql;

		Arc (PGBoolTmp<DInt,Int,PolygonSelector>* inPGBoolTmp
#if defined (DEBUG_PGBOOL)
			, UInt32 linkId
#endif
			) : Link (false, inPGBoolTmp
#if defined (DEBUG_PGBOOL)
			, linkId
#endif
			) {}
	};

	struct Contour
	{
		WhichPoly		whichPoly;
		Int32			contourId;
		Int32			numVertex;
		Int32			numArc;
		Link*			startLink;
		BoundBox<Int>	bbox;
		DInt			area2;
		bool			positiv;
		GS::Array<Contour> holes;
	};

	PGBoolean<PolygonSelector>* pgBoolean;

	const GS::Array<const PGPOLYEXT*>&			origPolys;
	const GS::Array<UInt32>&					polyEdgeOffsets;
	const GS::ArrayFB<PGEDGEEXT,1000>&			polyEdges;
	const GS::Array<const Polygon2DData*>&		polyDatas;

	const bool&		withoutHoles;
	const double&	origBBSide;
	const Coord&	origBBOffset;
	const bool&		isBSplitLine;
	bool*const&		isPolyRegular;

	PolygonSelector&							polygonSelector;

	bool			polyACovered;
	bool			polyBCovered;
	bool			polysDisjoint;
	bool			polyAHasZeroArea;
	bool			polyBHasZeroArea;
	bool			edgeTouch;
	bool			nodeTouch;

	Int		snapDist;
	Int		snapDist4;
	DInt	area2Minimum;

	bool	noChange;

	GS::ArrayFB<Link*, 1000>	allLinks;
	GS::ArrayFB<Node*, 1000>	allNodes;
	GS::ArrayFB<Contour, 10>	positivContours;
	GS::ArrayFB<Contour, 10>	outsideContours;
	Int32 numContours;
	bool linksSorted;
	bool nodesSorted;
	UInt32						generatedNodeIdCounter;
#if defined (DEBUG_PGBOOL)
	UInt32						idCounter;
#endif

	struct NodeSnapToLineData
	{
		Node*	node;
		Int		sortVal;
	};

	struct NodeSnapToArcData
	{
		Node*			node;
		Point<DInt,Int>	p;
		int				qnode;
	};

	typedef GS::ArrayFB<NodeSnapToLineData, 8>		NodeSnapToLineDataArray;
	typedef GS::ArrayFB<NodeSnapToArcData, 8>		NodeSnapToArcDataArray;

	struct CheckPositivContourData
	{
		Node*	polygonFirstNode;
		Int32	firstLinkIndex;
		Int32	endLinkIndex;
	};

	static CmpResult SortLinksOfNode (const void*, const void*);
	Node* sortLinksOfThisNode;

	Link* linkPtrArr[1000];

	GS::AbortInterfaceBase*	breaker;

	void Reinitialize ();

	PGRelPolyPosExt DoOperationStages (bool allStages);
	void GetResultPolygons (PGRESPOLYEXT* newPolygons);

	PGPositionExt SegmentInPoly (const Sector* sector, const CircleArc* arc, ResultSegmentPos::Et pos,
		PGRESSECTOREXT* newSectors, GS::Array<CircleArc>* newArcs);

	Point<DInt,Int> RoundToNodeGrid (const Point<DInt,Int>& p);
	Int RoundToRadiusGrid (Int r);
	Int CeilToRadiusGrid (Int r);
	Point<DInt,Int> CoordToPoint (const Coord& c);
	Coord PointToCoord (const Point<DInt,Int>& p);
	Int DistanceToInt (double d);
	static int GetPointQuarter (const Point<DInt,Int>& p);
	static bool IsCCWInQuarter (const Point<DInt,Int>& v, const Point<DInt,Int>& w);
	static int GetRelativePointQuarter (const Point<DInt,Int>& beg, const Point<DInt,Int>& p, int qb);
	static bool IsCCW (const Point<DInt,Int>& mid, const Point<DInt,Int>& end, int qm, int qe);
	static void FillLineStruct (Line* line);
	void FillArcStruct (Arc* arc);

	bool ConvertPoly (WhichPoly whichPoly);
	Node* InsertNewNode (const Coord& c, WhichPoly whichPoly, Int32 origVertex);
	Node* InsertNewLine (Node* begNode, const Coord& endCo);
	Node* InsertNewArc (Node* begNode, const Coord& endCo, const Coord& center, bool revOriented);
	void CloseContourWithLine (Node* begNode, Node* endNode);
	void CloseContourWithArc (Node* begNode, Node* endNode, const Coord& center, double r, bool revOriented);
	void SegmentArcToLines (Node* beg, Node* end, const Coord& center, bool revOriented);
	void ReturnContourProc (const Contour& contour, PGPOLYEXT* createdPoly);
	void ReturnContourData (const Contour& contour, Polygon2DData* poly);
	void ReturnResult (PGRESPOLYEXT* newPolygons);

	static CmpResult CompareNodes (const void* p1, const void* p2);
	static CmpResult CompareLinks (const void* p1, const void* p2);
	static CmpResult CompareNodeSnapToLineData (const void* p1, const void* p2);
	static CmpResult CompareNodeSnapToArcDataPositiv (const void* p1, const void* p2);
	static CmpResult CompareNodeSnapToArcDataNegativ (const void* p1, const void* p2);

	bool NodeToNodeSnap ();
	bool AddNodeIfNearToLine (Line* line, Node* node, NodeSnapToLineDataArray& snapNodes);
	bool AddNodeIfNearToArc (Arc* arc, Node* node, NodeSnapToArcDataArray& snapNodes);
	bool LinkToNodeSnap ();
	void InsertNodesToLine (Line* line, NodeSnapToLineDataArray& nodesToInsert);
	void InsertNodesToArc (Arc* arc, NodeSnapToArcDataArray& nodesToInsert);
	bool ApproxLineToLineIntersection (Line* l1, Line* l2);
	bool AddLineToLineIntersection (Line* l1, Line* l2, NodeSnapToLineDataArray& snapNodes1,
		NodeSnapToLineDataArray& snapNodes2);
	bool AddLineToArcIntersections (Line* line, Arc* arc, NodeSnapToLineDataArray& snapNodes1,
		NodeSnapToArcDataArray& snapNodes2);
	bool AddArcToArcIntersections (Arc* a1, Arc* a2, NodeSnapToArcDataArray& snapNodes1,
		NodeSnapToArcDataArray& snapNodes2);
	bool CreateLinkIntersections ();

	void		ProcessNode (Node* node);
	void		CalcOverlapAsPassingLink (PolygonSelector& polygonSelector, bool passingLeftToRight, WhichPoly whichPoly);
	void		CalcOverlapAsPassingLinkOfNode (PolygonSelector& polygonSelector, Node* node, Int32 linkIndex);
	
	int ReturnInfiniteLineCrossings (Link* link, Node* node, bool* fromBelow);
	
	void CalcLinkSideOverlaps ();
	bool IsCoincedentLinks (const Link& l1, const Link&l2);
	void ReverseLink (Link* link);
	PGRelPolyPosExt SelectGoodLinks ();
	PGPositionExt ReturnGoodSegments (const CircleArc* arc, ResultSegmentPos::Et pos, PGRESSECTOREXT* newSectors, GS::Array<CircleArc>* newArcs);
	bool IsNodeInsideContour (Node* node, const Contour& contour);
	static DInt GetLinkSweepArea2 (Link* link);
	static DInt GetLinkSweepArea2 (Link* link, WhichPoly whichPoly);
	void CollectContours (Contour* insideOf, Int32 startLinkIndex);
	static Link* GetContourPrevLink (Link* link, const Contour& contour);
	static Link* GetContourNextLink (Link* link, const Contour& contour);
	static Link* GetOutsideContourPrevLink (Link* link, const Contour& contour);
	static Link* GetOutsideContourNextLink (Link* link, const Contour& contour);

	void PrintContour (const Contour& contour, GS::OChannel& outChannel);
	void PrintResult (GS::OChannel& outChannel);

	Node* NewNode ();
	Line* NewLine ();
	Line* NewLine (const Line&);
	Arc* NewArc ();
	Arc* NewArc (const Arc&);
	void DeleteNode (Node*);
	void DeleteLink (Link*);
};

class PGBooleanBase {
private:
	friend class PGBooleanBaseInitializer;
	static void InitializeMemoryManager ();
	static void ExitMemoryManager ();

public:

	void* operator new (size_t);
	void operator delete (void*);
};

template <class PolygonSelector>
class PGBoolean : public PGBooleanBase
{
	template <class, class, class>
	friend class PGBoolTmp;

public:
	PGBoolean (GS::AbortInterfaceBase* breakerIn);
	~PGBoolean ();

	enum ResultPolygonHandling {
		KeepAllPolygons,
		SkipSmallPolygons
	};

	void GetResultPolygons (PGRESPOLYEXT* newPolygons);

	void PrintReport (const char* opName, PGRelPolyPosExt status, GS::OChannel& outChannel);

protected:

	typedef PGBoolTmp<SDoubleInt32, SignedInt32, PolygonSelector>	PGBool32Type;
	typedef PGBoolTmp<DInt64, Int64, PolygonSelector>				PGBool64Type;

#define MMAX(a, b) (((a) > (b)) ? (a) : (b))
	MemAlloc <
		MMAX (MMAX (MMAX (sizeof (typename PGBool32Type::Node), sizeof (typename PGBool64Type::Node)),
					MMAX (sizeof (typename PGBool32Type::Line), sizeof (typename PGBool64Type::Line))),
					MMAX (sizeof (typename PGBool32Type::Arc), sizeof (typename PGBool64Type::Arc)))
	> memAlloc;
#undef MMAX

	int		stage;

	Box2DData boundBox;

	bool				withoutHoles;
	bool				isSameDirEdgeLegal;
	bool				containsArc;
	bool				force64BitPrecision;
	bool				isBSplitLine;
	bool				polyPosition;
	double				origBBSide;
	Coord				origBBOffset;
	bool				b64BitPrecision;
	bool*				isPolyRegular;

	PolygonSelector		polygonSelector;

	GS::ArrayFB<const PGPOLYEXT*,2>			origPolys;
	GS::ArrayFB<UInt32, 2>					polyEdgeOffsets;
	GS::ArrayFB<PGEDGEEXT,1000>				polyEdges;
	GS::ArrayFB<const Polygon2DData*, 2>	polyDatas;

	ResultPolygonHandling					resultPolygonHandling;

	GS::AbortInterfaceBase*	breaker;

	PGBool32Type pgBoolean32;
	PGBool64Type pgBoolean64;

	void Reinitialize ();

	PGRelPolyPosExt DoOperationStages (bool allStages);

	void GetEdgesOfPoly (WhichPoly whichPoly);
	Box2DData GetBoundBox (WhichPoly whichPoly);
	Box2DData CalcBoundBox (WhichPoly whichPoly);
	void AddArcCenters (Box2DData* bbox, WhichPoly whichPoly);

	void PrintPolygon (GS::OChannel& outChannel, WhichPoly whichPoly);
};

template <class PolygonSelector>
GS_FORCE_INLINE Int32 GetSelectorPolyCount (const PolygonSelector& selector, WhichPoly whichPoly)
{
	Int32 count = selector.GetPolyOverlap (whichPoly);

	if (count != 0) {
		switch (selector.GetFillingMethod (whichPoly)) {
		case Alternative:
			count = (count & 1);
			break;
		case WindingRulePos:
			count = GS::Abs (count);
			break;
		}
	}
	return count;
}

class PGBooleanOp;

class BooleanPolygonSelector
{
private:
	Int32 overlaps [2];
	FillingMethod fillingMethodA, fillingMethodB;
	BoolFunctionType boolFunction;

public:
	BooleanPolygonSelector ();

	BooleanPolygonSelector (BoolFunctionType boolFunction, FillingMethod fillingMethodA, FillingMethod fillingMethodB);

	GS_FORCE_INLINE void			Reset ()
	{
		overlaps [0] = overlaps [1] = 0;
	}

	GS_FORCE_INLINE Int32			GetPolyOverlap (WhichPoly whichPoly) const
	{
		DBASSERT (whichPoly < 2);
		return overlaps [whichPoly];
	}

	GS_FORCE_INLINE void			SetPolyOverlap (WhichPoly whichPoly, Int32 overlap)
	{
		DBASSERT (whichPoly < 2);
		overlaps [whichPoly] = overlap;
	}

	GS_FORCE_INLINE WhichPoly		GetSelectedPoly () const
	{
		return boolFunction (GetPolyCount (0) > 0, GetPolyCount (1) > 0) ? 0 : None;
	}

	GS_FORCE_INLINE FillingMethod	GetFillingMethod (WhichPoly whichPoly) const
	{
		if (whichPoly == 1) {
			return fillingMethodB;
		} else {
			return fillingMethodA;
		}
	}

	GS_FORCE_INLINE Int32 GetPolyCount (WhichPoly whichPoly) const
	{
		return GetSelectorPolyCount (*this, whichPoly);
	}

#if defined (DEBUG_PGBOOL)
	bool operator == (const BooleanPolygonSelector& other) const;
#endif
};


class PGBooleanOp : public PGBoolean<BooleanPolygonSelector> {
public:

	PGBooleanOp (GS::AbortInterfaceBase* breaker);
	PGRelPolyPosExt DoBoolean (const PGPOLYEXT *poly1, const PGPOLYEXT *poly2, FillingMethod f1, FillingMethod f2,
							   BoolFunctionType boolFunction, bool* isPolyRegular = nullptr, bool withoutHolesIn = false);

	static PGPositionExt SegmentInPoly (const PGPOLYEXT& poly, FillingMethod fMeth, const Sector* sector, const CircleArc* arc, ResultSegmentPos::Et pos,
									    PGRESSECTOREXT* newSectors, GS::Array<CircleArc>* newArcs, GS::AbortInterfaceBase* breaker);


};


class PGBooleanClip;

class ClippingPolygonSelector
{
public:
	struct PolyOverlaps {
		PolygonBoolean::WhichPoly	whichPoly;
		Int32						overlap;

		bool operator == (const PolyOverlaps& rhs) const { return whichPoly == rhs.whichPoly; }

		PolyOverlaps (PolygonBoolean::WhichPoly	whichPoly, Int32 overlap = 0) : whichPoly (whichPoly), overlap (overlap) {}
	};

	class SmallObjAllocWrapper {
	private:
		SmallObjAllocator* alloc;
	public:
		SmallObjAllocWrapper () : alloc (nullptr) {}
		void	SetAlloc (SmallObjAllocator* alloc)				{ DBASSERT (this->alloc == nullptr); this->alloc = alloc; }
		void*	Alloc (UInt32 size) throw ()					{ return alloc->Allocate (size);			}
		void	Free (void* ptr, UInt32 /*reqSize*/) throw ()	{ SmallObjAllocator::Deallocate (ptr);	}
	};

	typedef QXTools::BTree <PolyOverlaps, PolyOverlaps, SmallObjAllocWrapper> TreeType;

private:	
	SmallObjAllocWrapper allocWrapper;
		
	TreeType tree;

	static short CmpPolyOverlaps (const PolyOverlaps& p1, const PolyOverlaps& p2)
	{
		if (p1.whichPoly < p2.whichPoly) {
			return -1;
		} else if (p2.whichPoly < p1.whichPoly) {
			return 1;
		} else {
			return 0;
		}		
	}


public:
	ClippingPolygonSelector ();

	void SetAlloc (SmallObjAllocator* alloc)
	{
		allocWrapper.SetAlloc (alloc);
	}

	GS_FORCE_INLINE void			Reset ()
	{
		tree.RemoveAll ();
	}

	GS_FORCE_INLINE Int32			GetPolyOverlap (PolygonBoolean::WhichPoly whichPoly) const
	{		
		QXTools::BTreePos<PolyOverlaps> pos = tree.Find (PolyOverlaps (whichPoly));
		if (pos != QXTools::BTreeNullPos) {
			return tree [pos].overlap;
		}
		return 0;
	}

	GS_FORCE_INLINE void			SetPolyOverlap (PolygonBoolean::WhichPoly whichPoly, Int32 overlap)
	{
		QXTools::BTreePos<PolyOverlaps> pos = tree.FindNextPos (PolyOverlaps (whichPoly));

		if (pos != QXTools::BTreeNullPos && tree [pos].whichPoly == whichPoly) {
			if (overlap != 0) {
				tree [pos].overlap = overlap;
			} else {
				tree.RemovePos (pos);
			}
		} else {
			if (overlap != 0) {
				tree.InsertBefore (pos, PolyOverlaps (whichPoly, overlap));
			}
		}		
	}

	// return the first poly with >0 overlap
	GS_FORCE_INLINE PolygonBoolean::WhichPoly	GetSelectedPoly () const
	{		
		for (QXTools::BTreePos<PolyOverlaps> pos = tree.NextPos (QXTools::BTreeNullPos); pos != QXTools::BTreeNullPos; pos = tree.NextPos (pos)) {
			if (tree [pos].overlap > 0) {
				return tree [pos].whichPoly;
			}
		}
		return PolygonBoolean::None;
	}

	GS_FORCE_INLINE FillingMethod	GetFillingMethod (PolygonBoolean::WhichPoly /*whichPoly*/) const
	{
		return WindingRulePos;
	}

	GS_FORCE_INLINE Int32 GetPolyCount (WhichPoly whichPoly) const
	{
		return GetSelectorPolyCount (*this, whichPoly);
	}

#if defined (DEBUG_PGBOOL)
	ClippingPolygonSelector (const ClippingPolygonSelector& src);

	bool operator == (const ClippingPolygonSelector& other) const;

	ClippingPolygonSelector& operator = (const ClippingPolygonSelector& src);
#endif
};


class PGBooleanClip : public PGBoolean<ClippingPolygonSelector> {
private:
	friend class ClippingPolygonSelector;

	SmallObjAllocator&		alloc;

public:
	PGBooleanClip (SmallObjAllocator& allocator, GS::AbortInterfaceBase* breaker) : PGBoolean (breaker), alloc (allocator) {}

	void			DoClip (const GS::Array<const PGPOLYEXT *>& polys, PGRESPOLYEXT* newPolygons, ResultPolygonHandling resultPolygonHandling);

	static constexpr MemSize	GetMaxAllocSize () {
		return ClippingPolygonSelector::TreeType::GetMaxAllocSize ();
	}
};

}

#include "PGBooleanImp.hpp"
#include "PGBooleanConversionsImp.hpp"
#include "PGBoolTmp.hpp"
#include "PGBoolTmpConversions.hpp"
#include "FastLogger.hpp"
#include "PGBoolTmpFindContours.hpp"
#include "PGBoolTmpIntersectLinks.hpp"

#endif
