// *********************************************************************************************************************
// Description:		COORDGRAPH class definition from ListSel.c
//
// Module:			QuantityTakeoff
// Namespace:
// Contact person:
//
// SG compatible
// *********************************************************************************************************************

#ifndef COORDGRAPH_HPP
#define COORDGRAPH_HPP

// from GSRoot
#include "Queue.hpp"

// from Geometry
#include "Point2DData.h"
#include "Point2D.hpp"

class CoordGraph {
private:
	// Ellistas tarolas
	typedef struct {
		Coord coord;
		GS::Array<UInt32> edges;
	} Vertex;

	GS::Array<Vertex> vertices;

	// Szelessegi bejarassal megnezzuk, hogy ossze van-e kotve ket pont
	bool IsLinked (UInt32 idx1, UInt32 idx2)
	{
		GS::Queue<UInt32> closed;
		GS::Queue<UInt32> opened;

		opened.Push (idx1);

		while (!opened.IsEmpty ()) {
			UInt32 actIdx = opened.Pop ();
			closed.Push (actIdx);

			for (UInt32 i = 0; i < vertices[actIdx].edges.GetSize (); ++i) {
				if (vertices[actIdx].edges[i] == idx2) {
					return true;
				} else if (!opened.Contains (vertices[actIdx].edges[i]) && !closed.Contains (vertices[actIdx].edges[i])) {
					opened.Push (vertices[actIdx].edges[i]);
				}
			}
		}

		return false;
	}

public:

	void AddEdge (Coord coord1, Coord coord2)
	{
		Int32 idx1 = -1, idx2 = -1;
		for (UInt32 i = 0; i < vertices.GetSize (); ++i) {
			if (Geometry::Dist (coord1, vertices[i].coord) < EPS) {
				idx1 = i;
			}
			if (Geometry::Dist (coord2, vertices[i].coord) < EPS) {
				idx2 = i;
			}
		}

		if (idx1 == -1) {
			vertices.PushNew ();
			Vertex& vertex = vertices.GetLast ();
			vertex.coord = coord1;
			idx1 = vertices.GetSize () - 1;
		}

		if (idx2 == -1) {
			vertices.PushNew ();
			Vertex& vertex = vertices.GetLast ();
			vertex.coord = coord2;
			idx2 = vertices.GetSize () - 1;
		}

		vertices[idx1].edges.Push (idx2);
		vertices[idx2].edges.Push (idx1);
	}

	void GetHolesLength (GS::Array<double>& holesLength)
	{
		GS::Array<UInt32> borderPoints; // Az elsofoku pontokat taroljuk itt, amiket meg nem parositottunk

		for (UInt32 i = 0; i < vertices.GetSize (); ++i) {
			DBASSERT (vertices[i].edges.GetSize () >=1 && vertices[i].edges.GetSize () <= 2);
			if (vertices[i].edges.GetSize () == 1) { // Ha elsofoku pont, akkor az egyik metszet szelenek kell lennie
				bool found = false;
				for (UInt32 j = 0; j < borderPoints.GetSize (); ++j) {
					if (IsLinked (i, borderPoints[j])) {
						holesLength.Push (Geometry::Dist (vertices[i].coord, vertices[borderPoints[j]].coord));
						borderPoints.Delete (j);
						found = true;
						break;
					}
				}
				if (!found) {
					borderPoints.Push (i);
				}
			}
		}

		DBASSERT (borderPoints.IsEmpty ());
	}
};

#endif
