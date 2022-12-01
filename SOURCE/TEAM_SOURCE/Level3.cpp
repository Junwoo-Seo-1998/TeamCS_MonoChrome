/******************************************************************************/
/*
File name: Level3.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level3.h"
#include "CommonLevel.h"
#include "Color.h"

void Level3::Initialize()
{
    error_sound.sound.LoadSound("sound/error.wav");
    next_level.sound.LoadSound("sound/Next_level.wav");
    timer = 0;
    backgroundMusic.LoadMusic("sound/level3_music.mp3");
    backgroundMusic.Play();
    platform.clear();
    cplatform.clear();
    mouse_timer = false;
    anime = 0;
    platform_control = false;

    cplatform_count = 0;
    cplatform_max = 0;
    platform_max = 0;

    camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);

    m_backgroundColor = Color().PLAYER_BACKGROUND;

    SetPhysicsWorld({ 0.f,-98.f });
    //
    player_dumy = new Helper(this);
    player_dumy->init("dumy", -250, 255, 32, 64, Color().WHITE, "texture/player.png");

    platform_dumy = new Helper(this);
    platform_dumy->init("dumy2", -250, 210, 100, 24, Color().BLACK, "texture/rect.png");

    player = new Player(this, camera);
    player->init("player", -50, 80, 32, 64, Color().WHITE);

    //
    mouse[0] = new Helper(this);
    mouse[0]->init("mouseleft", -35, 285, 32, 64, Color().WHITE, "texture/Left.png");

    mouse[1] = new Helper(this);
    mouse[1]->init("mousemiddle", 0, 285, 20, 64, Color().WHITE, "texture/Scroll.png");

    arrow[0] = new Helper(this);
    arrow[0]->init("arrow", 0, 385, 20, 64, Color().WHITE, "texture/arrow.png");

    mouse[2] = new Helper(this);
    mouse[2]->init("mouseright", 35, 285, 32, 64, Color().WHITE, "texture/Right.png");

    mouse[3] = new Helper(this);
    mouse[3]->init("mousebody", 0, 200, 100, 100, Color().WHITE, "texture/Body.png");
    //
    //
    mouse[4] = new Helper(this);
    mouse[4]->init("mouseleft", 365, 285, 32, 64, Color().WHITE, "texture/Left.png");

    mouse[5] = new Helper(this);
    mouse[5]->init("mousemiddle", 400, 285, 20, 64, Color().WHITE, "texture/Scroll.png");

    mouse[6] = new Helper(this);
    mouse[6]->init("mouseright", 435, 285, 32, 64, Color().WHITE, "texture/Right.png");

    arrow[1] = new Helper(this);
    arrow[1]->init("arrow", 435, 385, 20, 64, Color().WHITE, "texture/arrow.png");

    mouse[7] = new Helper(this);
    mouse[7]->init("mousebody", 400, 200, 100, 100, Color().WHITE, "texture/Body.png");
    //

    arrow[2] = new Helper(this);
    arrow[2]->init("arrow", 200, 385, 20, 64, Color().WHITE, "texture/arrow.png");
    arrow[2]->transform.rotation = 90;

    arrow[3] = new Helper(this);
    arrow[3]->init("arrow", -150, 240, 20, 64, Color().WHITE, "texture/arrow.png");
    arrow[3]->transform.rotation = 90;
    //

    platform.push_back(new Platform(this));
    platform[0]->init("platform", -50, 0, 100, 24, Color().BLACK);//main platform
    platform_max++;

    
    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[0]->init("cplatform1", 200, 200, 180, 24, Color().BLUE);
    cplatform_count++;
    
    cplatform.push_back(new ColorChangePlatform(this));
    cplatform[1]->init("cplatform", 200, -200, 180, 24, Color().BLUE);//Side platform
    cplatform_count++;

    platform.push_back(new Platform(this));
    platform[1]->init("platform", 450, 0, 100, 24, Color().BLACK);//Side platform
    platform_max++;

    destination = new Destination(this);
    destination->init("destination", 500, 50, Color().WHITE);

    platformcontrol = new PlatformControl(this, camera);

    cplatform_max = cplatform_count;
    cplatform_count = 0;
}


void Level3::Update(float dt)
{
    anime += dt;
    if(platform_control)
    {
        if (anime >= 0.5f)
        {
            mouse[1]->sprite.color = Color().WHITE;
            if (!mouse_timer)
            {
                mouse[6]->sprite.color = Color().BLACK;
                mouse_timer = true;
                anime = 0;
            }
            else
            {
                mouse[6]->sprite.color = Color().WHITE;
                mouse_timer = false;
                anime = 0;
            }
        }
    }
    else
    {
        mouse[6]->sprite.color = Color().WHITE;
        if (anime >= 0.5f)
        {
            if (!mouse_timer)
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
    }
    if (!backgroundMusic.IsPlaying())
    {
        backgroundMusic.Play();
    }

    camera.position.Set(player->transform.position.x, player->transform.position.y, 0);

    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_LEVEL4);

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
            m_game->Change(LV_LEVEL4);
            
        }
    }
    //platform control mode start 


    //platform control mode end 

    player->update(dt);
    UpdatePhysics(dt);
    Render(dt);
}

void Level3::Close()
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
    for (int i = 0; i < 12; i++)
    {
        delete mouse[i];
    }
    for (int i = 0; i < 4; i++)
    {
        delete arrow[i];
    }
    delete player_dumy;
    delete platform_dumy;
    delete destination;
    delete platformcontrol;
}
