/******************************************************************************/
/*
File name: Level6.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level6.h"
#include "CommonLevel.h"
#include "Color.h"

void Level6::Initialize()
{
    error_sound.sound.LoadSound("sound/error.wav");
    next_level.sound.LoadSound("sound/Next_level.wav");
    timer = 0;
    backgroundMusic.LoadMusic("sound/level6, 7_music.mp3");
    backgroundMusic.Play();

    platform.clear();
    cplatform.clear();

    m_backgroundColor = Color().PLAYER_BACKGROUND;

    platform_control = false;
    cplatform_count = 0;
    cplatform_max = 0;
    platform_max = 0;

    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);

    SetPhysicsWorld({ 0.f,-98.f });

    player = new Player(this, camera);

    player->init("player", -230, 30, 32, 64, Color().WHITE);

    platform.push_back(new Platform(this));
    platform[0]->init("platform", -230, 0, 150, 24, Color().BLACK);//시작 플렛폼
    platform_max++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[0]->init("cplatform", 100, 0, 24, 500, Color().GREEN);//키 플렛폼 
    cplatform[0]->transform.rotation = 0.f;
    cplatform_count++;

    platform.push_back(new Platform(this));
    platform[1]->init("platform", 400, -150, 150, 24, Color().BLACK);//오른쪽 아래 검은색
    platform_max++;

    platform.push_back(new Platform(this));
    platform[2]->init("platform", 400, 120, 150, 24, Color().BLACK);//오른쪽 위의 검은색
    platform_max++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[1]->init("cplatform1", 530, -370, 150, 24, Color().WHITE);//올라가야 하는 플랫폼, 실제로는 흰색이 들어갈것
    cplatform_count++;

    platform.push_back(new Platform(this));
    platform[3]->init("platform", 750, 130, 100, 24, Color().BLACK);//데스티네이션이 있는 플랫폼
    platform_max++;

    paint = new Paint(this);
    paint->init("paint", 400, 30, 30, 30, Color().BLUE);

    destination = new Destination(this);
    destination->init("destination", 750, 180, Color().RED);

    platformcontrol = new PlatformControl(this, camera);

    cplatform_max = cplatform_count;
    cplatform_count = 0;
}


void Level6::Update(float dt)
{
    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }
    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_LEVEL7);

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
            m_game->Change(LV_LEVEL7);
        }
    }

    if (m_input->IsTriggered(SDL_SCANCODE_TAB))
        m_game->Pause();

    player->update(dt);
    paint->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level6::Close()
{
    next_level.sound.Free();
    error_sound.sound.Free();
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
    delete paint;
}
