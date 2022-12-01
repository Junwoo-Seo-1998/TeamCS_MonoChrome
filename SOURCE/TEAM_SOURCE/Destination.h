/******************************************************************************/
/*
File name: Destination.h
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
class State;
class Destination :public Object
{
public:
    Destination(State* current_level);
    ~Destination() override;
public:
    virtual void init(std::string name, float positionX, float positionY, SDL_Color color);
    virtual void update(float dt);
private:
    State * p_level;
};