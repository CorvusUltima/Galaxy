#include "menu.h"










Menu::Button::Button(Vec2& topLeft)
{
	rect = RectF(topLeft, width, height);
}

void Menu::Button::Draw(Graphics& gfx,int  x,int y)
{

	if (type == Type::sound)
	{
		gfx.DrawSprite(0.,0, sound);
	}
}




bool Menu::Button::IsInside(const RectF& button, Mouse& mouse)
{
	       const int lmX = mouse.GetPosX();
		   const int lmY = mouse.GetPosY();
		return lmX > button.left && lmX <button.right && lmY >button.top && lmY < button.bottom ;
	
	
}



Menu::Menu(const Vec2& topleft, int nbuttons)
	:
	topleft(topleft)
{

	for ( int i = 0; i < nbuttons; i++)
	{
		Button(Vec2(topleft.x,topleft.y + (Button::height * i)),  Button::width, Button::height);
	}

}


void Menu::DrawMenu(Graphics& gfx)
{
	
	for (int i = 0.0f; i < nbuttons; i++)
	{
		if (i ==0)buttons[i].type = Button::Type::sound;
		
		buttons[i].Draw(gfx,topleft.x,topleft. y);
	}
}
