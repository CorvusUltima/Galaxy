#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "rng.h"
#include"RectF.h"
#include"Surface.h"
#include<string>

class img
{
public:
	//Spaceships
	//75x60
	static void TestAircraft(int x, int y, Graphics& gfx);
	//40x40
	static void TestEnemy(const Vec2& center, Graphics& gfx);
	//58x58
	static void Enemy_Mine(const Vec2& center, Graphics& gfx);

	//HP bar
	static void HP_Bar(const Vec2& topleft, float maxWidth, float height, float maxHealth, float currentHealth, Graphics& gfx, bool DivideSegments = false, float segmentHealth = 100.0f);
	//Status bar
	static void Status_Bar(const Vec2& topleft, float maxWidth, float height, float maxValue, float currentValue, Color c, Graphics& gfx);

	//Explosions
	//20x20
	static void Explosion_Small(const Vec2& center, Graphics& gfx);
	//24x24
	static void ExploM0(const Vec2& center, Graphics& gfx);
	//36x36
	static void ExploM1(const Vec2& center, Graphics& gfx);
	//40x40
	static void ExploM2(const Vec2& center, Graphics& gfx);
	//34x34
	static void ExploM3(const Vec2& center, Graphics& gfx);

};
