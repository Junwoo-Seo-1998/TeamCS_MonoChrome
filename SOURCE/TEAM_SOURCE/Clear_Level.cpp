/******************************************************************************/
/*
File name: Clear_Level.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Clear_Level.h"
#include "Color.h"
#include "CommonLevel.h"
const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

void Clear_Level::Initialize()
{
    m_backgroundColor = Color().BLACK;

    // Set Camera
    // You don't need to do this anymore
    //camera.Initialize(int(State::m_width), int(State::m_height));
    // Set position of the camera
    camera.position.Set(0, 0, 0);

    // Set main font
    // Load the font file to use as a main font
    // and set the default size of it
    mainFont = TTF_OpenFont("font/Default.ttf", 48);

    CreateAndRegisterHudText(&titleText, "CLEAR!", "Title");
    titleText.transform.position.Set(0.f, 200.f, 0.f);

    CreateAndRegisterHudText(&instructionsText, "Press C to go to next level", "Instructions");
    instructionsText.transform.position.Set(0.f, -200.f, 0.f);
}

void Clear_Level::Update(float dt)
{
    /******************* State ******************/

    // Move to level1 by pressing 'C' key
    if (m_input->IsTriggered(SDL_SCANCODE_C))
        m_game->Change(LV_MainMenu);

    // Pause current state and move to pause state
    if (m_input->IsTriggered(SDL_SCANCODE_P))
        m_game->Pause();

    // Must be one of the last functions called at the end of State Update
    UpdatePhysics(dt);
    Render(dt);
}

void Clear_Level::Close()
{
    // Wrap up state
    ClearBaseState();
}

void Clear_Level::CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id)
{
    // Set the object's name
    textObject->SetName(id);

    // Set the scale of the object
    textObject->transform.SetScale(650, 130);

    // Set the text to render out
    textObject->text.SetText(State::m_renderer, textContents, mainFont);

    // Set the colors r,g,b,a (0~255)
    textObject->text.color = WHITE;

    // Set either if the object to be hud or not
    textObject->text.isHud = true;

    // Register the object to the state
    AddObject(textObject);
}
