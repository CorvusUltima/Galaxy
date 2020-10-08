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
	Menu(Graphics& gfx);
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
		Button(Vec2& topLeft);
		void Draw(Graphics& gfx, int x,int y);
		bool IsInside(const RectF& button, Mouse& mouse);
		
	public:
	
		RectF rect;
		Type type;
		int position = 1;
		bool ButtonIsAddet = false;
		static constexpr int width = 200;
		static constexpr int height = 100;

	public:
		Surface sound = Surface("sound.bmp");
		Surface soundSelect = Surface("soundSelect.bmp");
	};

public:

	void DrawMenu();

private:

	
	Graphics& gfx;
	Vec2 pos = {gfx.ScreenWidth-200,100};
    int nbuttons=1;
	Button buttons[10];



};

