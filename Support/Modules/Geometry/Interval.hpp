#if !defined (INTERVAL_HPP)
#define INTERVAL_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "RealNumber.h"

namespace Geometry {

class GEOMETRY_DLL_EXPORT Interval
{
public:
	Interval (double start, double end);

	double GetStart		() const;
	double GetEnd		() const;
	double GetLength	() const;
	bool   IsEmpty		(double eps = EPS) const;

	static bool		AreIntersect		(const Interval& interval1, const Interval& interval2, const double eps = EPS);
	static double	IntersectionLength	(const Interval& interval1, const Interval& interval2);

private:
	double start;
	double end;
};

}


#endif
