// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLEANIMP_H
#define PGBOOLEANIMP_H

namespace PolygonBoolean {

template <class PolygonSelector>
PGBoolean<PolygonSelector>::PGBoolean (GS::AbortInterfaceBase* breakerIn) :
	stage (0),
	withoutHoles (false),
	isSameDirEdgeLegal (true),
	containsArc (false),
	force64BitPrecision (false),
	isBSplitLine (false),
	polyPosition (false),
	origBBSide (0.0),
	origBBOffset (SetCoord (0.0, 0.0)),
	b64BitPrecision (true),
	isPolyRegular (nullptr),
	resultPolygonHandling (SkipSmallPolygons),
	polygonSelector (),
	breaker (breakerIn),
	pgBoolean32 (this),
	pgBoolean64 (this)
{
	InitBox (&boundBox);
}

template <class PolygonSelector>
PGBoolean<PolygonSelector>::~PGBoolean ()
{
}

template <class PolygonSelector>
void PGBoolean<PolygonSelector>::Reinitialize ()
{
	stage = 0;
	polyEdges.Clear ();
	polyEdgeOffsets.Clear ();

	pgBoolean32.Reinitialize ();
	pgBoolean64.Reinitialize ();
}


template <class PolygonSelector>
PGRelPolyPosExt PGBoolean<PolygonSelector>::DoOperationStages (bool allStages)
{
	if (stage == 1) {
		Box2DData boundBoxA, boundBoxB;

		boundBox = boundBoxA = GetBoundBox (0);
		double pgEps = origPolys [0]->epsilon;

		for (UInt32 i = 1; i < origPolys.GetSize (); ++i) {
			pgEps = GS::Min (pgEps, origPolys [i]->epsilon);
			Box2DData tempBox = GetBoundBox (i);
			UnionBox (&tempBox, &boundBox);
			if (i == 1) {
				boundBoxB = tempBox;
			}
		}

		stage++;

		pgEps = GS::Max (pgEps, SmallEps);
		if (!allStages && (origPolys.GetSize () < 2 || !IsBoxesIntersect (boundBoxA, boundBoxB, Boundary_Closed, pgEps)))
			return PolysDisjunct;
	}

	if (stage == 2) {
		Box2DData bbox = boundBox;

		for (UInt32 i = 0; i < origPolys.GetSize (); ++i) {
			AddArcCenters (&bbox, i);
		}

		boundBox = bbox;

		double pgEps = origPolys [0]->epsilon;
		for (UInt32 i = 1; i < origPolys.GetSize (); ++i) {
			pgEps = GS::Min (pgEps, origPolys [i]->epsilon);
		}
		pgEps = GS::Max (pgEps, SmallEps);


		origBBSide = GS::Max (GS::Max (bbox.xMax - bbox.xMin, bbox.yMax - bbox.yMin), pgEps * 8);
		origBBOffset.x = bbox.xMin;
		origBBOffset.y = bbox.yMin;

		b64BitPrecision = force64BitPrecision || containsArc ||
			double (SDoubleInt32::maxCoordVal - SDoubleInt32::minCoordVal) / (10 * SDoubleInt32::minSnapDist) < origBBSide / pgEps;

		stage++;
	}

	try {
		return b64BitPrecision ? pgBoolean64.DoOperationStages (allStages) : pgBoolean32.DoOperationStages (allStages);
	}
	catch (const GeometryAlgorithmErrorException&) {
		if (b64BitPrecision)
			throw;
		pgBoolean32.Reinitialize ();
		b64BitPrecision = true;
		stage = 3;
		return pgBoolean64.DoOperationStages (allStages);
	}
}

template <class PolygonSelector>
void PGBoolean<PolygonSelector>::GetResultPolygons (PGRESPOLYEXT* newPolygons)
{
	try {
		if (stage == 0)
			return;

		DoOperationStages (true);

		if (b64BitPrecision)
			pgBoolean64.GetResultPolygons (newPolygons);
		else {
			try {
				pgBoolean32.GetResultPolygons (newPolygons);
			}
			catch (const GeometryAlgorithmErrorException&) {
				pgBoolean32.Reinitialize ();
				b64BitPrecision = true;
				stage = 3;
				DoOperationStages (true);
				pgBoolean64.GetResultPolygons (newPolygons);
			}
		}
	}
	catch (const GS::AbortException&)
	{
		Reinitialize ();
		throw;
	}	
	catch (const GS::Exception&)
	{
		DBBREAK ();
#if defined (DEBUVERS_RJ) || defined (DEBUVERS_HK)
		PrintReport ("", UnknownStatus, dbChannel);
#endif
		Reinitialize ();
		throw;
	}
}


} // namespace

#endif