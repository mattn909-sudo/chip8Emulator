#include <iostream>
#include "chip8.h"
#include "SDL2/SDL.h"
using namespace std;

void setupGraphics(){

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