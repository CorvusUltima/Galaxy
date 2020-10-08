#pragma once
#include"RectF.h"
#include"Vec2.h"
#include"Surface.h"
#include"Colors.h"
#include"Graphics.h"
#include"Mouse.h"
class Menu
{
public:
	
private:
	class Button
	{
	public:
		enum class Type
		{
			sound,
			soundSelect
		};

	public:
		Button() = default;
		Button(Vec2& topLeft);
		void Draw(Graphics& gfx, int x,int y);
		bool IsInside(const RectF& button, Mouse& mouse);
		
	public:
	
		RectF rect;
		Type type;
		int position = 1;
		bool ButtonIsAddet = false;
		static constexpr float width = 200.0f;
		static constexpr float height = 100.0f;

	public:
		Surface sound = Surface("sound.bmp");
		Surface soundSelect = Surface("soundSelect.bmp");
	};

public:
	Menu(const Vec2& topleft, int nbuttons);
	void DrawMenu(Graphics& gfx);
	
private:

	Vec2 topleft;
    int nbuttons=1;
	Button buttons[10];



};

