#include "Defender.h"

Defender::Defender(const Vec2& pos_in, float speed_in)
	:
	pos(pos_in),
	speed(speed_in)
	
{
}

void Defender::Draw(Graphics& gfx)

{
	int x = int(pos.x - width/2 );
	int y = int(pos.y-height/2);

	img::TestAircraft(x, y, gfx);
}

void Defender::Update(Keyboard& kbd,Graphics& gfx,float dt)
{
  
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

    if (kbd.KeyIsPressed(VK_SPACE)) Shoot();

}

const Vec2& Defender::GetPos()
{
    return pos;
}


void Defender::Shoot()
{
    const float left = pos.x - width / 2;
    const float top = pos.y - height / 2;

    if (reloadTime_current <= 0)
    {
        reloadTime_current = reloadTime_max;

        bullets.push_back(std::make_unique<Bullet>(Vec2(left + 25.0f, top), Vec2(0.0f, -1.0f), dmg, true));
        bullets.push_back(std::make_unique<Bullet>(Vec2(left + 50.0f, top), Vec2(0.0f, -1.0f), dmg, true));
    }

}
