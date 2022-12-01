/******************************************************************************/
/*
File name: Level7.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level7.h"
#include "CommonLevel.h"
#include "Color.h"

void Level7::Initialize()
{
    error_sound.sound.LoadSound("sound/error.wav");
    next_level.sound.LoadSound("sound/Next_level.wav");
    timer = 0;

    backgroundMusic.LoadMusic("sound/level6, 7_music.mp3");
    backgroundMusic.Play();

    platform.clear();
    cplatform.clear();

    m_backgroundColor = Color().PLAYER_BACKGROUND;
    paint = new Paint(this);
    platform_control = false;
    platform_max = 0;
    cplatform_count = 0;
    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);

    SetPhysicsWorld({ 0.f,-98.f });

    player = new Player(this, camera);
    player->init("player", -100, 30, 32, 64, Color().WHITE);

    platform.push_back(new ColorChangePlatform(this));
    platform[0]->init("platform", -100, 0, 200, 24, Color().BLACK);//시작 플렛폼
    platform_max++;

    platform.push_back(new ColorChangePlatform(this));
    platform[1]->init("platform", 450, 0, 100, 24, Color().BLACK);//우하단의 검은 플랫폼
    platform[1]->transform.rotation = 0.f;
    platform_max++;

    platform.push_back(new ColorChangePlatform(this));
    platform[2]->init("platform", 450, 100, 100, 24, Color().BLACK);//우상단의 검은 플랫폼 - 페인트 받는 장소
    platform_max++;

    platform.push_back(new ColorChangePlatform(this));
    platform[3]->init("platform", -100, 170, 200, 24, Color().BLACK);//좌상단의 골 플랫폼
    platform_max++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[0]->init("cplatform", 0, 210, 12, 50, Color().WHITE);//골 플랫폼 앞의 벽
    cplatform_count++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[1]->init("cplatform1", 200, 60, 12, 400, Color().GREEN);//중앙의 초록색 벽
    cplatform_count++;

    paint->init("paint", 450, 200, 30, 30, Color().BLUE);

    destination = new Destination(this);
    destination->init("destination", -100, 220, Color().RED);

    platformcontrol = new PlatformControl(this, camera);

    cplatform_max = cplatform_count;
    cplatform_count = 0;
}


void Level7::Update(float dt)
{
    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }
    if (m_input->IsTriggered(SDL_SCANCODE_1))
    {
        player->sprite.color = Color().RED;
    }
    if (m_input->IsTriggered(SDL_SCANCODE_2))
    {
        player->sprite.color = Color().GREEN;
    }
    if (m_input->IsTriggered(SDL_SCANCODE_3))
    {
        player->sprite.color = Color().BLUE;
    }
    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_LEVEL8);

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
            m_game->Change(LV_LEVEL8);
        }
    }

    if (m_input->IsTriggered(SDL_SCANCODE_TAB))
        m_game->Pause();

    player->update(dt);
    paint->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level7::Close()
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
    delete paint;
    delete platformcontrol;
}
