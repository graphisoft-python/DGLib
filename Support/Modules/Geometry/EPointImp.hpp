// *********************************************************************************************************************
// Description:		EPointImp.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

template<typename Int>
GS_FORCE_INLINE Point<Int>::Point ()
{
}

template<typename Int>
GS_FORCE_INLINE Point<Int>::Point (const Point& op) :
	x (op.x),
	y (op.y),
	z (op.z)
{
}

template<typename Int>
GS_FORCE_INLINE Point<Int>::Point (const Rational<Int>& x, const Rational<Int>& y, const Rational<Int>& z) :
	x (x),
	y (y),
	z (z)
{
}

template<typename Int>
inline const Point<Int>& Point<Int>::operator= (const Point& op)
{
	x = op.x;
	y = op.y;
	z = op.z;
	return *this;
}

template<typename Int>
inline bool Point<Int>::operator== (const Point& op) const
{
	return x == op.x && y == op.y && z == op.z;
}

template<typename Int>
inline bool Point<Int>::operator!= (const Point& op) const
{
	return x != op.x || y != op.y || z != op.z;
}

template<typename Int>
GS_FORCE_INLINE bool Point<Int>::IsNull () const
{
	return x.Sgn () == 0 && y.Sgn () == 0 && z.Sgn () == 0;
}

template<typename Int>
inline Point<Int> Point<Int>::operator- () const
{
	return Point (-x, -y, -z);
}

template<typename Int>
inline Point<Int> Point<Int>::operator+ (const Point& op) const
{
	return Point (x + op.x, y + op.y, z + op.z);
}

template<typename Int>
inline Point<Int> Point<Int>::operator- (const Point& op) const
{
	return Point (x - op.x, y - op.y, z - op.z);
}

template<typename Int>
inline Point<Int> Point<Int>::operator* (const Rational<Int>& op) const
{
	return Point (x * op, y * op, z * op);
}

template<typename Int>
inline Point<Int> Point<Int>::operator/ (const Rational<Int>& op) const
{
	return Point (x / op, y / op, z / op);
}

template<typename Int>
GS_FORCE_INLINE const Point<Int>& Point<Int>::operator+= (const Point& op)
{
	return *this = *this + op;
}

template<typename Int>
GS_FORCE_INLINE const Point<Int>& Point<Int>::operator-= (const Point& op)
{
	return *this = *this - op;
}

template<typename Int>
GS_FORCE_INLINE const Point<Int>& Point<Int>::operator*= (const Rational<Int>& op)
{
	return *this = *this * op;
}

template<typename Int>
GS_FORCE_INLINE const Point<Int>& Point<Int>::operator/= (const Rational<Int>& op)
{
	return *this = *this / op;
}

template<typename Int>
inline Rational<Int> Point<Int>::operator* (const Point& op) const
{
	return x * op.x + y * op.y + z * op.z;
}

template<typename Int>
inline Point<Int> Point<Int>::operator^ (const Point& op) const
{
	return Point (y * op.z - z * op.y, z * op.x - x * op.z, x * op.y - y * op.x);
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>&	Point<Int>::operator [] (UInt32 i) const
{
	DBASSERT (i < 3);
	static_assert (offsetof (Point<Int>, y) - offsetof (Point<Int>, x) == sizeof (Rational<Int>) && offsetof (Point<Int>, z) - offsetof (Point<Int>, x) == 2 * sizeof (Rational<Int>), "offset");
	return (&x)[i];
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>&			Point<Int>::operator [] (UInt32 i)
{
	DBASSERT (i < 3);
	static_assert (offsetof (Point<Int>, y) - offsetof (Point<Int>, x) == sizeof (Rational<Int>) && offsetof (Point<Int>, z) - offsetof (Point<Int>, x) == 2 * sizeof (Rational<Int>), "offset");
	return (&x)[i];
}

template<typename Int>
bool Point<Int>::SameOrientationVector (const Point& p) const
{
	char sx, sy, sz;
	short s1, s2;

	s1 = x.Sgn ();
	s2 = p.x.Sgn ();

	if (s1 == 0 || s2 == 0)
		sx = 0;
	else
		sx = s1 > 0 == s2 > 0 ? 1 : -1;

	s1 = y.Sgn ();
	s2 = p.y.Sgn ();

	if (s1 == 0 || s2 == 0)
		sy = 0;
	else
		sy = s1 > 0 == s2 > 0 ? 1 : -1;

	s1 = z.Sgn ();
	s2 = p.z.Sgn ();

	if (s1 == 0 || s2 == 0)
		sz = 0;
	else
		sz = s1 > 0 == s2 > 0 ? 1 : -1;

	if (sx >= 0 && sy >= 0 && sz >= 0)
		return true;
	if (sx <= 0 && sy <= 0 && sz <= 0)
		return false;

	return (*this * p).Sgn () >= 0;
}

template<typename Int>
bool Point<Int>::ParallelToVector (const Point &v) const
{
	Rational<Int> alpha;
	if (x.Sgn () != 0) {
		alpha = v.x / x;
		return y * alpha == v.y && z * alpha == v.z;
	} else if (y.Sgn () != 0) {
		alpha = v.y / y;
		return x * alpha == v.x && z * alpha == v.z;
	} else if (z.Sgn () != 0) {
		alpha = v.z / z;
		return x * alpha == v.x && y * alpha == v.y;
	}

	return true; // lhs is null, which is by definition parallel to any vector!
}


template<typename Int>
short Point<Int>::DotProductSgn (const Point& op) const
{
	return (x.Nom () * op.x.Nom () * y.Denom () * op.y.Denom () * z.Denom () * op.z.Denom () +
				y.Nom () * op.y.Nom () * x.Denom () * op.x.Denom () * z.Denom () * op.z.Denom () +
				z.Nom () * op.z.Nom () * x.Denom () * op.x.Denom () * y.Denom () * op.y.Denom ()).Sgn ();
}

template<typename Int>
GS_FORCE_INLINE void Point<Int>::Simplify ()
{
	x.Simplify ();
	y.Simplify ();
	z.Simplify ();
}

template<typename Int>
Coord3D Point<Int>::ConvertToCoord () const
{
	return Coord3D (x.ConvertToDouble (), y.ConvertToDouble (), z.ConvertToDouble ());
}

template<typename Int>
void Point<Int>::DBDump () const
{
	DBPrintf ("X = ");
	x.DBDump ();
	DBPrintf ("\n");

	DBPrintf ("Y = ");
	y.DBDump ();
	DBPrintf ("\n");

	DBPrintf ("Z = ");
	z.DBDump ();
	DBPrintf ("\n");
}

template<typename Int>
void BoundBox<Int>::UnifyBoundBox (const BoundBox& bb)
{
	if (bb.xmin < xmin)
		xmin = bb.xmin;
	if (bb.xmax > xmax)
		xmax = bb.xmax;

	if (bb.ymin < ymin)
		ymin = bb.ymin;
	if (bb.ymax > ymax)
		ymax = bb.ymax;

	if (bb.zmin < zmin)
		zmin = bb.zmin;
	if (bb.zmax > zmax)
		zmax = bb.zmax;
}

template<typename Int>
void BoundBox<Int>::GrowBox (Int d)
{
	xmin -= d;
	xmax += d;
	ymin -= d;
	ymax += d;
	zmin -= d;
	zmax += d;
}

template<typename Int>
bool BoundBox<Int>::DisjointBox (const BoundBox& bb) const
{
	return xmax < bb.xmin || xmin > bb.xmax || ymax < bb.ymin || ymin > bb.ymax || zmax < bb.zmin || zmin > bb.zmax;
}

template<typename Int>
bool BoundBox<Int>::IsValid () const
{
	return xmin <= xmax && ymin <= ymax && zmin <= zmax;
}

template<typename Int>
BoundBox<Int> PointBB (const Point<Int>& p)
{
	BoundBox<Int> bb;

	Integer<Int> i = p.x.Floor ();
	if (i.Width () == 1) {
		bb.xmin = i.ConvertToInt ();
		bb.xmax = p.x == bb.xmin || bb.xmin == BoundBox<Int>::MaxInt ? bb.xmin : bb.xmin + 1;
	} else
		bb.xmin = bb.xmax = (i.Sgn () > 0 ? BoundBox<Int>::MaxInt : BoundBox<Int>::MinInt);

	i = p.y.Floor ();
	if (i.Width () == 1) {
		bb.ymin = i.ConvertToInt ();
		bb.ymax = p.y == bb.ymin || bb.ymin == BoundBox<Int>::MaxInt ? bb.ymin : bb.ymin + 1;
	} else
		bb.ymin = bb.ymax = (i.Sgn () > 0 ? BoundBox<Int>::MaxInt : BoundBox<Int>::MinInt);

	i = p.z.Floor ();
	if (i.Width () == 1) {
		bb.zmin = i.ConvertToInt ();
		bb.zmax = p.z == bb.zmin || bb.zmin == BoundBox<Int>::MaxInt ? bb.zmin : bb.zmin + 1;
	} else
		bb.zmin = bb.zmax = (i.Sgn () > 0 ? BoundBox<Int>::MaxInt : BoundBox<Int>::MinInt);

	return bb;
}


template<typename Int>
GS_FORCE_INLINE P2<Int>::P2 ()
{
}

template<typename Int>
GS_FORCE_INLINE P2<Int>::P2 (const P2& op) :
	x (op.x),
	y (op.y)
{
}

template<typename Int>
GS_FORCE_INLINE P2<Int>::P2 (const Rational<Int>& x, const Rational<Int>& y) :
	x (x),
	y (y)
{
}

template<typename Int>
inline const P2<Int>& P2<Int>::operator= (const P2& op)
{
	x = op.x;
	y = op.y;
	return *this;
}

template<typename Int>
inline bool P2<Int>::operator== (const P2& op) const
{
	return x == op.x && y == op.y;
}

template<typename Int>
inline bool P2<Int>::operator!= (const P2& op) const
{
	return x != op.x || y != op.y;
}

template<typename Int>
GS_FORCE_INLINE bool P2<Int>::IsNull () const
{
	return x.Sgn () == 0 && y.Sgn () == 0;
}

template<typename Int>
inline P2<Int> P2<Int>::operator- () const
{
	return P2 (-x, -y);
}

template<typename Int>
inline P2<Int> P2<Int>::operator+ (const P2& op) const
{
	return P2 (x + op.x, y + op.y);
}

template<typename Int>
inline P2<Int> P2<Int>::operator- (const P2& op) const
{
	return P2 (x - op.x, y - op.y);
}

template<typename Int>
inline P2<Int> P2<Int>::operator* (const Rational<Int>& op) const
{
	return P2 (x * op, y * op);
}

template<typename Int>
inline P2<Int> P2<Int>::operator/ (const Rational<Int>& op) const
{
	return P2 (x / op, y / op);
}

template<typename Int>
GS_FORCE_INLINE const P2<Int>& P2<Int>::operator+= (const P2& op)
{
	return *this = *this + op;
}

template<typename Int>
GS_FORCE_INLINE const P2<Int>& P2<Int>::operator-= (const P2& op)
{
	return *this = *this - op;
}

template<typename Int>
GS_FORCE_INLINE const P2<Int>& P2<Int>::operator*= (const Rational<Int>& op)
{
	return *this = *this * op;
}

template<typename Int>
GS_FORCE_INLINE const P2<Int>& P2<Int>::operator/= (const Rational<Int>& op)
{
	return *this = *this / op;
}

template<typename Int>
inline Rational<Int> P2<Int>::operator* (const P2& op) const
{
	return x * op.x + y * op.y;
}

template<typename Int>
inline Rational<Int> P2<Int>::operator^ (const P2& op) const
{
	return x * op.y - y * op.x;
}

template<typename Int>
GS_FORCE_INLINE const Rational<Int>&	P2<Int>::operator [] (UInt32 i) const
{
	DBASSERT (i < 2);
	static_assert (offsetof (P2<Int>, y) - offsetof (P2<Int>, x) == sizeof (Rational<Int>), "offset");
	return (&x)[i];
}

template<typename Int>
GS_FORCE_INLINE Rational<Int>&			P2<Int>::operator [] (UInt32 i)
{
	DBASSERT (i < 2);
	static_assert (offsetof (P2<Int>, y) - offsetof (P2<Int>, x) == sizeof (Rational<Int>), "offset");
	return (&x)[i];
}

template<typename Int>
short P2<Int>::DotProductSgn (const P2& op) const
{
	return (x.Nom () * op.x.Nom () * y.Denom () * op.y.Denom () + y.Nom () * op.y.Nom () * x.Denom () * op.x.Denom ()).Sgn ();
}

template<typename Int>
short P2<Int>::CrossProductSgn (const P2& op) const
{
	return (x.Nom () * op.y.Nom () * y.Denom () * op.x.Denom ()).Compare (y.Nom () * op.x.Nom () * x.Denom () * op.y.Denom ());
}

template<typename Int>
short P2<Int>::P2Quarter () const
{
	switch (x.Sgn ()) {
		default:
		case 1:
			return y.Sgn () >= 0 ? 0 : 3;
		case 0:
			return y.Sgn () > 0 ? 1 : 3;
		case -1:
			return y.Sgn () > 0 ? 1 : 2;
	}
}

template<typename Int>
short P2<Int>::P2Eighth () const
{
	switch (x.Sgn ()) {
		default:
		case 1:
			switch (y.Sgn ()) {
				default:
				case 1:
					return x > y ? 0 : 1;
				case 0:
					return 0;
				case -1:
					return x < -y ? 6 : 7;
			}
		case 0:
			return y.Sgn () > 0 ? 2 : 6;
		case -1:
			switch (y.Sgn ()) {
				default:
				case 1:
					return y > -x ? 2 : 3;
				case 0:
					return 4;
				case -1:
					return x < y ? 4 : 5;
			}
	}
}

template<typename Int>
short CompareP2sCCW (const P2<Int>& p1, bool fw1, const P2<Int>& p2, bool fw2)
{
	short q1 = p1.P2Quarter ();
	if (!fw1)
		q1 ^= 2;

	short q2 = p2.P2Quarter ();
	if (!fw2)
		q2 ^= 2;

	if (q1 < q2)
		return -1;
	else if (q1 > q2)
		return 1;

	q1 = p1.P2Eighth ();
	if (!fw1)
		q1 ^= 4;

	q2 = p2.P2Eighth ();
	if (!fw2)
		q2 ^= 4;

	if (q1 < q2)
		return -1;
	else if (q1 > q2)
		return 1;
	else if (fw1 == fw2)
		return p2.CrossProductSgn (p1);
	else
		return p1.CrossProductSgn (p2);
}

template<typename Int>
GS_FORCE_INLINE void P2<Int>::Simplify ()
{
	x.Simplify ();
	y.Simplify ();
}

template<typename Int>
void BB2<Int>::UnifyBoundBox (const BB2& bb)
{
	if (bb.xmin < xmin)
		xmin = bb.xmin;
	if (bb.xmax > xmax)
		xmax = bb.xmax;

	if (bb.ymin < ymin)
		ymin = bb.ymin;
	if (bb.ymax > ymax)
		ymax = bb.ymax;
}

template<typename Int>
bool BB2<Int>::DisjointBox (const BB2& bb) const
{
	return xmax < bb.xmin || xmin > bb.xmax || ymax < bb.ymin || ymin > bb.ymax;
}

template<typename Int>
BB2<Int> PointBB (const P2<Int>& p)
{
	BB2<Int> bb;

	bb.xmin = p.x.Floor ().ConvertToInt ();
	bb.ymin = p.y.Floor ().ConvertToInt ();
	bb.xmax = p.x == bb.xmin ? bb.xmin : bb.xmin + 1;
	bb.ymax = p.y == bb.ymin ? bb.ymin : bb.ymin + 1;

	return bb;
}

