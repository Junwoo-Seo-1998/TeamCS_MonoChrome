/******************************************************************************/
/*
File name: Level8.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level8.h"
#include "CommonLevel.h"
#include "Color.h"

void Level8::Initialize()
{
    error_sound.sound.LoadSound("sound/error.wav");
    next_level.sound.LoadSound("sound/Next_level.wav");
    backgroundMusic.LoadMusic("sound/level8_music.mp3");
    backgroundMusic.Play();
    timer = 0;
    platform.clear();
    cplatform.clear();

    platform_control = false;

    cplatform_count = 0;
    cplatform_max = 0;
    platform_max = 0;

    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera 
    camera.position.Set(0, 0, 0);

    m_backgroundColor = Color().PLAYER_BACKGROUND;

    SetPhysicsWorld({ 0.f,-98.f });

    player = new Player(this, camera);
    player->init("player", 0, 0, 32, 64, Color().WHITE);

    platform.push_back(new Platform(this));
    platform[0]->init("platform", 0, -30, 600, 24, Color().BLACK);
    platform_max++;

    //platform.push_back(new Platform(this));
    //platform[1]->init("platform", 700, -50, 24, 500, Color().BLACK);
    //platform_max++;

    //platform.push_back(new Platform(this));
    //platform[2]->init("platform", -600, -50, 24, 600, Color().BLACK);
    //platform_max++;

    platform.push_back(new Platform(this));
    platform[1]->init("platform", -290, -90, 24, 100, Color().BLACK);
    platform_max++;

    platform.push_back(new Platform(this));
    platform[2]->init("platform", -450, -350, 300, 24, Color().BLACK);
    platform_max++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[0]->init("cplatform", 500, -50, 250, 250, Color().WHITE);
    cplatform[0]->transform.rotation = 45.f;
    cplatform_count++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[1]->init("cplatform1", -450, -30, 250, 24, Color().WHITE);
    cplatform[1]->transform.rotation = 0.f;
    cplatform_count++;

    /*cplatform.push_back(new ColorChangePlatform(this));
    cplatform[2]->init("cplatform2", -200, -200, 200, 24, Color().WHITE);
    platform_count++;*/

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[2]->init("cplatform3", 0, -350, 500, 24, Color().WHITE);
    cplatform_count++;

    destination = new Destination(this);
    destination->init("destination", 625, -230, Color().RED);

    paint = new Paint(this);
    paint->init("paint", 100, 100, 30, 30, Color().GREEN);

    paint2b = new Paint(this);
    paint2b->init("paint", -500, -250, 30, 30, Color().BLUE);

    platformcontrol = new PlatformControl(this, camera);

    cplatform_max = cplatform_count;
    cplatform_count = 0;
}

void Level8::Update(float dt)
{
    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }
    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_MainMenu);

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
            m_game->Change(LV_CLEAR);
        }
    }
    //platform control mode start 


    //platform control mode end 
    paint->update(dt);
    paint2b->update(dt);
    player->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level8::Close()
{
    next_level.sound.Free();
    error_sound.sound.Free();
    backgroundMusic.Stop();
    delete player;
    for (int i = 0; i < cplatform_max; i++)
    {
        delete cplatform[i];
    }
    for (int i = 0; i < platform_max; i++)
    {
        delete platform[i];
    }
    delete destination;
    delete platformcontrol;
    delete paint;
    delete paint2b;
}
