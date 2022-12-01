/******************************************************************************/
/*
File name: SplashScreen.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SplashScreen.h"
#include "CommonLevel.h"
#include "Color.h"
void SplashScreen::Initialize()
{
         timer = 0;
	m_backgroundColor = Color().WHITE;
	camera.position.Set(0, 0, 0);

	digipenLogo.SetName("DLogo");
	digipenLogo.transform.position.Set(0.f, 200.f, 0.f);
	digipenLogo.transform.SetScale(600, 200);
	digipenLogo.transform.rotation = 0;
	digipenLogo.sprite.LoadImage("texture/DigipenRed.png", m_renderer);

	teamLogo.SetName("TLogo");
	teamLogo.transform.position.Set(0.f, -200.f, 0.f);
	teamLogo.transform.SetScale(300, 300);
	teamLogo.transform.rotation = 0;
	teamLogo.sprite.LoadImage("texture/SampleLogo.png", m_renderer);

	AddObject(&digipenLogo);
	AddObject(&teamLogo);
}

void SplashScreen::Update(float dt)
{
	//m_game->Change(LV_MainMenu);
	if (m_input->IsTriggered(SDL_SCANCODE_C))
		m_game->Change(LV_MainMenu);
      
        timer += dt;
        if (m_backgroundColor.r > 0)
        {
            m_backgroundColor.r -= 3;
            m_backgroundColor.g -= 3;
            m_backgroundColor.b -= 3;
        }

        if (timer > 2.f)
        {
            m_game->Change(LV_MainMenu);
        }
        
	UpdatePhysics(dt);
	Render(dt);
}

void SplashScreen::Close()
{
	ClearBaseState();
}
