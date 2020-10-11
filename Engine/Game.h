/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Numbers.h"
#include "rng.h"
#include "FrameTimer.h"
#include "Vec2.h"
#include "Space.h"
#include "img.h"
#include"Defender.h"
#include"Surface.h"
#include"Enemy.h"
#include"CircleF.h"
#include"menu.h"


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
    FrameTimer ft;
	float fWorldSpeed = 180.0f;
	Space space;
	enum class GameState
	{
		GameOn,
		GamePaused
	};
	/********************************/


	//Testing purposes:
	GameState GS;
	int x = 400;
	int y = 300;
	Enemy  testEnemy;
	Defender def;
	Surface surf = Surface("vol333.bmp");
	Surface down = Surface("Down.bmp");
	CircleF cf;
	Menu menu;
	int test = 0;
	Vec2 kita{ 50.0f,50.0f };
	int slider = 0;
	void Gif6(int& slider, Graphics& gfx,Vec2& centar, const std::string& vol1,const std::string& vol2, const std::string& vol3, const std::string& vol4, const std::string& vol5, const std::string& vol6);	
}; 