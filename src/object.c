#include "object.h"

/****************************************************************************************/
/* This linked list stores all the Objects in the game. Objects are automatically added */
/* and removed from the list with the functions CreateObject and DestroyObject().       */
/* Memory allocation for the list and the Objects within it is handled with             */
/* InitialiseObject() and CleanupObject().                                              */
/****************************************************************************************/
static LinkedList *object_list = NULL;

/**************************************************************************************/
/* This unsigned int represents an OpenGL texture handle. Memory allocation regarding */
/* this handle is managed with InitialiseObject() and CleanupObject().                */
/**************************************************************************************/
static GLuint object_texture = 0;

/*****************************************************/
/* Calling this function creates the Object list and */
/* uploads the Object texture to the graphics card.  */
/* Needless to say, no other functions from this     */
/* module should be called before this one.          */
/*****************************************************/
void InitialiseObjects(){
    /***********************************************/
    /* This PixelRGBA array represents the default */
    /* texture to be applied to each Object.       */
    /***********************************************/
    const PixelRGBA IMAGE_DATA[] = {
        {255, 255, 255, 255}, {255, 255, 255, 255},
        {255, 255, 255, 255}, {255, 255, 255, 255}
    };
    /**************************************************************/
    /* STEP 1: Check that *object_list is not a valid LinkedList. */
    /**************************************************************/
    if(!object_list){
        /*****************************************/
        /* Allocate memory for a new LinkedList. */
        /*****************************************/
        object_list = createLinkedList();
    }
    /*********************************************************/
    /* STEP 2: Check if object_texture has already been set. */
    /*********************************************************/
    if(object_texture){
        /****************************************************/
        /* The default texture has already been assigned,   */
        /* there is no need to continue initialisation.     */
        /****************************************************/
        return;
    }
    /******************************************/
    /* Generate a texture handle for the GPU. */
    /******************************************/
    glGenTextures(1, &object_texture);
    /*************************************/
    /* Upload the pixel data to the GPU. */
    /*************************************/
    glBindTexture   (GL_TEXTURE_2D, object_texture);
    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, IMAGE_DATA);
    /**************************/
    /* Set image parameters.  */
    /**************************/
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);                                 
}
/********************************************************************/
/* This function frees all memory allocated by the Object module.   */
/* Needless to say, after calling this function, no other functions */
/* from the Object module should be called.                         */
/********************************************************************/
void CleanupObjects(){
    /******************************************/
    /* If object_list points to valid memory. */
    /******************************************/
    if(object_list){
        /******************************/
        /* Free every member of list. */
        /******************************/
        Link *link;
        for(link = object_list->head; link != NULL; link = link->next){
            /* Bang! */
            free(link->data);
        }
        /******************************/
        /* Free the list from memory. */
        /******************************/
        destroyLinkedList(object_list);
    }
    /****************************************/
    /* If object_texture is a valid handle. */
    /****************************************/
    if(object_texture){
        /*********************/
        /* Free the texture. */
        /*********************/
        glDeleteTextures(1, &object_texture);
    }
    /******************************/
    /* Prevent dangling pointers. */
    /******************************/
    object_list = NULL;
    object_texture = 0;
}

Object *CreateObject(){
    /************************************/
    /* Allocate space for a new Object. */
    /************************************/
    Object *object = (Object*)malloc(sizeof(Object));
    if(object == NULL){
        /***********************************/
        /* Handle memory allocation error. */
        /***********************************/
        printf("Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }
    /**************************************/
    /* Add the Object to the Object list. */
    /**************************************/
    pushData(object_list, object);
    /**************************************/
    /* Return the newly allocated Object. */
    /**************************************/
    return object;
}

void DestroyObject(Object *object){
    popData(object_list, object);
    free(object);
}

void DrawObjects(){
    Link *link;
    /* This loop cycles through every Object in the Object list. */
    for(link = object_list->head; link != NULL; link = link->next){

        /* This pointer is the current Object we will be drawing. */
        Object *object = (Object*)link->data;

        /* Draw the Object as a ConvexPolygon. */
        glBindTexture(GL_TEXTURE_2D, 0);
        DrawPolygon(object->shape, object->position.x, object->position.y);
    }
    
}
/**************************************************************************************************************/
/* This function is used to enable the ObjectsColliding() function to project Objects onto an arbitrary axis. */
/**************************************************************************************************************/
static void ProjectObject(Object *object, Vector *axis, float *min, float *max){
    int count;
    /* Set the minimum and mximum values as the Object centre. */
    *min = (axis->x*object->position.x)+(axis->y*object->position.y);
    *max = (axis->x*object->position.x)+(axis->y*object->position.y);
    /**************************************************************/
    /* To project an Object onto an axis we need to cycle through */
    /* every vertex the Object's shape comprises of.              */
    /**************************************************************/
    for(count = 0; count < object->shape->length; count++){

        /* Pointer to the current polygon vertex. */
        Vector *polygon_vertex = (Vector*)(object->shape->data) + count;

        /* The polygon vertex is translated by the object's */
        /* position and stored in this Vector struct.       */
        Vector shape_vertex;

        /* This float stores the projected value of the shape vertex. */
        /* That is the dot product of the axis and the vertex.        */
        float projection;

        shape_vertex.x = object->position.x + polygon_vertex->x;
        shape_vertex.y = object->position.y + polygon_vertex->y;

        /*******************************************/
        /* Project the shape vertex onto the axis. */
        /*******************************************/
        projection = (shape_vertex.x * axis->x) + (shape_vertex.y * axis->y);

        /************************************************************/
        /* Check if the projection is an appropriate min/max value. */
        /************************************************************/
        if(projection < *min){
            *min = projection;
        }
        else if(projection > *max){
            *max = projection;
        }
    }
}

static void ResolveCollision(Object *a, Object *b, Vector *vector, float amount){
    /* The relative position of the two Objects. Used to determine if the vector is seperating. */
    Vector relative_position;
    /* Dot product of v and relative_position. Used to determine if the vector is seperating. */
    float dot_product;

    relative_position.x = a->position.x - b->position.x;
    relative_position.y = a->position.y - b->position.y;

    dot_product = (relative_position.x*vector->x)+(relative_position.y*vector->y);

    if(dot_product < 0.0f){
        vector->x = -vector->x;
        vector->y = -vector->y;
    }
    a->position.x += amount * vector->x * 0.5f;
    a->position.y += amount * vector->y * 0.5f;
    b->position.x -= amount * vector->x * 0.5f;
    b->position.y -= amount * vector->y * 0.5f;
}

int ObjectsColliding(Object *a, Object *b){
    int count;

    /* The start point of a polygon side. */
    Vector *v_1;
    /* The end point of a polygon side. */
    Vector *v_2;
    /* The polygon side normal. */
    Vector normal;

    /* The magnitude of the polygon side. */
    float magnitude;
    /* The min/max projection values for polygon A. */
    float projection_a[2];
    /* The min/max projection values for polygon B. */
    float projection_b[2];

    /* The directional vector of intersection. */
    Vector intersection_vector;
    /* The depth of the intersection, if any. */
    float intersection_depth = 9001;

    for(count = 0; count < a->shape->length; count++){

        /* Define v_1. */
        v_1 = (a->shape->data + count);

        /* Define v_2. Make sure it points to valid memory. */
        v_2 = count == a->shape->length - 1
        ? a->shape->data
        : a->shape->data + count + 1;

        /* Calculate the vector normal. */
        normal.x = -(v_1->y - v_2->y);
        normal.y =  (v_1->x - v_2->x);

        /* Calculate the vector magnitude. */
        magnitude = sqrtf(normal.x*normal.x + normal.y*normal.y);

        /* Normalise the vector normal. */
        normal.x /= magnitude;
        normal.y /= magnitude;

        /* Project both objects onto the side normal. */
        ProjectObject(a, &normal, &projection_a[0], &projection_a[1]);
        ProjectObject(b, &normal, &projection_b[0], &projection_b[1]);

        /* Check for an axis of seperation. */
        if(projection_a[1] <= projection_b[0] || projection_b[1] <= projection_a[0]){
            /* Axis of seperation found. */
            return 0;
        }

        if(projection_b[1] < projection_a[1]){
            float d = (projection_a[1]-projection_a[0]) - (projection_a[1] - projection_b[1]);
            if(d < intersection_depth){
                intersection_depth = d;
                memcpy(&intersection_vector, &normal, sizeof(Vector));
            }
        }
        else{
            float d = (projection_b[1]-projection_b[0]) - (projection_b[1] - projection_a[1]);
            if(d < intersection_depth){
                intersection_depth = d;
                memcpy(&intersection_vector, &normal, sizeof(Vector));
            }
        }
    }

    for(count = 0; count < b->shape->length; count++){

        /* Define v_1. */
        v_1 = (b->shape->data + count);

        /* Define v_2. Make sure it points to valid memory. */
        v_2 = count == b->shape->length - 1
        ? b->shape->data
        : b->shape->data + count + 1;

        /* Calculate the vector normal. */
        normal.x = -(v_1->y - v_2->y);
        normal.y =  (v_1->x - v_2->x);

        /* Calculate the vector magnitude. */
        magnitude = sqrtf(normal.x*normal.x + normal.y*normal.y);

        /* Normalise the vector normal. */
        normal.x /= magnitude;
        normal.y /= magnitude;

        /* Project both objects onto the side normal. */
        ProjectObject(a, &normal, &projection_a[0], &projection_a[1]);
        ProjectObject(b, &normal, &projection_b[0], &projection_b[1]);

        /* Check for an axis of seperation. */
        if(projection_a[1] <= projection_b[0] || projection_b[1] <= projection_a[0]){
            /* Axis of seperation found. */
            return 0;
        }

        if(projection_b[1] < projection_a[1]){
            float d = (projection_a[1]-projection_a[0]) - (projection_a[1] - projection_b[1]);
            if(d < intersection_depth){
                intersection_depth = d;
                memcpy(&intersection_vector, &normal, sizeof(Vector));
            }
        }
        else{
            float d = (projection_b[1]-projection_b[0]) - (projection_b[1] - projection_a[1]);
            if(d < intersection_depth){
                intersection_depth = d;
                memcpy(&intersection_vector, &normal, sizeof(Vector));
            }
        }
    }
    
    ResolveCollision(a, b, &intersection_vector, intersection_depth);

    /* No axis of seperation found, the objects must collide. */
    return 1;
}