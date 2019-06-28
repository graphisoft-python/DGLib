// *********************************************************************************************************************
// Description:		Matrix2 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX23_HPP)
#define GS_MATRIX23_HPP

#pragma once

// from Geometry
#include "Matrix2.hpp"

struct TRANMAT;

namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix23
{
	DECLARE_ROOT_CLASS_INFO

private:

	double		m_storage[2][3];	// first index: raw, second index: column

public:

	Matrix23 (void);
	Matrix23 (const Matrix23& src);
	Matrix23 (const Vector& vec1, const Vector& vec2, const Vector& vec3);		// three column vectors
	Matrix23 (const Matrix22& matr, const Vector& vec);

	virtual ~Matrix23 ();

	static void IdentMatrix (Matrix23& result);
	static void RowVectorsMatrix (const Vector& vec1, const Vector& vec2, Matrix23& result);
	static void ColVectorsMatrix (const Vector& vec1, const Vector& vec2, const Vector& vec3, Matrix23& result);
	static void RotationMatrix (const double& alpha, Matrix23& result);
	static void ScalingMatrix (const double& scalx, const double& scaly, Matrix23& result);
	static GSErrCode Transformation2DMatrix (const Coord& originalPoint1, 
											 const Coord& originalPoint2, 
											 const Coord& originalPoint3, 
											 const Coord& transformedPoint1, 
											 const Coord& transformedPoint2, 
											 const Coord& transformedPoint3, 
											 Matrix23& result);

	static void MirrorXMatrix (Matrix23& result);
	static void MirrorYMatrix (Matrix23& result);

	void GetOffsetVector (Vector& vec) const;
	void SetOffsetVector (const Vector& vec);
	void GetRowVectors (Vector& vec1, Vector& vec2) const;
	void GetColVectors (Vector& vec1, Vector& vec2, Vector& vec3) const;
	void GetMatrix22 (Matrix22& matr, Vector& vec) const;
	void SetMatrix22 (const Matrix22& matr, const Vector& vec);
	inline double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	inline void		Set (UIndex i, UIndex j, const double& x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix23& dest) const;
	Vector TransfV (const Vector& v) const;
	Coord TransfC (const Coord& v) const;

	Matrix23& operator= (const Matrix23& src);

	Matrix23		operator- () const;
	Matrix23		operator+ (const Matrix23&) const;
	Matrix23		operator- (const Matrix23&) const;
	Matrix23		operator+ (const Vector&) const;
	Matrix23		operator* (const double&) const;
	Coord			operator* (const Coord&) const;

	Matrix23		operator* (const Matrix23&) const;

	const Matrix23&	operator+= (const Matrix23&);
	const Matrix23&	operator+= (const Vector&);
	const Matrix23&	operator-= (const Matrix23&);
	const Matrix23&	operator*= (const double&);
	const Matrix23&	operator*= (const Matrix23&);

	bool	operator== (const Matrix23&) const;
	bool	operator!= (const Matrix23&) const;

	GSErrCode Read_array (GS::IChannel& ic);
	GSErrCode Write_array (GS::OChannel& oc) const;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML (GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const;

	void IVMatrix (GS::PlatformSign inplatform);
	void IVMatrix (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

	TRANMAT ToTranMat () const;

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix23 operator* (double skal, Matrix23& mm) { Matrix23 res = mm * skal; return res; }

} // namespace Geometry

GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, Geometry::Matrix23& m);

GEOMETRY_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const Geometry::Matrix23& m);

#endif

