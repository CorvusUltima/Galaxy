#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"
#include "Keyboard.h"
#include "Surface.h"
struct Button
{
public:
	Button(const RectF& rect, const Surface& unselected, const Surface& hoveredOver, const Surface& selected)
		:
		button(rect),
		unselected(unselected),
		hoveredOver(hoveredOver),
		selected(selected)
	{
	}
	void Update(const Keyboard& kbd, const Vec2& pointer, float dt)
	{
		bHoveredOver = button.isContaining(pointer);

		if (bHoveredOver && (kbd.KeyIsPressed(VK_RETURN) || kbd.KeyIsPressed(VK_SPACE))) bSelected = true;

		if (bSelected) fBarTimer = fBarTimerMax;
		else if (bHoveredOver) fBarTimer += dt;
		else fBarTimer = 0;
		if (fBarTimer < fBarTimerMax) fBarPercentage = fBarTimer / fBarTimerMax;
		else fBarPercentage = 1.0f;
	}
	void Draw(Graphics& gfx)
	{
		int x = (int)button.left;
		int y = (int)button.top;
		if (bSelected) gfx.DrawSprite(x, y, selected);
		else if (bHoveredOver) gfx.DrawSprite(x, y, hoveredOver);
		else gfx.DrawSprite(x, y, unselected);
	}

	RectF button;
	bool bSelected = false;
	bool bHoveredOver = false;
	Surface unselected;
	Surface hoveredOver;
	Surface selected;

	//Variables for drawing stats bar
	float fBarTimer = 0;
	static constexpr float fBarTimerMax = 1.2f;
	float fBarPercentage = 0;
};

