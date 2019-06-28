// *****************************************************************************
//
// Utility function(s) for IrregularPolygon2D class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	MAM
//
// *****************************************************************************

#ifndef GEOMETRY_IRREGULARPOLYGON2DOPERATIONS_HPP_
#define GEOMETRY_IRREGULARPOLYGON2DOPERATIONS_HPP_

namespace Geometry {

GEOMETRY_DLL_EXPORT
Sector	ProjectIrregularPolygon2DToLine (const IrregularPolygon2D& polygon, const Sector& projectionLine);

GEOMETRY_DLL_EXPORT
GS::Array<Coord>	GetIrregularPolygon2DAndLineIntersections (const Geometry::IrregularPolygon2D& polygon, const Coord& lineCoord, const Vector& lineDirection);

GEOMETRY_DLL_EXPORT
GS::Array<Coord>	GetIrregularPolygon2DAndHalfLineIntersections (const Geometry::IrregularPolygon2D& polygon, const Coord& halfLineBegCoord, const Vector& halfLineDirection);
	
}		// namespace Geometry

#endif		// GEOMETRY_IRREGULARPOLYGON2DOPERATIONS_HPP_