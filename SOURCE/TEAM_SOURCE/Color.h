/******************************************************************************/
/*
File name: Color.h
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include <SDL2/SDL.h>

class Color
{
public:
    Color() = default;
    bool AreTheySame(const SDL_Color& left, const SDL_Color&right);
    const SDL_Color RED = { 255,0,0,255 };
    const SDL_Color GREEN = { 0,255,0,255 };
    const SDL_Color BLUE = { 0,0,255,255 };
    const SDL_Color WHITE = { 255,255,255,255 };
    const SDL_Color BLACK = { 0,0,0,255 };
    const SDL_Color INVISBLE = { 1, 1, 1, 0 };
    const SDL_Color PLAYER_BACKGROUND = { 8, 134, 150, 255 };
    const SDL_Color PLATFORM_BACKGROUND = { 150, 134, 8, 255 };
};
