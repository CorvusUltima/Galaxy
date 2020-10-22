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
	//50x50
	static void def_Interceptor(const Vec2& center, Graphics& gfx);
	//70x80
	static void def_Destroyer(const Vec2& center, Graphics& gfx);
	//120x100
	static void def_Battleship(const Vec2& center, Graphics& gfx);
	//40x40
	static void TestEnemy(const Vec2& center, Graphics& gfx);
	//58x58
	static void Enemy_Mine(const Vec2& center, Graphics& gfx);
	//150x120
	static void Boss_test(const Vec2& center, Graphics& gfx);

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
