/****************************************************************************/
/*																			*/
/*					3D parametric line curve								*/
/* Namespaces:        Contact person:										*/
/*     Geometry          VT													*/
/****************************************************************************/


#if !defined (Line3D_HPP)
#define Line3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Coord3d.h"
#include "Box3DData.h"
#include "Curve3D.hpp"

namespace Geometry {
class Line3D;
//------------------------------------------------------------------------------
// CLASS   : Line3D
//------------------------------------------------------------------------------
// DESCRIPTION :
// The 'Line3D' represents a 3D libe with a base point direction vector
//------------------------------------------------------------------------------
class GEOMETRY_DLL_EXPORT Line3D : public Curve3D
{
	protected :

		Coord3D		m_basePoint;		// base point of the line
		Vector3D	m_direction;		// direction vector

	public :
		// constructors, destructor
		Line3D (void);			// default constructor
		Line3D (const Coord3D& in_po1, const Coord3D& in_po2);	// with two poitns
		~Line3D (void);

		// ---- member functions ----------------------------------------
		// accessor functions
		const Coord3D&	GetBasePoint (void)  const				{ return m_basePoint; }
		void			SetBasePoint (const Coord3D& in_po)		{ m_basePoint = in_po; }
		const Vector3D&	GetDirection (void) const				{ return m_direction; }
		void			SetDirection (const Vector3D& in_vect)	{ m_direction = in_vect; }

		void	SetLine3D (const Coord3D& in_po1, const Coord3D& in_po2);	// with a base point and an endpoint


		// -------------------- inherited pure virtual member functions --------------------
		// returns the surface type
		Curve3DType	GetType (void) const override;

		// clones or copies the object
		Curve3D*	Clone (Curve3D* io_object = nullptr) const override;

		// returns he bounding box of the curve segment
		Box3DType	GetBoundBox3D (void) const override;

		// returns the 3D point at the given parameter
		Coord3D		GetPoint (double in_t) const override;

		// returns the first derivative at the given parameter
		Vector3D	GetFirstDerivative(double in_t) const override;
		Vector3D	GetSecondDerivative(double in_t) const override;

			// -------------------- virtual member functions with default behaviour --------------------
		// resets the curve, deletes owned plane if exists
		void		Reset (void);

		// returns the closest 3D point of the curve and its parameter
		bool		ClosestPoint (	const Coord3D& in_coord,
									Coord3D* out_po,
									double* out_t = nullptr) const;

		// returns the intersection of the curve with a surface
		// or returns false if there is no default behavoiur
		bool		IntCurveCurve (	Curve3D const* in_curve,
									Int32*						out_x_po_count,
									GS::PagedArray<Coord3D>*	out_x_po_array,
									GS::PagedArray<double>*		out_x_t1_array = nullptr,
									GS::PagedArray<double>*		out_x_t2_array = nullptr) const override;

		// returns the intersection of the surface with a surface
		// or returns false if there is no default behavoiur
		bool		IntCurveSurf (	Surface3D const* in_surf,
									Int32*						out_x_po_count,
									GS::PagedArray<Coord3D>*	out_x_po_array,
									GS::PagedArray<double>*		out_x_t_array = nullptr,
									GS::PagedArray<Coord>*		out_x_par_array = nullptr) const override;

		Coord3D		ProjectToLine (const Coord3D& coord) const;

		static Coord3D ProjectToLine (const Coord3D& coord, const Vector3D& lineDir, const Coord3D& linePoint);

		double		DistFromLine (const Coord3D& point) const;
};
// Line3D } ---------------------------------------------------------------

}
#endif
