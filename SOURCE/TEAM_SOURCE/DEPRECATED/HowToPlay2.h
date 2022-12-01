/******************************************************************************/
/*
File name: HowToPlay2.h
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
class HowToPlay2 : public State
{
	friend class Game;
protected:
	HowToPlay2() : State() {};
	~HowToPlay2() override {};
	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;
private:
	Object wasdblue, z, xtoplayer, qe, ctomoveon;
};