/******************************************************************************/
/*
File name: HowToPlay1.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "HowToPlay1.h"
#include "CommonLevel.h"
#include "Color.h"

void HowToPlay1::Initialize()
{
	m_backgroundColor = Color().WHITE;
	camera.position.Set(0, 0, 0);

	wasd.SetName("wasd");
	wasd.transform.position.Set(-200.f, 0.f, 0.f);
	wasd.transform.SetScale(500, 200);
	wasd.transform.rotation = 0;
	wasd.sprite.LoadImage("texture/wasd.png", m_renderer);

	mouse.SetName("mouse");
	mouse.transform.position.Set(300.f, 0.f, 0.f);
	mouse.transform.SetScale(400, 300);
	mouse.transform.rotation = 0;
	mouse.sprite.LoadImage("texture/MouseControlsPlayer.png", m_renderer);

	ctomoveon.SetName("ctomoveon");
	ctomoveon.transform.position.Set(0.f, -300.f, 0.f);
	ctomoveon.transform.SetScale(500, 200);
	ctomoveon.transform.rotation = 0;
	ctomoveon.sprite.LoadImage("texture/CtoMoveon.png", m_renderer);


	AddObject(&wasd);
	AddObject(&mouse);
	AddObject(&ctomoveon);
}

void HowToPlay1::Update(float dt)
{
	if (m_input->IsTriggered(SDL_SCANCODE_C))
		m_game->Change(LV_HowToPlay2);

	// Pause current state and move to pause state
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();
	UpdatePhysics(dt);
	Render(dt);
}

void HowToPlay1::Close()
{
	ClearBaseState();
}