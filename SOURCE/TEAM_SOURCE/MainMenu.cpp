/******************************************************************************/
/*
File name: MainMenu.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "CommonLevel.h"
#include "Color.h"
const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

void MainMenu::Initialize()
{
	m_backgroundColor = Color().BLACK;

	// Set Camera
	// You don't need to do this anymore
	//camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera

	camera.position.Set(0, 0, 0);
	mouse = new MouseUtility(this, camera);
	// Set main font
	// Load the font file to use as a main font
	// and set the default size of it
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

	CreateAndRegisterHudText(&titleText, "Monochrome", "Title", 500.f, 100.f);
	titleText.transform.position.Set(0.f, 200.f, 0.f);

	CreateAndRegisterHudText(&startbutton, "Start", "Start", 200.f, 100.f);
	startbutton.transform.position.Set(0.f, 50.f, 0.f);

	b1top = startbutton.transform.position.y + (startbutton.transform.GetScale().y / 2);
	b1bottom = startbutton.transform.position.y - (startbutton.transform.GetScale().y / 2);
	b1left = startbutton.transform.position.x - (startbutton.transform.GetScale().x / 2);
	b1right = startbutton.transform.position.x + (startbutton.transform.GetScale().x / 2);

	CreateAndRegisterHudText(&creditsbutton, "Credits", "Credits", 200.f, 100.f);
	creditsbutton.transform.position.Set(0.f, -100.f, 0.f);

	b2top = creditsbutton.transform.position.y + (creditsbutton.transform.GetScale().y / 2);
	b2bottom = creditsbutton.transform.position.y - (creditsbutton.transform.GetScale().y / 2);
	b2left = creditsbutton.transform.position.x - (creditsbutton.transform.GetScale().x / 2);
	b2right = creditsbutton.transform.position.x + (creditsbutton.transform.GetScale().x / 2);

	CreateAndRegisterHudText(&quitbutton, "Quit", "Quit", 200.f, 100.f);
	quitbutton.transform.position.Set(0.f, -250.f, 0.f);

	b3top = quitbutton.transform.position.y + (quitbutton.transform.GetScale().y / 2);
	b3bottom = quitbutton.transform.position.y - (quitbutton.transform.GetScale().y / 2);
	b3left = quitbutton.transform.position.x - (quitbutton.transform.GetScale().x / 2);
	b3right = quitbutton.transform.position.x + (quitbutton.transform.GetScale().x / 2);
	//CreateAndRegisterHudText(&instructionsText, "Press C to go to next level", "Instructions");
	//instructionsText.transform.position.Set(0.f, -200.f, 0.f);
}

void MainMenu::Update(float dt)
{
	/******************* State ******************/
	CheckButton1();
	CheckButton2();
	CheckButton3();
	// Move to level1 by pressing 'C' key
	if (m_input->IsTriggered(SDL_SCANCODE_C))
		m_game->Change(LV_LEVEL1);

	if (m_input->IsTriggered(SDL_SCANCODE_SPACE))
		m_game->Change(LV_Credits);

	// Pause current state and move to pause state
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();
	if (m_input->IsTriggered(SDL_BUTTON_LEFT))
	{
		if (CheckButton1() == true)
			m_game->Change(LV_LEVEL1);
		if (CheckButton2() == true)
			m_game->Change(LV_Credits);
		if (CheckButton3() == true)
			m_game->Quit();
	}
	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void MainMenu::Close()
{
	// Wrap up state
	ClearBaseState();
}

void MainMenu::CreateAndRegisterHudText(Object * textObject, const char * textContents, const char * id, float sizex, float sizey)
{
	textObject->SetName(id);
	textObject->transform.SetScale(sizex, sizey);
	textObject->text.SetText(State::m_renderer, textContents, mainFont);
	textObject->text.color = Color().WHITE;
	textObject->text.isHud = true;
	AddObject(textObject);
}

bool MainMenu::CheckButton1()
{
	if ((b1left <= mouse->get_mouse_pos().x) && (b1right >= mouse->get_mouse_pos().x)
		&& (b1bottom <= mouse->get_mouse_pos().y) && (b1top >= mouse->get_mouse_pos().y))
		return true;
	else
		return false;
}

bool MainMenu::CheckButton2()
{
	if ((b2left <= mouse->get_mouse_pos().x) && (b2right >= mouse->get_mouse_pos().x)
		&& (b2bottom <= mouse->get_mouse_pos().y) && (b2top >= mouse->get_mouse_pos().y))
		return true;
	else
		return false;
}

bool MainMenu::CheckButton3()
{
	if ((b3left <= mouse->get_mouse_pos().x) && (b3right >= mouse->get_mouse_pos().x)
		&& (b3bottom <= mouse->get_mouse_pos().y) && (b3top >= mouse->get_mouse_pos().y))
		return true;
	else
		return false;
}