#include <iostream>
#include "chip8.h"
#include "SDL2/SDL.h"
using namespace std;

typedef struct{
    SDL_Window *window;
}sdl_t;

bool setupGraphics(sdl_t *sdl){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Could not initialize SDL subsystems");
        SDL_Log(SDL_GetError());
        return false;
    }
    sdl ->window = SDL_CreateWindow("CHIP8 Emulator by Matthew Nguyen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,600,0);
    return true;
}

void setupInput(){

}

chip8 myChip8;

int main(int argc, char **argv){
    
    setupGraphics();
    setupInput();

    myChip8.initialize();
    myChip8.loadGame();

    for(;;){
        myChip8.emulateCycle();

        if(myChip8.drawFlag){
            drawGraphics()
        }

        myChip8.setKeys();
    }

    return 0;
}