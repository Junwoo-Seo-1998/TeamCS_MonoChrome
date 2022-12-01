/******************************************************************************/
/*
File name: Paint.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Paint.h"
#include "PaintBall.h"
#include "engine/State.h"
Paint::Paint(State * current_level):p_level(current_level),drop_rate(3.f),current_rate(0.f)
{
}
Paint::~Paint()
{
    for (auto paintball : paintballs)
    {
        delete paintball;
    }
    paintballs.clear();
    p_level->RemoveObject(this);
}
void Paint::init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color)
{
    SetName(name.c_str());
    transform.position.Set(positionX, positionY, 0);
    transform.SetScale(scaleX, scaleY);
    sprite.color = color;
    sprite.LoadImage("texture/paint.png", p_level->m_renderer);
    p_level->AddObject(this);
}

void Paint::update(float dt)
{
    DropPaint(dt, sprite.color);
    for (auto paintball : paintballs)
    {
        paintball->update(dt);
    }
    paintballs.remove_if([](PaintBall*paintball) {
	if (paintball->is_dead)
	{
	    delete paintball;
	    return true;
	}
	return false;
    });

}

void Paint::DropPaint(float dt,SDL_Color color)
{
    if (current_rate<=0.f)
    {
	PaintBall*paint = new PaintBall(p_level);
	paint->init("paint", transform.position.x, transform.position.y, 10, 10, color);
	paint->physics.SetVelocity({0,-10});
	paintballs.push_front(paint);//do not for get del it's just for test
	current_rate = drop_rate;
    }
    else
	current_rate -= dt;
	
    
}
