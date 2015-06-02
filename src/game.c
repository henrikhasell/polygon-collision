#include "game.h"

static Object *object_1 = NULL;
static Object *object_2 = NULL;

void Game_Initialise(){
    InitialiseObjects();
    /*************************************************/
    /* Allocate memory for all Objects in the scene. */
    /*************************************************/
    object_1 = CreateObject();
    object_2 = CreateObject();
    /**************************************/
    /* Position the objects in the scene. */
    /**************************************/
    object_1->shape = &triangle;
    object_1->position.x = 200.0f;
    object_1->position.y = 300.0f;

    object_2->shape = &pentagon;
    object_2->position.x = 600.0f;
    object_2->position.y = 300.0f;
}

void Game_Cleanup(){
    /*********************************************/
    /* Free memory for all Objects in the scene. */
    /*********************************************/
    DestroyObject(object_1);
    DestroyObject(object_2);
    CleanupObjects();
}

void Game_FrameLogic(){

    /* Get keyboard state. */
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    const float speed = 1.0f;

    if(key_state[SDL_GetScancodeFromKey('w')]){
        object_1->position.y -= speed;
    }
    if(key_state[SDL_GetScancodeFromKey('s')]){
        object_1->position.y += speed;
    }
    if(key_state[SDL_GetScancodeFromKey('a')]){
        object_1->position.x -= speed;
    }
    if(key_state[SDL_GetScancodeFromKey('d')]){
        object_1->position.x += speed;
    }
}

void Game_FrameRender(){
    /***************************************/
    /* Check if the Objects are colliding. */
    /***************************************/
    if(ObjectsColliding(object_1, object_2)){
        glColor3f(0.0f, 1.0f, 0.0f);
        RenderString("We have a collision! \1", 10.0f, 20.0f + GLYPH_WIDTH*2, GLYPH_WIDTH, GLYPH_HEIGHT);
    }
    else{
        glColor3f(1.0f, 0.0f, 0.0f);
        RenderString("Axis of seperation detected.", 10.0f, 20.0f + GLYPH_WIDTH*2, GLYPH_WIDTH, GLYPH_HEIGHT);
    }
    /***********************************/
    /* Draw every Object in the scene. */
    /***********************************/
    DrawObjects();
}
