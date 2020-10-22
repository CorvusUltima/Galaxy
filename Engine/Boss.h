#pragma once
#include"Graphics.h"
#include "Vec2.h"
#include"img.h"
#include"Bullet.h"




class Boss
{
public:

	enum class Model
	{
		lvl1,
		lvl2,
		lvl3  // dont ask me for the names right now i  am totaly blank at this moment .

	};



	Boss(const Model model , const Vec2& pos);
	
    void Draw(Graphics& gfx);
	void Update(float dt, Graphics& gfx);



private:

	Vec2 pos;
	Model model;
	float width;
	float height;
	float speed;
	float HealthMax = 0;
	float HealthCurent = HealthMax;




};

