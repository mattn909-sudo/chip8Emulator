#include "chip8.h"

void chip8::initialize(){
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    for(int i = 0; i < 4096;i++){
        memory[i] = 0;
    }

    for(int i = 0; i < 16;i++){
        stack[i] = 0;
        V[i] = 0;
    }

    for(int i = 0; i < (64*32); i++){
        gfx[i] = 0;
    }

    for(int i = 0; i < 80; i++){
        memory[i] = chip8_fontset[i];
    }
    


}

void chip8::emulateCycle(){
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void chip8::loadGame(std::string game){

}

void chip8::setKeys(){

}