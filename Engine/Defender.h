#pragma once
#include"Graphics.h"
#include"img.h"
#include"RectF.h"
#include"Vec2.h"
#include"Keyboard.h"
#include "Bullet.h"

class Defender
{
public:

	Defender() = default;
	Defender(const Vec2& pos_in, float speed_in);
	void Draw(Graphics& gfx);
	void Update(Keyboard& kbd,Graphics&gfx,float dt);
	const Vec2& GetPos();
	//void Respawn();
	float dmg = 30.0f;
	float colRadius = 50.0f;

	std::vector<Bullet*> bullets;

	Vec2 pos;
private:

	void Shoot();


	
	Vec2 dir{ 0.0f,0.0f };
	static constexpr float width =75;
	static constexpr  float height=60;
	float speed;
	float reload = 0;

};
