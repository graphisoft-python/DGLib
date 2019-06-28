#if !defined (TRANMAT_H)
#define TRANMAT_H

#pragma once

/*================================	CONSTANTS	============================*/

#define	TR_IDENT		0x0001
#define	TR_DET_1		0x0002
#define	TR_SINGULAR		0x0004
#define	TR_MIRROR		0x0040

#define	TR_TRANSL_ONLY	0x0008
#define	TR_SCALE_ONLY	0x0010
#define	TR_ROTATE_ONLY	0x0020

#define	TR_TRANSL_INCL	0x0080
#define	TR_SCALE_INCL	0x0100

#define	TR_UNDECOMPOSED	0x1000	/*vv02.02*/

#include "Matrix34.hpp"
#include "Matrix3.hpp"

typedef struct TRANMAT {
	short	status;
	short	dummy1;
	short	dummy2;
	short	dummy3;
	Geometry::Matrix34 tmx;

} TRANMAT;				/* 104 */

// Represents a linear transformation in the 3D Euclidean space.
struct LINTRAN {
	Geometry::Matrix33 tmx;

};

#endif
