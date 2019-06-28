// Contact person: KiP

#ifndef HELIX3D_HPP
#define HELIX3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"
#include "Plane.hpp"


namespace Geometry 
{

class HelixPlaneIntersectionCalculator;

class GEOMETRY_DLL_EXPORT Helix3D
{
public:
	enum ParamType 
	{
		AngleParam,
		LengthParam
	};

	static Helix3D		Create (const Plane& localCoordFrame, double radius, double pitchPerTurn, double begAngleParam, double endAngleParam, bool isInfinite);
	static Helix3D		CreateOneTwistPerpendicularHelix (const Coord3D& begC, const Coord3D& endC, double angle);

	const Plane&		GetLocalCoordFrame		() const;
	double				GetRadius				() const;
	double				GetBegParam				(ParamType paramType = AngleParam) const;
	double				GetEndParam				(ParamType paramType = AngleParam) const;
	double				GetPitch				() const;
	double				GetPitchPerTurn			() const;
	Vector3D			GetAxisDir				() const;
	Coord3D				GetBegC					() const;
	Coord3D				GetEndC					() const;
	Box3DType			GetBounds				() const;
	bool				IsInfinite				() const;
	bool				Reflected				() const;
	
	bool				IsValidAngleParam		(double angleParam) const;
	double				ToLengthParam			(double angleParam) const;
	double				ToAngleParam			(double lengthParam) const;

	bool				IsPointOf				(const Coord3D& point, bool extendToInfinite = false) const;
	Coord3D				GetPoint				(double param, ParamType paramType = AngleParam) const;	
 	double				GetParam				(const Coord3D& point, ParamType paramType = AngleParam) const;	
	Coord3D				GetClosestPoint			(const Coord3D& point) const;
	double				GetDistance				(const Coord3D& point) const;
	Vector3D			GetTangential			(double param, ParamType paramType = AngleParam) const;	
	GS::Array<Coord3D>	SegmentUp				(double tolerance) const;
	GenArc				ProjectAlongMainAxis	() const;										// the result GenArc is in LocalCoordFrame!

	// Modification
	void				ExtendToInfinite		();

	// Serialization
	GSErrCode			Read					(GS::IChannel& ic);
	GSErrCode			Write					(GS::OChannel& oc) const;

private:
	Plane		localCoordFrame;
	double		radius;
	double		pitch;
	double		begAngleParam;
	double		endAngleParam;
	bool		isInfinite;
	bool		reflected;

	double CalcX (double angleParam) const;
	double CalcY (double angleParam) const;
	double CalcZ (double angleParam) const;
	Coord3D CalcLocalPoint (double angleParam) const;
	double CalcAngleParamFromLocalZ (double localZ) const;

	double CalcDX (double angleParam) const;
	double CalcDY (double angleParam) const;
	double CalcDZ (double angleParam) const;

	Helix3D ();	// disabled, use constructor functions

	friend HelixPlaneIntersectionCalculator;
};

GEOMETRY_DLL_EXPORT
GS::Array<Coord3D> GEOM_CALL CalcHelixLineIntersections (const Helix3D& helix, const Coord3D& linePoint, const Vector3D& lineDir);

GEOMETRY_DLL_EXPORT
GS::Array<Coord3D> GEOM_CALL CalcHelixRayIntersections (const Helix3D& helix, const Coord3D& rayStartPoint, const Vector3D& rayDir);

GEOMETRY_DLL_EXPORT
GS::Array<Coord3D> GEOM_CALL CalcHelixSectorIntersections (const Helix3D& helix, const Sector3D& sector);

GEOMETRY_DLL_EXPORT
GS::Array<Coord3D> GEOM_CALL CalcHelixPlaneIntersections (const Helix3D& helix, const PlaneEq& plane);

}

#endif
