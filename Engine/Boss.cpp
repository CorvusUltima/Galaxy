#include "Boss.h"

Boss::Boss(const Model model, const Vec2& pos)
	:
	model(model),
	pos(pos)

{
	switch(model)
	{
	case Model::lvl1:

		width = 150.0f;
		height = 120.0f;
		speed = 60.0f;
		colRadius = width / 2;

	 break;
	}
}

void Boss::Draw(Graphics& gfx)
{
	const Vec2 HP_Bar_topleft= Vec2(pos.x - width / 2.0f, pos.y - height / 2.0f - 10.0f);;


	switch(model)
	{
	case Model::lvl1:

		img::Boss_test(pos,gfx);

		break;

	}

	img::HP_Bar(HP_Bar_topleft,width,10.0f,HealthMax,HealthCurent,gfx);
}

void Boss::Update(float dt, Graphics& gfx)
{
	if (GoUp) pos.y -= speed * dt;
	if (GoDown)pos.y+= speed * dt;
	if (GoRight)pos.x += speed * dt;
	if (GoLeft)pos.x -= speed * dt;

	 if (pos.y >= gfx.ScreenHeight/2 + 100)
	{
		GoDown =false;
		GoUp = true;
	}
	 else if (pos.y<=150)
	 {
		 GoDown = true;
		 GoUp = false;
	 }
	 if (pos.x >= gfx.ScreenWidth - width)
	 {
		 GoRight = false;
		 GoLeft = true;
	 }
	 else if (pos.x <= gfx.ScreenLeft + width)
	 {
		 GoRight = true;
		 GoLeft = false;
	 }
	 Shot();
	 reloadTime_current -= dt;
}

float Boss::GetDmg()
{
	return dmg;
}

Vec2 Boss::GetPos()
{
	return  pos;
}

CircleF Boss::GetColCircle() const
{
	return CircleF(pos, colRadius);
}

void Boss::TakeDmg(float dmg)
{
	HealthCurent -= dmg;
}

bool Boss::bDead()
{
	return Dead;
}


void Boss::Shot()
{
	const float bottom = pos.y + height / 2;


	if (reloadTime_current <= 0)
	{

		reloadTime_current = reloadTime_max;
		bullets.push_back(std::make_unique<Bullet>(CircleF(Vec2(pos.x, bottom), 6.0f), Vec2(BulletAng, 1.0f), Colors::Red, 150.0f, dmg));
		
		
		if (BulletAng >= 8.0f || BulletAng >= -8.0f)
		{
			if(RightLeft)BulletAng -= 1.0f;
			if(LeftRight)BulletAng += 1.0f;
			if (RightLeft && BulletAng  <= -6.0f)
			{
				RightLeft = false;
				LeftRight = true;
			}
			else if (LeftRight && BulletAng >=8.0f)
			{
				RightLeft = true;
				LeftRight =false;
			}
		}
		
		
	}
}
		
