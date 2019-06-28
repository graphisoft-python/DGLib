#include "Point2D.hpp"

namespace VBCalculations
{

Coord CalculateBreakMarkOverhangStraight (const Coord& breakMarkEndPoint, const double amount, const double breakMarkAngle, const Vector& breakMarkOffsetDirection);
Coord CalculateBreakMarkOverhangArc (const Coord& breakMarkEndPoint, const double amount, const Coord arcOrigo, const Vector& breakMarkOffsetDirection);

}