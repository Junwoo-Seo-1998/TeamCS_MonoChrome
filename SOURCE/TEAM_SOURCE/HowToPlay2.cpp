/******************************************************************************/
/*
File name: HowToPlay2.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "HowToPlay2.h"
#include "CommonLevel.h"
#include "Color.h"
void HowToPlay2::Initialize()
{
	m_backgroundColor = Color().WHITE;
	camera.position.Set(0, 0, 0);

	wasdblue.SetName("wasdblue");
	wasdblue.transform.position.Set(-200.f, 150.f, 0.f);
	wasdblue.transform.SetScale(500, 200);
	wasdblue.transform.rotation = 0;
	wasdblue.sprite.LoadImage("texture/wasdblue.png", m_renderer);

	z.SetName("qe");
	qe.transform.position.Set(-200.f, -100.f, 0.f);
	qe.transform.SetScale(500, 100);
	qe.transform.rotation = 0;
	qe.sprite.LoadImage("texture/QE.png", m_renderer);

	/*z.SetName("z");
	z.transform.position.Set(300.f, 150.f, 0.f);
	z.transform.SetScale(300, 100);
	z.transform.rotation = 0;
	z.sprite.LoadImage("texture/Z.png", m_renderer);*/

	xtoplayer.SetName("xtoplayer");
	xtoplayer.transform.position.Set(400.f, 0.f, 0.f);
	xtoplayer.transform.SetScale(500, 300);
	xtoplayer.transform.rotation = 0;
	xtoplayer.sprite.LoadImage("texture/MouseControls.png", m_renderer);

	ctomoveon.SetName("ctomoveon");
	ctomoveon.transform.position.Set(0.f, -300.f, 0.f);
	ctomoveon.transform.SetScale(500, 200);
	ctomoveon.transform.rotation = 0;
	ctomoveon.sprite.LoadImage("texture/CtoMoveon.png", m_renderer);

	AddObject(&wasdblue);
	AddObject(&z);
	AddObject(&xtoplayer);
	AddObject(&qe);
	AddObject(&ctomoveon);
}

void HowToPlay2::Update(float dt)
{
	if (m_input->IsTriggered(SDL_SCANCODE_C))
		m_game->Change(LV_LEVEL1);

	// Pause current state and move to pause state
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();
	UpdatePhysics(dt);
	Render(dt);
}

void HowToPlay2::Close()
{
	ClearBaseState();
}
