/******************************************************************************/
/*
File name: PaintBall.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PaintBall.h"
#include "engine/State.h"
#include "Player.h"

PaintBall::PaintBall(State* current_level):Bullet(current_level)
{
}

PaintBall::~PaintBall()
{   
    p_level->RemoveObject(this);
}

void PaintBall::init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color)
{
    Bullet::init(name, positionX, positionY, scaleX, scaleY, color);
    sound_effect.SetName("paint_colide");
    sound_effect.sound.LoadSound("sound/paint_colide.wav");
    sound_effect.sound.SetVolume(100);
}

void PaintBall::update(float dt)
{
    timecount += dt;
    if (timecount >= 3.f)
    {
	is_dead = true;
    }
    if (physics.IsColliding())
	is_dead = true;
    if (physics.IsCollidingWith("player"))
    {
        sound_effect.sound.Play();
	Object*obj = physics.GetCollidingWith();
        Player* player = dynamic_cast<Player*>(obj);
        if(player==nullptr)
            return;
	player->having_color = sprite.color;  
    }
}
