// *********************************************************************************************************************
// Description:		Matrix2 based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	RJ
//
// *********************************************************************************************************************

#if !defined (GS_MATRIX2_HPP)
#define GS_MATRIX2_HPP

#pragma once

#include <cstddef>

// from GSRoot
#include "GSDebug.hpp"
#include "Channel.hpp"
#include "XMLChannel.hpp"

// from Geometry
#include "Real.hpp"
#include "Length.hpp"
#include "Vector2D.hpp"
#include "Coord.h"


namespace Geometry {

class GEOMETRY_DLL_EXPORT Matrix22 {
	DECLARE_ROOT_CLASS_INFO

private:

	double m_storage[2][2];		// first index: raw, second index: column

public:

	Matrix22 (void);
	Matrix22 (const Matrix22& src);
	Matrix22 (const Vector2d& vec1, const Vector2d& vec2);			// two column vectors
	
	virtual ~Matrix22 ();

	static void IdentMatrix (Matrix22& result);
	static void RowVectorsMatrix (const Vector2d& vec1, const Vector2d& vec2, Matrix22& result);
	static void ColVectorsMatrix (const Vector2d& vec1, const Vector2d& vec2, Matrix22& result);
	static void RotationMatrix (const double& alpha, Matrix22& result);
	static void ScalingMatrix (const double& scalx, const double& scaly, Matrix22& result);
	static void MirrorXMatrix (Matrix22& result);
	static void MirrorYMatrix (Matrix22& result);

	void GetRowVectors (Vector2d& vec1, Vector2d& vec2) const;
	void GetColVectors (Vector2d& vec1, Vector2d& vec2) const;
	inline double	Get (UIndex i, UIndex j) const { return m_storage[i][j]; }
	inline void		Set (UIndex i, UIndex j, const double& x) { m_storage[i][j] = x; }

	double DetMatrix (void) const;
	GSErr InvMatrix (Matrix22& dest) const;
	Vector2d TransfV (const Vector2d& v) const;
	Coord TransfC (const Coord& v) const;

	void Transpose (void);
	void Transpose (Matrix22& dest) const;

	Matrix22& operator= (const Matrix22& src);

	Matrix22		operator- () const;
	Matrix22		operator+ (const Matrix22&) const;
	Matrix22		operator- (const Matrix22&) const;
	Matrix22		operator* (const double&) const;
	Vector2d		operator* (const Vector2d&) const;
	Coord			operator* (const Coord&) const;

	Matrix22		operator* (const Matrix22&) const;

	const Matrix22&	operator+= (const Matrix22&);
	const Matrix22&	operator-= (const Matrix22&);
	const Matrix22&	operator*= (const double&);
	const Matrix22&	operator*= (const Matrix22&);

	bool	operator== (const Matrix22&) const;
	bool	operator!= (const Matrix22&) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* tagName = nullptr) const;

private:
	GSErrCode			ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

};

inline Matrix22 operator* (double skal, Matrix22& mm) {  Matrix22 res = mm * skal; return res; }

} // namespace Geometry

GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, Geometry::Matrix22& m);

GEOMETRY_DLL_EXPORT  GSErrCode Write (GS::OChannel& oc, const Geometry::Matrix22& m);


#endif

