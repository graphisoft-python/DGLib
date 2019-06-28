// Contact person: AB

#ifndef CUBICBEZIERCURVE3D_HPP
#define CUBICBEZIERCURVE3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"


namespace Geometry 
{


class GEOMETRY_DLL_EXPORT CubicBezierCurve3D
{
public:	
	enum BezierSegmentMode {
		FirstSegment	= 1,
		NormalSegment	= 2,
		LastSegment		= 3
	};

private:	
	Coord3D		m_startPoint;
	Coord3D		m_endPoint;
	Vector3D	m_startHandle;
	Vector3D	m_endHandle;

	Coord3D		m_startControl;		// control = point + handle
	Coord3D		m_endControl;

public:
	static CubicBezierCurve3D	CreateFromPolylineSegment (const Coord3D& beforeStartPoint, const Coord3D& segmentStartPoint, const Coord3D& segmentEndPoint, const Coord3D& afterEndPoint, BezierSegmentMode segmentMode);

	CubicBezierCurve3D		();
	CubicBezierCurve3D		(const Coord3D& startPoint, const Vector3D& startHandle, const Coord3D& endPoint, const Vector3D& endHandle);
	
	const Coord3D&	GetStartPoint	(void) const					{ return m_startPoint;	 }
	const Coord3D&	GetEndPoint		(void) const					{ return m_endPoint;	 }
	const Vector3D&	GetStartHandle	(void) const					{ return m_startHandle;	 }
	const Vector3D&	GetEndHandle	(void) const					{ return m_endHandle;	 }
	const Coord3D&	GetStartControl	(void) const					{ return m_startControl; }
	const Coord3D&	GetEndControl	(void) const					{ return m_endControl;	 }

	void			SetStartPoint	(const Coord3D& startPoint)		{ m_startPoint	 = startPoint;	}
	void			SetEndPoint		(const Coord3D& endPoint)		{ m_endPoint	 = endPoint;	}
	void			SetStartHandle	(const Vector3D& startHandle)	{ m_startHandle	 = startHandle;		m_startControl = m_startPoint   + m_startHandle; }
	void			SetEndHandle	(const Vector3D& endHandle)		{ m_endHandle	 = endHandle;		m_endControl   = m_endPoint     + m_endHandle;	 }
	void			SetStartControl	(const Coord3D& startControl)	{ m_startControl = startControl;	m_startHandle  = m_startControl - m_startPoint;	 }
	void			SetEndControl	(const Coord3D& endControl)		{ m_endControl	 = endControl;		m_endHandle    = m_endControl   - m_endPoint;	 }

	
	bool			GetPoint		(double param, Coord3D& result) const;
	bool			Split			(double param, CubicBezierCurve3D& startCurveOut, CubicBezierCurve3D& endCurveOut) const;
	bool			GetSubCurve		(double startParam, double endParam, CubicBezierCurve3D& subCurveOut) const;
	double			EstimateError	(void) const;									// Crude estimation of the maximum deviation of a cubic Bezier curve from it's base segment.
	double			EstimateSegmentationError (unsigned int numSegments) const;
};


}	// namespace Geometry

#endif
