/******************************************************************************/
/*!
\file   MainMenu.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Conaining examples how to use engine
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class Clear_Level : public State
{
    friend class Game;

protected:

    Clear_Level() : State() {};
    ~Clear_Level() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;

private:

    Object titleText;
    Object instructionsText;

    void CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id);
};

