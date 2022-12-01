/******************************************************************************/
/*
File name: PauseMenu.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include"Button.h"
class State;

class PauseMenu
{
public:
    PauseMenu(State* current_level,Camera& cam);
    
    void drawmenu();
    
    void update();
private:
    void input_update();
    State * p_level;
    Button button1;
    //ButtonMute mute;
};