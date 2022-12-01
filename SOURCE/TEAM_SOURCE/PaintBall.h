/******************************************************************************/
/*
File name: PaintBall.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "Bullet.h"
class PaintBall:public Bullet
{
public:
    PaintBall(State* current_level);
    ~PaintBall() override;
    void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color);
    void update(float dt) override;
private:
    Object sound_effect;
};