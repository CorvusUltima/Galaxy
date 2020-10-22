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
#include "Explosion.h"
#include"CircleF.h"
#include "Button.h"
#include <memory>
#include"menu.h"
#include"sound.h"
#include "Boss.h"


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void SpawnEnemies();
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	void SpawnEnemy(Enemy::Model model, int x_coordinate)
	{
		enemy.push_back(std::make_unique <Enemy>(model, Vec2((float)x_coordinate, 50.0f)));
	}
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
    FrameTimer ft;
	Numbers numb;
	float fWorldSpeed = 180.0f;
	Space space;
	enum class GameState
	{
		SelectionScreen,
		Loading,
		Playing,
		Paused

	};

	enum class MenuState
	{
	 Selection,
     MenuSelection,
	 BarSelection

	};
	/********************************/
	GameState GameState = GameState::SelectionScreen;
	Vec2 pointer = { 600.0f, 500.0f };
	Button btn_diff_easy;
	Button btn_diff_normal;
	Button btn_diff_hard;
	Button btn_start_inactive;
	Button btn_start_active;
	Button btn_interceptor;
	Button btn_destroyer;
	Button btn_battleship;
	Defender def;
	Color color;
	Menu menu;
	Menu barmenu;
	Boss boss;
	std::vector < std::unique_ptr < Enemy > > enemy; //Enemies
	std::vector < std::unique_ptr < Explosion > > explo; //Explosions (visual purposes)
	Sound Laser;
	Sound ExplosionLarge;
	Sound ExplosionScif;
	float fElapsedTime = 0;

	int nWave = -1; //Current wave of enemies
	static constexpr int nWavesMax = 100;
	bool isSpawned[nWavesMax] = { false }; //Bool for checking if the particular wave of enemies has already been spawned

}; 