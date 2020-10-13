#include "CircleF.h"


CircleF::CircleF(Vec2 center, float r)
	:
	center(center),
	r(r)
{
}

bool CircleF::IsOverLapingWith(const CircleF& other)
{
	return (other.center - center).GetLengthSq() < (other.r + r) * (other.r + r);

}

bool CircleF::isContaining(const Vec2& coordinate)
{
	return (coordinate - center).GetLengthSq() < r * r;
}
