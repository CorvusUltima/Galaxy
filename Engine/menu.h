#pragma once
#include"RectF.h"
#include"Vec2.h"
#include"Surface.h"
#include"Colors.h"
#include"Graphics.h"
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
			sound
		};
		void Draw(Graphics& gfx, int x,int y);
	
		Type type;
		int position = 1;
		bool ButtonIsAddet = false;
		Surface sound;
	};

public:

	void DrawMenu();

private:

	
	Graphics& gfx;
	Vec2 pos = {gfx.ScreenWidth-200,100};
	int nbuttons=1;
	Button buttons[10];



};

