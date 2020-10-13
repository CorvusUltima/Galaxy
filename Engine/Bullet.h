#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "CircleF.h"
#include "rng.h"
class Bullet
{
public:

	Bullet(const CircleF& circle, const Vec2& dir, const Color& c, float speed, float dmg, bool homing = false);
	void Update(float dt, const Vec2& target = { -1.0f, 0 });
	void Draw(Graphics& gfx);
	void delete_offscreen(Graphics& gfx);
	bool isTargetHit(const CircleF& target);
	bool isTargetAquired(const Vec2& target);

	CircleF circle;
	bool bDeleted = false;

private:

	Vec2 dir;
	float dmg;
	Color c;
	Color c_base;
	float speed = 0.0f;
	bool bHoming = false; //Only for enemy bullets, too much work to use for defender :D
	float DetectionRadius = 400.0f;
};

