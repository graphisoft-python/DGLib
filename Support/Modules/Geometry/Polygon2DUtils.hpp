// *****************************************************************************
//
// Utility function(s) for Polygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	MA
//
// *****************************************************************************

#ifndef GEOMETRY_POLYGON2DUTILS_HPP
#define GEOMETRY_POLYGON2DUTILS_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Coord.h"
#include "GenArc2DData.h"
#include "Sector2DData.h"
#include "Point2DData.h"
#include "Poly2DTypes.hpp"

struct Circle;

namespace Geometry {

class GEOMETRY_DLL_EXPORT Polygon2DCanonization {
	struct MyPair;
public:
	static void CanonizePolyByRotationAndSwap (const GS::Array<Coord>& irrVertices, const GS::Array<UIndex>& irrContourEnds, Geometry::Polygon2D& poly);
};

GEOMETRY_DLL_EXPORT
GenArc	ProjectPolygon2DToCircle (const Polygon2D& polygon, const Circle& projectionCircle);


template<typename PolyType>
void	GetExtremePointsOfPolys (const GS::Array<PolyType> polys, const Vector& direction, GS::Array<Coord>& minima, GS::Array<Coord>& maxima)
{
	typedef typename PolyType::ConstVertexIterator ConstVertexIterator;
	typedef typename PolyType::ConstEdgeIterator ConstEdgeIterator;

	GS::Array<Coord> possibleExtremePoints;

	GenArc arc;
	Sector dummySector;
	for (const PolyType& poly : polys) {
		for (ConstVertexIterator vertexIt = poly.BeginVertex (); vertexIt != poly.EndVertex (); ++vertexIt) {
			possibleExtremePoints.Push (vertexIt->GetCoord ());
		}
		for (ConstEdgeIterator edgeIt = poly.BeginEdge (); edgeIt != poly.EndEdge (); ++edgeIt) {
			if (!edgeIt->IsStraight ()) {
				edgeIt->GetSector (dummySector, arc);
				GS::Array<Coord> arcExtremePointsInDirection;
				GetTangentPointsByDirection (arc, direction, arcExtremePointsInDirection);
				possibleExtremePoints.Append (arcExtremePointsInDirection);
			}
		}
	}
	
	GetExtremePointsOfPointSetByDir (possibleExtremePoints, direction, minima, maxima);
}

} // namespace Geometry

#endif