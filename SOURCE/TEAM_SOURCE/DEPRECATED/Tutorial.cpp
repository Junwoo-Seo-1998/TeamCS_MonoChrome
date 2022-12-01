#include "Tutorial.h"
#include "CommonLevel.h"
#include "Color.h"

void Tutorial::Initialize()
{
	platform_control = false;
	platform_count = 0;
	camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera
	camera.position.Set(0, 0, 0);
	m_backgroundColor = { 8, 134, 150, 255 };
	SetPhysicsWorld({ 0.f,-98.f });

	player = new Player(this, camera);
	player->init("player", -200, -30, 32, 64, Color().WHITE);
	platform1 = new Platform(this);
	platform1->init("platform", -200, -50, 200, 12, Color().BLACK);
	platform2 = new Platform(this);
	platform2->init("platform", -75, 0, 200, 12, Color().WHITE);
	platform3 = new Platform(this);
	platform3->init("platform", 200, 50, 400, 12, Color().BLACK);
	cplatform.push_back(new ColorChangePlatform(this));
	cplatform[0]->init("cplatform", 300, 150, 12, 100, Color().BLUE);
	platform_count++;
	platform_max = platform_count;
	platform_count = 0;

	destination = new Destination(this);
	destination->init("destination", 400, 150, Color().RED);
}

void Tutorial::Update(float dt)
{
	if (m_input->IsTriggered(SDL_SCANCODE_C))
		m_game->Change(LV_MainMenu);

        if (m_input->IsTriggered(SDL_SCANCODE_R))
            m_game->Restart();

	if (m_input->IsTriggered(SDL_SCANCODE_1))
	{
		player->sprite.color = Color().RED;
	}
	if (m_input->IsTriggered(SDL_SCANCODE_2))
	{
		player->sprite.color = Color().GREEN;
	}
	if (m_input->IsTriggered(SDL_SCANCODE_3))
	{
		player->sprite.color = Color().BLUE;
	}
	player->update(dt);
	//platform control mode start 
	if (platform_control == false)
	{
		player->update(dt);
	}
	if (m_input->IsTriggered(SDL_SCANCODE_X))
	{
		if (platform_control == true)
		{
			platform_control = false;
		}
		else if (platform_control == false)
		{
			platform_control = true;

		}
	}
	if (platform_control == true)
	{
		camera.position.x = cplatform[platform_count]->transform.position.x;
		camera.position.y = cplatform[platform_count]->transform.position.y;

		if (m_input->IsTriggered(SDL_SCANCODE_Z))
		{
			if (platform_count < platform_max - 1)
				platform_count++;
			else
				platform_count = 0;
		}
		if (m_input->IsPressed(SDL_SCANCODE_Q))
		{
			if (Color().AreTheySame(cplatform[platform_count]->sprite.color, Color().GREEN))
				cplatform[platform_count]->transform.rotation -= dt * 100.f;
		}

		if (m_input->IsPressed(SDL_SCANCODE_E))
		{
			if (Color().AreTheySame(cplatform[platform_count]->sprite.color, Color().GREEN))
				cplatform[platform_count]->transform.rotation += dt * 100.f;

		}

		if (m_input->IsPressed(SDL_SCANCODE_D))
		{
			if (Color().AreTheySame(cplatform[platform_count]->sprite.color, Color().BLUE))
				cplatform[platform_count]->physics.SetVelocity(10.f, 0.f);

		}
		if (m_input->IsReleased((SDL_SCANCODE_D)))
		{
			cplatform[platform_count]->physics.SetVelocity(0.f, 0.f);
		}


		if (m_input->IsPressed((SDL_SCANCODE_A)))
		{
			if (Color().AreTheySame(cplatform[platform_count]->sprite.color, Color().BLUE))
				cplatform[platform_count]->physics.SetVelocity(-10.f, 0.f);

		}
		if (m_input->IsReleased((SDL_SCANCODE_A)))
		{
			cplatform[platform_count]->physics.SetVelocity(0.f, 0.f);
		}


		if (m_input->IsPressed((SDL_SCANCODE_W)))
		{
			if (Color().AreTheySame(cplatform[platform_count]->sprite.color, Color().BLUE))
				cplatform[platform_count]->physics.SetVelocity(0.f, 10.f);
		}

		if (m_input->IsReleased((SDL_SCANCODE_W)))
		{
			cplatform[platform_count]->physics.SetVelocity(0.f, 0.f);
		}


		if (m_input->IsPressed((SDL_SCANCODE_S)))
		{
			if (Color().AreTheySame(cplatform[platform_count]->sprite.color, Color().BLUE))
				cplatform[platform_count]->physics.SetVelocity(0.f, -10.f);
		}
	}
	if (destination->physics.IsCollidingWith("player"))
	{
		m_game->Change(LV_MainMenu);
	}
	UpdatePhysics(dt);
	Render(dt);
}

void Tutorial::Close()
{
	delete player;
	delete platform1, platform3;
	cplatform.clear();
}
