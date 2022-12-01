/******************************************************************************/
/*
File name: Level1.h
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
class Level1 :public State
{
public:
    Level1() :State() {};
    ~Level1() override {};
    void Initialize() override;
    void Update(float dt) override;
    void Close() override;
private:
    Player * player;
    std::vector<Platform*> platform;
    Destination* destination;
    Helper* helper[3];

    bool is_clear;
    float timer;
    Object next_level;
    Object background;
    bool platform_control;
    int platform_count;
    int platform_max;
};
