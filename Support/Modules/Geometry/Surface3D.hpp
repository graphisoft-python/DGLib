// *****************************************************************************
// 3D parametric surface (patch) base class.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          VT
//
// [SG compatible]
// *****************************************************************************

#if !defined (Surface3D_HPP)
#define Surface3D_HPP

#pragma once

#include "PeriodicInterval.hpp"
#include "Coord.h"
#include "Box3DData.h"

namespace Geometry {

// -------------------forward declarations, typedefs --------------------------
class SurfacePlane;
class Surface3D;
class Curve3D;

// *****************************************************************************
// A 3D parametric surface class
// *****************************************************************************
class GEOMETRY_DLL_EXPORT Surface3D  {
protected:
	PeriodicInterval			m_U_interval;		// u1..u2 interval of the surface segment with possible periodicity (2PI or else)
	PeriodicInterval			m_V_interval;		// v1..v2 interval ...
	SurfacePlane*		m_plane;			// optional host plane pointer of the surface (i.e. plane of a Cylinder3D)

public:
	// 3D surface types
	enum Surface3DType {
		Surface3D_ST_UNKNOWN	= 0,
		Surface3D_ST_PLANE		= 1,
		Surface3D_ST_CYLINDER	= 2,
		Surface3D_ST_SPHERE		= 3,
		Surface3D_ST_EXTRUSION	= 4,
		Surface3D_ST_REVOLVED	= 5
	};

	Surface3D				();
	Surface3D				(	const PeriodicInterval& in_U_intval,
								const PeriodicInterval& in_V_intval);
	virtual ~Surface3D	();

		// -------------------- general member functions --------------------
	// bounding parameter handling functions
	const PeriodicInterval& GetUInterval (void) const;
	const PeriodicInterval& GetVInterval (void) const;
	void			SetUInterval (const PeriodicInterval& in_intval);
	void			SetVInterval (const PeriodicInterval& in_intval);

	// interpolate parameter
	Coord InterpolateParameter (const Coord& in_par) const;

	// returns true if the parameter is inside the segment
	bool			ParamInPatch (const Coord& in_par) const;

	// base plane handling functions
	SurfacePlane*	GetSurfacePlane (void) const;
	void			SetSurfacePlane (SurfacePlane* in_surf);

	// base surface <-> world transformations
	// transforms a coordinate/free vector from world to the coordinate system
	// of the plane of the surface
	Coord3D			WorldToSurfCoordSysCoord3D	(const Coord3D& in_coord) const;
	Vector3D		WorldToSurfCoordSysVector3D	(const Vector3D& in_vect) const;

	// transforms a coordinate/free vector from the coordinate system
	// of the plane of the surface to the world
	Coord3D			SurfCoordSysToWorldCoord3D	(const Coord3D& in_coord) const;
	Vector3D		SurfCoordSysToWorldVector3D	(const Vector3D& in_vect) const;

		// -------------------- pure virtual member functions --------------------
	// returns the surface type
	virtual Surface3DType	GetType (void) const = 0;

	// clones or copies the object
	virtual Surface3D*	Clone (Surface3D* io_object = nullptr) const = 0;

	// returns he bounding box of the curve segment
	virtual Box3DType	GetBoundBox3D (void) const = 0;

	// returns the parameter for a given 3D point
	virtual Coord		GetParam (const Coord3D& in_po) const = 0;

	// returns the 3D point at the given parameter
	virtual Coord3D		GetPoint (const Coord& in_par) const = 0;

	// returns the first derivative at the given parameter
	virtual Vector3D	GetUDerivative(const Coord& in_par) const = 0;
	virtual Vector3D	GetVDerivative(const Coord& in_par) const = 0;

	// returns the second derivative at the given parameter
	virtual Vector3D	GetUUDerivative(const Coord& in_par) const = 0;
	virtual Vector3D	GetUVDerivative(const Coord& in_par) const = 0;
	virtual Vector3D	GetVUDerivative(const Coord& in_par) const = 0;
	virtual Vector3D	GetVVDerivative(const Coord& in_par) const = 0;

		// -------------------- virtual member functions with default behavior --------------------
	// resets the surface deletes owned plane if exists
	virtual void		Reset (void);

	// projects a bounding polygon to the U,V parametric space of the surface
	// the curved surfaces will use the given 3D chordal tolerance of the resulted polygon
	virtual bool		CreateSurfacePolygon3D (const GS::PagedArray<Coord3D>& inPolygon,
												double inChordDist,
												GS::PagedArray<Coord>* outPolygon) const;

	// test a point to a given bounding polygon on the surface and returns false if OUT, true if IN,
	// and sets the 'outOnPoly' flag to true if the point is on the surface
	virtual bool		PointInSurfacePolygon3D (const Coord3D& inPoint,
												 const GS::PagedArray<Coord3D>& inPolygon,
												 double inChordDist,
												 bool* outOnPoly) const;

	// steps on the surface in the given direction, which closes a given angle with
	// the local U derivative on the local touching plane at the surface point
	virtual Coord		StepOnSurface (	const Coord& inParam,
										double inChordDist,
										bool inUAxisRelativeAngle = true,
										double inAngleRadian = 0.0,
										short* out_err = nullptr) const;

	// returns the closest 3D point of the curve and its parameter
	virtual bool		ClosestPoint (	const Coord3D& in_coord,
										Coord3D* out_po,
										Coord* out_par = nullptr) const;

	// returns the intersection of the curve with a surface
	// or returns false if there is no default behavior
	virtual bool		IntCurveSurf (	Curve3D const* in_curve,
										Int32*						out_x_po_count,
										GS::PagedArray<Coord3D>*	out_x_po_array,
										GS::PagedArray<double>*		out_x_t_array = nullptr,
										GS::PagedArray<Coord>*		out_x_par_array = nullptr) const;

	// returns the intersection of the surface with a surface
	// or returns false if there is no default behavior
	virtual bool		IntSurfSurf (	Surface3D const* in_surf,
										Int32*						out_x_curve_count,
										GS::PagedArray<Curve3D*>*	out_x_curve_array) const;
};
// ------------------------------ typedefs --------------------------------------------------
typedef Surface3D* Surface3DPtr;
typedef Surface3D const* Surface3DConstPtr;


//   --------------------------------- function prototypes ----------------------------------
// returns the intersection curves of a surface to surface inersection
GEOMETRY_DLL_EXPORT Int32 IntSurfSurf (	Surface3D const*			in_surf1,
										Surface3D const*			in_surf2,
										Int32*						out_x_curve_count,
										GS::PagedArray<Curve3D*>*	out_x_curve_array);

// returns the intersection curves of a surface to surface inersection
GEOMETRY_DLL_EXPORT Int32 IntCurveSurf (	Curve3D const* in_curve,
										Int32*						out_x_po_count,
										GS::PagedArray<Coord3D>*	out_x_po_array,
										GS::PagedArray<double>*		out_x_t_array = nullptr,
										GS::PagedArray<Coord>*		out_x_par_array = nullptr);

}

#endif
