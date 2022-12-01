/******************************************************************************/
/*
File name: Helper.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Helper.h"
#include "engine\State.h"
#include "Color.h"
Helper::Helper(State * current_level)
    :Object(), p_level(current_level)
{}

Helper::~Helper()
{
    p_level->RemoveObject(this);
}

void Helper::init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color, char* texture)
{
    SetName(name.c_str());
    transform.position.Set(positionX, positionY, 0);
    transform.SetScale(scaleX, scaleY);
    sprite.color = color;
    sprite.LoadImage(texture, p_level->m_renderer);
    physics.GenerateBody(p_level->GetPhysicsWorld(), &transform); 
    physics.ActivePhysics(false);
    p_level->AddObject(this);
}

void Helper::update(float)//dt)
{
    if (this->GetName() == "D")
    {
        if (p_level->m_input->IsPressed(SDL_SCANCODE_D)) //플랫폼 이동 with physics
        {
            sprite.color = Color().BLACK;

        }
        if (p_level->m_input->IsReleased((SDL_SCANCODE_D)))
        {
            sprite.color = Color().WHITE;
        }
    }

    if (this->GetName() == "A")
    {
        if (p_level->m_input->IsPressed((SDL_SCANCODE_A)))
        {

            sprite.color = Color().BLACK;

        }
        if (p_level->m_input->IsReleased((SDL_SCANCODE_A)))
        {
            sprite.color = Color().WHITE;
        }
    }

    if (this->GetName() == "W")
    {
        if (p_level->m_input->IsPressed((SDL_SCANCODE_W)))
        {
            sprite.color = Color().BLACK;
        }

        if (p_level->m_input->IsReleased((SDL_SCANCODE_W)))
        {
            sprite.color = Color().WHITE;
        }
    }

    if (this->GetName() == "mouseleft"|| this->GetName() == "mouseleft1"|| this->GetName() == "mouseleft2"|| this->GetName() == "mouseleft3")
    {
        if (p_level->m_input->IsPressed(SDL_BUTTON_LEFT))
        {
            sprite.color = Color().BLACK;
        }

        if (p_level->m_input->IsReleased((SDL_BUTTON_LEFT)))
        {
            sprite.color = Color().WHITE;
        }
    }

    if (this->GetName() == "mouseright" || this->GetName() == "mouseright1" || this->GetName() == "mouseright2" || this->GetName() == "mouseright3")
    {
        if (p_level->m_input->IsPressed((SDL_BUTTON_RIGHT)))
        {
            sprite.color = Color().BLACK;
        }

        if (p_level->m_input->IsReleased((SDL_BUTTON_RIGHT)))
        {
            sprite.color = Color().WHITE;
        }
    }

    if (this->GetName() == "mousemiddle" || this->GetName() == "mousemiddle1" || this->GetName() == "mousemiddle2" || this->GetName() == "mousemiddle3")
    {
        if (p_level->m_input->IsPressed((SDL_BUTTON_MIDDLE)))
        {
            sprite.color = Color().BLACK;
        }

        if (p_level->m_input->IsReleased((SDL_BUTTON_MIDDLE)))
        {
            sprite.color = Color().WHITE;
        }
    }

}
