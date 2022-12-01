/******************************************************************************/
/*
File name: ColorChangePlatform.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ColorChangePlatform.h"
#include "Color.h"

ColorChangePlatform::ColorChangePlatform(State* current_level):Platform(current_level)
{

}

void ColorChangePlatform::init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color)
{
	Platform::init(name, positionX, positionY, scaleX, scaleY, color);
	b2Body* body= physics.GetBody();
	body->SetType(b2BodyType::b2_kinematicBody);
}

void ColorChangePlatform::update(float dt)
{
	Platform::update(dt);
}

void ColorChangePlatform::ColorAbility()
{
    Color color;
    if (color.AreTheySame(sprite.color, color.RED))
    {

    }
    if (color.AreTheySame(sprite.color,color.GREEN))
    {
    	
    }
    if (color.AreTheySame(sprite.color, color.BLUE))
    {
    
    }
}
