#ifndef OBJECT_H
#define OBJECT_H

/***************************************/
/* Window managment, rendering context */
/* and input are powered by SDL        */
/* (Simple Direct media Layer).        */
/***************************************/
#include <SDL2/SDL_opengl.h>

/**********************************************/
/* Used for calculating the vector magnitude. */
/**********************************************/
#include <math.h>
/***************************************************/
/* All created Objects are stored in a LinkedList. */
/***************************************************/
#include "list.h"
/**********************************************/
/* Object texture is represented by an Image. */
/**********************************************/
#include "image.h"
/**********************************************/
/* Object shapes are represented by Polygons. */
/**********************************************/
#include "polygon.h"
/************************************************/
/* Object positions are represented as Vectors. */
/************************************************/
#include "vector.h"
/******************************************************************/
/* Objects have their address printed to the screen using Glyphs. */
/******************************************************************/
#include "glyph.h"
/*************************************/
/* This struct represents an Object. */
/*************************************/
typedef struct Object{
    /* The ConvexPolygon* points to a Polygon which represents the shape of the Object.  */
    /* Multiple Objects should point to the same Polygon to avoid data duplication.      */
    ConvexPolygon *shape;
    /* This vector represents the Objects position. */
    Vector position;
}Object;
/***************************************************************************************/
/* This function initialises Object related resources.                                 */
/* It should be called before any other Object related function.                       */
/* It initialises the Object LinkedList all objects are listed in, among other things. */
/***************************************************************************************/
void InitialiseObjects();
/********************************************************************/
/* This function frees Object related resourses, such as the Object */
/* list and all dynamically allocated Objects.                      */
/********************************************************************/
void CleanupObjects();
/*******************************************************************************************/
/* This function returns a newly allocated Object which has been added to the Object list. */
/*******************************************************************************************/
Object *CreateObject();
/**********************************************************************************************************/
/* This function frees an object. It should only be called on Objects within the Object list.             */
/* It is also not strictly necessary to avoid memory leaks, as CleanupObjects() also frees these Objects. */
/**********************************************************************************************************/
void DestroyObject(Object *object);
/*****************************************************************/
/* This function draws all of the Objects within the LinkedList. */
/*****************************************************************/
void DrawObjects();
/**************************************************************************/
/* This function returns 1 if two Objects intersect and 0 is they do not. */
/**************************************************************************/
int ObjectsColliding(Object *a, Object *b);

#endif /* OBJECT_H */
