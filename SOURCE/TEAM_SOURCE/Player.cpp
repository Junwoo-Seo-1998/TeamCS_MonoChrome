/******************************************************************************/
/*
File name: Player.cpp
Project name: Monochrome
Author(s): Major: JunWoo Seo, secondary: ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Player.h"
#include "engine\State.h"
#include "Color.h"

Player::Player(State * current_level,Camera& cam)
:Object(), p_level(current_level),is_ground(false),up(false),down(false),left(false),right(false), is_collide_cplatform(false), is_jumping(true), is_pcmode(false)
,gun(current_level,cam,this),having_color({255,255,255,255})
{
	
}

Player::~Player()
{
    p_level->RemoveObject(&sound_effect);
    p_level->RemoveObject(this);
}

void Player::init(std::string name, float positionX, float positionY, float scaleX, float /*scaleY*/, SDL_Color color)
{
	// Sound effect
	sound_effect.SetName("jump");
	// Load the sound file to play
	// *Only wav files work
	sound_effect.sound.LoadSound("sound/jump.wav");
	p_level->AddObject(&sound_effect);

	y_pos = positionY;
	SetName(name.c_str());
        is_dead = false;
        is_stop = false;
	transform.position.Set(positionX, positionY, 0);
        scaleX = scaleX + 10;
	transform.SetScale(scaleX, (scaleX/28.f)*51.f); //for ratio 
	sprite.color = color;
	sprite.LoadImage("texture/newrunning.png", p_level->m_renderer);
        
        //gle true so animation activates 
        
        sprite.activeAnimation = true;
         //number of frames to update
        sprite.SetFrame(7);
        // speed of frame updating
        sprite.SetSpeed(10.f);
        //the animation
        sprite.rewindAnimation = true;

	physics.pOwnerTransform = &transform;
	physics.bodyType = Physics::DYNAMIC;
	physics.bodyShape = Physics::BOX;
	physics.radius = 32;
	physics.SetRestitution(0.f);
	physics.GenerateBody(p_level->GetPhysicsWorld(), &transform);
	p_level->AddObject(this);

	gun.init("pistol", 0, 0, 50, 5, { 255, 255, 255,255 });

	

}

void Player::fall_check()
{
    if (this->transform.position.y < -500)
    {
        is_dead = true;
    }
}
void Player::ground_check()
{
        
        float diff = y_pos - transform.position.y;
        diff = std::abs(diff);
	if (diff<=0.4f)//last == current then ground
	{
		is_ground = true;
	}
	else 
		is_ground=false;
	y_pos = transform.position.y;// last pos save
}

void Player::colide_with_cplatform(void)
{
    if ((this->physics.IsCollidingWith("cplatform")|| this->physics.IsCollidingWith("cplatform1")|| this->physics.IsCollidingWith("cplatform2") || 
        this->physics.IsCollidingWith("cplatform3") || this->physics.IsCollidingWith("cplatform4") || this->physics.IsCollidingWith("cplatform5") || 
        this->physics.IsCollidingWith("cplatform6") || this->physics.IsCollidingWith("cplatform7") || this->physics.IsCollidingWith("cplatform8") || 
        this->physics.IsCollidingWith("cplatform9") || this->physics.IsCollidingWith("cplatform10")))
    {
        is_collide_cplatform = false;
    }
    else
    {
        is_collide_cplatform = true;
    }

}

void Player::jump_check(void)
{
    if (this->physics.IsColliding())
    {
        is_jump = false;
    }
    else
    {
        is_jump = true;
    }
}

bool Player::get_colide(void)
{
    return is_collide_cplatform;
}

void Player::input_update()
{
	const float speed = 10.f;
	b2Vec2 movement = {0.f,0.f};
	if (is_ground)
	{
            if (is_stop == false)
            {
                if (p_level->m_input->IsPressed(SDL_SCANCODE_A))
                    left = true;
                else
                    left = false;

                if (p_level->m_input->IsPressed(SDL_SCANCODE_D))
                    right = true;
                else
                    right = false;

                if (p_level->m_input->IsTriggered(SDL_SCANCODE_W))
                    up = true;
                else
                    up = false;

                if (left)
                {
                    movement.x = -1;
                    sprite.flip=SDL_FLIP_HORIZONTAL;
                }
                if (right)
                {
                    movement.x = 1;
                    sprite.flip = SDL_FLIP_NONE;
                }
                if (up)
                {
		    sound_effect.sound.Play();
                    movement.y = 1;
                }

                movement.x *= speed;
                // Changed double speed to triple speed
                movement.y *= speed * 3;
                physics.SetVelocity(movement);
            }
	    
	}
    if (right||left)
    {
        is_moving = true;
    }
    else
    {
        is_moving = false;
    }


	if (p_level->m_input->IsPressed(SDL_BUTTON_LEFT))
	{
            if(is_stop==false)
		gun.fire();
            
	}

       
}
void Player::update(float dt)
{
    
    
    ground_check();
    fall_check();
    gun.update(dt);
    colide_with_cplatform();
    input_update();
    jump_check();
    if (is_pcmode)
    {
        sprite.SetCurrentFrame(false, 0);
        //add platform control animation at here
    }
    else if (is_moving)
    {
        if (sprite.GetCurrentFrame() >= 6)
        {
            sprite.SetCurrentFrame(false, 2);
        }
        if(sprite.GetCurrentFrame()==0)
        {
            sprite.SetCurrentFrame(false, 2);
        }
    }
    else
    {
        sprite.SetCurrentFrame(false, 1);//여기서 멈춘다
    }
}
