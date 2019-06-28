// *********************************************************************************************************************
// Description:		EPoint.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#pragma once

#ifndef EPOINT_HPP
#define EPOINT_HPP

#include "Rational.hpp"
#include "Vector3D.hpp"


namespace QXTools {

template<typename Int>
struct Point
{
	Rational<Int> x, y, z;

	Point ();
	Point (const Point&);
	Point (const Rational<Int>&, const Rational<Int>&, const Rational<Int>&);

	const Point& operator= (const Point&);

	bool operator== (const Point&) const;
	bool operator!= (const Point&) const;
	bool IsNull () const;

	Point operator- () const;
	Point operator+ (const Point&) const;
	Point operator- (const Point&) const;
	Point operator* (const Rational<Int>&) const;
	Point operator/ (const Rational<Int>&) const;

	const Point& operator+= (const Point&);
	const Point& operator-= (const Point&);
	const Point& operator*= (const Rational<Int>&);
	const Point& operator/= (const Rational<Int>&);

	Rational<Int> operator* (const Point&) const;
	Point operator^ (const Point&) const;

	const Rational<Int>&	operator [] (UInt32 i) const;
	Rational<Int>&			operator [] (UInt32 i);

	bool SameOrientationVector (const Point&) const;
	bool ParallelToVector (const Point &) const;
	short DotProductSgn (const Point&) const;

	void Simplify ();
	Coord3D ConvertToCoord () const;
	void DBDump () const;
};

template<typename Int>
struct BoundBox
{
	Int xmin, xmax, ymin, ymax, zmin, zmax;

	void UnifyBoundBox (const BoundBox& bb);
	void GrowBox (Int d);

	bool DisjointBox (const BoundBox& bb) const;

	bool IsValid () const;

	bool operator == (const BoundBox& bb) const
	{
		return xmin == bb.xmin && xmax == bb.xmax && ymin == bb.ymin && ymax == bb.ymax && zmin == bb.zmin && zmax == bb.zmax;
	}

	static const Int MaxInt;
	static const Int MinInt;
};
template<typename Int> const Int BoundBox<Int>::MaxInt = ~(Int (1) << (sizeof (Int) * 8 - 1));
template<typename Int> const Int BoundBox<Int>::MinInt = -MaxInt - 1;

template<typename Int>
BoundBox<Int> PointBB (const Point<Int>& p);


template<typename Int>
struct P2
{
	Rational<Int> x, y;

	P2 ();
	P2 (const P2&);
	P2 (const Rational<Int>&, const Rational<Int>&);

	const P2& operator= (const P2&);

	bool operator== (const P2&) const;
	bool operator!= (const P2&) const;
	bool IsNull () const;

	P2 operator- () const;
	P2 operator+ (const P2&) const;
	P2 operator- (const P2&) const;
	P2 operator* (const Rational<Int>&) const;
	P2 operator/ (const Rational<Int>&) const;

	const P2& operator+= (const P2&);
	const P2& operator-= (const P2&);
	const P2& operator*= (const Rational<Int>&);
	const P2& operator/= (const Rational<Int>&);

	Rational<Int> operator* (const P2&) const;
	Rational<Int> operator^ (const P2&) const;

	const Rational<Int>&	operator [] (UInt32 i) const;
	Rational<Int>&			operator [] (UInt32 i);

	short DotProductSgn (const P2&) const;
	short CrossProductSgn (const P2&) const;

	short P2Quarter () const;
	short P2Eighth () const;

	void Simplify ();
};

template<typename Int>
short CompareP2sCCW (const P2<Int>& p1, bool fw1, const P2<Int>& p2, bool fw2);

template<typename Int>
struct BB2
{
	Int xmin, xmax, ymin, ymax;

	void UnifyBoundBox (const BB2& bb);
	bool DisjointBox (const BB2& bb) const;
};

template<typename Int>
BB2<Int> PointBB (const P2<Int>& p);


#include "EPointImp.hpp"

}

#endif
