#include "Space.h"

Space::Star::Star(float fSpeed, Color c, Graphics& gfx)
	:
	fSpeed (fSpeed),
	c (c)
{
	x = rng::rdm_float(0, (float)gfx.ScreenWidth);
	y = rng::rdm_float(0, (float)gfx.ScreenHeight);
}

void Space::Star::Draw(Graphics& gfx)
{
	if(y < (float)(gfx.ScreenHeight - 1) && y > 0)
	gfx.PutPixel((int)x, (int)y, c);
}

void Space::Star::Update(float dt, Graphics& gfx)
{
	y += fSpeed * dt;
	if (y >= (float)(gfx.ScreenHeight - 1))
	{
		x = rng::rdm_float(0, (float)gfx.ScreenWidth);
		y = 0;
	}
}

Space::Space(float WorldSpeed, Graphics& gfx)
	:
	fWorldSpeed(WorldSpeed)
{
	for (int i = 0; i < nStars; i++)
	{
		if (i < nStars / 3) stars[i] = Star(fWorldSpeed, Colors::MakeRGB(255, 255, 255), gfx);
		else if (i < (nStars / 3) * 2) stars[i] = Star(fWorldSpeed * 0.7f, Colors::MakeRGB(192, 192, 192), gfx);
		else if (i < nStars) stars[i] = Star(fWorldSpeed * 0.4f, Colors::MakeRGB(128, 128, 128), gfx);
	}
}

void Space::Draw(Graphics& gfx) 
{
	for (auto& s : stars) s.Draw(gfx);
}

void Space::Update(float dt, Graphics& gfx)
{
	fDistance += (fWorldSpeed * dt) / 10.0f;
	for (auto& s : stars) s.Update(dt, gfx);
}

float Space::GetDistance() const
{
	return fDistance;
}
