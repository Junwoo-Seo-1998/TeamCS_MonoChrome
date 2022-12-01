/******************************************************************************/
/*
File name: Level4.h
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
#include "Destination.h"
#include <vector>
#include "Color.h"
#include "PlatformControl.h"
#include "Paint.h"
class Level4 :public State
{
public:
    Level4() :State() {};
    ~Level4() override {};
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
    Paint* paint;
    Helper* player_dumy[2];
    Helper* arrow[3];
    Helper* mouse[4];
    bool platform_control;
    int cplatform_count;
    int cplatform_max;
    int platform_max;
    bool is_clear;
    float timer;
    bool mouse_timer;
    float anime;
};
