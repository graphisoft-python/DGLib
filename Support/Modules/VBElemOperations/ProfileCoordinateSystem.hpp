// *********************************************************************************************************************
// Description:		Local coordinate system for profiled elems (wall/beam/column)
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	KiP
//
// SG compatible
// *********************************************************************************************************************

#ifndef PROFILECOORDINATESYSTEM_HPP
#define PROFILECOORDINATESYSTEM_HPP

#include "VBElemOperationsExport.hpp"
#include "Plane.hpp"


class VB_ELEM_OPERATIONS_DLL_EXPORT ProfileCoordinateSystem {

public:
	enum CreateFlag {
		IncludeFlip					= 0x0001,
		IncludeRotation				= 0x0002,
		IncludeSlantedDistorsion	= 0x0004,
		UseSlantedProfilePlane		= 0x0008
	};

private:
	UInt32				createFlags;
	Geometry::Plane		plane;
	Coord				curveOrigo;

public:
	ProfileCoordinateSystem ();
	ProfileCoordinateSystem (const ProfileCoordinateSystem& source);
	ProfileCoordinateSystem	(UInt32 _createFlags, const Geometry::Plane& _plane, const Coord& _curveOrigo);
	~ProfileCoordinateSystem ();

	ProfileCoordinateSystem&	operator= (const ProfileCoordinateSystem& source);

	inline	Geometry::Plane		GetPlane () const { return plane; }
	inline	Coord3D				GetOrigo () const { return plane.GetBasePoint (); }
	inline	Vector3D			GetXAxis () const { return plane.GetXAxis (); }
	inline	Vector3D			GetYAxis () const { return plane.GetYAxis (); }
	inline	Vector3D			GetZAxis () const { return plane.GetZAxis (); }
	inline	Coord				GetCurveOrigo () const { return curveOrigo; }

	inline	bool				IsSet (UInt32 flag) const { return (createFlags & flag) == flag; }

	inline	Coord3D				ProfileToWorld (const Coord& profileCoord) const { return plane.PlaneToWorld (profileCoord); }
	inline	Coord3D				ProfileToWorld (double x, double y) const { return ProfileToWorld (Coord (x, y)); }
	inline	Coord3D				WorldToProfile (const Coord3D& worldCoord) const { return plane.WorldToPlane (worldCoord); }
};


#endif // PROFILECOORDINATESYSTEM_HPP
