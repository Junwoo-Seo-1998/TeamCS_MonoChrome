/******************************************************************************/
/*
File name: Level8.h
Project name: Monochrome
Author(s): SungMin Moon
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
#include "Paint.h"
class Level8 :public State
{
public:
    Level8() :State() {};
    ~Level8() override {};
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
    Paint * paint, *paint2b;
    bool platform_control;
    int cplatform_count;
    int cplatform_max;
    int platform_max;
    bool is_clear;
    float timer;
};
