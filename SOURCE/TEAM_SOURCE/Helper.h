/******************************************************************************/
/*
File name: Helper.h
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
class State;
class Helper :public Object
{
public:
    Helper(State* current_level);
    ~Helper() override;
public:
    virtual void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color, char* texture);
    virtual void update(float dt);
private:
    State * p_level;
};