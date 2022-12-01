/******************************************************************************/
/*
File name: Gun.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Gun.h"
#include "engine\State.h"
#include "Color.h"
#include "Player.h"

Gun::Gun(State * current_level, Camera& cam,Object*owner)
:Object(),p_level(current_level),p_owner(owner),mouse(current_level,cam)
{}

Gun::~Gun()
{
	p_level->RemoveObject(&sound_effect);
	for (auto bullet:bullets)
	{
		p_level->RemoveObject(bullet);
	}
	p_level->RemoveObject(this);
}

void Gun::init(std::string name, float positionX, float positionY, float scaleX, float /*scaleY*/, SDL_Color color)
{
	// Sound effect
	 sound_effect.SetName("firesound");
	// Load the sound file to play
	// *Only wav files work
	sound_effect.sound.LoadSound("sound/fire.wav");
	p_level->AddObject(&sound_effect);

	SetName(name.c_str());

	transform.position.Set(positionX, positionY, 0.f);
	transform.SetScale(scaleX, (scaleX/33.f)*18.f);

	sprite.color = color;
	sprite.LoadImage("texture/gun.png", p_level->m_renderer);
	//Turret.customPhysics.bodyType = CustomPhysics::STATIC;

	//Turret.physics.bodyType = Physics::STATIC;
	//Turret.physics.GenerateBody(GetPhysicsWorld(), &Turret.transform);
	p_level->AddObject(this);
}

void Gun::update(float dt)
{
        Player* player = dynamic_cast<Player*>(p_owner);
        if(player==nullptr)
            return;
	transform.position = p_owner->transform.position;
        
	transform.rotation = mouse.get_rad_respect_mouse(p_owner)*(180.f / (float)std::acos(-1));//to degree
        float rad = mouse.get_rad_respect_mouse(this);
        b2Vec2 directionVector = { cos(rad) ,sin(rad) };
        if (directionVector.x < 0)
            sprite.flip = SDL_FLIP_VERTICAL;
        else
            sprite.flip = SDL_FLIP_NONE;
        directionVector *= transform.GetScale().x;
        transform.position.x += directionVector.x;
        transform.position.y += directionVector.y;
        sprite.color = player->having_color;
	bullets.remove_if([](Bullet* bullet)
	{
		if (bullet->is_dead)
		{
			delete bullet;
			return true;
		}
		return false;
	}
	);
	for (auto bullet : bullets)
	{
		bullet->update(dt);
	}
}

void Gun::fire()
{
    Color color;
    if (!color.AreTheySame(color.WHITE,sprite.color))
    {
        float rad = mouse.get_rad_respect_mouse(this);
        b2Vec2 directionVector = { cos(rad) ,sin(rad) };
        directionVector *= 100;
        b2Vec2 ownerpos = { transform.position.x,transform.position.y };
        b2Vec2 tip = get_tip_pos() + ownerpos;
        Bullet*p_bullet = new Bullet(p_level);
        SDL_Color ownercolor = sprite.color;
        p_bullet->init("bullet", tip.x, tip.y, 10, 10, ownercolor);
        p_bullet->physics.SetVelocity(directionVector);
        bullets.push_front(p_bullet);//do not for get del it's just for test
        Player*player = dynamic_cast<Player*>(p_owner);
        if(player==nullptr)
            return;
        player->having_color = Color().WHITE;
	sound_effect.sound.Play();
    }  
}

b2Vec2 Gun::get_tip_pos()
{
	
	b2Vec2 tipLocation;
	float rad= mouse.get_rad_respect_mouse(this);
	b2Vec2 directionVector = { cos(rad) ,sin(rad) };

	float turretWidth = (transform.GetScale().x / 2.f);
	tipLocation.x = turretWidth * directionVector.x;
	tipLocation.y = turretWidth * directionVector.y;

	return tipLocation;
}
