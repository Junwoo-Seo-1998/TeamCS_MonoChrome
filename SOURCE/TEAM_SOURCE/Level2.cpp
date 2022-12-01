/******************************************************************************/
/*
File name: Level2.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level2.h"
#include "CommonLevel.h"
#include "Color.h"
void Level2::Initialize()
{   
    error_sound.sound.LoadSound("sound/error.wav");
    next_level.sound.LoadSound("sound/Next_level.wav");

    timer = 0;
    mouse_timer = false;
    anime = 0;
    backgroundMusic.LoadMusic("sound/level2_music.mp3");
    backgroundMusic.Play();

    platform.clear();
    cplatform.clear();

    platform_control = false;
    cplatform_count = 0;
    cplatform_max = 0;
    platform_max = 0;
    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);
    m_backgroundColor = { 8, 134, 150, 255 };
    SetPhysicsWorld({ 0.f,-98.f });

    player_dumy = new Helper(this);
    player_dumy->init("dumy", -250, 205, 32, 64, Color().WHITE, "texture/player.png");

    platform_dumy = new Helper(this);
    platform_dumy->init("dumy2", -250, 160, 100, 24, Color().BLACK, "texture/rect.png");

    player = new Player(this, camera);
    player->init("player", -100, 30, 32, 64, Color().WHITE);

    platform.push_back(new Platform(this));
    platform[0]->init("platform", -100, 0, 100, 24, Color().BLACK);//main platform
    platform_max++;

    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[0]->init("cplatform", 200, 0, 24, 450, Color().GREEN);//Side platform
    cplatform_count++;


    platform.push_back(new Platform(this));
    platform[1]->init("platform", 500, 0, 100, 23, Color().BLACK);//Side platform
    platform_max++;

    destination = new Destination(this);
    destination->init("destination", 500, 50, Color().WHITE);
    //
    mouse[0] = new Helper(this);
    mouse[0]->init("mouseleft", -35, 235, 32, 64, Color().WHITE, "texture/Left.png");

    mouse[1] = new Helper(this);
    mouse[1]->init("mousemiddle", 0, 235, 20, 64, Color().WHITE, "texture/Scroll.png");

    arrow[0] = new Helper(this);
    arrow[0]->init("arrow", 0, 335, 20, 64, Color().WHITE, "texture/arrow.png");

    arrow[1] = new Helper(this);
    arrow[1]->init("arrow", -150, 205, 20, 64, Color().WHITE, "texture/arrow.png");
    arrow[1]->transform.rotation = 90.f;

    mouse[2] = new Helper(this);
    mouse[2]->init("mouseright", 35, 235, 32, 64, Color().WHITE, "texture/Right.png");

    mouse[3] = new Helper(this);
    mouse[3]->init("mousebody", 0, 150, 100, 100, Color().WHITE, "texture/Body.png");
    //
    //

    platformcontrol = new PlatformControl(this, camera);

    cplatform_max = cplatform_count;
    cplatform_count = 0;
}


void Level2::Update(float dt)
{
    anime += dt;
    if (anime >= 0.5f)
    {
        if(!mouse_timer)
        {
            mouse[1]->sprite.color = Color().BLACK;
            mouse_timer = true;
            anime = 0;
        }
        else
        {
            mouse[1]->sprite.color = Color().WHITE;
            mouse_timer = false;
            anime = 0;
        }
    }

    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }

    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_LEVEL3);

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
    }
    if (m_input->IsTriggered(SDL_BUTTON_MIDDLE))
    {
        if (platform_control == true)
        {
            m_backgroundColor = Color().PLAYER_BACKGROUND;
            platform_control = false;
            player->is_pcmode = false;
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
            m_game->Change(LV_LEVEL3);
        }
    }
    //platform control mode start 

    //platform control mode end 
    for (int i = 0; i < 4; i++)
    {
        mouse[i]->update(dt);
    }
    player->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level2::Close()
{
    backgroundMusic.Stop();
    error_sound.sound.Free();
    next_level.sound.Free();
    delete player;
    for (int i = 0; i < cplatform_max; i++)
    {
        delete cplatform[i];
    }
    delete destination;
    destination = nullptr;
    delete platformcontrol;
    platformcontrol = nullptr;
    for (int i = 0; i < 4; i++)
    {
        delete mouse[i];
    }
  
    delete arrow[0];
    delete arrow[1];

    for (int i = 0; i < platform_max; i++)
    {
        delete platform[i];
    }
    delete player_dumy;
    delete platform_dumy;
}
