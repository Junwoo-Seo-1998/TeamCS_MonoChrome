/******************************************************************************/
/*
File name: MainMenu.h
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "MouseUtility.h"
class MainMenu : public State
{
	friend class Game;

protected:

	MainMenu() : State() {};
	~MainMenu() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:

	Object titleText;
	Object startbutton;
	Object creditsbutton;
	Object quitbutton;

	float b1top, b1bottom, b1left, b1right;
	float b2top, b2bottom, b2left, b2right;
	float b3top, b3bottom, b3left, b3right;
	//Object instructionsText;
	MouseUtility * mouse;
	void CreateAndRegisterHudText(Object * textObject, const char * textContents, const char * id, float sizex, float sizey);
	bool CheckButton1();
	bool CheckButton2();
	bool CheckButton3();
};

