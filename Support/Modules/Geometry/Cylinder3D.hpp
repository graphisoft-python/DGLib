/****************************************************************************/
/*																			*/
/*					3D parametric cylinder surface								*/
/* Namespaces:        Contact person:										*/
/*     Geometry          VT													*/
/****************************************************************************/


#if !defined (CYLINDER3D_HPP)
#define CYLINDER3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Coord3d.h"
#include "Box3DData.h"
#include "Surface3D.hpp"

namespace Geometry {
class Cylinder3D;
//------------------------------------------------------------------------------
// CLASS   : Cylinder3D
//------------------------------------------------------------------------------
// DESCRIPTION :
// The 'Cylinder3D' represents a cylindric surface on a plane
//------------------------------------------------------------------------------
class GEOMETRY_DLL_EXPORT Cylinder3D : public Surface3D
{
	protected :

		double 		m_radius;						// radius of the cylinder
		bool		m_negArc;

	public :
		// constructors, destructor
		Cylinder3D (void);			// default constructor - initializes to a Cartesian coordinate system
		Cylinder3D (double in_radius,
					const Coord3D& in_po,
					const Vector3D& in_z_vect);	// with a base point and a normal
		Cylinder3D (double in_radius,
					const Coord3D& in_po,
					const Vector3D& in_z_vect,
					const Vector3D& in_x_vect);
		Cylinder3D (const Coord3D& inOrigin,	// origin and start and end point
					const Coord3D& inStartPo,
					const Coord3D& inEndPo,
					const Vector3D& in_normal,
					bool			negArc);

		~Cylinder3D (void);

		// ---- member functions ----------------------------------------
		// angle and height intervals
		const PeriodicInterval& GetAngleInterval (void) const;
		void					SetAngleInterval (const PeriodicInterval& in_intval);
		double					GetHeight (void) const;
		void					SetHeight (double in_height);
		bool					IsNegArc (void) const { return m_negArc; };

		void	SetCylinder3D (	double in_radius,
								const Coord3D& in_po,
								const Vector3D& in_z_vect);	// with a base point and a nornmal
		void	SetCylinder3D (double in_radius,
								const Coord3D& in_po,
								const Vector3D& in_z_vect,
								const Vector3D& in_x_vect);  // -"- + X axis
		void	SetCylinder3D (const Coord3D& inOrigin,	// origin and start and end point
								const Coord3D& inStartPo,
								const Coord3D& inEndPo,
								const Vector3D& in_normal,
								bool			inNegArc);

		// -------------------- inherited pure virtual member functions --------------------
		// returns the surface type
		Surface3DType	GetType (void) const override;

		// clones or copies the object
		Surface3D*	Clone (Surface3D* io_object = nullptr) const override;

		// returns he bounding box of the curve segment
		Box3DType	GetBoundBox3D (void) const override;

		// returns the 3D point at the given parameter
		Coord		GetParam (const Coord3D& in_po) const override;

		// returns the 3D point at the given parameter
		Coord3D		GetPoint (const Coord& in_par) const override;

		// returns the first derivative at the given parameter
		Vector3D	GetUDerivative(const Coord& in_par) const override;
		Vector3D	GetVDerivative(const Coord& in_par) const override;

		// returns the second derivative at the given parameter
		Vector3D	GetUUDerivative(const Coord& in_par) const override;
		Vector3D	GetUVDerivative(const Coord& in_par) const override;
		Vector3D	GetVUDerivative(const Coord& in_par) const override;
		Vector3D	GetVVDerivative(const Coord& in_par) const override;

			// -------------------- virtual member functions with default behavior --------------------
		// resets the curve, deletes owned plane if exists
		void		Reset (void) override;

		// projects a bounding polygon to the U,V parametric space of the surface
		// the curved surfaces will use the given 3D chordal tolerance of the resulted polygon
		bool		CreateSurfacePolygon3D (const GS::PagedArray<Coord3D>& inPolygon,
											double inChordDist,
											GS::PagedArray<Coord>* outPolygon) const override;

		// steps on the surface in the given direction, which closes a given angle with
		// the local U derivative on the local touching plane at the surface point
		Coord		StepOnSurface (	const Coord& inParam,
									double inChordDist,
									bool inUAxisRelativeAngle,
									double inAngleRadian = 0.0,
									short* out_err = nullptr) const override;

		// returns the closest 3D point of the curve and its parameter
		bool		ClosestPoint (	const Coord3D& in_coord,
									Coord3D* out_po,
									Coord* out_par = nullptr) const override;

		// returns the intersection of the curve with a surface
		// or returns false if there is no default behavior
		bool		IntCurveSurf (	Curve3D const* in_curve,
									Int32*						out_x_po_count,
									GS::PagedArray<Coord3D>*	out_x_po_array,
									GS::PagedArray<double>*		out_x_t_array = nullptr,
									GS::PagedArray<Coord>*		out_x_par_array = nullptr) const override;

		// returns the intersection of the surface with a surface
		// or returns false if there is no default behavior
		bool		IntSurfSurf (	Surface3D const* in_surf,
									Int32*						out_x_curve_count,
									GS::PagedArray<Curve3D*>*	out_x_curve_array) const override;

};
// Cylinder3D } ---------------------------------------------------------------


}
#endif
