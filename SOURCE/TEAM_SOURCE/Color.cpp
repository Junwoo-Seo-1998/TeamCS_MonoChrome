/******************************************************************************/
/*
File name: Color.cpp
Project name: Monochrome
Author(s): JunWoo Seo
All content © 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Color.h"

bool Color::AreTheySame(const SDL_Color & left, const SDL_Color & right)
{
    if (left.r!=right.r)
        return false;
    if (left.g != right.g)
        return false;
    if (left.b != right.b)
        return false;
    if (left.a != right.a)
        return false;
    return true;
}
