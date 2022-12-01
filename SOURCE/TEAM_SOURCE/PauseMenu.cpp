/******************************************************************************/
/*
File name: PauseMenu.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PauseMenu.h"
#include "engine/State.h"
#include "CommonLevel.h"
PauseMenu::PauseMenu(State * current_level,Camera& cam)
:p_level(current_level),button1(current_level,cam)
{
}
void PauseMenu::drawmenu()
{
    button1.init("Main Menu",50, 0, 0, 500, 70);
}

void PauseMenu::update()
{
    button1.update();
    input_update();
}

void PauseMenu::input_update()
{
    if (p_level->m_input->IsTriggered(SDL_SCANCODE_TAB))
    {
	p_level->m_game->Resume();
    }
    if (p_level->m_input->IsTriggered(SDL_BUTTON_LEFT))
    {
	button1.click();
    }
}


