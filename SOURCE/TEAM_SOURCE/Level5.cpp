/******************************************************************************/
/*
File name: Level5.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level5.h"
#include "CommonLevel.h"
#include "Color.h"

void Level5::Initialize()
{
    error_sound.sound.LoadSound("sound/error.wav");
    next_level.sound.LoadSound("sound/Next_level.wav");
    timer = 0;
    backgroundMusic.LoadMusic("sound/level4, 5_music.mp3");
    backgroundMusic.Play();

    platform.clear();
    cplatform.clear();

    m_backgroundColor = Color().PLAYER_BACKGROUND;
    platform_control = false;
    cplatform_count = 0;
    platform_max = 0;
    cplatform_max = 0;
    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);

    SetPhysicsWorld({ 0.f,-98.f });

    player = new Player(this, camera);
    player->init("player", -50, 30, 32, 64, Color().WHITE);

    platform.push_back(new Platform(this));
    platform[0]->init("platform", -80, 0, 100, 24, Color().BLACK);//main platform
    platform_max++;

    platform.push_back(new Platform(this));
    platform[1]->init("platform", 25, 60, 24, 180, Color().BLACK);//Side platform
    platform[1]->transform.rotation = -45.f;
    platform_max++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[0]->init("cplatform", 450, -100, 24, 150, Color().WHITE);
    cplatform_count++;

    platform.push_back(new Platform(this));
    platform[2]->init("platform", 400, 230, 100, 24, Color().BLACK);//destination
    platform_max++;

    platform.push_back(new Platform(this));
    platform[3]->init("platform", -130, 0, 100, 24, Color().BLACK);
    platform_max++;

    platform.push_back(new Platform(this));
    platform[4]->init("platform", -230, 0, 100, 24, Color().BLACK);
    platform_max++;

    platform.push_back(new Platform(this));
    platform[5]->init("platform", 129, 119, 100, 24, Color().BLACK);
    platform_max++;

    paint[0] = new Paint(this);
    paint[0]->init("paint", -100, 150, 30, 30, Color().BLUE);

    paint[1] = new Paint(this);
    paint[1]->init("paint", -200, 150, 30, 30, Color().GREEN);

    destination = new Destination(this);
    destination->init("destination", 425, 290, Color().RED);

    platformcontrol = new PlatformControl(this, camera);

    cplatform_max = cplatform_count;
    cplatform_count = 0;
}


void Level5::Update(float dt)
{
    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }

    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_LEVEL6);

    if (m_input->IsTriggered(SDL_SCANCODE_R))
        m_game->Restart();

    if (player->is_dead == true)
    {
        player->is_dead = false;
        m_game->Restart();
    }


    if (platform_control == true)
    {
        platformcontrol->Update(cplatform, cplatform_count, cplatform_max, dt);
        if (platformcontrol->is_collide_to_player)
        {
            player->is_pcmode = false;
            m_backgroundColor = Color().PLAYER_BACKGROUND;
            player->is_stop = false;
            platform_control = false;
        }

    }

    if (m_input->IsTriggered(SDL_BUTTON_MIDDLE))
    {
        if (platform_control == true)
        {
            m_backgroundColor = Color().PLAYER_BACKGROUND;
            player->is_pcmode = false;
            platform_control = false;
            player->is_stop = false;
        }
        else if (player->is_jump == false)
        {
            if (player->get_colide())
            {
                if (platform_control == false)
                {
                    m_backgroundColor = Color().PLATFORM_BACKGROUND;
                    player->is_pcmode = true;
                    platform_control = true;
                    player->is_stop = true;
                }
              
            }
            else
            {
                error_sound.sound.Play();
            }
        }
    }
    if (destination->physics.IsCollidingWith("player"))
    {
        next_level.sound.Play();
        is_clear = true;
    }
    if (is_clear)
    {
        destination->sprite.color = Color().BLACK;
        timer += dt;
        if (timer>1.f)
        {
            timer = 0;
            is_clear = false;
            m_game->Change(LV_LEVEL6);
        }
    }

    paint[0]->update(dt);
    paint[1]->update(dt);
    player->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level5::Close()
{
    next_level.sound.Free();
    error_sound.sound.Free();
    backgroundMusic.Stop();
    delete player;
    for (int i = 0; i < platform_max; i++)
    {
        delete platform[i];
    }
    for (int i = 0; i < cplatform_max; i++)
    {
        delete cplatform[i];
    }
    delete destination;
    delete platformcontrol;
    delete paint[1];
    delete paint[0];
}
