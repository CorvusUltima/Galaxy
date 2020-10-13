#include "Defender.h"

Defender::Defender(const Vec2& pos, const Model model, const Difficulty diff)
	:
	pos(pos),
	model(model)
	
{
    SetDifficulty(diff);
    switch (model)
    {
    case Model::Fighter:
        width = 75.0f;
        height = 60.0f;
        speed = 480.0f;
        health_max = 400.0f;
        reloadTime_max = 0.08f;
        dmg = 8.0f;
        bulletSpeed = 600.0f;
        bulletRadius = 2.0f;
        break;
    case Model::Destroyer:
        width = 75.0f;
        height = 60.0f;
        speed = 0;
        health_max = 1000.0f;
        reloadTime_max = 0.3f;
        dmg = 30.0f;
        bulletSpeed = 500.0f;
        bulletRadius = 0;
        break;
    case Model::Battleship:
        width = 75.0f;
        height = 60.0f;
        speed = 0;
        health_max = 1000.0f;
        shield_max = 0;
        shield_recharge = 3.0f;
        reloadTime_max = 0.3f;
        dmg = 30.0f;
        bulletSpeed = 500.0f;
        bulletRadius = 0;
        break;
    }

    health_max *= diff_multiplier;
    health_current = health_max;
    shield_current = shield_max;
    dmg *= diff_multiplier;
    reloadTime_current = 0.0f;
    colRadius = std::max(width, height) / 2.0f;
}

void Defender::Draw(Graphics& gfx)

{
    RectF rect = { pos.x - width / 2.0f,  pos.x + width / 2.0f, pos.y - height / 2.0f, pos.y + height / 2.0f };

    img::HP_Bar(Vec2((float)(gfx.ScreenLeft + 10), (float)(gfx.ScreenTop + 10)), 200.0f, 30.0f, health_max, health_current, gfx);
    //Shield
    img::Status_Bar(Vec2((float)(gfx.ScreenLeft + 10), (float)(gfx.ScreenTop + 45)), 200.0f, 30.0f, shield_max, shield_current, Colors::Gray, gfx);

    //Reload timer
    Color c;
    if (reloadTime_current <= 0) c = Colors::White;
    else c = Colors::MakeRGB(96, 96, 96);
    img::Status_Bar({ rect.left, rect.bottom + 2.0f }, width, 3.0f, reloadTime_max, reloadTime_max - reloadTime_current, c, gfx);

    switch (model)
    {
    case Model::Fighter:
        img::TestAircraft((int)rect.left, (int)rect.top, gfx);
        break;
    case Model::Destroyer:

        break;
    case Model::Battleship:

        break;
    }

}

void Defender::Update(Keyboard& kbd,Graphics& gfx,float dt)
{
    if (shield_current < shield_max) shield_current += shield_recharge * dt;
    else shield_current = shield_max;
    if (health_current <= 0) bDead = true;

    dir = { 0.0f,0.0f };

    if (kbd.KeyIsPressed(VK_LEFT))
    {
        dir.x -= 1.0f;
    }
    if (kbd.KeyIsPressed(VK_RIGHT))
    {
        dir.x += 1.0f;
    }
    if (kbd.KeyIsPressed(VK_UP))  
    {
        dir.y -= 1.0f;
    }
    if (kbd.KeyIsPressed(VK_DOWN))                
    {
        dir.y += 1.0f;
    }
    pos += dir.GetNormalized() * speed*dt;
   
    const float right = pos.x + width / 2;
    const float left = pos.x - width / 2;
    const float top = pos.y - height / 2;
    const float bottom = pos.y + height / 2;
    
    if (right > float(gfx.ScreenRight))
    {
        pos.x = float(gfx.ScreenRight) - width / 2.0f;
    }
    else if (left <= float(gfx.ScreenLeft))
    {
        pos.x = float(gfx.ScreenLeft) + width / 2.0f;
    }
    if (top <= float(gfx.ScreenTop))
    {
        pos.y = float(gfx.ScreenTop) + height / 2.0f;
    }
    else if (bottom > float(gfx.ScreenBottom))
    {
        pos.y = float(gfx.ScreenBottom) - height / 2.0f;

    }

    reloadTime_current -= dt;

    if (kbd.KeyIsPressed(VK_SPACE)) Shoot();

}

void Defender::TakeDmg(float dmg)
{
    shield_current -= dmg;
    if (shield_current < 0.0f)
    {
        health_current += shield_current;
        shield_current = 0.0f;
    }
}

Vec2 Defender::GetPos() const
{
    return pos;
}

CircleF Defender::GetColCircle() const
{
    return CircleF(pos, colRadius);
}

float Defender::GetDmg() const
{
    return dmg;
}


void Defender::SetDifficulty(const Difficulty diff)
{
    difficulty = diff;

    switch (difficulty)
    {
    case Difficulty::Easy:
        diff_multiplier = 1.33f;
        break;
    case Difficulty::Normal:
        diff_multiplier = 1.0f;
        break;
    case Difficulty::Hard:
        diff_multiplier = 0.67f;
        break;
    }
}

void Defender::Shoot()
{
    const float left = pos.x - width / 2;
    const float top = pos.y - height / 2;

    if (reloadTime_current <= 0)
    {
        reloadTime_current = reloadTime_max;

        switch (model)
        {
        case Model::Fighter:
            bullets.push_back(std::make_unique<Bullet>(CircleF(Vec2(left + 25.0f, top), bulletRadius), Vec2(0.0f, -1.0f), Colors::Cyan, bulletSpeed, dmg));
            bullets.push_back(std::make_unique<Bullet>(CircleF(Vec2(left + 50.0f, top), bulletRadius), Vec2(0.0f, -1.0f), Colors::Cyan, bulletSpeed, dmg));
            break;
        case Model::Destroyer:
            break;
        case Model::Battleship:
            break;
        }
    }

}
