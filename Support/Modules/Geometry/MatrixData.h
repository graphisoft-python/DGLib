#if !defined (MATRIXDATA_H)
#define MATRIXDATA_H

#pragma once

#if !defined (TRANMAT_H)
#include "TRANMAT.h"
#endif

	// Etimology:
	//
	// Matrix	- matrix
	// Data		- not a class only data
	// 33		- 3 rows 3 columns
	// d		- with double items (elements)

namespace Geometry {

// 2 x 2 Matrices

	typedef double	Matrix22dData[2][2];

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InitMatrix22d (Matrix22dData* matrix);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	AddMatrix22d (Matrix22dData* result, const Matrix22dData* a, const Matrix22dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	SubtractMatrix22d (Matrix22dData* result, const Matrix22dData* a, const Matrix22dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	UnaryMinusMatrix22d (Matrix22dData* result, const Matrix22dData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	MultiplyMatrix22d (Matrix22dData* result, const Matrix22dData* a, const Matrix22dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InvertMatrix22d (Matrix22dData* result, const Matrix22dData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	ScalarMultiplyMatrix22d (Matrix22dData* result, const Matrix22dData* a, const Matrix22dData* b);

// 3 x 3 Matrices

	typedef double	Matrix33dData[3][3];

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InitMatrix33d (Matrix33dData* matrix);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	AddMatrix33d (Matrix33dData* result, const Matrix33dData* a, const Matrix33dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	SubtractMatrix33d (Matrix33dData* result, const Matrix33dData* a, const Matrix33dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	UnaryMinusMatrix33d (Matrix33dData* result, const Matrix33dData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	MultiplyMatrix33d (Matrix33dData* result, const Matrix33dData* a, const Matrix33dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InvertMatrix33d (Matrix33dData* result, const Matrix33dData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	ScalarMultiplyMatrix33d (Matrix33dData* result, const Matrix33dData* a, const Matrix33dData* b);

// 4 x 4 Matrices

	typedef double	Matrix44dData[4][4];

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InitMatrix44d (Matrix44dData* matrix);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	AddMatrix44d (Matrix44dData* result, const Matrix44dData* a, const Matrix44dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	SubtractMatrix44d (Matrix44dData* result, const Matrix44dData* a, const Matrix44dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	UnaryMinusMatrix44d (Matrix44dData* result, const Matrix44dData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	MultiplyMatrix44d (Matrix44dData* result, const Matrix44dData* a, const Matrix44dData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InvertMatrix44d (Matrix44dData* result, const Matrix44dData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	ScalarMultiplyMatrix44d (Matrix44dData* result, const Matrix44dData* a, const Matrix44dData* b);

// n x n Matrices

	typedef double	MatrixnndData;

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InitMatrixnnd (UInt32 size, MatrixnndData* matrix);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	AddMatrixnnd (UInt32 size, MatrixnndData* result, const MatrixnndData* a, const MatrixnndData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	SubtractMatrixnnd (UInt32 size, MatrixnndData* result, const MatrixnndData* a, const MatrixnndData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	UnaryMinusMatrixnnd (UInt32 size, MatrixnndData* result, const MatrixnndData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	MultiplyMatrixnnd (UInt32 size, MatrixnndData* result, const MatrixnndData* a, const MatrixnndData* b);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InvertMatrixnnd (UInt32 size, MatrixnndData* result, const MatrixnndData* a);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	ScalarMultiplyMatrixnnd (UInt32 size, MatrixnndData* result, const MatrixnndData* a, const MatrixnndData* b);

// Old functions, will be replaced:

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	InvMat (short n, double *a, double *inva);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	TMConjug (TRANMAT *ctran, TRANMAT *atran, TRANMAT *btran, bool avers);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	TMComplementer (TRANMAT *ctran, const TRANMAT *atran, const TRANMAT *btran, const bool avers);

	GEOMETRY_DLL_EXPORT bool	GEOM_CALL	TMInvert (TRANMAT *btran, const TRANMAT *atran);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMMatProduct (TRANMAT *ctran, const TRANMAT *atran, const TRANMAT *btran);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMFillStatus (TRANMAT *tran);
}

#endif
