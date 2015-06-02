#include "application.h"

int main(int argc, char *argv[]){

    Application_Startup();

    Application_MainLoop();

    Application_Cleanup();

    return EXIT_SUCCESS;

}