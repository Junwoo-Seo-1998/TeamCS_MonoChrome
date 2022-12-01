/******************************************************************************/
/*!
\file   Object.h
\author Juyong Jeong
\par    email: jeykop14\@digipen.edu
\par    GAM150 demo
\date   2018/03/16

This is base object class containing component classes
*/
/******************************************************************************/
#pragma once
#include "SoundEffect.h"
#include "Text.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Particle.h"

class Object {

	friend class State;

	unsigned    m_id = 0;	        // Object unique id - By Engine
	std::string m_name = "Unnamed";	// Object name - By User

public:

	Object();
	virtual ~Object();

	bool active = true;		// Object active toggle

	// Components
	SoundEffect	sound;		// Sound component
	Text		text;		// Text component
	Sprite		sprite;		// Sprite component
	Transform	transform;	// Transform component
	Physics		physics;	// Physics component
	Emitter		emitter;	// Emitter component

	// Manage name and id
	void				SetName(const char* name);
	const std::string&	GetName() const;
	unsigned			GetId() const;
	
private:

	// Virtual functions to be used for derived Object classes
	virtual void Initialize();
	virtual void Update(float dt);
	virtual void Close();

	Object(const Object&) = delete;
	Object(Object&&) = delete;
	Object& operator=(const Object&) = delete;
	Object& operator=(Object&&) = delete;

};