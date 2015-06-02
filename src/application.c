#include "application.h"

/****************************************************/
/* Static variables associated with an SDL context. */
/****************************************************/
static SDL_Window *app_window;    /* A handle representing the window.         */
static SDL_GLContext app_context; /* A handle representing the OpenGL context. */

void Application_Startup(){

    /* Attempt to initialise SDL. */
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        /* Handle initialisation error. */
        printf("Failed to initialise SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Attempt to create an SDL window. */
    app_window = SDL_CreateWindow(PROJECT_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if(app_window == NULL){
        /* Handle window creation error. */
        printf("Failed to create an SDL window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Set SDL OpenGL context flags. */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    /* Attempt to create an OpenGL context. */
    app_context = SDL_GL_CreateContext(app_window);
    if(app_context == NULL){
        /* Handle context creation error. */
        printf("Failed to create an OpenGL context: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /****************************************************************/
    /* At this point SDL initialisation has completed successfully. */
    /* OpenGL will now be initialised.                              */
    /****************************************************************/

    /* Enable texture rendering. */
    glEnable(GL_TEXTURE_2D);

    /* Enable blending and set blending mode. */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Change OpenGL's point size. */
    glPointSize(5.0f);
    
    /* Set the clear colour. */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* Set the projection matrix. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    /* Set the modelview matrix. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /**************************************************/
    /* OpenGL initialisation is now done. Application */
    /* specific modules will now be initialised.      */
    /**************************************************/
    
    /**************************************************/
    /* The application module requires text rendering */
    /* to draw the watermark to the screen.           */
    /**************************************************/
    InitialiseGlyph();
    /*****************************************************/
    /* Game related resources (used in the application's */
    /* main loop) are initialised here.                  */
    /*****************************************************/
    Game_Initialise();
}

void Application_Cleanup(){
    Game_Cleanup();

    CleanupGlyph();

    /* Destroy the application's OpenGL context. */
    SDL_GL_DeleteContext(app_context);

    /* Destroy the application's SDL window. */
    SDL_DestroyWindow(app_window);

    /* Free resources used by SDL. */
    SDL_Quit();
}

void Application_MainLoop(){
    /* Non zero value signifies an OpenGL error. */
    int gl_error = 0;
    
    /* app_finished signifies wether */
    /* the program should continue.  */
    int app_finished = 0;

    /* This while loop represents the "main" loop.    */
    /* It will not return until the app has finished. */
    while(!app_finished){

        /* This event union is used to */
        /* store polled event data.    */
        SDL_Event app_event;

        do{
            /* Check for OpenGL errors. */
            gl_error = glGetError();
            if(gl_error){
                /* If there is an OpenGL error, print it out. */
                printf("OpenGL error: %i\n", gl_error);
            }
        }
        /* Keep checking for errors until none are reported. */
        while(gl_error);

        /* This while loop polls events while */
        /* there is an event to handle.       */
        while(SDL_PollEvent(&app_event)){

            switch(app_event.type){

            case SDL_QUIT:
                /* The user wants to quit,   */
                /* mark the app as finished. */
                app_finished = 1;
                break;

            case SDL_KEYDOWN:
                /* The user has pressed a key, */
                /* do something!               */
                break;

            case SDL_KEYUP:
                /* The user has released a key, */
                /* do something!                */
                break;

            default:
                /* We have no idea what just happened, */
                /* do something?                       */
                break;
            }

        }

        Game_FrameLogic();

        /* Clear the frame buffer. */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render the game. */
        Game_FrameRender();

        /* Draw the watermark to the screen. */
        glColor3f(1.0f, 1.0f, 1.0f);
        RenderString("You are running: " PROJECT_TITLE, 10.0f, 10.0f, GLYPH_WIDTH*2, GLYPH_HEIGHT*2);

        /* Swap the frame buffer. */
        SDL_GL_SwapWindow(app_window);

        SDL_Delay(1000/60);
    }
}
