#include "menu.h"


void Menu::Button::Draw(Graphics& gfx, Type& type, int x, int y)
{
	if (type == Type::sound)
	{
		gfx.DrawSprite(x, y, sound);
		position++;
	}
}


void Menu::DrawMenu(Graphics& gfx)
{
	
	for (int i = 0; i < nbuttons; i++)
	{
		if (i == 1 )type = Button::Type::sound;
		
		buttons[i].Draw(gfx,type,pos.x, pos. y);
	}
}
