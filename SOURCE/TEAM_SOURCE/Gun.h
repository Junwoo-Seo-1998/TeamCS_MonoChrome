/******************************************************************************/
/*
File name: Gun.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
#include "MouseUtility.h"
#include <list>
#include "Bullet.h"
class State;
class Gun :public Object
{
public:
	Gun(State* current_level, Camera& cam,Object*owner);
	~Gun() override;
public:
	void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color);
	void update(float dt);
	void fire();
private:
	b2Vec2 get_tip_pos();
	State * p_level;
	Object * p_owner;
	Object sound_effect;
	MouseUtility mouse;
	std::list<Bullet*>bullets;
};