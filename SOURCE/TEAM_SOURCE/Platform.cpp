/******************************************************************************/
/*
File name: Platform.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Platform.h"
#include "engine\State.h"
Platform::Platform(State * current_level)
:Object(), p_level(current_level)
{}

Platform::~Platform()
{
	p_level->RemoveObject(this);
}

void Platform::init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color)
{
	SetName(name.c_str());
	transform.position.Set(positionX, positionY, 0);
	transform.SetScale(scaleX, scaleY);
	sprite.color = color;
	sprite.LoadImage("texture/rect.png", p_level->m_renderer);
	physics.pOwnerTransform = &transform;
	physics.bodyType = Physics::STATIC;//파란색 플랫폼을 움직이려면 STATIC에서 DYNAMIC로 변환해줘야함
	physics.bodyShape = Physics::BOX;
	physics.radius = 32;
	physics.SetRestitution(0.f);
	physics.GenerateBody(p_level->GetPhysicsWorld(), &transform);
	p_level->AddObject(this);
}

void Platform::update(float )//dt)
{
}
