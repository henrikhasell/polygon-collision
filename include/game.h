#ifndef GAME_H
#define GAME_H

/***************************************/
/* Window managment, rendering context */
/* and input are powered by SDL        */
/* (Simple Direct media Layer).        */
/***************************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

/********************************************************/
/* This module presents an abstraction for Objects.     */
/* It is reuired to represent and render scene objects. */
/********************************************************/
#include "object.h"
/************************************************************/
/* This module is used to render information to the screen. */
/************************************************************/
#include "glyph.h"

void Game_Initialise();

void Game_Cleanup();

void Game_FrameLogic();

void Game_FrameRender();

#endif /* GAME_H */
