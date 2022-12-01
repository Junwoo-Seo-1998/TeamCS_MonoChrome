#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "Player.h"
#include "Platform.h"
#include "ColorChangePlatform.h"
#include <vector>
#include "Destination.h"
class Tutorial :public State
{
public:
	Tutorial() :State() {};
	~Tutorial() override {};
	void Initialize() override;
	void Update(float dt) override;
	void Close() override;
private:
	Player * player;
	Platform *platform1, *platform2, *platform3;
	std::vector<ColorChangePlatform*> cplatform;
	Destination* destination;
	bool platform_control;
	int platform_count;
	int platform_max;
};
