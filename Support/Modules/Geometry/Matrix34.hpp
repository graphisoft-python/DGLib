// *********************************************************************************************************************
// Description:		Matrix3 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX34_HPP)
#define GS_MATRIX34_HPP

#pragma once

#include <cstddef>

// from GSRoot
#include "GSDebug.hpp"
#include "Channel.hpp"
#include "XMLChannel.hpp"

// from Geometry
#include "Real.hpp"
#include "Length.hpp"
#include "Vector3D.hpp"
#include "Coord3d.h"
#include "Matrix3.hpp"

namespace Geometry {
	class Matrix23;
}

namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix34 {
	DECLARE_ROOT_CLASS_INFO

private:

	double		m_storage[3][4];	// first index: raw, second index: column

public:

	Matrix34 (void);
	Matrix34 (const Matrix34& src);
	Matrix34 (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3);							// three row vectors
	Matrix34 (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3, const Vector3d& vec4);		// four column vectors
	Matrix34 (const Matrix33& matr, const Vector3d& vec1);

	virtual ~Matrix34 ();

	static void IdentMatrix (Matrix34& result);
	static void RowVectorsMatrix (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3, Matrix34& result);
	static void ColVectorsMatrix (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3, const Vector3d& vec4, Matrix34& result);
	static void RotationXMatrix (const double& alpha, Matrix34& result);
	static void RotationYMatrix (const double& alpha, Matrix34& result);
	static void RotationZMatrix (const double& alpha, Matrix34& result);
	static void ScalingMatrix (const double& scalx, const double& scaly, const double& scalz, Matrix34& result);
	static void From2DTransformationMatrix (const Matrix23& transformation2d, Matrix34& result);
	static void MirrorXYMatrix (Matrix34& result);
	static void MirrorYZMatrix (Matrix34& result);
	static void MirrorZXMatrix (Matrix34& result);

	void GetOffsetVector3d (Vector3d& vec1) const;
	void SetOffsetVector3d (const Vector3d& vec1);
	void GetRowVectors3d (Vector3d& vec1, Vector3d& vec2, Vector3d& vec3) const;
	void GetColVectors3d (Vector3d& vec1, Vector3d& vec2, Vector3d& vec3, Vector3d& vec4) const;
	void GetMatrix33 (Matrix33& matr, Vector3d& vec) const;
	void SetMatrix33 (const Matrix33& matr, const Vector3d& vec);
	inline double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	inline void		Set (UIndex i, UIndex j, const double& x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix34& dest) const;
	Vector3d TransfV (const Vector3d& v) const;
	Coord3D TransfC (const Coord3D& v) const;

	Matrix34& operator= (const Matrix34& src);

	Matrix34		operator- () const;
	Matrix34		operator+ (const Matrix34&) const;
	Matrix34		operator- (const Matrix34&) const;
	Matrix34		operator+ (const Vector3d&) const;
	Matrix34		operator* (const double&) const;
	Coord3D			operator* (const Coord3D&) const;

	Matrix34		operator* (const Matrix34&) const;

	const Matrix34&	operator+= (const Matrix34&);
	const Matrix34&	operator+= (const Vector3d&);
	const Matrix34&	operator-= (const Matrix34&);
	const Matrix34&	operator*= (const double&);
	const Matrix34&	operator*= (const Matrix34&);

	bool	operator== (const Matrix34&) const;
	bool	operator!= (const Matrix34&) const;

	GSErrCode Read_array	(GS::IChannel& ic);
	GSErrCode Write_array (GS::OChannel& oc) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* tagName = nullptr) const;

	void IVMatrix (GS::PlatformSign inplatform);
	void IVMatrix (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix34 operator* (double skal, Matrix34& mm) {  Matrix34 res = mm * skal; return res; }

} // namespace Geometry

GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, Geometry::Matrix34& m);

GEOMETRY_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const Geometry::Matrix34& m);


#endif

