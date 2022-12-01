/******************************************************************************/
/*
File name: Player.h
Project name: Monochrome
Author(s): Major: JunWoo Seo, secondary: ChunMook Kim
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "engine\Object.h"
#include "Gun.h"
class State;
class Player:public Object
{
public:
	Player(State* current_level,Camera&cam);
	~Player() override;
public:
	void init(std::string name, float positionX, float positionY, float scaleX, float scaleY, SDL_Color color);
	void update(float dt);
        SDL_Color having_color;
private:
	void ground_check();
	void input_update();
        void fall_check();
        void colide_with_cplatform();
private:
	State * p_level;
	float y_pos;
	
	bool up, down, left, right;
        bool is_collide_cplatform;
        bool is_jumping;
	Object sound_effect;
	Gun gun;
        
public:
        bool is_ground;
        bool is_dead;
        bool is_stop;
        bool is_jump;
        bool is_moving;
        bool is_pcmode;
        bool get_colide(void);
        void jump_check(void);
};