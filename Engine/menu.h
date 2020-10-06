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
	
		Type type;
		Graphics gfx;
		int position = 1;
		bool ButtonIsAddet = false;
		Surface sound;
	};

public:
	
	 Menu() = default;
	void DrawMenu(Graphics& gfx);

private:

	
	Graphics& gfx;
	Button::Type& type;
	Vec2 pos = {gfx.ScreenWidth-200,100};
	int nbuttons=1;



};

