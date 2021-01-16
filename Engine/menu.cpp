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
	case Type::resume:
		if (!IsSelected) gfx.DrawSprite(int(rect.left), int(rect.top), resume);
		else gfx.DrawSprite(int(rect.left), int(rect.top), resumeSelect);

	}
}

void Menu::Button::DrawSelector(Graphics& gfx, Menu& menu)
{
	Surface selector = Surface("leftpointer.bmp");
	gfx.DrawSprite(menu.selector.x, menu.selector.y - 10, selector);

}


Menu::Menu(const Vec2& topleft, int nbuttons,int nbars)
	:
	topleft(topleft),
	nbuttons(nbuttons),
	nbars(nbars)
{

	for ( int i = 0; i < nbuttons; i++)
	{
		buttons[i] = { Vec2(topleft.x,topleft.y + (Button::height * i)) };

		switch (i)  //Initialize button types
		{
		case 0:
			buttons[i].type = Button::Type::resume;
			break;
		case 1:
			buttons[i].type = Button::Type::sound;
			break;
		}
	}

	selector = { buttons[0].rect.right + 5.0f, buttons[0].rect.GetCenter().y };

	for (int i = 0; i < nbars; i++)
	{

		bars[i] = { Vec2(topleft.x,topleft.y + (Bar::height * i)) };

		switch (i)  //Initialize exter memory precusor for atomic bomb ...nah just bar´s 
		{
		case 0:
			bars[i].type = Bar::Type::sfx;
			break;
		case 1:
			bars[i].type = Bar::Type::music;
			break;
		case 2:
			bars[i].type = Bar::Type::back;
			break;


		}

		BarSelector = { bars[0].rect.right + 5.0f, bars[0].rect.GetCenter().y };
	}





}


void Menu::DrawMenu(Graphics& gfx,Menu& menu)
{
	for (int i = 0; i < nbuttons; i++)
	{
		buttons[i].Draw(gfx);
		buttons[i].DrawSelector(gfx, menu);
	}
}



void Menu::DrawBar(Graphics& gfx,Menu&menu)
{
	for (int i = 0; i < nbars; i++)
	{
		bars[i].Draw(gfx);
		bars[i].DrawSelector(gfx, menu);
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
		else if (kbd.KeyIsPressed(VK_UP) && selector.y< buttons[0].rect.bottom && selector.y> buttons[0].rect.top)
		{
			
			selector.y = buttons[nbuttons - 1].rect.GetCenter().y;
		}
		
		
		if (kbd.KeyIsPressed(VK_DOWN) && selector.y < buttons[nbuttons - 1].rect.top) //Check if selector is currently pointing abow the menu button ([nbuttons - 1] pointing to the last one)
		{
			selector.y += Button::height;
		}
		else if (kbd.KeyIsPressed(VK_DOWN) && selector.y > buttons[nbuttons - 1].rect.top && selector.y < buttons[nbuttons - 1].rect.bottom)
		{
			selector.y = buttons[0].rect.GetCenter().y;
		}
		if (kbd.KeyIsPressed(VK_SPACE) && selector.y< buttons[0].rect.bottom && selector.y> buttons[0].rect.top)
		{
			bResume = true;
		}

		if (kbd.KeyIsPressed(VK_SPACE) && selector.y< buttons[1].rect.bottom && selector.y> buttons[1].rect.top)
		{
			bSound = true;
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

void Menu::BarUpdate(Keyboard& kbd, float dt,Graphics& gfx)
{



	//Updating selector position
	fSelectorMoveCooldown -= dt;
	if (fSelectorMoveCooldown <= 0)
	{

 		if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed(VK_DOWN))click.Play(bars[0].MaxSfxVolume, bars[0].SfxVolume);// just adding sound of clikcing while in menu 
		

		if (kbd.KeyIsPressed(VK_UP) &&BarSelector.y > bars[0].rect.bottom) //Check if selector is currently pointing below the first bar 
		{
			BarSelector.y -= Bar::height;
		}
		else if (kbd.KeyIsPressed(VK_UP) && BarSelector.y<bars[0].rect.bottom && BarSelector.y> bars[0].rect.top)
		{

			BarSelector.y = bars[nbars - 1].rect.GetCenter().y;
		}
		if (kbd.KeyIsPressed(VK_SPACE) && BarSelector.y< bars[2].rect.bottom && BarSelector.y> bars[2].rect.top)
		{
			bBack = true;
		}

		if (kbd.KeyIsPressed(VK_DOWN) && BarSelector.y < bars[nbars - 1].rect.top) //Check if selector is currently pointing abow the menu button ([nbuttons - 1] pointing to the last one)
		{
			BarSelector.y += Bar::height;
		}
		else if (kbd.KeyIsPressed(VK_DOWN) && BarSelector.y >bars[nbars - 1].rect.top && BarSelector.y < bars[nbars - 1].rect.bottom)
		{
			BarSelector.y = bars[0].rect.GetCenter().y;
		}
		if (kbd.KeyIsPressed(VK_SPACE) && BarSelector.y< bars[0].rect.bottom && BarSelector.y> bars[0].rect.top)
		{
			bSfx = true;
		}

		
		
		if (bars[0].BarIsSelected && kbd.KeyIsPressed(VK_LEFT) && bars[0].SfxVolume >= 0)
		{

			bars[0].SfxVolume -= 0.005f;

		}
		else if (bars[0].BarIsSelected && kbd.KeyIsPressed(VK_RIGHT) && bars[0].SfxVolume < bars[0].MaxSfxVolume)

		{

			bars[0].SfxVolume += 0.005f;

		}
		
		if (bars[1].BarIsSelected && kbd.KeyIsPressed(VK_LEFT) && bars[1].MusicVolume >= 0)
		{

			bars[1].MusicVolume -= 0.005f;

		}
		else if (bars[1].BarIsSelected && kbd.KeyIsPressed(VK_RIGHT) && bars[1].MusicVolume< bars[1].MaxMusicVolume)

		{

			bars[1].MusicVolume += 0.005f;

		}

		
		fSelectorMoveCooldown = 0.3f;

		

	}
	if (!kbd.KeyIsPressed(VK_UP) && !kbd.KeyIsPressed(VK_DOWN)) fSelectorMoveCooldown = 0; //Put selector off cooldown if commands for moving it aren't being pressed

	//Check and update which button is currently selected
	for (int i = 0; i < nbars; i++)
	{
		bars[i].BarIsSelected = BarSelector.y >bars[i].rect.top &&BarSelector.y < bars[i].rect.bottom;
		
	}
	

}

float Menu::SfxVolume()
{
	return bars[0].SfxVolume;
}

Vec2 Menu::GetSelector()
{
	return selector;
}

Menu::Bar::Bar(Vec2& topLeft)
{
	rect = RectF(topLeft, width, height);
}


void Menu::Bar::Draw(Graphics& gfx)
{
	switch (type)
	{
	case Type::sfx:
		if (!BarIsSelected) gfx.DrawSprite(int(rect.left), int(rect.top), sfx);
		else gfx.DrawSprite(int(rect.left), int(rect.top), sfxSelect);
		img::Status_Bar(Vec2(rect.left + 50, rect.top), width, height, MaxSfxVolume, SfxVolume, Colors::Green, gfx);
		break;

	case Type::music:
		if (!BarIsSelected) gfx.DrawSprite(int(rect.left), int(rect.top), music);
		else gfx.DrawSprite(int(rect.left), int(rect.top), musicSelect);
		img::Status_Bar(Vec2(rect.left + 50, rect.top), width, height, MaxMusicVolume,MusicVolume, Colors::Green, gfx);
		break;
	case Type::back:
		if (!BarIsSelected) gfx.DrawSprite(int(rect.left + 75), int(rect.top), back);
		else  gfx.DrawSprite(int(rect.left + 75), int(rect.top), backSelect);

		break;
	}

	if (Bar::type==Bar::Type::back)gfx.DrawRectEmpty((int)rect.left+ (int)75, (int)rect.top, (int)100, (int)height, (int)3, Colors::White);

	else
	gfx.DrawRectEmpty((int)rect.left, (int)rect.top, (int)width+50, (int)height,3, Colors::White );

}

void Menu::Bar::DrawSelector(Graphics& gfx,Menu& menu)
{
	Surface barselector = Surface("leftpointer.bmp");
	gfx.DrawSprite(menu.BarSelector.x, menu.BarSelector.y-10, barselector);

}
