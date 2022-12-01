#include "Game.h"
#include "engine/StateManager.h"

Game::Game()
{
    m_stateManager = new StateManager;
}

Game::~Game()
{
    if (m_stateManager) {
        delete m_stateManager;
        m_stateManager = nullptr;
    }
}

/**
* \brief
* Initialize game states and window size
*
* \return
* True
*/
bool Game::Initialize()
{
    // Set window size
    State::m_width = SCREEN_WIDTH, State::m_height = SCREEN_HEIGHT;

    // Set state ids
    mainMenu.SetId(LV_MainMenu);
    pauseLevel.SetId(LV_Pause);
    TESTlevel.SetId(LV_TEST);
    level1.SetId(LV_LEVEL1);
    level2.SetId(LV_LEVEL2);
    level3.SetId(LV_LEVEL3);
    level4.SetId(LV_LEVEL4);
    level5.SetId(LV_LEVEL5);
    level6.SetId(LV_LEVEL6);
    level7.SetId(LV_LEVEL7);
    level8.SetId(LV_LEVEL8);
    
    tutorial.SetId(LV_TUTORIAL);
    howtoplay1.SetId(LV_HowToPlay1);
    howtoplay2.SetId(LV_HowToPlay2);
    clear.SetId(LV_CLEAR);
	splashscreen.SetId(LV_SplashScreen);
	credits.SetId(LV_Credits);
    // Register states
    RegisterState(&mainMenu);    
    RegisterState(&level1);
    RegisterState(&level2);
    RegisterState(&level3);
    RegisterState(&level4);
    RegisterState(&level5);
    RegisterState(&level6);
    RegisterState(&level7);
    RegisterState(&level8);

    RegisterState(&tutorial);
    RegisterState(&TESTlevel);
    RegisterState(&howtoplay1);
    RegisterState(&howtoplay2);
    RegisterState(&clear);
	RegisterState(&splashscreen);
	RegisterState(&credits);
    // Register pause state
    RegisterPauseState(&pauseLevel);

    // Set starting state
    //SetFirstState(&mainMenu);
	SetFirstState(&splashscreen);

    // Initlialize current state
    GetCurrentState()->Initialize();

    return true;
}

/**
* \brief
* Update state manager
*
* \param dt
* Delta time
*/
void Game::Update(float dt)
{
    StateManager::SetWindowSize(m_width, m_height);
    m_stateManager->Update(dt);
}

/**
* \brief
* Wrap all state stacks up
*/
void Game::Close()
{
    m_stateManager->Close();
}

/**
* \brief
* Set a state as a pause state
*
* \param state
* Address of state to set as the pause state
*/
void Game::RegisterPauseState(State* state)
{
    m_stateManager->RegisterPauseState(state);
}

/**
* \brief
* Stop updating current state and move to pause state
*/
void Game::Pause()
{
    m_stateManager->Pause();
}

/**
* \brief
* Close pause state and move back to last state
*/
void Game::Resume()
{
    m_stateManager->Resume();
}

/**
* \brief
* Restart current state
*/
void Game::Restart()
{
    m_stateManager->Restart();
}

/**
* \brief
* Add a state
*
* \param state
* Address of state to add
*/
void Game::RegisterState(State* state)
{
    m_stateManager->RegisterState(state);
}

/**
* \brief
* Set a state to starting point
*
* \param state
* Address of state to set as the first state
*/
void Game::SetFirstState(State* state)
{
    m_stateManager->SetFirstState(state);
}

/**
* \brief
* Return the address of the current state
*
* \return m_stack.top()
*/
State* Game::GetCurrentState()
{
    return m_stateManager->GetCurrentState();
}

/**
* \brief
* Set game state manager to shutdown
*/
void Game::Quit()
{
    m_stateManager->Quit();
}

/**
* \brief
* Change current state to other state
*
* \param stateId
* Id of state to change
*/
void Game::Change(unsigned stateId)
{
    m_stateManager->Change(stateId);
}


/**
* \brief
* Check either if the app gets ready to quit
*
* \return m_stateManager->IsQuit()
*/
bool Game::IsQuit()
{
    return m_stateManager->IsQuit();
}
