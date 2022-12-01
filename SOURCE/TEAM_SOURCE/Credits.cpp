/******************************************************************************/
/*
File name: Credits.cpp
Project name: Monochrome
Author(s): SungMin Moon
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/#include "Credits.h"
#include "CommonLevel.h"
#include "Color.h"

void Credits::Initialize()
{

	m_backgroundColor = Color().WHITE;
	camera.position.Set(0, 0, 0);
	backbutton = new Button(this, camera);
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

	CreateAndRegisterHudText(&text0, "President: Claude Comair", "President", 600, 50);
	text0.transform.position.Set(100.f, 250.f, 0.f);

	CreateAndRegisterHudText(&textinst, "Instructor: David Ly, Rudy Castan, TA Juyong Jeong", "Instructor", 600, 50);
	textinst.transform.position.Set(100.f, 200.f, 0.f);

	CreateAndRegisterHudText(&text1, "Presented by Team CS", "CreatedBy", 600, 50);
	text1.transform.position.Set(100.f, 150.f, 0.f);

	CreateAndRegisterHudText(&text2, "Producer: Chunmook Kim", "Producer", 600, 50);
	text2.transform.position.Set(100.f, 100.f, 0.f);

	CreateAndRegisterHudText(&text3, "Tech Director: Junwoo Seo", "TechD", 600, 50);
	text3.transform.position.Set(100.f, 50.f, 0.f);

	CreateAndRegisterHudText(&text4, "Design Lead: Sungmin Moon", "Design", 600, 50);
	text4.transform.position.Set(100.f, 0.f, 0.f);

	CreateAndRegisterHudText(&soundcamp, "Gold Bass Digger Sound Asset supported via Samsung Soundcamp.", "Soundcamp", 800, 50);
	soundcamp.transform.position.Set(0.f, -250.f, 0.f);

	CreateAndRegisterHudText(&reserved, "All content 2018 DigiPen (USA) Corporation, all rights reserved.", "Reserved", 800, 50);
	reserved.transform.position.Set(0.f, -300.f, 0.f);

	backbutton->init("Back", 50, -500, 300, 100, 50);

}

void Credits::Update(float dt)
{
	backbutton->update();
	// Move to level1 by pressing 'C' key
	if (m_input->IsTriggered(SDL_SCANCODE_C))
		m_game->Change(LV_LEVEL1);

	// Pause current state and move to pause state
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();

	if (m_input->IsTriggered(SDL_BUTTON_LEFT))
		backbutton->click();

	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void Credits::Close()
{
	ClearBaseState();
}


void Credits::CreateAndRegisterHudText(Object * textObject, const char * textContents, const char * id, float sizex, float sizey)
{
	textObject->SetName(id);
	textObject->transform.SetScale(sizex, sizey);
	textObject->text.SetText(State::m_renderer, textContents, mainFont);
	textObject->text.color = Color().BLACK;
	textObject->text.isHud = true;
	AddObject(textObject);
}
