/******************************************************************************/
/*
File name: SoundControl.cpp
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SoundControl.h"


SoundControl::SoundControl(State* current_level):p_level(current_level)
{

}

void SoundControl::ControlAudio()
{
    static int volume = 64;

    if (p_level->m_input->IsTriggered(SDL_SCANCODE_UP)) {
        volume += 8;
        if (volume > 128)
            volume = 128;
    }

    else if (p_level->m_input->IsTriggered(SDL_SCANCODE_DOWN)) {
        volume -= 8;
        if (volume < 0)
            volume = 0;
    }

    //p_level->backgroundMusic.SetVolume(volume);
}
