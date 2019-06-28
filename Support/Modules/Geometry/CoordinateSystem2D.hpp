// contact person : KiP

#ifndef COORDINATE_SYSTEM_2D_HPP
#define COORDINATE_SYSTEM_2D_HPP

#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "Matrix23.hpp"

// =====================================================================================================================

namespace Geometry {


DECLARE_EXCEPTION_CLASS (SingularCoordinateSystemException, GeometryException, Error, GEOMETRY_DLL_EXPORT)


class GEOMETRY_DLL_EXPORT CoordinateSystem2D
{
public:
	static CoordinateSystem2D CreateGlobal ();
	static CoordinateSystem2D CreateOrthonormalized (const Coord& origo, double xAxisAngle);
	static CoordinateSystem2D CreateOrthonormalized (const Coord& origo, const Vector& xAxis)					CAN_THROW (SingularCoordinateSystemException);
	static CoordinateSystem2D CreateGeneral (const Coord& origo, const Vector& xAxis, const Vector& yAxis)		CAN_THROW (SingularCoordinateSystemException);

	const Coord&	GetOrigo () const;
	const Vector&	GetXAxis () const;
	const Vector&	GetYAxis () const;

	Coord	LocalToGlobal (const Coord& localCoord) const;
	Coord	GlobalToLocal (const Coord& globalCoord) const;

private:
	Coord origo;
	Vector xAxis;
	Vector yAxis;

	Geometry::Matrix23 localToGlobal;
	Geometry::Matrix23 globalToLocal;

	void InitMatrices ();
};

}
#endif
