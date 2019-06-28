// Contact person : KiP

#ifndef PROFILE_TO_CUSTOMPLANE_TRANSFORMER_HPP
#define PROFILE_TO_CUSTOMPLANE_TRANSFORMER_HPP

#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "Matrix23.hpp"
#include "Plane.hpp"

// from VBElements
#include "BeamTypes.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

namespace VBEO {

class VB_ELEM_OPERATIONS_DLL_EXPORT ProfileToCustomPlaneTransformer
{
public:
	enum ProfileTrafoInclusion
	{
		IncludeProfileTrafo,
		OmitProfileTrafo
	};

	static ProfileToCustomPlaneTransformer	CreateForBeam (const VBElem::BeamConstRef& beam, 
														   double refLinePointParam /*[0, 1]*/,
														   ProfileTrafoInclusion profileTrafoInclusion,
														   const GS::Optional<Vector3D>& customPlaneNormal = GS::NoValue /*useable only for straight beams*/);
	
	static ProfileToCustomPlaneTransformer	CreateForColumn (const VBElem::ColumnConstRef& column, 
															 double refLinePointParam /*[0, 1]*/, 
															 ProfileTrafoInclusion profileTrafoInclusion, 
															 const GS::Optional<Vector3D>& customPlaneNormal = GS::NoValue /*useable only for straight columns*/);	
	
	static ProfileToCustomPlaneTransformer	CreateForWall (const VBElem::WallConstRef& wall, 
														   double refLinePointParam /*[0, 1]*/, 
														   ProfileTrafoInclusion profileTrafoInclusion,
														   const GS::Optional<Vector3D>& customPlaneNormal = GS::NoValue /*useable only for straight walls*/);

	static ProfileToCustomPlaneTransformer	CreateForBeamBeginPlane		(const VBElem::BeamConstRef& beam, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);
	static ProfileToCustomPlaneTransformer	CreateForBeamEndPlane		(const VBElem::BeamConstRef& beam, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);
	static ProfileToCustomPlaneTransformer	CreateForColumnTopPlane		(const VBElem::ColumnConstRef& column, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);
	static ProfileToCustomPlaneTransformer	CreateForColumnBottomPlane	(const VBElem::ColumnConstRef& column, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);
	static ProfileToCustomPlaneTransformer	CreateForColumnCutPlane		(const VBElem::ColumnConstRef& column, double refLinePointParam /*[0, 1]*/, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);
	static ProfileToCustomPlaneTransformer	CreateForWallBeginPlane		(const VBElem::WallConstRef& wall, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);
	static ProfileToCustomPlaneTransformer	CreateForWallEndPlane		(const VBElem::WallConstRef& wall, ProfileTrafoInclusion profileTrafoInclusion = IncludeProfileTrafo);

	Coord3D		ProfileToCustomPlane (const Coord& coordInProfile) const;
	Sector3D	ProfileToCustomPlane (const Sector& sectorInProfile) const;
	Vector3D	ProfileToCustomPlane (const Vector& vectorInProfile) const;

	Coord		CustomPlaneToProfile (const Coord3D& coordOnCustomPlane) const;
	Sector		CustomPlaneToProfile (const Sector3D& sectorOnCustomPlane) const;
	Vector		CustomPlaneToProfile_V (const Vector3D& vectorOnCustomPlane) const;

	Coord3D		GetCustomPlaneBasePoint () const;
	Vector3D	GetCustomPlaneNormal () const;

private:
	Geometry::Matrix23 profileTrafo;
	Geometry::Matrix23 invProfileTrafo;
	Geometry::Plane verticalPlane;
	Geometry::Plane customPlane;

	ProfileToCustomPlaneTransformer ();

	void	SetupPlanesForStraightExtrusion (const Coord3D& refLinePoint, const Vector3D& extrusionVect, const Vector3D& verticalPlaneXAxis, const Vector3D& customPlaneNormal);
	void	SetupPlanesForCurvedExtrusion	(const Coord& arcBegC, const Coord& arcEndC, double arcAngle, double zLevel, double refLinePointParam);
	void	SetupProfileTrafo				(const Geometry::Matrix23& trafo);
	void	SetupIdentityProfileTrafo		();

	static bool IsValidExtusionCurvePointParam (double param);
};

}

#endif
