// *********************************************************************************************************************
// Description:		OrientedBoundingBox2D
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	VSZG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ORIENTEDBOUNDINGBOX2D_HPP)
#define ORIENTEDBOUNDINGBOX2D_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from Geometry
#include	"GeometricDefinitions.h"
#include	"Coord.h"
#include	"Box2DData.h"
#include	"TRANMAT.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Geometry {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


class GEOMETRY_DLL_EXPORT OrientedBoundingBox2D {
public:
	enum {
		XMinYMin,
		XMaxYMin,
		XMaxYMax,
		XMinYMax
	};

	OrientedBoundingBox2D (const Coord& startPoint, const Vector& primaryDirection);

	const Coord&	operator[] (Int32 i)		const;
	const Coord*	GetPoints ()				const;
	double			GetPrimaryThickness ()		const	{ return mBox.xMax - mBox.xMin;	}
	double			GetSecondaryThickness ()	const	{ return mBox.yMax - mBox.yMin;	}

	bool			IsEmpty ()					const	{ return Geometry::IsEmptyBox (mBox); }
	bool			IsInBox (const					Coord& p,
							 Geometry::Boundary		boundaries = Geometry::Boundary_Closed,
							 double					eps = Eps)	const;

	void			AddPoint (const Coord& p);

	//	size > 0 is applied on the right side, size < 0 is applied on the left side
	void			IncreasePrimaryThickness	(double size);
	void			IncreaseSecondaryThickness	(double size);

	//void	AddBox (const OrientedBoundingBox2D& src);

private:
	void	GeneratePoints () const;

	TRANMAT			mW2L, mL2W;
	Coord			mStart;
	bool			mIsFirst;
	mutable bool	mNeedGeneration;
	mutable Coord	mPoints[4];
	Box2DData		mBox;
};


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Geometry

#endif
