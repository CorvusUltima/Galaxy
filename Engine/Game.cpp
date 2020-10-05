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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    space(fWorldSpeed, gfx),
    def(Vec2(400.0f, 300.0f), 300.0f),
    testEnemy(Vec2(400.0f, 100.0f))
    
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
        for (int i = 0; i < def.bullets.size(); i++)
        {
            def.bullets[i]->Update(dt);
            def.bullets[i]->delete_offscreen(gfx);
            if (!testEnemy.bDead && def.bullets[i]->bHitTarget(testEnemy.GetPos(), testEnemy.colRadius))
            {
                testEnemy.TakeDmg(def.dmg);
                gfx.DrawSprite((int)def.bullets[i]->pos.x, (int)(def.bullets[i]->pos.y - def.bullets[i]->radius), surf);
            }
            if (def.bullets[i]->bDeleted) def.bullets.erase(std::remove(def.bullets.begin(), def.bullets.end(), def.bullets[i]));
            
        }
        testEnemy.Update(dt, gfx);
        for (int i = 0; i < testEnemy.bullets.size(); i++)
        {
            testEnemy.bullets[i]->Update(dt);
            testEnemy.bullets[i]->delete_offscreen(gfx);
            testEnemy.bullets[i]->bHitTarget(def.GetPos(), def.colRadius);
            if (testEnemy.bullets[i]->bDeleted) testEnemy.bullets.erase(std::remove(testEnemy.bullets.begin(), testEnemy.bullets.end(), testEnemy.bullets[i]));
        }
        testEnemy.DoDefenderColision(def);
        break;
    case Game::GameState::GamePaused:
        break;
    }
   
   
}

void Game::ComposeFrame()
{ 
   // gfx.DrawSprite(0,0, surf);
    space.Draw(gfx);
    def.Draw(gfx);
    for (int i = 0; i < def.bullets.size(); i++) def.bullets[i]->Draw(gfx);
    
    if (!testEnemy.DoDefenderColision(def))
    {
        testEnemy.Draw(gfx);
    }

    for (int i = 0; i < testEnemy.bullets.size(); i++) testEnemy.bullets[i]->Draw(gfx);

}

