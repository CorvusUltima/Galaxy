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

		void Draw(Graphics& gfx, int x,int y);
		void Update();
		bool IsInside(RectF& button, Mouse& mouse);
	
		Type type;
		int position = 1;
		bool ButtonIsAddet = false;
		Surface sound;
		Surface soundSelect;

	};

public:

	void DrawMenu();

private:

	
	Graphics& gfx;
	Vec2 pos = {gfx.ScreenWidth-200,100};
	int nbuttons=1;
	Button buttons[10];



};

