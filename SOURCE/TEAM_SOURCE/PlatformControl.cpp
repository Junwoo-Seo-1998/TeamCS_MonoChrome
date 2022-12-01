/******************************************************************************/
/*
File name: PlatformControl.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PlatformControl.h"
#include "Color.h"
#include "Application.h"
#include "Game.h"
PlatformControl::PlatformControl(State* current_level, Camera& cam) :p_level(current_level), camera(cam), is_collide_to_player(false)
{
    Sound_check = true;
    PC_mode_on.SetName("OnSound");
    PC_mode_off.SetName("OffSound");
    Next_plafform.SetName("NextPlatformSound");
    Control_platform.SetName("ControlPlatformSound");

    PC_mode_on.sound.LoadSound("sound/PCmode_in.wav");
    PC_mode_off.sound.LoadSound("sound/PCmode_out.wav");
    Next_plafform.sound.LoadSound("sound/Choose_next.wav");
    Control_platform.sound.LoadSound("sound/Platform_moving.wav");

    target_platform_arrow = new Helper(current_level);
    target_platform_arrow->init("arrow", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/Arrow.png");

    rotation_guide[0] = new Helper(current_level);
    rotation_guide[0]->init("Q", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/Q.png");

    rotation_guide[1] = new Helper(current_level);
    rotation_guide[1]->init("E", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/E.png");

    move_guide[0] = new Helper(current_level);
    move_guide[0]->init("W", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/W.png");

    move_guide[1] = new Helper(current_level);
    move_guide[1]->init("A", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/A.png");

    move_guide[2] = new Helper(current_level);
    move_guide[2]->init("S", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/S.png");

    move_guide[3] = new Helper(current_level);
    move_guide[3]->init("D", 0.f, 0.f, 50, 50, Color().INVISBLE, "texture/D.png");
}

void PlatformControl::Update(std::vector<ColorChangePlatform*> platform, int& platform_count, int& platform_max, float dt)
{
    if (Sound_check)
    {
        PC_mode_on.sound.Play();
    }
    Sound_check = false;
    is_collide_to_player = false;
    if (platform[platform_count]->physics.IsCollidingWith("player"))//안티 근두운
    {
        is_collide_to_player = true;
        Sound_check = true;
        PC_mode_off.sound.Play();
    }
    target_platform_arrow->sprite.color = Color().WHITE;
    target_platform_arrow->transform.position.Set(platform[platform_count]->transform.position.x, platform[platform_count]->transform.position.y + 60, 0);
    camera.position.x = platform[platform_count]->transform.position.x;//카메라 위치를 플렛폼으로 설정
    camera.position.y = platform[platform_count]->transform.position.y;
    if (platform_max != 1)
    {
        if (p_level->m_input->IsTriggered(SDL_BUTTON_RIGHT))//다음 플렛폼으로 넘어감
        {
            platform[platform_count]->physics.SetVelocity(0.f, 0.f);
            if (platform_count < platform_max - 1)
            {
                Next_plafform.sound.Play();
                platform_count++;
            }
            else
            {
                Next_plafform.sound.Play();
                platform_count = 0;
            }

        }
        if (p_level->m_input->IsTriggered(SDL_BUTTON_LEFT))//다음 플렛폼으로 넘어감
        {
            platform[platform_count]->physics.SetVelocity(0.f, 0.f);
            if (platform_count > 0)
            {
                Next_plafform.sound.Play();
                platform_count--;
            }

            else
            {
                Next_plafform.sound.Play();
                platform_count = platform_max - 1;
            }
        }
    }
    if (Color().AreTheySame(platform[platform_count]->sprite.color, Color().GREEN))
    {
        rotation_guide[0]->sprite.color = Color().WHITE;
        rotation_guide[0]->transform.position.Set(platform[platform_count]->transform.position.x-100, platform[platform_count]->transform.position.y-100, 0);
        rotation_guide[1]->sprite.color = Color().WHITE;
        rotation_guide[1]->transform.position.Set(platform[platform_count]->transform.position.x+100, platform[platform_count]->transform.position.y-100, 0);

        if (p_level->m_input->IsPressed(SDL_SCANCODE_Q))//회전1
        {
            platform[platform_count]->transform.rotation += dt * 100.f;  //회전 
            rotation_guide[0]->sprite.color = Color().GREEN;
        }

        if (p_level->m_input->IsPressed(SDL_SCANCODE_E))//회전2
        {
            platform[platform_count]->transform.rotation -= dt * 100.f;  //회전 
            rotation_guide[1]->sprite.color = Color().GREEN;
        }

        if (p_level->m_input->IsReleased(SDL_SCANCODE_Q))//회전1
        {
            rotation_guide[0]->sprite.color = Color().WHITE;
            Control_platform.sound.Free();
        }

        if (p_level->m_input->IsReleased(SDL_SCANCODE_E))//회전2
        {
            rotation_guide[1]->sprite.color = Color().WHITE;
            Control_platform.sound.Free();
        }
    }
    else
    {
        rotation_guide[0]->sprite.color = Color().INVISBLE;
        rotation_guide[1]->sprite.color = Color().INVISBLE;
    }

    if (Color().AreTheySame(platform[platform_count]->sprite.color, Color().BLUE))
    {
        
        for (int i = 0; i < 4; i++)
        {
            move_guide[i]->sprite.color = Color().WHITE;
        }
        move_guide[0]->transform.position.Set(platform[platform_count]->transform.position.x, platform[platform_count]->transform.position.y+100, 0);
        move_guide[1]->transform.position.Set(platform[platform_count]->transform.position.x - 200, platform[platform_count]->transform.position.y, 0);
        move_guide[2]->transform.position.Set(platform[platform_count]->transform.position.x, platform[platform_count]->transform.position.y-100, 0);
        move_guide[3]->transform.position.Set(platform[platform_count]->transform.position.x + 200, platform[platform_count]->transform.position.y, 0);
        if (p_level->m_input->IsPressed(SDL_SCANCODE_D)) //플랫폼 이동 with physics
        {
            platform[platform_count]->physics.SetVelocity(10.f, 0.f);
            move_guide[3]->sprite.color = Color().BLUE;
        }
        if (p_level->m_input->IsReleased((SDL_SCANCODE_D)))
        {
            platform[platform_count]->physics.SetVelocity(0.f, 0.f);
            move_guide[3]->sprite.color = Color().WHITE;
        }
        if (p_level->m_input->IsPressed((SDL_SCANCODE_A)))
        {
            platform[platform_count]->physics.SetVelocity(-10.f, 0.f);
            move_guide[1]->sprite.color = Color().BLUE;
        }
        if (p_level->m_input->IsReleased((SDL_SCANCODE_A)))
        {
            platform[platform_count]->physics.SetVelocity(0.f, 0.f);
            move_guide[1]->sprite.color = Color().WHITE;
        }
        if (p_level->m_input->IsPressed((SDL_SCANCODE_W)))
        {
                platform[platform_count]->physics.SetVelocity(0.f, 10.f);
                move_guide[0]->sprite.color = Color().BLUE;
        }
        if (p_level->m_input->IsReleased((SDL_SCANCODE_W)))
        {
            platform[platform_count]->physics.SetVelocity(0.f, 0.f);
            move_guide[0]->sprite.color = Color().WHITE;
        }
        if (p_level->m_input->IsPressed((SDL_SCANCODE_S)))
        {
            platform[platform_count]->physics.SetVelocity(0.f, -10.f);
            move_guide[2]->sprite.color = Color().BLUE;
        }
        if (p_level->m_input->IsReleased((SDL_SCANCODE_S)))
        {
            platform[platform_count]->physics.SetVelocity(0.f, 0.f);
            move_guide[2]->sprite.color = Color().WHITE;
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            move_guide[i]->sprite.color = Color().INVISBLE;
        }
    }
    if (p_level->m_input->IsTriggered((SDL_BUTTON_MIDDLE)))
    {
        PC_mode_off.sound.Play();
        platform[platform_count]->physics.SetVelocity(0.f, 0.f);
        target_platform_arrow->sprite.color = Color().INVISBLE;
        rotation_guide[0]->sprite.color = Color().INVISBLE;
        rotation_guide[1]->sprite.color = Color().INVISBLE;
        for (int i = 0; i < 4; i++)
        {
            move_guide[i]->sprite.color = Color().INVISBLE;
        }
        Sound_check = true;
    }
    if (is_collide_to_player)
    {
        platform[platform_count]->physics.SetVelocity(0.f, 0.f);
        target_platform_arrow->sprite.color = Color().INVISBLE;
        rotation_guide[0]->sprite.color = Color().INVISBLE;
        rotation_guide[1]->sprite.color = Color().INVISBLE;
        for (int i = 0; i < 4; i++)
        {
            move_guide[i]->sprite.color = Color().INVISBLE;
        }
    }
    
}

PlatformControl::~PlatformControl()
{
    delete target_platform_arrow;
    delete rotation_guide[0];
    delete rotation_guide[1];
    for (int i = 0; i < 4; i++)
    {
        delete move_guide[i];
    }
}