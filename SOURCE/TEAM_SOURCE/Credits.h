/******************************************************************************/
/*
File name: Credits.h
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "MouseUtility.h"
#include "Button.h"
class Credits : public State
{
	friend class Game;
protected:
	Credits() : State() {};
	~Credits() override {};
	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;
private:
	Object text0, textinst, text1, text2, text3, text4, reserved, soundcamp;
	Button * backbutton;
	void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id, float sizex, float sizey);
};