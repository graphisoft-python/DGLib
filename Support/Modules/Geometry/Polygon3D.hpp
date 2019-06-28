/****************************************************************************/
/*																			*/
/*					3D Convex Polygon data and its operations				*/
/* Namespaces:        Contact person:										*/
/*     Geometry          VT													*/
/****************************************************************************/


#if !defined (POLYGON3D_HPP)
#define POLYGON3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Coord3d.h"
#include "Plane.hpp"
#include "Box3DData.h"
#include "PeriodicInterval.hpp"

namespace Geometry {
// return type for the polygon - polygon classification
enum PolygonInPolygonType {
	OutsidePolygon		= 0,
	InsidePolygon		= 1,
	OnPolygon			= 2,
	IntersectingPolygon	= 3
};
// *****************************************************************************
// A simple 3D polygon, with linear edges
// *****************************************************************************
class GEOMETRY_DLL_EXPORT Polygon3D
{
	private:
		GS::PagedArray<Coord3D>		m_pointArray;			// array of polygon points
		mutable Plane				m_polygonPlane;			// plane of the polygon
		mutable bool				m_polygonPlaneValid;	// plane validity flag
	public:
		Polygon3D (void)
				: m_polygonPlaneValid(false)
			{}

			// constructor with three points
		Polygon3D (	const Coord3D& in_po1,
					const Coord3D& in_po2,
					const Coord3D& in_po3)
				: m_polygonPlaneValid(false)
		{
			m_pointArray.SetSize(3);
			m_pointArray[0] = in_po1;
			m_pointArray[1] = in_po2;
			m_pointArray[2] = in_po3;
			CreatePlane ();
		}

		// constructor with four points
		Polygon3D (	const Coord3D& in_po1,
					const Coord3D& in_po2,
					const Coord3D& in_po3,
					const Coord3D& in_po4)
					: m_polygonPlaneValid(false)
		{
			m_pointArray.SetSize(4);
			m_pointArray[0] = in_po1;
			m_pointArray[1] = in_po2;
			m_pointArray[2] = in_po3;
			m_pointArray[3] = in_po4;
			CreatePlane ();
		}

		Polygon3D (const Polygon3D& in_poly)
				:	m_pointArray(in_poly.m_pointArray),
					m_polygonPlane(in_poly.m_polygonPlane),
					m_polygonPlaneValid(in_poly.m_polygonPlaneValid)
		{}

		~Polygon3D ()
		{}

		Polygon3D&  operator= (const Polygon3D& in_poly)
		{
			m_pointArray = in_poly.m_pointArray;
			m_polygonPlane = in_poly.m_polygonPlane;
			m_polygonPlaneValid = in_poly.m_polygonPlaneValid;
			return *this;
		}

		// initializes the polygon
		void  Init (void)
		{
			m_pointArray.Clear ();
			m_polygonPlaneValid = false;
		}
		// ---------------------------------------------------------------------------
		// get the size of the point array

		// get/set the whole point array
		const GS::PagedArray<Coord3D>&	GetPointArray () const	{ return m_pointArray; }
		void							SetPointArray  (const GS::PagedArray<Coord3D>& in_array)
																{ m_pointArray = in_array; m_polygonPlaneValid = false; }
		// performs an inversion on the polygon
		void							Invert (void);

		// gets/set a plane
		const Plane&					GetPlane (void) const				{ return m_polygonPlane; }
		void							setPlane (const Plane& in_plane)	{ m_polygonPlane = in_plane; m_polygonPlaneValid = true;}

		// creates a plane from the points
		bool							CreatePlane (Plane* io_plane = nullptr) const;

		// check whether all points are on the same plane
		bool							AllCoord3DOnPlane (double in_eps = EPS) const;

		// VERTEX operations ---------------------------------------------------------
		// gets/set the point count
		int								GetCoord3DCount (void) const			{ return m_pointArray.GetSize (); }
		void							SetCoord3DCount (Int32 in_count)		{ m_pointArray.SetSize (in_count); }

		// gets/set a point
		const Coord3D&					GetCoord3D (int in_index) const					{ return m_pointArray[in_index]; }
		void							SetCoord3D (Int32 in_index, const Coord3D& in_po){ m_pointArray[in_index] = in_po; }
		void							GetSector3D (Int32 in_index, Sector3D& out_sect) const
		{
			out_sect.c1 = m_pointArray[in_index];
			out_sect.c2 = m_pointArray[(in_index+1)%m_pointArray.GetSize ()];
		}

		// gets a point of the polygon around its perimeter (0...n)
		Coord3D							GetPerimeterPoint (double in_param) const;

		// adds/removes a point
		void							AddCoord3D	(const Coord3D& in_po, double in_eps = EPS);
		void							RemoveCoord3D (Int32 in_index);

		// calculates the area of the polygon
		double							GetArea (void) const;

		//closest point and distance of a point from the edges of the poly
		double							ClosestCoord3D (const Coord3D& in_po,
														Coord3D* out_po = nullptr ) const;
		// calculates the enclosing box
		Box3DType						GetBounds (void)  const;
		Box3DType						GetPlanarBounds (void)  const;

		// conversions from world to plane and back
		Coord3D							WorldToPolygon3DPlane (const Coord3D& in_po) const;
		Coord3D							Polygon3DPlaneToWorld (const Coord3D& in_po) const;

#if defined (DEBUVERS)
		void							ListVRML (	bool full_file = true,
													float r = 1,
													float g = 1,
													float b = 1) const;
#endif
};

}
#endif
