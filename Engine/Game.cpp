/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include<iostream>

Game::Game(MainWindow& wnd)
    :
    wnd(wnd),
    gfx(wnd),
    space(fWorldSpeed, gfx),
    def(Vec2(400.0f, 300.0f), 300.0f),
    testEnemy(Vec2(400.0f, 100.0f)),
    menu(Vec2(400,0),5)
   
    
{ 
}

void Game::Go()
{

	gfx.BeginFrame();
    float ElapsedTime = ft.Mark();
    while (ElapsedTime > 0.0f)
    {
        const float dt = std::min(0.0025f, ElapsedTime);
        UpdateModel(dt);
        ElapsedTime -= dt;
    }
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
    menu.Update(wnd.kbd, dt);
    
    if (wnd.kbd.KeyIsPressed(VK_SPACE))
    {
        GS = GameState::GameOn;
    }
    if (GS != GameState::GameOn)
    {
        GS = GameState::GamePaused;
   }
    
    
    switch (GS)
    {
    case Game::GameState::GameOn:

        space.Update(dt, gfx);
        def.Update(wnd.kbd, gfx, dt);
        for (auto b : def.bullets)
        {
            b->Update(dt);
            if (!testEnemy.bDead && b->bHitTarget(testEnemy.GetPos(), testEnemy.colRadius))
            {
                testEnemy.TakeDmg(def.dmg);
                gfx.DrawSprite((int)b->pos.x, (int)(b->pos.y - b->radius), surf);
            }
        }
        testEnemy.Update(dt, gfx);
        for (auto b : testEnemy.bullets)
        {
            b->Update(dt);
            b->bHitTarget(def.GetPos(), def.colRadius);

        }
        testEnemy.DoDefenderColision(def);
        break;
    case Game::GameState::GamePaused:
        break;
    }
   
   
}

void Game::Gif6(int& slider, Graphics& gfx, Vec2& centar, const  std::string& vol1, const std::string& vol2, const std::string& vol3, const  std::string& vol4, const std::string& vol5, const  std::string& vol6)

    {
        Surface s1 = Surface(vol1);
        Surface s2 = Surface(vol2);
        Surface s3 = Surface(vol3);
        Surface s4 = Surface(vol4);
        Surface s5 = Surface(vol5);
        Surface s6 = Surface(vol6);


        slider++;

        if (slider > 0 && slider < 1)
        {
            gfx.DrawSprite(centar.x, centar.y, s1);
        }

        if (slider > 1 && slider < 2)

        {
            gfx.DrawSprite(centar.x, centar.y, s2);
        }


        if (slider >2&& slider <3)

        {
            gfx.DrawSprite(centar.x, centar.y, s3);
        }

        if (slider >3 && slider <4)

        {
            gfx.DrawSprite(centar.x, centar.y, s4);;
        }
        if (slider > 4 && slider <6)

        {
            gfx.DrawSprite(centar.x, centar.y, s5);
        }
        if (slider >6&& slider <8)

        {
            gfx.DrawSprite(centar.x, centar.y, s6);;
        }

        
    
}




void Game::ComposeFrame()
{ 
   // gfx.DrawSprite(0,0, surf);
    space.Draw(gfx);
    def.Draw(gfx);
    for (auto b : def.bullets) b->Draw(gfx);
    gfx.DrawSprite(gfx.ScreenWidth-20, 0, down);
   
    menu.DrawMenu(gfx);
    
    if (!testEnemy.DoDefenderColision(def))
    {
        testEnemy.Draw(gfx);

    }
    for (auto b : testEnemy.bullets) b->Draw(gfx);
    test++;
    
}

