// *********************************************************************************************************************
// Description:		RailingGeometryUtils
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	TZ
//
// SG compatible
// *********************************************************************************************************************

#if !defined _RAILING_GEOMETRY_UTILS_HPP_
#define _RAILING_GEOMETRY_UTILS_HPP_

#pragma once

// from GSRoot
#include "Array.hpp"

// from Geometry
#include "Polyline25D.hpp"

// VBElemOperations
#include "VBElemOperationsExport.hpp"


namespace VBCalculations {
namespace Railing {

VB_ELEM_OPERATIONS_DLL_EXPORT
GS::Array<GS::Pair<double, double>>		GetAbsAnglesRadii (const Geometry::Polyline25D& polyLine25D);
VB_ELEM_OPERATIONS_DLL_EXPORT
GS::Array<UInt32>						GetDivCounts (const GS::Array<GS::Pair<double, double>>& absAnglesRadii);
VB_ELEM_OPERATIONS_DLL_EXPORT
void									ConvertPolylineToSegments (const Geometry::Polyline25D& polyLine25D, const GS::Array<UInt32>& divCounts, GS::Array<Coord3D>* segments);

template <typename T>
static T	Sum (const GS::Array<T>& elements)
{
	T sum = T ();
	for (auto it = elements.Enumerate (); it != nullptr; ++it) {
		sum += *it;
	}
	return sum;
}

}	// namespace Railing
}	// namespace VBCalculations

#endif	// _RAILING_GEOMETRY_UTILS_HPP_
