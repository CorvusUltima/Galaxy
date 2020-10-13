#pragma once
#include "Graphics.h"
#include "img.h"
#include "Vec2.h"
struct Explosion
{
	enum class Size
	{
		Small,
		Medium
	};
	Explosion(const Vec2& pos, Size size)
		:
		pos(pos),
		size(size)
	{
		switch (size)
		{
		case Size::Small:
			duration = 0.1f;
			break;
		case Size::Medium:
			duration = 0.24f;
			break;
		default:
			duration = 0.0f;

		}
	}
	void Update(float dt)
	{
		duration -= dt;
		bExpired = duration <= 0;
	}
	void Draw(Graphics& gfx)
	{
		switch (size)
		{
		case Size::Small:
			img::Explosion_Small(pos, gfx);
			break;
		case Size::Medium:
			if (duration > 0.18f) img::ExploM0(pos, gfx);
			else if (duration > 0.12f) img::ExploM1(pos, gfx);
			else if (duration > 0.06f) img::ExploM2(pos, gfx);
			else img::ExploM3(pos, gfx);
			break;
		}

	}

	Vec2 pos;
	Size size;
	float duration;
	bool bExpired = false;
};

