/******************************************************************************/
/*
File name: Paint.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
#include <list>

class State;
class PaintBall;
class Paint :public Object
{
public:
    Paint(State* current_level);
    ~Paint() override;
public:
    virtual void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color);
    virtual void update(float dt);
private:
    void DropPaint(float dt,SDL_Color color);
    State * p_level;
    std::list<PaintBall*>paintballs;
    float drop_rate;
    float current_rate;
};