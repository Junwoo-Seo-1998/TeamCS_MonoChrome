/******************************************************************************/
/*
File name: Bullet.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Bullet.h"
#include "engine\State.h"
#include <iostream>

Bullet::Bullet(State * current_level) :Object(), p_level(current_level), is_dead(false),timecount(0.f)
{
}

Bullet::~Bullet()
{
	p_level->RemoveObject(this);
}

void Bullet::init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color)
{
	SetName(name.c_str());

	transform.position.Set(positionX, positionY, 0.f);
	transform.SetScale(scaleX, scaleY);

	sprite.color = color;
	sprite.LoadImage("texture/circle.png", p_level->m_renderer);
	physics.pOwnerTransform = &transform;
	physics.bodyType = Physics::DYNAMIC;
	physics.bodyShape = Physics::CIRCLE;
	physics.radius = scaleX;
	physics.SetRestitution(0.f);
	physics.GenerateBody(p_level->GetPhysicsWorld(), &transform);
	//physics.ActiveCollision(true);
	p_level->AddObject(this);
}

void Bullet::update(float dt)
{
    timecount += dt;
    if (timecount>=3.f)
    {
        is_dead = true;
    }
    colliding_update();
}

void Bullet::colliding_update()
{
	if(physics.IsColliding())
	    is_dead = true;
	if (physics.IsCollidingWith("cplatform"))
	{
	    Object*obj = physics.GetCollidingWith();
	    obj->sprite.color = sprite.color;
	}
        if (physics.IsCollidingWith("cplatform1"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform2"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform3"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform4"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform5"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform6"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform7"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform8"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform9"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
        if (physics.IsCollidingWith("cplatform10"))
        {
            Object*obj = physics.GetCollidingWith();
            obj->sprite.color = sprite.color;
        }
	if (physics.IsCollidingWith("player"))
	    is_dead = false;
}
