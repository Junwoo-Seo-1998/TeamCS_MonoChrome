/******************************************************************************/
/*
File name: Level5.h
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
#include "PlatformControl.h"
#include <vector>
#include "Color.h"
#include "Paint.h"
class Level5 :public State
{
public:
    Level5() :State() {};
    ~Level5() override {};
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
    Paint* paint[2];
    bool platform_control;
    int cplatform_count;
    int cplatform_max;
    int platform_max;
    bool is_clear;
    float timer;
};
