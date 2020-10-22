#include "Boss.h"

Boss::Boss(const Model model, const Vec2& pos)
	:
	model(model),
	pos(pos)

{
	switch(model)
	{
	case Model::lvl1:

		width = 40.0f;
		height = 40.0f;
		speed = 3.0f;
	 break;
	}




}

void Boss::Draw(Graphics& gfx)
{
	const Vec2 HP_Bar_topleft= Vec2(pos.x - width / 2.0f, pos.y - height / 2.0f - 10.0f);;


	switch(model)
	{
	case Model::lvl1:

		img::TestEnemy(pos,gfx);

		break;

	}

	img::HP_Bar(HP_Bar_topleft,width,10.0f,HealthMax,HealthCurent,gfx);
}

void Boss::Update(float dt,Graphics&gfx)
{

	bool GoDown = true;
	bool GoUp = false;
	if (pos.y < gfx.ScreenHeight / 2 && GoDown && !GoUp) pos.y += speed * dt;
	else  if (pos.y >= gfx.ScreenHeight / 2)
	{
		pos.y -= speed * dt;
		GoDown = false;
		GoUp = true;
	}
	if (pos.y >= gfx.ScreenHeight - 115)
	{
		GoDown = true;
		GoUp = false;
	}
		
}
