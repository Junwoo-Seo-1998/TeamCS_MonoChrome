/******************************************************************************/
/*
File name: Level2.h
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
class Level2 :public State
{
public:
    Level2() :State() {};
    ~Level2() override {};
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
    Helper* mouse[4];
    Helper* arrow[2];
    Helper* player_dumy;
    Helper* platform_dumy;
    bool is_clear;
    float timer;
    bool platform_control;
    int cplatform_count;
    int cplatform_max;
    int platform_max;
    bool mouse_timer;
    float anime;
};
