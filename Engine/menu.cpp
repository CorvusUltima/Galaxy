#include "menu.h"










Menu::Button::Button(Vec2& topLeft)
{
	rect = RectF(topLeft, width, height);
}


void Menu::Button::Draw(Graphics& gfx,int  x,int y)
{

	if (type == Type::sound&&!IsSelected)
	{
		gfx.DrawSprite(int(rect.left), int(rect.top), sound);
	}
	else if (type == Type::sound && IsSelected)
	{

		gfx.DrawSprite(int(rect.left), int(rect.top), soundSelect);
	}
}

void Menu::Button::Update(Vec2& selector)
{
	if (selector.y ==rect.GetCenter().y)
	{

		IsSelected = true;
	}
}







Menu::Menu(const Vec2& topleft, int nbuttons)
	:
	topleft(topleft)
{

	for ( int i = 0; i < nbuttons; i++)
	{
		buttons[i] = { Vec2(topleft.x,topleft.y + (Button::height * i)) };
	}

	selector.y = buttons[0].rect.GetCenter().y;
	selector.x = buttons[0].rect.right + 5.0f;

}


void Menu::DrawMenu(Graphics& gfx)
{

	
	buttons[0].type = Button::Type::sound;
	buttons[1].type = Button::Type::sound;
	buttons[2].type = Button::Type::sound;

		buttons[0].Draw(gfx, topleft.x, topleft.y );
		buttons[1].Draw(gfx, topleft.x, topleft.y );
		

}

void Menu::Update(Keyboard& kbd)
{
	if (kbd.KeyIsPressed(VK_UP) && selector.y > buttons[0].height+topleft.y)
	{
		selector.y -= buttons[0].height;
	}
	if (kbd.KeyIsPressed(VK_DOWN) && selector.y < buttons[nbuttons].height + topleft.y)
	{
		selector.y += buttons[0].height;
	}

	if (selector.y ==buttons[nbuttons].rect.GetCenter().y)
	{

		buttons[nbuttons].IsSelected = true;
	}
	else if(selector.y != buttons[nbuttons].rect.GetCenter().y)
	{

		buttons[nbuttons].IsSelected = false;
	}
}



