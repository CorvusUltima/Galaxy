#pragma once
#include"RectF.h"
#include"Vec2.h"
#include"Surface.h"
#include"Colors.h"
#include"Graphics.h"
class Menu
{
private:
	class Button
	{
	public:
     
		
		enum class Type
		{
			sound
		};

		void Draw(Graphics& gfx, Type& type,int x,int y);

		Type& type;
		int position = 1;
		bool ButtonIsAddet = false;
		Surface sound;
	};

public:
	
	Menu(Graphics& gfx);
	Menu() = default;
	void DrawMenu(Graphics& gfx);
	Menu() = default;

private:

	
	Graphics& gfx;
	Vec2 pos = {gfx.ScreenWidth-200,100};
	static const int nButtonsMax = 10;
	Button buttons[nButtonsMax];
	int nbuttons=1;



};

