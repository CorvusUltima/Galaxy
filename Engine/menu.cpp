#include "menu.h"


void Menu::Button::Draw(Graphics& gfx, int x, int y)
{

	if (type == Type::sound)
	{
		gfx.DrawSprite(x, y, sound);
		position++;
	}
}

void Menu::Button::Update()
{
}

bool Menu::Button::IsInside(RectF& button, Mouse& mouse)
{
	       const int lmX = mouse.GetPosX();
		   const int lmY = mouse.GetPosY();
		return lmX > button.left && lmX <button.right && lmY >button.top && lmY < button.bottom ;
	
	
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
