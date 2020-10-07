#pragma once
#include"Graphics.h"
#include"img.h"
#include"RectF.h"
#include"Vec2.h"
#include"Keyboard.h"
#include "Bullet.h"
#include"CircleF.h"
#include <memory>

class Enemy
{
public:
	enum class Model
	{
		test
	};
	enum class MovePattern
	{
		Sinusoid_Down,
		ModelDefault
	};
	enum class FirePattern
	{
		SingleBullet_Down,
		ModelDefault
	};
	Enemy(const Model model, const Vec2& pos,
		const MovePattern MovePattern = MovePattern::ModelDefault, const FirePattern FirePattern = FirePattern::ModelDefault);
	void Draw(Graphics& gfx);
	void Update(float dt, Graphics& gfx);
	void TakeDmg(float dmg);
	Vec2 GetPos() const;
	float GetDmg() const;
	bool hasCrashedInto(const CircleF& circle);
	bool hasCrashedInto(const Vec2& coordinate);
	CircleF GetColCircle() const;

	float collision_dmg = 0;
	bool bDead = false;

	std::vector < std::unique_ptr<Bullet>> bullets;

private:
	void Move(float dt);
	void Shoot();

	Model model;
	MovePattern movePattern = MovePattern::ModelDefault;
	FirePattern firePattern = FirePattern::ModelDefault;
	Vec2 pos;
	float width = 0;
	float height = 0;
	float colRadius = 0;
	float speed = 0;
	float health_max = 0;
	float health_current = health_max;
	float dmg = 0;
	float fMoveTimer = 0;
	float reloadTime_max = 0;
	float reloadTime_current = reloadTime_max;

};

