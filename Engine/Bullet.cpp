#include "Bullet.h"

Bullet::Bullet(const CircleF& circle, const Vec2& dir, const Color& c, float speed, float dmg, bool homing)
	:
	circle(circle),
	c(c),
	dir(dir),
	speed(speed),
	dmg(dmg),
	bHoming(homing)
{
	c_base = c;
}

void Bullet::Update(float dt, const Vec2& target)
{
	if (target.x >= 0) //Aquire target only if it is initialized
		if (bHoming && isTargetAquired(target))
		{
			float c_changer = rng::rdm_float(0.0f, 1.0f);
			c = Color((int)((float)c_base.GetR() * c_changer), (int)((float)c_base.GetG() * c_changer), (int)((float)c_base.GetB() * c_changer)); //Blinking color while projectile is following the target
			dir = target - circle.center; //Follow target if it's inside detection radius
		}
		else c = c_base; //Reset the color to original if target is not in site anymore
	circle.center += dir.GetNormalized() * speed * dt;
}

void Bullet::Draw(Graphics& gfx)
{
	gfx.DrawCircle((int)circle.center.x, (int)circle.center.y, (int)circle.r, c);
}

void Bullet::delete_offscreen(Graphics& gfx)
{
	const int left = (int)(circle.center.x - circle.r);
	const int right = (int)(circle.center.x + circle.r);
	const int top = (int)(circle.center.y - circle.r);
	const int bottom = (int)(circle.center.y + circle.r);
	if (right < gfx.ScreenLeft || left > gfx.ScreenRight || bottom < gfx.ScreenTop || top > gfx.ScreenBottom) bDeleted = true;
}

bool Bullet::isTargetHit(const CircleF& target)
{
		if (circle.IsOverLapingWith(target))
		{
			bDeleted = true;
			return true;
		}
		else return false;
}

bool Bullet::isTargetAquired(const Vec2& target)
{
	CircleF detection_circle(circle.center, DetectionRadius);
	return detection_circle.isContaining(target);
}


