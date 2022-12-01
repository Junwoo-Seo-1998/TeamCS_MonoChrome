/******************************************************************************/
/*
    File name: Destination.cpp
    Project name: Monochrome
    Author(s): ChunMook Kim
    All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include"Destination.h"
#include "engine\State.h"
Destination::Destination(State * current_level)
    :Object(), p_level(current_level)
{}

Destination::~Destination()
{
    p_level->RemoveObject(this);
}

void Destination::init(std::string name, float positionX, float positionY, SDL_Color color)
{
    SetName(name.c_str());
    transform.position.Set(positionX, positionY, 0);
    transform.SetScale(64, 64);
    sprite.color = color;
    sprite.LoadImage("texture/destination.png", p_level->m_renderer);
    physics.pOwnerTransform = &transform;
    physics.bodyType = Physics::STATIC;
    physics.bodyShape = Physics::BOX;
    physics.radius = 16;
    physics.SetRestitution(0.f);
    physics.GenerateBody(p_level->GetPhysicsWorld(), &transform);
    p_level->AddObject(this);
}

void Destination::update(float)//dt)
{

}
