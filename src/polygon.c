#include "polygon.h"

/* This represents the multiplier applied to the normalised shape coordinates listed below. */
#define SCALE 100.0f

static Vector square_data[] = {
    {-0.5f*SCALE, -0.5f*SCALE},
    { 0.5f*SCALE, -0.5f*SCALE},
    { 0.5f*SCALE,  0.5f*SCALE},
    {-0.5f*SCALE,  0.5f*SCALE}
};

static Vector triangle_data[] = {
    { 0.000000f*SCALE, -0.500000f*SCALE},
    { 0.433013f*SCALE,  0.250000f*SCALE},
    {-0.433013f*SCALE,  0.250000f*SCALE}
};

static Vector circle_data[] = {
    { 0.000000f*SCALE,-0.500000f*SCALE},
    { 0.154509f*SCALE,-0.475528f*SCALE},
    { 0.293893f*SCALE,-0.404509f*SCALE},
    { 0.404509f*SCALE,-0.293893f*SCALE},
    { 0.475528f*SCALE,-0.154508f*SCALE},
    { 0.500000f*SCALE, 0.000000f*SCALE},
    { 0.475528f*SCALE, 0.154509f*SCALE},
    { 0.404509f*SCALE, 0.293893f*SCALE},
    { 0.293893f*SCALE, 0.404509f*SCALE},
    { 0.154508f*SCALE, 0.475528f*SCALE},
    {-0.000000f*SCALE, 0.500000f*SCALE},
    {-0.154509f*SCALE, 0.475528f*SCALE},
    {-0.293893f*SCALE, 0.404508f*SCALE},
    {-0.404509f*SCALE, 0.293892f*SCALE},
    {-0.475528f*SCALE, 0.154508f*SCALE},
    {-0.500000f*SCALE,-0.000000f*SCALE},
    {-0.475528f*SCALE,-0.154509f*SCALE},
    {-0.404508f*SCALE,-0.293893f*SCALE},
    {-0.293892f*SCALE,-0.404509f*SCALE},
    {-0.154508f*SCALE,-0.475528f*SCALE}
};

static Vector pentagon_data[] = {
    { 0.000000f*SCALE, -0.500000f*SCALE},
    { 0.475528f*SCALE, -0.154508f*SCALE},
    { 0.293893f*SCALE,  0.404509f*SCALE},
    {-0.293893f*SCALE,  0.404508f*SCALE},
    {-0.475528f*SCALE, -0.154509f*SCALE}
};

ConvexPolygon square = {
    (Vector*)&square_data,
    4
};

ConvexPolygon triangle = {
    (Vector*)&triangle_data,
    3
};

ConvexPolygon circle = {
    (Vector*)&circle_data,
    20
};

ConvexPolygon pentagon = {
    (Vector*)&pentagon_data,
    5
};

void DrawPolygon(ConvexPolygon *p, float x, float y){

    int count;
    /*******************************/
    /* Draw the fill of the shape. */
    /*******************************/
    glColor4f(1.0f, 0.0f, 0.0f, 0.25f);
    glBegin(GL_TRIANGLE_FAN);
    for(count = 0; count < p->length; count++){
        Vector *v = p->data + count;
        glVertex2f(x + v->x, y + v->y);
    }
    glEnd();
    /**********************************/
    /* Draw the outline of the shape. */
    /**********************************/
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for(count = 0; count < p->length; count++){
        Vector *v = p->data + count;
        glVertex2f(x + v->x, y + v->y);
    }
    glEnd();

    /***************************/
    /* Draw the shape normals. */
    /***************************/
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    for(count = 0; count < p->length; count++){
        /**********************************************************************/
        /* This pair of vectors represents the coordinates of a polygon side. */
        /**********************************************************************/
        Vector *v_1;
        Vector *v_2;
        /****************************************************/
        /* This vector represents the midpoint of the side. */
        /****************************************************/
        Vector midpoint;
        /**************************************************/
        /* This vector represents the normal of the side. */
        /**************************************************/
        Vector normal;
        /*******************************************/
        /* This float stores the vector magnitude. */
        /*******************************************/
        float magnitude;
        /***************/
        /* Define v_1. */
        /***************/
        v_1 = (p->data + count);
        /********************************************************/
        /* Make sure that v_2 does not point to invalid memory. */
        /********************************************************/
        if(count < p->length - 1){
            v_2 = (p->data + count + 1);
        }
        else{
            v_2 = p->data;
        }
        /************************************************************/
        /* Calculate the midpoint of the side based on v_1 and v_2. */
        /************************************************************/
        midpoint.x = x + v_1->x + (v_2->x - v_1->x)/2.0f;
        midpoint.y = y + v_1->y + (v_2->y - v_1->y)/2.0f;
        /******************************/
        /* Calculate the side normal. */
        /******************************/
        normal.x = -(v_1->y - v_2->y);
        normal.y =  (v_1->x - v_2->x);
        /***********************************/
        /* Calculate the vector magnitude. */
        /***********************************/
        magnitude = sqrtf(normal.x*normal.x + normal.y*normal.y);
        /*************************/
        /* Normalise the vector. */
        /*************************/
        normal.x /= magnitude;
        normal.y /= magnitude;
        /********************/
        /* Draw the vector. */
        /********************/
        glVertex2f(midpoint.x, midpoint.y);
        glVertex2f(midpoint.x + 10.0f*normal.x, midpoint.y + 10.0f*normal.y);
    }
    glEnd();
}
