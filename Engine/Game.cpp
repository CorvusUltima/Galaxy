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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    space(fWorldSpeed, gfx),
    btn_diff_easy({ 200.0f, 295.0f, 500.0f, 535.0f }, Surface("btn_easy_unselected.bmp"), Surface("btn_easy_hovered.bmp"), Surface("btn_easy_selected.bmp")),
    btn_diff_normal({ 299.0f, 449.0f, 500.0f, 535.0f }, Surface("btn_normal_unselected.bmp"), Surface("btn_normal_hovered.bmp"), Surface("btn_normal_selected.bmp")),
    btn_diff_hard({ 454.0f, 554.0f, 500.0f, 535.0f }, Surface("btn_hard_unselected.bmp"), Surface("btn_hard_hovered.bmp"), Surface("btn_hard_selected.bmp")),
    btn_start_inactive({550.0f, 670.0f, 600.0f, 635.0f}, Surface("btn_StartInactive.bmp"), Surface("btn_StartInactive.bmp"), Surface("btn_StartInactive.bmp")),
    btn_start_active({ 550.0f, 670.0f, 600.0f, 635.0f }, Surface("btn_StartActive_unselected.bmp"), Surface("btn_StartActive_hovered.bmp"), Surface("btn_StartActive_hovered.bmp"))
    
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
    switch (GameState)
    {
    case GameState::SelectionScreen:

        Vec2 dir = { 0, 0 };
        if (wnd.kbd.KeyIsPressed(VK_LEFT)) dir.x -= 1.0f;
        if (wnd.kbd.KeyIsPressed(VK_RIGHT)) dir.x += 1.0f;
        if (wnd.kbd.KeyIsPressed(VK_UP)) dir.y -= 1.0f;
        if (wnd.kbd.KeyIsPressed(VK_DOWN)) dir.y += 1.0f;
        pointer += dir.GetNormalized() * 300.0f * dt;

        btn_diff_easy.Update(wnd.kbd, pointer);
        if (btn_diff_easy.bSelected)
        {
            btn_diff_normal.bSelected = false;
            btn_diff_hard.bSelected = false;
        }
        btn_diff_normal.Update(wnd.kbd, pointer);
        if (btn_diff_normal.bSelected)
        {
            btn_diff_easy.bSelected = false;
            btn_diff_hard.bSelected = false;
        }
        btn_diff_hard.Update(wnd.kbd, pointer);
        if (btn_diff_hard.bSelected)
        {
            btn_diff_easy.bSelected = false;
            btn_diff_normal.bSelected = false;
        }

        if (btn_diff_easy.bSelected || btn_diff_normal.bSelected || btn_diff_hard.bSelected) btn_start_active.Update(wnd.kbd, pointer); //Able to start game only if difficulty is selected
        if (btn_start_active.bSelected) GameState = GameState::Loading;

        break;

    case GameState::Loading:

        Defender::Difficulty diff;
        diff = Defender::Difficulty::Easy;
        if (btn_diff_easy.bSelected) diff = Defender::Difficulty::Easy;
        else if (btn_diff_normal.bSelected) diff = Defender::Difficulty::Normal;
        else if (btn_diff_hard.bSelected) diff = Defender::Difficulty::Hard;
        def = { Vec2(400.0f, 600.0f), Defender::Model::Interceptor, diff };
        GameState = GameState::Playing;
        break;

    case Game::GameState::Playing:

        fElapsedTime += dt; //Measures time passed from the start of the game
        nWave = -1 + (int)(fElapsedTime / 3.0f); //Increases the wave by 1 every 3 seconds (temporary)
        SpawnWave(nWave);  //Spawn the current wave of enemies

        while(enemy.size() < 2) enemy.push_back(std::make_unique <Enemy>(Enemy::Model::test, Vec2(rng::rdm_float(330.0f, 830.0f), 50.0f))); //Infinite enemies just for testing

        space.Update(dt, gfx);
        def.Update(wnd.kbd, gfx, dt);
        for (int i = 0; i < def.bullets.size(); i++) //Update defender bullets
        {
            def.bullets[i]->Update(dt);
            def.bullets[i]->delete_offscreen(gfx); //Mark bullets that are off screen to be deleted
            for (int j = 0; j < enemy.size(); j++)
            if (def.bullets[i]->isTargetHit(CircleF(enemy[j]->GetColCircle()))) //Check collision against all enemies
            {
                enemy[j]->TakeDmg(def.GetDmg());
                explo.push_back(std::make_unique<Explosion>(def.bullets[i]->circle.center, Explosion::Size::Small)); //Create explosion at the site of impact
            }
            if (def.bullets[i]->bDeleted) def.bullets.erase(std::remove(def.bullets.begin(), def.bullets.end(), def.bullets[i])); //Delete bullets if needed
            
        }
        for (int i = 0; i < enemy.size(); i++) //Update enemies
        {
            enemy[i]->Update(dt, gfx);
            if (enemy[i]->hasCrashedInto(def.GetPos())) def.TakeDmg(enemy[i]->collision_dmg); //Check if enemy crashed into defender
            for (int j = 0; j < enemy[i]->bullets.size(); j++) //Update bullets for all enemies
            {
                enemy[i]->bullets[j]->Update(dt, def.GetPos());
                enemy[i]->bullets[j]->delete_offscreen(gfx); //Mark bullets that are off screen to be deleted
                if (enemy[i]->bullets[j]->isTargetHit(def.GetColCircle())) //Check collision against the defender
                {
                    def.TakeDmg(enemy[i]->GetDmg());
                    explo.push_back(std::make_unique<Explosion>(enemy[i]->bullets[j]->circle.center, Explosion::Size::Small)); //Create explosion at the site of impact
                }
                if (enemy[i]->bullets[j]->bDeleted) enemy[i]->bullets.erase(std::remove(enemy[i]->bullets.begin(), enemy[i]->bullets.end(), enemy[i]->bullets[j])); //Delete bullets if needed
            }
            if (enemy[i]->bDead) //Check if any enemy is dead
            {
                explo.push_back(std::make_unique<Explosion>(enemy[i]->GetPos(), Explosion::Size::Medium)); //Create explosion where enemy died
                enemy[i]->mark_remove(gfx); //Mark enemies that need to be deleted
                if(enemy[i]->BulletCount() == 0) enemy.erase(std::remove(enemy.begin(), enemy.end(), enemy[i])); //Delete dead enemies when all their bullets are deleted
            }
        }
        for (int i = 0; i < explo.size(); i++) //Update and delete explosions
        {
            explo[i]->Update(dt);
            if (explo[i]->bExpired) explo.erase(std::remove(explo.begin(), explo.end(), explo[i]));
        }
        break;
    case Game::GameState::Paused:
        break;
    }
   
   
}

void Game::ComposeFrame()
{ 
    switch (GameState)
    {
    case GameState::Playing:

        space.Draw(gfx); //Background
        def.Draw(gfx); //Defender
        for (int i = 0; i < def.bullets.size(); i++) def.bullets[i]->Draw(gfx); //Defender bullets

        for (int i = 0; i < enemy.size(); i++) //Enemies
        {
            enemy[i]->Draw(gfx);
            for (int j = 0; j < enemy[i]->bullets.size(); j++) enemy[i]->bullets[j]->Draw(gfx); //Enemy bullets
        }

        for (int i = 0; i < explo.size(); i++) explo[i]->Draw(gfx); //Explosions

        break;

    case GameState::SelectionScreen:

        btn_diff_easy.Draw(gfx);
        btn_diff_normal.Draw(gfx);
        btn_diff_hard.Draw(gfx);
        if (btn_diff_easy.bSelected || btn_diff_normal.bSelected || btn_diff_hard.bSelected) btn_start_active.Draw(gfx);
        else btn_start_inactive.Draw(gfx);

        gfx.DrawCircleEmpty((int)pointer.x, (int)pointer.y, 6, Colors::Orange); //Pointer

        break;
    }
}

