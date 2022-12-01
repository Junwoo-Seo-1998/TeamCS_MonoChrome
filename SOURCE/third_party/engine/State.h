/******************************************************************************/
/*!
\file   State.h
\author Juyong Jeong
\par    email: jeykop14\@digipen.edu
\par    GAM150 demo
\date   2018/03/15

This is virtual base class for derived user-custom State classes
*/
/******************************************************************************/

#pragma once
#include <vector>
#include "engine\Camera.h"
#include "engine\Music.h"
#include "Box2D\Common\b2Math.h"
#include "Input.h"

class Game;
class Object;
class Physics;
class Graphic;
class b2World;
class CustomPhysics;
class CustomBaseObject;
struct _TTF_Font;

class State {

	friend Physics;

	// type definition of object vector
	using Objects = std::vector<Object*>;
	// type definition of grahpic vector
	using Graphics = std::vector<Graphic*>;
	// type definition of physics vector
	using PhysicsVector = std::vector<Physics*>;
	// type definition of custom physics vector
	using CustomPhysicsVector = std::vector<CustomPhysics*>;

public:

	State();
	virtual	~State();

	// Virtual functions
	// There are derived to propageted
	virtual	void Initialize() = 0;
	virtual	void Update(float dt) = 0;
	virtual	void Close() = 0;

	// Set the object's unique id 
	void	 SetId(unsigned stateId);
	// Get the object's id as an unsigend numter
	unsigned GetId();

	bool m_useBuiltInPhysics;					// Toggle decides either to use built-in physics or custom physics

	static float			m_width, m_height;	// Shared window size info
	static SDL_Rect			m_viewport;			// Shared viewport rect
	static SDL_Renderer		*m_renderer;		// Shared pointer to renderer
	static Input			*m_input;	        // Shared pointer to input
	static Game		        *m_game;			// Shared pointer to game(state manager)

	/////////////////////////////////////////////////////////////
	//	Object manager
	/////////////////////////////////////////////////////////////
	// Register the object to the state
	void	AddObject(Object *object);
	// Check if there is specific object by passing an object's id
	bool	HasObject(unsigned objectId);
	// Check if there is specific object by passing a pointer to object
	bool	HasObject(Object *object);
	// Check if there is specific object by passing an object's name
	bool	HasObject(const char* name);
	// Remove the object from the state by passing an object's id
	void	RemoveObject(unsigned objectId);
	// Remove the object from the statet by passing a pointer to object
	void	RemoveObject(Object *object);
	// Remove the object from the state by passing an object's name
	void	RemoveObject(const char* name);
	// Get the object from the state by passing an object's id
	Object*	GetObject(unsigned objectId);
	// Get the object from the state by passing an object's name
	Object*	GetObject(const char* name);
	// Get the object list(vector)
	const Objects& GetObjects() const;
	// Initialize every object in the list
	void	InitializeObjects();
	// Update every object in the list
	void	UpdateObjects(float dt);
	// Close every object in the list
	void	CloseObjects();

	/////////////////////////////////////////////////////////////
	//	Graphic system
	/////////////////////////////////////////////////////////////
	// Remove the sprite from a object
	void RemoveSpriteComponent(Sprite* sprite);
	// Remove the text from a object
	void RemoveTextComponent(Text* text);
	// Remove the emitter from a object
	void RemoveEmitterComponent(Emitter* emitter);
	// Add emitter component to object
	void AddEmitterComponent(Object* object);
	// Add sprite component to object
	void AddSpriteComponent(Object* object);
	// Add text component to object
	void AddTextComponent(Object* object);

	/////////////////////////////////////////////////////////////
	//	Graphic system
	/////////////////////////////////////////////////////////////
	// Get the list of hud graphic components
	Graphics* GetHudGraphicList();
	// Get the list of normal graphic components
	Graphics* GetNormalGraphicList();

	/////////////////////////////////////////////////////////////
	//	Physics system
	/////////////////////////////////////////////////////////////
	// Add physics component to object
	void	AddPhysicsComponent(Object* object);
	// Remove the physics component from the object
	void	RemovePhysicsComponent(Physics* physics);
	// Get the list of physics components
	PhysicsVector* GetPhysicsList();
	// Get the pointer to world(physics)
	b2World* GetPhysicsWorld();

protected:

	// Clear info set from base state
	void ClearBaseState();

	/////////////////////////////////////////////////////////////
	//	Graphic system
	/////////////////////////////////////////////////////////////
	// Render sprites texts and emitters
	void Render(float dt);

	/////////////////////////////////////////////////////////////
	//	Physics system
	/////////////////////////////////////////////////////////////
	// Initialize box2d world 
	void	SetPhysicsWorld(const b2Vec2& gravity);
	// Update physics info
	void	UpdatePhysics(float dt);
	// Remove allocated world memory
	void	RemovePhysicsWorld();


	Camera		camera;				// Main Camera
	_TTF_Font*	mainFont = nullptr;	// Main Font
	Music		backgroundMusic;	// Main background music
	// State backgroud color
	SDL_Color m_backgroundColor{ 255, 255, 255, 255 };

private:

	// Remove the graphic from the rendering vector
	void RemoveGraphicComponent(Graphic* graphic);

	static unsigned m_ObjectIdSettor;	// Set object's unique id

	Objects	 m_objects;					// Object list
	unsigned m_id;						// State unique number

	Graphics m_hudGraphics;				// Hud sprites
	Graphics m_worldGraphics;			// World sprites

	b2World*		m_world = nullptr;	// Box2d physics world
	PhysicsVector	m_physicsList;		// physics list

public:

	/////////////////////////////////////////////////////////////
	//	These functions can be editted by students.
	//	Students are allowed to modify following codes
	//	if using more advanced Box2D Physics functionality.
	//	*** But the others should be kept as is ***
	/////////////////////////////////////////////////////////////

	b2World					*m_customWorld = nullptr;
	CustomPhysicsVector		m_customPhysicsList;
	// Get the pointer to world(physics)
	b2World* GetCustomPhysicsWorld();
	// Initialize box2d world 
	void SetCustomPhysicsWorld(const b2Vec2& gravity);
	// Update physics info
	void UpdateCustomPhysics(float dt);
	// Add physics component to object
	void AddCustomPhysicsComponent(CustomBaseObject* object);
	// Remove allocated world memory
	void RemoveCustomPhysicsWorld();
	// Clear all the custom physics components
	void ClearCustomPhysicsComponent();

	/////////////////////////////////////////////////////////////

private:

	State(const State&) = delete;
	State(State&&) = delete;
	State& operator=(const State&) = delete;
	State& operator=(State&&) = delete;

};