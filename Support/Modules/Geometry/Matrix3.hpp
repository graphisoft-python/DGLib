// *********************************************************************************************************************
// Description:		Matrix3 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX3_HPP)
#define GS_MATRIX3_HPP

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


namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix33 {
	DECLARE_ROOT_CLASS_INFO

private:

	double		m_storage[3][3];	// first index: raw, second index: column

public:

	Matrix33 (void);
	Matrix33 (const Matrix33& src);
	Matrix33 (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3);			// three column vectors

	virtual ~Matrix33 ();

	static void IdentMatrix (Matrix33& result);
	static void RowVectorsMatrix (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3, Matrix33& result);
	static void ColVectorsMatrix (const Vector3d& vec1, const Vector3d& vec2, const Vector3d& vec3, Matrix33& result);
	static void RotationXMatrix (const double& alpha, Matrix33& result);
	static void RotationYMatrix (const double& alpha, Matrix33& result);
	static void RotationZMatrix (const double& alpha, Matrix33& result);
	static void ScalingMatrix (const double& scalx, const double& scaly, const double& scalz, Matrix33& result);
	static void MirrorXYMatrix (Matrix33& result);
	static void MirrorYZMatrix (Matrix33& result);
	static void MirrorZXMatrix (Matrix33& result);

	void GetRowVectors3d (Vector3d& vec1, Vector3d& vec2, Vector3d& vec3) const;
	void GetColVectors3d (Vector3d& vec1, Vector3d& vec2, Vector3d& vec3) const;
	inline double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	inline void		Set (UIndex i, UIndex j, const double& x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix33& dest) const;
	Vector3d TransfV (const Vector3d& v) const;
	Coord3D TransfC (const Coord3D& v) const;

	Matrix33& operator= (const Matrix33& src);

	Matrix33		operator- () const;
	Matrix33		operator+ (const Matrix33&) const;
	Matrix33		operator- (const Matrix33&) const;
	Matrix33		operator* (const double&) const;
	Coord3D			operator* (const Coord3D&) const;

	Matrix33		operator* (const Matrix33&) const;

	const Matrix33&	operator+= (const Matrix33&);
	const Matrix33&	operator-= (const Matrix33&);
	const Matrix33&	operator*= (const double&);
	const Matrix33&	operator*= (const Matrix33&);

	bool	operator== (const Matrix33&) const;
	bool	operator!= (const Matrix33&) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* tagName = nullptr) const;

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix33 operator* (double skal, Matrix33& mm) {  Matrix33 res = mm * skal; return res; }

} // namespace Geometry

GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, Geometry::Matrix33& m);

GEOMETRY_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const Geometry::Matrix33& m);


#endif

