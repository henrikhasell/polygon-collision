#ifndef POLYGON_H
#define POLYGON_H

#include <SDL2/SDL_opengl.h>

#include <math.h>

#include "vector.h"

/*********************************************************************/
/* Each ConvexPolygon is represented by a series of verticies.       */
/* Each Vertex contains positional data and texture coordinate data. */
/*********************************************************************/

typedef struct ConvexPolygon{
    /********************************/
    /* A pointer to a Vertex array. */
    /********************************/
    Vector *data;
    /***********************************/
    /* The length of the Vertex array. */
    /***********************************/
    int length;
}ConvexPolygon;

extern ConvexPolygon square;
extern ConvexPolygon triangle;
extern ConvexPolygon circle;
extern ConvexPolygon pentagon;

void DrawPolygon(ConvexPolygon *p, float x, float y);

#endif /* POLYGON_H */
