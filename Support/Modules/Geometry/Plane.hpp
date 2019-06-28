/****************************************************************************/
/*																			*/
/*					3D plane surface										*/
/* Namespaces:        Contact person:										*/
/*     Geometry          VT													*/
/****************************************************************************/


#if !defined (PLANE_HPP)
#define PLANE_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Coord.h"
#include "Coord3d.h"
#include "Plane3DData.h"
#include "Box3DData.h"
#include "Surface3D.hpp"

struct HalfPlane2DData;
namespace Geometry {

template<USize RowCount, USize ColumnCount, class ElementType> class Matrix;
typedef	Matrix<4, 4, double>	Matrix44d;

//------------------------------------------------------------------------------
// CLASS   : Plane
//------------------------------------------------------------------------------
// DESCRIPTION :
// The 'Plane' represents a 3D Plane with a base point and X, Y Z axis vectors
// Useful as a coordinate system
//------------------------------------------------------------------------------
class GEOMETRY_DLL_EXPORT Plane
{
		Coord3D		m_basePoint;						// base point of the plane
		Vector3D	m_X_axis, m_Y_axis, m_Z_axis;		// axes ...
		Vector3D	m_InvX, m_InvY, m_InvZ;				// for WorldToPlane conversion (inverse matrix columns)

		void CalcOrthonormalInverse ();
		void CalcInverse ();

	public :
		// constructors create orthonormal coordinate frames (see InitPlane, SetPlane)
		Plane (void);
		explicit Plane (const Coord3D& in_po);
		explicit Plane (double z);
		Plane (const Coord3D& in_po, const Vector3D& in_z_vect);
		Plane (const Coord3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect);
		Plane (const Coord3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect, const Vector3D& in_y_vect);
		Plane (const PlaneEq& in_plane);
		Plane (const double a, const double b, const double c, const double d);
		explicit Plane (const TRANMAT& tr);

		// ---- member functions ----------------------------------------
		// access functions
		const Coord3D&	GetBasePoint (void)  const				{ return m_basePoint; }
		void			SetBasePoint (const Coord3D& in_po)		{ m_basePoint = in_po; }
		const Vector3D&	GetXAxis (void) const					{ return m_X_axis; }
		const Vector3D&	GetYAxis (void) const					{ return m_Y_axis; }
		const Vector3D&	GetZAxis (void) const					{ return m_Z_axis; }
		Vector3D		GetNormalVector (void) const			{ return m_X_axis ^ m_Y_axis; }

		// functions for creating orthonormal coordinate frame:
		void	InitPlane (void);
		void	SetPlane (const Coord3D& in_po, const Vector3D& in_z_vect);	// with a base point and a normal
		void	SetPlane (const Coord3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect);  // -"- + X axis
		void	SetPlane (const Coord3D& in_po, const Vector3D& in_z_vect, const Vector3D& in_x_vect, const Vector3D& in_y_vect);
		void	SetPlane (const TRANMAT& tr);

		// create general x-y coordinate frame (though x-y-z is always counterclockwise):
		void	SetPlaneXY (const Coord3D& base, const Vector3D& x, const Vector3D& y);

		// if plane is not vertical (its normal is not in the global X-Y plane), then these functions create a coordinate frame
		// in which each point's two coordinates are the same as the point's first two coordinates in the global 3D space:
		void	SetPlaneEq (const PlaneEq& in_plane);
		void	SetUpHorPlane (double z);
		void	SetUpPlane2D3DTransf (const Coord3D& c, const Vector3D& n);

		void	Transform (const TRANMAT& tran);
		void	InverseTransformWTrafo (const Matrix44d& trafo);
		void	InverseTransformWTransposedTrafo (const Matrix44d& transposedTrafo);

		PlaneEq	GetPlaneEq (void) const;
		TRANMAT	ToTranMat (void) const;
		TRANMAT	InvToTranMat (void) const;

		// tests if the planes are parallel
		bool IsParallelPlane (const Plane& in_plane) const;

		// tests if the planes are coplanar
		bool IsCoplanarPlane (const Plane& in_plane) const;

		// tests if the point is on the plane
		bool IsPlaneCoord3D (const Coord3D& in_po) const;

		double DistFromPlane (const Coord3D& point) const;

		// conversions from world to plane and back
		Coord3D		WorldToPlane	(const Coord3D& in_po) const;
		Vector3D	WorldToPlaneV	(const Vector3D& in_ve) const;
		Vector3D	WorldToPlaneCv	(const Vector3D& in_ve) const;
		Coord3D		PlaneToWorld	(const Coord3D& in_po) const;
		Vector3D	PlaneToWorldV	(const Vector3D& in_ve) const;
		Vector3D	PlaneToWorldCv	(const Vector3D& in_ve) const;
		Coord3D		PlaneToWorld	(const Coord& in_po) const;
		Vector3D	PlaneToWorldV	(const Vector& in_po) const;
		Coord3D		PlaneToWorld	(double x, double y) const;
		Vector3D	PlaneToWorldV	(double x, double y) const;
		Coord3D		PlaneToWorld	(double x, double y, double z) const;
		Vector3D	PlaneToWorldV	(double x, double y, double z) const;
		Vector3D	PlaneToWorldCv	(double x, double y, double z) const;

		Coord3D ProjectToPlane (const Coord3D& c) const;
		Vector3D ProjectToPlaneV (const Vector3D& v) const; 
		bool ProjectToPlaneAlongZ (const Coord3D& c, Coord3D& out_c) const;
		
		static Coord3D ProjectToPlane (const Coord3D& coord, const Vector3D& planeNormal, const Coord3D& planePoint);

		GSErrCode QuickRead (GS::IChannel& ic);
		GSErrCode QuickWrite (GS::OChannel& oc) const;

		GSErrCode ReadXML (GS::XMLIChannel& ic, const char* tagName = nullptr);
		GSErrCode WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const;
};
// Plane } ---------------------------------------------------------------

// ------------------------------ typedefs --------------------------------------------------
typedef Plane* PlanePtr;
typedef Plane const* PlaneConstPtr;

//------------------------------------------------------------------------------
// Function		: CalcCutLineFromPlanes()
// Description  : calculates the cutLine which corresponds to a cutPlane on the selected plane
// Input        : const Plane&		plane
//				: const Plane&		cutPlane
// Output       : HalfPlane2DData&	cutLine
// Returns      : false, if the cutPlane is parallel with the selected plane
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool CalcCutLineFromPlanes (const Plane& plane, const Plane& cutPlane, HalfPlane2DData& cutLine);

//------------------------------------------------------------------------------
// Function		: XSector3DPlane()
// Description  : intersects a plane with a sector
// Input        : const Sector3D& 	s
//				: const Geometry::Plane&		p
// Output       : Coord3D& x_po, double* tRes
// Returns      : bool xsect
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool XSector3DPlane (const Sector3D& 	s, const Geometry::Plane&	p, Coord3D& x_po, double* tRes = nullptr);

//------------------------------------------------------------------------------
// Function		: XPlanes()
// Description  : intersects two planes
// Input        : const Geometry::Plane&		p1
//				: const Geometry::Plane&		p2
// Output       : Sector3D	*s
// Returns      : bool xsect
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool XPlanes (const Geometry::Plane&		plane1,
								  const Geometry::Plane&		plane2,
								  Sector3D*						s);

//------------------------------------------------------------------------------
// Function		: X3Planes()
// Description  : intersects three planes
// Input        : const Geometry::Plane&		p1
//				: const Geometry::Plane&		p2
//				: const Geometry::Plane&		p3
// Output       : Coord3D	*p
// Returns      : bool xsect
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool X3Planes (const Geometry::Plane&		plane1,
	const Geometry::Plane&		plane2,
	const Geometry::Plane&		plane3,
	Coord3D*						p);



//------------------------------------------------------------------------------
// Function		: CreatePlane()
// Description  : creates a plane from the points
// Input        : const GS::PagedArray<Coord3D>& in_pointArray
// Output       : Geometry::Plane& out_p
// Returns      : returns true if all points are coplanar
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool	GEOM_CALL	CreatePlane (
											const GS::PagedArray<Coord3D>& in_pointArray,
											Geometry::Plane& out_p);

//------------------------------------------------------------------------------
// function		: GetRegressionPlane ()
// Description  : creates the regression plane to the given points if possible
// Input        : const GS:PagedArray<Coord3D>& points
// Output       : Geometry::Plane& plane - resulted plane
// Returns      : bool status - true if the plane is created
//------------------------------------------------------------------------------
GEOMETRY_DLL_EXPORT bool	GEOM_CALL	GetRegressionPlane (
											const GS::PagedArray<Coord3D>&	points,
											Geometry::Plane& plane);

GEOMETRY_DLL_EXPORT Coord	GEOM_CALL	PlaneCoordStrict (const Coord3D& p, const Plane& plane);

GEOMETRY_DLL_EXPORT bool	GEOM_CALL	AreSamePlanes (const Geometry::Plane& plane1, const Geometry::Plane& plane2);

} // namespace Geometry

#endif
