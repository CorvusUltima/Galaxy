#include "Enemy.h"

Enemy::Enemy(const Model model, const Vec2& pos, const MovePattern MovePattern, const FirePattern FirePattern)
	:
	model(model),
	pos(pos)
{
	movePattern = MovePattern;
	firePattern = FirePattern;

	switch (model)
	{
	case Model::test:
		width = 40.0f;
		height = 40.0f;
		speed = 60.0f;
		health_max = 90.0f;
		dmg = 10.0f;
		collision_dmg = 100.0f;
		reloadTime_max = 1.2f;
		if(MovePattern == MovePattern::ModelDefault) movePattern = MovePattern::Sinusoid_Down;
		if(FirePattern == FirePattern::ModelDefault) firePattern = FirePattern::SingleBullet_Down;
		break;
	case Model::Mine:
		width = 58.0f;
		height = 58.0f;
		speed = 30.0f;
		health_max = 350.0f;
		collision_dmg = 250.0f;
		if (MovePattern == MovePattern::ModelDefault) movePattern = MovePattern::StraightDown;
		if (FirePattern == FirePattern::ModelDefault) firePattern = FirePattern::None;
		break;
	}
	health_current = health_max;
	reloadTime_current = reloadTime_max;
	colRadius = std::max(width, height) / 2.0f;
	fMoveTimer = 0;

}

void Enemy::Draw(Graphics& gfx)
{
	const Vec2 HP_Bar_topleft = Vec2(pos.x - width / 2.0f, pos.y - height / 2.0f - 10.0f);

	switch (model)
	{
	case Model::test:
		img::TestEnemy(pos, gfx);
		break;
	case Model::Mine:
		img::Enemy_Mine(pos, gfx);
		break;
	}

	img::HP_Bar(HP_Bar_topleft, width, 5.0f, health_max, health_current, gfx);
}

void Enemy::Update(float dt, Graphics& gfx)
{
	if( health_current <= 0 ||
		(pos.y - height / 2.0f > (float)gfx.ScreenBottom + 15.0f)) //Enemy (and his health bar) went down off screen boundaries
		bDead = true;

	if (pos.y - height / 2.0f <= (float)gfx.ScreenBottom + 15.0f) //Move and shoot only if enemy (and his health bar) didn't go thorugh the bottom of the screen
	{
		Move(dt);
		Shoot();
	}
	reloadTime_current -= dt;
}

void Enemy::TakeDmg(float dmg)
{
	health_current -= dmg;
}

Vec2 Enemy::GetPos() const
{
	return pos;
}

float Enemy::GetDmg() const
{
	return dmg;
}

bool Enemy::hasCrashedInto(const CircleF& circle)
{
	if (GetColCircle().IsOverLapingWith(circle))
	{
		bDead = true;
		return true;
	}
	else return false;
}

bool Enemy::hasCrashedInto(const Vec2& coordinate)
{
	if (GetColCircle().isContaining(coordinate))
	{
		bDead = true;
		return true;
	}
	else return false;
}

CircleF Enemy::GetColCircle() const
{
	return CircleF(pos, colRadius);
}

void Enemy::mark_remove(Graphics& gfx)
{
	if (bDead) pos.y = (float)gfx.ScreenBottom + 15.0f + height / 2.0f;
}


const int Enemy::BulletCount() const
{
	return (int)bullets.size();
}

void Enemy::Move(float dt)
{
	pos.y += speed * dt;
	switch (movePattern)
	{
	case MovePattern::StraightDown:
		break;
	case MovePattern::Sinusoid_Down:
		fMoveTimer += 2.4f * dt;
		pos.x += 400.0f * cos(fMoveTimer) * dt;
		break;
	}
	
}

void Enemy::Shoot()
{
	const float bottom = pos.y + height / 2;

	if (reloadTime_current <= 0)
	{
		reloadTime_current = reloadTime_max;

		switch (firePattern)
		{
		case FirePattern::None:
			break;
		case FirePattern::SingleBullet_Down:
			bullets.push_back(std::make_unique<Bullet>(CircleF(Vec2(pos.x, bottom), 6.0f), Vec2(0.0f, 1.0f), Colors::Red, 500.0f, dmg));
			break;
		}
	}
}
