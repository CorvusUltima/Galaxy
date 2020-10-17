#pragma once
#include "Graphics.h"
#include "rng.h"

class Space
{
private:
	class Star
	{
	public:
		Star() = default;
		Star(float Speed, Color c, Graphics& gfx);
		void Draw(Graphics& gfx);
		void Update(float dt, Graphics& gfx);

	private:
		float x;
		float y;
		Color c;
		float fSpeed;
	};
public:
	Space(float WorldSpeed, Graphics& gfx);
	void Draw(Graphics& gfx);
	void Update(float dt, Graphics& gfx);
	float GetDistance() const;

private:
	static constexpr int nStars = 1500;
	Star stars[nStars];
	float fWorldSpeed;
	float fDistance = 0;
};

