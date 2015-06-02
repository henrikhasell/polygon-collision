/***********************************************************************************************************/
/* This module is intended to hide the details of SDL's window managment from the rest of the application. */
/* This is done so that it can be easily replaced by another window managment system.                      */
/***********************************************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

/*********************************/
/* Preprocessor defines go here. */
/*********************************/
#define PROJECT_TITLE "Collision Test"

/***************************************/
/* Window managment, rendering context */
/* and input are powered by SDL        */
/* (Simple Direct media Layer).        */
/***************************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdlib.h> /* Used for memory allocation. */
#include <stdio.h>  /* Used for console output.    */

/*****************************************************************/
/* This module gives the application the ability to render text. */
/*****************************************************************/
#include "glyph.h"

/***************************/
/* Game related resources. */
/***************************/
#include "game.h"

/*******************************************************************************************/
/* These functions handle the running of the application (startup, cleanup and managment). */
/*******************************************************************************************/
void Application_Startup();
void Application_Cleanup();
void Application_MainLoop();

#endif /* APPLICATION_H */
