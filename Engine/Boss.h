#pragma once
#include"Graphics.h"
#include "Vec2.h"
#include"img.h"
#include"Bullet.h"
#include<memory>




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
	Vec2 GetPos();
	std::vector<std::unique_ptr<Bullet>> bullets;


private:

	void Shot();


	Vec2 pos;
	Model model;
	float width;
	float height;
	float speed;
	float HealthMax = 100;
	float HealthCurent = HealthMax;
	float reloadTime_max =0.5f;
	float BulletAng =6.0f;
	float reloadTime_current = reloadTime_max;
	bool GoDown=false;//bool for Movement  of Boss in update 
	bool GoUp=true;//bool for Movement  of Boss in update 
	bool GoRight = true;//bool for Movement  of Boss in update 
	bool GoLeft = false;//bool for Movement  of Boss in update 
	bool RightLeft = true;//determens the direction of shooting angle for boss 
	bool LeftRight = false;//determens the direction of shooting angle for boss
};

