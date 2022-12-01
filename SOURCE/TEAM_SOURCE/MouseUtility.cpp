/******************************************************************************/
/*
File name: MouseUtility.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "MouseUtility.h"
#include "engine\State.h"
#include "CommonLevel.h"
MouseUtility::MouseUtility(State * current_level,Camera& cam):p_level(current_level),camera(cam)
{

}

b2Vec2 MouseUtility::get_mouse_pos()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	b2Vec2 res={ (float)x,(float)y };
	res = { res.x - p_level->m_width / 2,-res.y + p_level->m_height / 2 };
	res.x += camera.position.x;
	res.y += camera.position.y;
	return res;
}

float MouseUtility::get_rad_respect_mouse(Object * obj)
{
	b2Vec2 mousepos = get_mouse_pos();
	b2Vec2 objpos = { obj->transform.position.x,obj->transform.position.y};
	b2Vec2 diff = { mousepos.x - objpos.x,mousepos.y - objpos.y };
	diff.Normalize();
	return std::atan2(diff.y, diff.x);
}
