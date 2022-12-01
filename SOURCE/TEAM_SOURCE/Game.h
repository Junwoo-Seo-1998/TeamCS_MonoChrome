/******************************************************************************/
/*!
\file   Game.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Game will only handle the changes of the game states (Level switching)
ie. Main Menu, Levels, Pause, etc.
No game play logic should be added here.
*/
/******************************************************************************/

#pragma once

// Level headers
#include "MainMenu.h"
#include "PauseState.h"
#include "Level_Test.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Tutorial.h"
#include "HowToPlay1.h"
#include "HowToPlay2.h"
#include "SplashScreen.h"
#include "Clear_Level.h"
#include "Credits.h"
//This is the list of levels the game has. When adding a new level(state)
//add it to this list. They are tagged with LV_ to enable better autocomplete 
typedef enum
{
    LV_MainMenu = 0,
    //	LV_Level1,

    LV_Pause,
    //etc.
    LV_TEST,
    LV_LEVEL1,
    LV_LEVEL2,
    LV_LEVEL3,
    LV_LEVEL4,
    LV_LEVEL5,
    LV_LEVEL6,
    LV_LEVEL7,
    LV_LEVEL8,
    LV_TUTORIAL,
    LV_HowToPlay1,
    LV_HowToPlay2,
	LV_SplashScreen,
    LV_CLEAR,
    LV_NUM_LEVELS,
	LV_Credits
}Level_ID;

class StateManager;

class Game
{
    friend class Application;

    StateManager *m_stateManager = nullptr;

public:

    Game();
    ~Game();

    void	RegisterState(State* state);
    void	SetFirstState(State* state);
    State*	GetCurrentState();

    void	Quit();
    void	Change(unsigned stateId);

    bool	Initialize();
    void	Update(float dt);
    void	Close();

    void	RegisterPauseState(State *state);
    void	Pause();
    void	Resume();
    void	Restart();
    bool	IsQuit();

private:

    // All the level(state) declarations are here
    MainMenu	mainMenu;
    PauseState	pauseLevel;
    Level_Test	TESTlevel;
    Level1          level1;
    Level2          level2;
    Level3          level3;
    Level4          level4;
    Level5          level5;
    Level6          level6;
    Level7          level7;
    Level8          level8;
    Tutorial		tutorial;
    HowToPlay1		howtoplay1;
    HowToPlay2		howtoplay2;
    Clear_Level             clear;
	SplashScreen	splashscreen;
	Credits			credits;
public:

    static constexpr int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
    int	m_width = 0, m_height = 0;

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

};