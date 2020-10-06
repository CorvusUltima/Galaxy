#include "menu.h"


void Menu::Button::Draw(Graphics& gfx, int x, int y)
{
	if (type == Type::sound)
	{
		gfx.DrawSprite(x, y, sound);
		position++;
	}
}


Menu::Menu(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Menu::DrawMenu()
{
	
	for (int i = 0; i < nbuttons; i++)
	{
		if (i == 1 )buttons[i].type = Button::Type::sound;
		
		buttons[i].Draw(gfx, pos.x, pos. y);
	}
}
