/******************************************************************************/
/*
File name: Level_Test.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level_Test.h"
#include "CommonLevel.h"
#include "Color.h"

void Level_Test::Initialize()
{
    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);
    m_backgroundColor = {255,255,255,255};
    SetPhysicsWorld({ 0.f,-98.f });
    
    player = new Player(this, camera);
    player->init("player", 0, 0, 32, 64, {255,255,0,255});
    platform = new Platform(this);
    platform->init("platform", 0, -50, 300, 12, {255,0,0,255});
    cplatform = new ColorChangePlatform(this);
    cplatform->init("cplatform",50, 300, 300, 12, {255,0,0,255});
    paint = new Paint(this);
    paint->init("paint", 0, 100, 30, 30, Color().RED);
}

void Level_Test::Update(float dt)
{
    if (m_input->IsTriggered(SDL_SCANCODE_TAB))
	m_game->Pause();
    if (m_input->IsTriggered(SDL_SCANCODE_C))
	m_game->Change(LV_MainMenu);

    if (m_input->IsTriggered(SDL_SCANCODE_R))
        m_game->Restart();

    if (m_input->IsTriggered(SDL_SCANCODE_1))
    {
        player->sprite.color=Color().RED;
    }
    if (m_input->IsTriggered(SDL_SCANCODE_2))
    {
        player->sprite.color = Color().GREEN;
    }
    if (m_input->IsTriggered(SDL_SCANCODE_3))
    {
        player->sprite.color = Color().BLUE;
    }
    player->update(dt);
    paint->update(dt);
    UpdatePhysics(dt);
    Render(dt); 
}

void Level_Test::Close()
{
    delete player;
    delete platform;
    delete cplatform;
    delete paint;
}
