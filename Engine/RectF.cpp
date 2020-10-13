#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{

}

RectF::RectF(const Vec2& topleft, const Vec2& bottomRight)
	:
	RectF(topleft.x,bottomRight.x,topleft.y,bottomRight.y)
{
}

RectF::RectF(const Vec2& topleft, float width, float height)
	:
	RectF(topleft,topleft+Vec2(width,height))
{
}

bool RectF::isOverLappingWith(const RectF& other) const
{
	return right>other.left&& left<other.right&& bottom>other.top&& top<other.bottom;
}

bool RectF::isContaining(const Vec2& point) const
{
	return point.x > left && point.x < right && point.y > top && point.y < bottom;
}

RectF RectF::FromCenter(const Vec2& center, float width, float height)
{
	return RectF(center.x - width/2, center.x + width/2, center.y -height/2, center.y + height/2);
}

Vec2 RectF::GetCenter() const
{
	return Vec2((left + right) / 2.0f, (top + bottom) / 2.0f);
}
