#include "Enemy.h"

Enemy::Enemy(const Vec2& pos)
	:
	pos(pos)
{
}

void Enemy::Draw(Graphics& gfx)
{
	int x = int(pos.x - width / 2.0f);
	int y = int(pos.y - height / 2.0f);
	if (!bDead)
	{
		img::TestEnemy(x, y, gfx);
		img::HP_Bar(Vec2((float)x, (float)y - 10.0f), width, 5.0f, healthMax, health, gfx);
	}
}

void Enemy::Update(float dt, Graphics& gfx)
{
	bDead = health <= 0;
	if (!bDead)
	{
		fMoveTimer += 2.4f * dt;
		pos.x += 400.0f * cos(fMoveTimer) * dt;
		pos.y += 0.0f * dt;

		reload -= dt;
		if (reload > 0) reload -= dt;
		else
		{
			Shoot();
			reload = 0.6f;
		}
	}
}

void Enemy::TakeDmg(float dmg)
{
	health -= dmg;
}

const Vec2& Enemy::GetPos()
{
	return pos;
}

bool Enemy::DoDefenderColision(Defender& def)
{
	CircleF  cf;
	float R = 50.0f;

	return (cf.isInside(pos.x, pos.y, R, def.GetPos().x, def.GetPos().y));
}

void Enemy::Shoot()
{
	const float bottom = pos.y + height / 2;

	if (reload <= 0)
	{
		reload = 0.1f;
		bullets.push_back(std::make_unique<Bullet>(Vec2(pos.x, bottom), dmg, false));
	}
}
