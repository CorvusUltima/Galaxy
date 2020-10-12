#include "menu.h"










Menu::Button::Button(Vec2& topLeft)
{
	rect = RectF(topLeft, width, height);
}


void Menu::Button::Draw(Graphics& gfx)
{
	//Now using switch statement to determine which button to draw
	switch (type)
	{
	case Type::sound:
		if(!IsSelected) gfx.DrawSprite(int(rect.left), int(rect.top), sound);
		else gfx.DrawSprite(int(rect.left), int(rect.top), soundSelect);
		break;
	}
}


Menu::Menu(const Vec2& topleft, int nbuttons)
	:
	topleft(topleft),
	nbuttons(nbuttons)
{

	for ( int i = 0; i < nbuttons; i++)
	{
		buttons[i] = { Vec2(topleft.x,topleft.y + (Button::height * i)) };

		switch (i)  //Initialize button types
		{
		case 0:
			buttons[i].type = Button::Type::sound;
			break;
		case 1:
			buttons[i].type = Button::Type::sound;
			break;
		case 2:
			buttons[i].type = Button::Type::sound;
			break;
		case 3:
			buttons[i].type = Button::Type::sound;
			break;
		case 4:
			buttons[i].type = Button::Type::sound;
			break;
		}
	}

	selector = { buttons[0].rect.right + 5.0f, buttons[0].rect.GetCenter().y };

}


void Menu::DrawMenu(Graphics& gfx)
{
	for (int i = 0; i < nbuttons; i++)
	{
		buttons[i].Draw(gfx);
	}
}

void Menu::Update(Keyboard& kbd, float dt)
{
	//Updating selector position
	fSelectorMoveCooldown -= dt;
	if (fSelectorMoveCooldown <= 0)
	{
		if (kbd.KeyIsPressed(VK_UP) && selector.y > buttons[0].rect.bottom) //Check if selector is currently pointing below the first menu button
		{
			selector.y -= Button::height;
		}
		if (kbd.KeyIsPressed(VK_DOWN) && selector.y < buttons[nbuttons - 1].rect.top) //Check if selector is currently pointing abow the menu button ([nbuttons - 1] pointing to the last one)
		{
			selector.y += Button::height;
		}
		fSelectorMoveCooldown = 0.3f;
	}
	if(!kbd.KeyIsPressed(VK_UP) && !kbd.KeyIsPressed(VK_DOWN)) fSelectorMoveCooldown = 0; //Put selector off cooldown if commands for moving it aren't being pressed

	//Check and update which button is currently selected
	for (int i = 0; i < nbuttons; i++)
	{
		buttons[i].IsSelected = selector.y > buttons[i].rect.top && selector.y < buttons[i].rect.bottom;
	}
}



