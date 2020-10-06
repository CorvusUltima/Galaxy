#pragma once
#include"Vec2.h"
class RectF
{

public:
	RectF() = default;
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topleft, const Vec2& bottomRight);
	RectF(const Vec2& topleft, float width, float height);
	bool isOverLappingWith(const RectF& other);
	bool isInside(const RectF& other);
	static RectF FromCenter(const Vec2& center, float width, float height);
	Vec2 GetCenter() const;
	

public:

	float left;
	float  right;
	float top;
	float bottom;






};