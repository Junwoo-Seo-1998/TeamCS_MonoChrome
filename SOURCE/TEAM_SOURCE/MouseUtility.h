/******************************************************************************/
/*
File name: MouseUtility.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
class State;
class Object;
class MouseUtility
{
public:
	MouseUtility(State* current_level, Camera& cam);
	b2Vec2 get_mouse_pos();
	float get_rad_respect_mouse(Object*obj);
private:
	State * p_level;
	Camera&camera;
};
