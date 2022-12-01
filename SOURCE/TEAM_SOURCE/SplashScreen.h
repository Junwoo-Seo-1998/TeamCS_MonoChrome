/******************************************************************************/
/*
File name: SplashScreen.h
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
class SplashScreen : public State
{
	friend class Game;
protected:
	SplashScreen() : State() {};
	~SplashScreen() override {};
	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;
private:
	Object digipenLogo, teamLogo;
        float timer;
};