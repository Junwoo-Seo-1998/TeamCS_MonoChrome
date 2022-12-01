/******************************************************************************/
/*
File name: SoundControl.h
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
class SoundControl
{
private:
    State * p_level;
public:
    SoundControl(State* current_level);
    void ControlAudio();
};

