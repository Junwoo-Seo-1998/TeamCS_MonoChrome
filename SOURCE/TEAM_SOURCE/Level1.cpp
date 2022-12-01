/******************************************************************************/
/*
File name: Level1.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level1.h"
#include "CommonLevel.h"
#include "Color.h"

void Level1::Initialize()
{
    timer = 0;
    is_clear = false;
    backgroundMusic.LoadMusic("sound/level1_music.mp3");
    backgroundMusic.Play();
    next_level.sound.LoadSound("sound/Next_level.wav");
    platform.clear();

    platform_control = false;
    platform_count = 0;
    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);
    m_backgroundColor = Color().PLAYER_BACKGROUND;

    SetPhysicsWorld({ 0.f,-98.f });

    player = new Player(this, camera);
    player->init("player", -600, 30, 32, 64, Color().WHITE);

    helper[0] = new Helper(this);
    helper[0]->init("W", -400, 300, 64, 64, Color().WHITE, "texture/W.png");

    helper[1] = new Helper(this);
    helper[1]->init("A", -464, 226, 64, 64, Color().WHITE, "texture/A.png");

    helper[2] = new Helper(this);
    helper[2]->init("D", -336, 226, 64, 64, Color().WHITE, "texture/D.png");

    platform.push_back(new Platform(this));
    platform[0]->init("platform", -100, 0, 1000, 24, Color().BLACK);//main platform
    platform_count++;

    destination = new Destination(this);
    destination->init("destination", 400, 50, Color().WHITE);

    platform_max = platform_count;
    platform_count = 0;
}


void Level1::Update(float dt)
{

    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }
    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_LEVEL2);

    if (m_input->IsTriggered(SDL_SCANCODE_R))
        m_game->Restart();

    if (player->is_dead == true)
    {
        player->is_dead = false;
        m_game->Restart();
    }

    if (destination->physics.IsCollidingWith("player"))
    {
        next_level.sound.Play();
        is_clear = true;
    }
    if(is_clear)
    {
        destination->sprite.color = Color().BLACK;
        timer += dt;
        if(timer>1.f)
        {
            m_game->Change(LV_LEVEL2);
        }
    }
    helper[0]->update(dt);
    helper[1]->update(dt);
    helper[2]->update(dt);
    player->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level1::Close()
{
    next_level.sound.Free();
    backgroundMusic.Stop();
    delete player;
    for (int i = 0; i < platform_max; i++)
    {
        delete platform[i];
    }
    delete destination;
    for (int i = 0; i < 3; i++)
    {
        delete helper[i];
    }
}
