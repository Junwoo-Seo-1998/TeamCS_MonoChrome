/******************************************************************************/
/*
File name: Level_Test.h
Project name: Monochrome
Author(s): JunWoo Seo 
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "Player.h"
#include "Platform.h"
#include "ColorChangePlatform.h"
#include "Paint.h"

class Level_Test:public State
{
public:
	Level_Test() :State() {};
	~Level_Test() override {};
	void Initialize() override;
	void Update(float dt) override;
	void Close() override;
private:
	Player *player;
	Platform* platform;
	ColorChangePlatform*cplatform;
	Paint *paint;
};
