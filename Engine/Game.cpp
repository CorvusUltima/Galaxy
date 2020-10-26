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
    menu(Vec2(gfx.ScreenWidth/2,100),4,2),
    barmenu(Vec2(gfx.ScreenWidth / 2-300, 150), 0, 3),
    space(fWorldSpeed, gfx),
    boss(Boss::Model::lvl1,Vec2(200.0f,200.0f)),
    btn_diff_easy({ 350.0f, 445.0f, 550.0f, 585.0f }, Surface("btn_easy_unselected.bmp"), Surface("btn_easy_hovered.bmp"), Surface("btn_easy_selected.bmp")),
    btn_diff_normal({ 520.0f, 670.0f, 550.0f, 585.0f }, Surface("btn_normal_unselected.bmp"), Surface("btn_normal_hovered.bmp"), Surface("btn_normal_selected.bmp")),
    btn_diff_hard({ 745.0f, 845.0f, 550.0f, 585.0f }, Surface("btn_hard_unselected.bmp"), Surface("btn_hard_hovered.bmp"), Surface("btn_hard_selected.bmp")),
    btn_start_inactive({530.0f, 650.0f, 700.0f, 735.0f}, Surface("btn_StartInactive.bmp"), Surface("btn_StartInactive.bmp"), Surface("btn_StartInactive.bmp")),
    btn_start_active({ 530.0f, 650.0f, 700.0f, 735.0f }, Surface("btn_StartActive_unselected.bmp"), Surface("btn_StartActive_hovered.bmp"), Surface("btn_StartActive_hovered.bmp")),
    btn_interceptor({ 260.0f, 390.0f, 180.0f, 290.0f }, Surface("btn_Interceptor_unselected.bmp"), Surface("btn_Interceptor_hovered.bmp"), Surface("btn_Interceptor_selected.bmp")),
    btn_destroyer({ 530.0f, 660.0f, 180.0f, 290.0f }, Surface("btn_Destroyer_unselected.bmp"), Surface("btn_Destroyer_hovered.bmp"), Surface("btn_Destroyer_selected.bmp")),
    btn_battleship({ 800.0f, 930.0f, 180.0f, 290.0f }, Surface("btn_Battleship_unselected.bmp"), Surface("btn_Battleship_hovered.bmp"), Surface("btn_Battleship_selected.bmp")),
    Laser(L"laserGun.wav"),
    ExplosionLarge(L"ExplosionLarge.wav"),
    ExplosionScif(L"ExplosionSciF.wav")

    
{
}

void Game::Go()
{

	gfx.BeginFrame();
    SpawnEnemies();
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

        //Pointer movement
        Vec2 dir = { 0, 0 };
        if (wnd.kbd.KeyIsPressed(VK_LEFT)) dir.x -= 1.0f;
        if (wnd.kbd.KeyIsPressed(VK_RIGHT)) dir.x += 1.0f;
        if (wnd.kbd.KeyIsPressed(VK_UP)) dir.y -= 1.0f;
        if (wnd.kbd.KeyIsPressed(VK_DOWN)) dir.y += 1.0f;
        pointer += dir.GetNormalized() * 500.0f * dt;
        if (pointer.x > float(gfx.ScreenRight) - 6.0f)
        {
            pointer.x = float(gfx.ScreenRight) - 6.0f;
        }
        else if (pointer.x <= float(gfx.ScreenLeft) + 6.0f)
        {
            pointer.x = float(gfx.ScreenLeft) + 6.0f;
        }
        if (pointer.y <= float(gfx.ScreenTop) + 6.0f)
        {
            pointer.y = float(gfx.ScreenTop) + 6.0f;
        }
        else if (pointer.y > float(gfx.ScreenBottom) - 6.0f)
        {
            pointer.y = float(gfx.ScreenBottom) - 6.0f;

        }

        //Defender selection
        btn_interceptor.Update(wnd.kbd, pointer, dt);
        if (btn_interceptor.bSelected)
        {
            btn_destroyer.bSelected = false;
            btn_battleship.bSelected = false;
        }
        btn_destroyer.Update(wnd.kbd, pointer, dt);
        if (btn_destroyer.bSelected)
        {
            btn_interceptor.bSelected = false;
            btn_battleship.bSelected = false;
        }
        btn_battleship.Update(wnd.kbd, pointer, dt);
        if (btn_battleship.bSelected)
        {
            btn_interceptor.bSelected = false;
            btn_destroyer.bSelected = false;
        }

        //Difficulty selection
        btn_diff_easy.Update(wnd.kbd, pointer, dt);
        if (btn_diff_easy.bSelected)
        {
            btn_diff_normal.bSelected = false;
            btn_diff_hard.bSelected = false;
        }
        btn_diff_normal.Update(wnd.kbd, pointer, dt);
        if (btn_diff_normal.bSelected)
        {
            btn_diff_easy.bSelected = false;
            btn_diff_hard.bSelected = false;
        }
        btn_diff_hard.Update(wnd.kbd, pointer, dt);
        if (btn_diff_hard.bSelected)
        {
            btn_diff_easy.bSelected = false;
            btn_diff_normal.bSelected = false;
        }

        //Able to start game only if aircraft and difficulty is selected
        if ((btn_interceptor.bSelected || btn_destroyer.bSelected || btn_battleship.bSelected)
            && (btn_diff_easy.bSelected || btn_diff_normal.bSelected || btn_diff_hard.bSelected))
            btn_start_active.Update(wnd.kbd, pointer, dt);
        if (btn_start_active.bSelected) GameState = GameState::Loading;

        break;

    case GameState::Loading:

        Defender::Model model;
        Defender::Difficulty diff;
        if (btn_interceptor.bSelected) model = Defender::Model::Interceptor;
        else if (btn_destroyer.bSelected) model = Defender::Model::Destroyer;
        else if (btn_battleship.bSelected) model = Defender::Model::Battleship;
        if (btn_diff_easy.bSelected) diff = Defender::Difficulty::Easy;
        else if (btn_diff_normal.bSelected) diff = Defender::Difficulty::Normal;
        else if (btn_diff_hard.bSelected) diff = Defender::Difficulty::Hard;
        def = { Vec2(400.0f, 600.0f), model, diff };
        GameState = GameState::Playing;
        break;

    case Game::GameState::Playing:

        fElapsedTime += dt; //Measures time passed from the start of the game

        //while(enemy.size() < 2) enemy.push_back(std::make_unique <Enemy>(Enemy::Model::test, Vec2(rng::rdm_float(330.0f, 830.0f), 50.0f))); //Infinite enemies just for testing

        space.Update(dt, gfx);
        def.Update(wnd.kbd, gfx, dt);
        boss.Update(dt, gfx);
        
        
        for (int i = 0; i < boss.bullets.size(); i++)// update boss bullts 
        {
           boss.bullets[i]->Update(dt);
           boss.bullets[i]->delete_offscreen(gfx); //Mark bullets that are off screen to be deleted

        }
        

           
        for (int i = 0; i < def.bullets.size(); i++) //Update defender bullets
        {
            def.bullets[i]->Update(dt);
            Laser.Play(1.0f, barmenu.SfxVolume());
            def.bullets[i]->delete_offscreen(gfx); //Mark bullets that are off screen to be deleted
            for (int j = 0; j < enemy.size(); j++)
            if (def.bullets[i]->isTargetHit(CircleF(enemy[j]->GetColCircle()))) //Check collision against all enemies
            {
                enemy[j]->TakeDmg(def.GetDmg());
                if (enemy[j]->GetHealth() <= 0) def.AddScore(enemy[j]->fScore); //Update score if enemy is killed;
                explo.push_back(std::make_unique<Explosion>(def.bullets[i]->circle.center, Explosion::Size::Small)); //Create explosion at the site of impact
            }
            if (def.bullets[i]->bDeleted) def.bullets.erase(std::remove(def.bullets.begin(), def.bullets.end(), def.bullets[i])); //Delete bullets if needed
            
        }
        for (int i = 0; i < enemy.size(); i++) //Update enemies
        {
            enemy[i]->Update(dt, gfx);
            if (enemy[i]->hasCrashedInto(def.GetColCircle()))  //Check if enemy crashed into defender
            {
                def.TakeDmg(enemy[i]->collision_dmg);
                def.AddScore(enemy[i]->fScore);
            }
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
               ExplosionLarge.Play(1.0f,barmenu.SfxVolume());
                enemy[i]->mark_remove(gfx); //Mark enemies that need to be deleted
                if(enemy[i]->BulletCount() == 0) enemy.erase(std::remove(enemy.begin(), enemy.end(), enemy[i])); //Delete dead enemies when all their bullets are deleted
            }
        }
        for (int i = 0; i < explo.size(); i++) //Update and delete explosions
        {
            explo[i]->Update(dt);
            if (explo[i]->bExpired) explo.erase(std::remove(explo.begin(), explo.end(), explo[i]));
        }

        if ( wnd.kbd.KeyIsPressed(VK_ESCAPE)) Game::GameState = Game::GameState::Paused;
       
        break;

    case Game::GameState::Paused:   
        menu.Update(wnd.kbd, dt);
        barmenu.BarUpdate(wnd.kbd, dt);

        if (menu.bResume && wnd.kbd.KeyIsPressed(VK_SPACE) && !menu.soundBarON)
        {

            Game::GameState = Game::GameState::Playing;

            menu.bResume = false;
        }

        if (menu.bSound && wnd.kbd.KeyIsPressed(VK_SPACE)) menu.soundBarON = true;
        if (menu.soundBarON && wnd.kbd.KeyIsPressed(VK_ESCAPE)) menu.soundBarON = false;
        if (barmenu.bBack)menu.soundBarON = false;
        barmenu.bBack = false;
            break;
    } 
}


void Game::ComposeFrame()
{ 
    switch (GameState)
    {
    case GameState::Playing:

        space.Draw(gfx); //Background
        numb.Draw(gfx.ScreenLeft + 20, gfx.ScreenBottom - 40, (int)space.GetDistance(), Colors::White, gfx); //Distance
        def.Draw(gfx);//Defender
        boss.Draw(gfx);
        for (int i = 0; i < def.bullets.size(); i++) def.bullets[i]->Draw(gfx); //Defender bullets

        for (int i = 0; i < enemy.size(); i++) //Enemies
        {
            enemy[i]->Draw(gfx);
            for (int j = 0; j < enemy[i]->bullets.size(); j++) enemy[i]->bullets[j]->Draw(gfx); //Enemy bullets
        }

        for (int i = 0; i < explo.size(); i++) explo[i]->Draw(gfx); //Explosions

        
        numb.Draw(gfx.ScreenRight - 80, gfx.ScreenTop + 10, (int)def.GetScore(), Colors::White, gfx); //Score
        

        for (int i = 0; i < boss.bullets.size(); i++)
        {
            boss.bullets[i]->Draw(gfx);
        }

        break;

    case GameState::SelectionScreen:
    {

        btn_interceptor.Draw(gfx);
        btn_destroyer.Draw(gfx);
        btn_battleship.Draw(gfx);
        btn_diff_easy.Draw(gfx);
        btn_diff_normal.Draw(gfx);
        btn_diff_hard.Draw(gfx);
        if ((btn_interceptor.bSelected || btn_destroyer.bSelected || btn_battleship.bSelected)
            && (btn_diff_easy.bSelected || btn_diff_normal.bSelected || btn_diff_hard.bSelected))
            btn_start_active.Draw(gfx);
        else btn_start_inactive.Draw(gfx);
        const float StatsBar_MaxWidth = 120.0f;
        const float StatsBar_Height = 10.0f;
        const float StatsBar_MaxValue = 100.0f;
        const float StatsBar_SegmentValue = 10.0f;
        if (btn_interceptor.bSelected || btn_interceptor.bHoveredOver)
        {
            gfx.DrawSprite(260, 150, Surface("btn_Interceptor_name.bmp"));
            gfx.DrawSprite(190, 300, Surface("btn_Defender_stats.bmp"));
            img::HP_Bar({ 270.0f, 300.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.125f * StatsBar_MaxValue * btn_interceptor.fBarPercentage, gfx, true, 10.0f); //Damage
            img::HP_Bar({ 270.0f, 315.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, StatsBar_MaxValue * btn_interceptor.fBarPercentage, gfx, true, 10.0f); //Attack Speed
            img::HP_Bar({ 270.0f, 330.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.333f * StatsBar_MaxValue * btn_interceptor.fBarPercentage, gfx, true, 10.0f); //Defense
            img::HP_Bar({ 270.0f, 345.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.83f * StatsBar_MaxValue * btn_interceptor.fBarPercentage, gfx, true, 10.0f); //Move Speed
        }
        if (btn_destroyer.bSelected || btn_destroyer.bHoveredOver)
        {
            gfx.DrawSprite(530, 150, Surface("btn_Destroyer_name.bmp"));
            gfx.DrawSprite(460, 300, Surface("btn_Defender_stats.bmp"));
            img::HP_Bar({ 540.0f, 300.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.92f * StatsBar_MaxValue * btn_destroyer.fBarPercentage, gfx, true, 10.0f); //Damage
            img::HP_Bar({ 540.0f, 315.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.24f * StatsBar_MaxValue * btn_destroyer.fBarPercentage, gfx, true, 10.0f); //Attack Speed
            img::HP_Bar({ 540.0f, 330.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.5f * StatsBar_MaxValue * btn_destroyer.fBarPercentage, gfx, true, 10.0f); //Defense
            img::HP_Bar({ 540.0f, 345.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.54f * StatsBar_MaxValue * btn_destroyer.fBarPercentage, gfx, true, 10.0f); //Move Speed
        }
        if (btn_battleship.bSelected || btn_battleship.bHoveredOver)
        {
            gfx.DrawSprite(800, 150, Surface("btn_Battleship_name.bmp"));
            gfx.DrawSprite(730, 300, Surface("btn_Defender_stats.bmp"));
            img::HP_Bar({ 810.0f, 300.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.42f * StatsBar_MaxValue * btn_battleship.fBarPercentage, gfx, true, 10.0f); //Damage
            img::HP_Bar({ 810.0f, 315.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.42f * StatsBar_MaxValue * btn_battleship.fBarPercentage, gfx, true, 10.0f); //Attack Speedd
            img::HP_Bar({ 810.0f, 330.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, StatsBar_MaxValue * btn_battleship.fBarPercentage, gfx, true, 10.0f); //Defense
            img::HP_Bar({ 810.0f, 345.0f }, StatsBar_MaxWidth, StatsBar_Height, StatsBar_MaxValue, 0.27f * StatsBar_MaxValue * btn_battleship.fBarPercentage, gfx, true, 10.0f); //Move Speed
        }

        gfx.DrawCircleEmpty((int)pointer.x, (int)pointer.y, 6, Colors::Orange); //Pointer
    }
        break;

    case GameState::Paused:

      

        if (!menu.bResume&&!menu.soundBarON) menu.DrawMenu(gfx);
      
       if (menu.soundBarON) barmenu.DrawBar(gfx);

    

       if (!menu.bResume && !wnd.kbd.KeyIsPressed(VK_SPACE) && !menu.soundBarON)
       {

            menu.DrawMenu(gfx);


       }

            break;

    }
    
}

void Game::SpawnEnemies()
{
    const int distance = (int)space.GetDistance();
    if (nWave < nWavesMax)
    {
        if (isSpawned[nWave]) nWave++;

        switch (nWave)
        {
        case 0:
            if (distance >= 30)
            {
                SpawnEnemy(Enemy::Model::test, 400);
                SpawnEnemy(Enemy::Model::test, 800);

                isSpawned[nWave] = true;
            }
            break;
        case 1:
            if (distance >= 60)
            {
                SpawnEnemy(Enemy::Model::Mine, 200);
                SpawnEnemy(Enemy::Model::Mine, 400);
                SpawnEnemy(Enemy::Model::Mine, 600);
                SpawnEnemy(Enemy::Model::Mine, 800);
                SpawnEnemy(Enemy::Model::Mine, 1000);

                isSpawned[nWave] = true;
            }
            break;
        case 2:
            if (distance >= 120)
            {
                SpawnEnemy(Enemy::Model::test, 300);
                SpawnEnemy(Enemy::Model::test, 600);
                SpawnEnemy(Enemy::Model::test, 900);

                isSpawned[nWave] = true;
            }
            break;
        default:
            break;
        }
    }
}