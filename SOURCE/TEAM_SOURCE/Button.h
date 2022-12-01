/******************************************************************************/
/*
File name: Button.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include"MouseUtility.h"
class State;
class Button :public Object
{
public:
    Button(State * current_level, Camera& cam);
    ~Button();
    void init(std::string button_text,int font_size,float positionX, float positionY, float scaleX, float scaleY);
    void update();
    virtual void click();
private:
    MouseUtility mouse;
    State * p_level;
    bool is_mouse_on;
    Object	text;
};