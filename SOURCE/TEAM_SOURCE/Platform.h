/******************************************************************************/
/*
File name: Platform.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/#pragma once
#include "engine\Object.h"
class State;
class Platform:public Object
{
public:
	Platform(State* current_level);
	~Platform() override;
public:
	virtual void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color);
	virtual void update(float dt);
private:
	State * p_level;
};