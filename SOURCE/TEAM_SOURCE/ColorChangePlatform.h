/******************************************************************************/
/*
File name: ColorChangePlatform.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "Platform.h"
class ColorChangePlatform:public Platform
{
public:
	ColorChangePlatform(State* current_level);
	void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color) override;
	void update(float dt) override;
private:
	void ColorAbility();
};