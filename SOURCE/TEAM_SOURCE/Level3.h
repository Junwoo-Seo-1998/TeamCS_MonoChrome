/******************************************************************************/
/*
File name: Level3.h
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "Player.h"
#include "Platform.h"
#include "ColorChangePlatform.h"
#include "PlatformControl.h"
#include "Destination.h"
#include <vector>
#include "Color.h"
#include "Helper.h"
class Level3 :public State
{
public:
    Level3() :State() {};
    ~Level3() override {};
    void Initialize() override;
    void Update(float dt) override;
    void Close() override;
private:
    Object error_sound;
    Object next_level;
    Player * player;
    std::vector<ColorChangePlatform*> cplatform;
    std::vector<Platform*> platform;
    Destination* destination;
    PlatformControl* platformcontrol;
    bool platform_control;
    int cplatform_count;
    int cplatform_max;
    int platform_max;
    bool is_clear;
    float timer;
    Helper* mouse[12];
    Helper* arrow[4];
    Helper* player_dumy;
    Helper* platform_dumy;
    bool mouse_timer;
    float anime;
};
