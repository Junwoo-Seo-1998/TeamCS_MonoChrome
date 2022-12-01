/******************************************************************************/
/*
File name: Bullet.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
class State;
class PaintBall;
class Bullet :public Object
{
    friend PaintBall;
public:
	Bullet(State* current_level);
	~Bullet() override;
public:
	virtual void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color);
	virtual void update(float dt);
	bool is_dead;
private:
	void colliding_update();
private:
	State * p_level;
        float timecount;
	
};