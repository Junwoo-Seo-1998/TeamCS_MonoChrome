#include "CommonLevel.h"

void PauseState::Initialize()
{
	m_backgroundColor = {0,0,0,255};

	camera.position.Set(0, 0, 0);
	menu.drawmenu();
}

void PauseState::Update(float dt)
{
	/******************* State ******************/

	// Move to level1 by pressing 'R' key
	/*if (m_input->IsTriggered(SDL_SCANCODE_TAB))
	    m_game->Resume();
	if (m_input->IsTriggered(SDL_SCANCODE_R))
	{
	    m_game->Resume();
	    m_game->Change(LV_LEVEL1);
	}*/
	menu.update();
	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void PauseState::Close()
{
	// Wrap up state
	ClearBaseState();
}
