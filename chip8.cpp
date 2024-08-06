#include "chip8.h"

void chip8::initialize(){

}

void chip8::emulateCycle(){
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void chip8::loadGame(std::string game){

}

void chip8::setKeys(){

}