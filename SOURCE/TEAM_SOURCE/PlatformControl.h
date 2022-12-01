/******************************************************************************/
/*
File name: PlatformControl.h
Project name: Monochrome
Author(s): ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include<vector>
#include"ColorChangePlatform.h"
#include"Helper.h"
class Camera;
class State;
class PlatformControl
{
public:
    ~PlatformControl();
    PlatformControl(State* current_level, Camera& cam);
    void Update(std::vector<ColorChangePlatform*> platform, int& platform_count, int& platform_max, float dt);
private:
    Camera & camera;
    State * p_level;
public:
    Helper* target_platform_arrow;
    Helper* rotation_guide[2];
    Helper* move_guide[4];
public:
    Object PC_mode_on;
    Object PC_mode_off;
    Object Next_plafform;
    Object Control_platform;
public:
    bool is_collide_to_player;
    bool Sound_check;
};