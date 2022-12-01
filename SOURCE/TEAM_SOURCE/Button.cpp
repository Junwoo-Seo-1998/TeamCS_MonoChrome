/******************************************************************************/
/*
File name: Button.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include"Button.h"
#include"engine\State.h"
#include "CommonLevel.h"
Button::Button(State * current_level,Camera& cam)
:Object(),p_level(current_level),mouse(current_level,cam),is_mouse_on(false)
{
    
}

Button::~Button()
{
    p_level->RemoveObject(this);
    p_level->RemoveObject(&text);
}

void Button::init(std::string button_text, int font_size, float positionX, float positionY, float scaleX, float scaleY)
{
    SetName("Button");
    transform.position.Set(positionX, positionY, 0);
    transform.SetScale(scaleX, scaleY);
    sprite.color = { 255,255,255,255 };
    sprite.LoadImage("texture/rect.png", p_level->m_renderer);
    p_level->AddObject(this);

    //text
    _TTF_Font*mainFont = TTF_OpenFont("font/Default.ttf", font_size);
    text.SetName("Title");
    // Set the position of the object
    text.transform.position.Set(positionX, positionY, 0.0f);
    // Set the scale of the object
    text.transform.SetScale(scaleX, scaleY);
    text.text.SetText(p_level->m_renderer, button_text.c_str(), mainFont);
    text.text.color = SDL_Color{ 0, 0, 0, 255 };
    // Set either if the object to be hud or not
    text.text.isHud = true;
    p_level->AddObject(&text);
}

void Button::update()
{
    b2Vec2 scalehalf = transform.GetScale();
    scalehalf = { scalehalf.x / 2,scalehalf.y / 2 };
    b2Vec2 pos = { transform.position.x,transform.position.y };
    float top, bottom, left, right;
    top = pos.y + scalehalf.y;
    bottom = pos.y - scalehalf.y;
    left = pos.x - scalehalf.x;
    right = pos.x + scalehalf.x;
    b2Vec2 mouse_pos = mouse.get_mouse_pos();
    if ((left<=mouse_pos.x)&&(mouse_pos.x<=right)&& (bottom <= mouse_pos.y) && (mouse_pos.y <= top))
	is_mouse_on = true;
    else
	is_mouse_on = false;
}

void Button::click()
{
    if (is_mouse_on)
    {
	p_level->m_game->Resume();
	p_level->m_game->Change(LV_MainMenu);
    }
    
}

