// *****************************************************************************
// 3D parametric curve base class.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          VT
//
// [SG compatible]
// *****************************************************************************

#if !defined (CURVE3D_HPP)
#define CURVE3D_HPP

#pragma once

#include "PeriodicInterval.hpp"
#include "Coord.h"
#include "Box3DData.h"

namespace Geometry {


// -------------------forward declarations, typedefs --------------------------
class SurfacePlane;
typedef SurfacePlane* SurfacePlanePtr;
typedef SurfacePlane const* SurfacePlaneConstPtr;
class Surface3D;

// *****************************************************************************
// A 3D parametric curve segment class
// *****************************************************************************
class GEOMETRY_DLL_EXPORT Curve3D  {

protected:
	PeriodicInterval			m_interval;		// t1..t2 interval of the curve segmment with possible periodicity (2PI or else)
	SurfacePlane*		m_plane;		// optional host plane pointer of the curve

public:
	// ------------------------- constants, enums ---------------------------------
	// 3D curve types
	enum Curve3DType {
		CT_UNKNOWN	= 0,
		CT_LINE		= 1,
		CT_ARC		= 2
	};

	Curve3D				();
	Curve3D				(const PeriodicInterval& in_intval);
	virtual ~Curve3D	();

		// -------------------- general member functions --------------------
	// bounding parameter handling functions
	const PeriodicInterval& GetInterval (void) const;
	void			SetInterval (const PeriodicInterval& in_intval);

	// returns true if the parameter is inside the segment
	bool			ParamInSegment (double in_t) const;

	// returns the interpolated 3D parameter of the curve
	double			InterpolateParameter (double in_t) const;

	// base plane handling functions
	SurfacePlane*	GetSurfacePlane	(void) const;
	void			SetSurfacePlane	(SurfacePlane* in_surf);

	// base surface <-> world transformations
	// transforms a coordinate/free vector from world to the coordinate system
	// of the plane of the surface
	Coord3D			WorldToCurveCoordSysCoord3D		(const Coord3D& in_coord) const;
	Vector3D		WorldToCurveCoordSysVector3D	(const Vector3D& in_vect) const;

	// transforms a coordinate/free vector from the coordinate system
	// of the plane of the surface to the world
	Coord3D			CurveCoordSysToWorldCoord3D		(const Coord3D& in_coord) const;
	Vector3D		CurveCoordSysToWorldVector3D	(const Vector3D& in_vect) const;

		// -------------------- pure virtual member functions --------------------
	// returns the curve type
	virtual Curve3DType	GetType (void) const = 0;

	// clones or copies the object
	virtual Curve3D*	Clone (Curve3D* io_object = nullptr) const = 0;

	// returns he bounding box of the curve segment
	virtual Box3DType	GetBoundBox3D (void) const = 0;

	// returns the six bounding parameters of the the curve in 3D or on the plane
	// bottom X, bottom Y, bottom Z, top X, top Y, top Z
	virtual bool GetBoundParams (	double*			out_params,
									SurfacePlaneConstPtr in_plane = nullptr) const;

	// returns the 3D point at the given parameter
	virtual Coord3D		GetPoint (double in_t) const = 0;

	// returns the first derivative at the given parameter
	virtual Vector3D	GetFirstDerivative(double in_t) const = 0;

	// returns the second derivative at the given parameter
	virtual Vector3D	GetSecondDerivative(double in_t) const = 0;

		// -------------------- virtual member functions with default behaviour --------------------
	// resets the curve, deletes owned plane if exists
	void				Reset (void);

	// returns the closest 3D point of the curve and its parameter
	virtual bool ClosestPoint (Coord3D* out_po, double* out_t = nullptr) const;

	// returns the intersection of the curve with the other curve
	// or returns false if there is no default behavoiur
	virtual bool IntCurveCurve (Curve3D const* in_curve,
								Int32*						out_x_po_count,
								GS::PagedArray<Coord3D>*	out_x_po_array,
								GS::PagedArray<double>*		out_x_t1_array = nullptr,
								GS::PagedArray<double>*		out_x_t2_array = nullptr) const;

	// returns the intersection of the curve with a surface
	// or returns false if there is no default behavoiur
	virtual bool IntCurveSurf (	Surface3D const* in_surf,
								Int32*						out_x_po_count,
								GS::PagedArray<Coord3D>*	out_x_po_array,
								GS::PagedArray<double>*		out_x_t_array	= nullptr,
								GS::PagedArray<Coord>*		out_x_par_array = nullptr) const;
};

// ------------------------------ typedefs --------------------------------------------------
typedef Curve3D* Curve3DPtr;
typedef Curve3D const* Curve3DConstPtr;

//   --------------------------------- function prototypes ----------------------------------
// returns the intersection curves of a surface to surface inersection
GEOMETRY_DLL_EXPORT Int32 IntCurveCurve (Curve3D const* in_curve1,
										Curve3D const* in_curve2,
										Int32*						out_x_po_count,
										GS::PagedArray<Coord3D>*	out_x_po_array,
										GS::PagedArray<double>*		out_x_t1_array = nullptr,
										GS::PagedArray<double>*		out_x_t2_array = nullptr);

}

#endif
