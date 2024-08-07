#include "chip8.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

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
    pc += 2;
    switch(opcode & 0xF000){
        case 0x0000:
            switch(opcode & 0x000F){
                case 0x0000:
                    //clear screen
                    for(int i = 0; i < (64*32); i++){
                        gfx[i] = 0;
                    }
                    break;
                case 0x00E:
                    //return
                    sp += 1;
                    pc = stack[sp];
                    break;
            }
            break;
        case 0x1000:
            //1nnn
            //goto address NNN
            pc = opcode & 0x0FFF;
            break;
        case 0x2000:
            //2nnn
            //calls sub routine at NNN
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
            break;
        case 0x3000:
            //3xnn
            //if(vx == nn)
            break;
        case 0x4000:
            //4xnn if(vx != nn)
            break;
        case 0x5000:
            //5xy0 if(vx == vy)
            break;
        case 0x6000:
            //6xnn vx = nn
            V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            break;
        case 0x7000:
            //7xnn vx += nn
            V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            break;
        case 0x8000:
            switch (opcode & 0x000F){
                case 0x0000:
                    //8xy0 vx = vy
                    break;
                case 0x0001:
                    //8xy1 vx |= vy
                    break;
                case 0x0002:
                    //8xy2 vx &= vy
                    break;
                case 0x0003:
                    //8xy3 vx ^= vy
                    break;
                case 0x0004:
                    //8xy4 vx += vy
                    if(V[(opcode & 0x00F0)>> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])){
                        V[0xF] = 1;
                    }
                    else{
                        V[0xF] = 0;
                        V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0)>> 4];
                    }
                    break;
                case 0x0005:
                    //8xy5 vx -= vy
                    if(V[(opcode & 0x00F0)>> 4] >= (V[(opcode & 0x0F00) >> 8])){
                        V[0xF] = 0;
                    }
                    else{
                        V[0xF] = 1;
                        V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0)>> 4];
                        pc += 2;
                    }
                    break;
                case 0x0006:
                    //8xy6 vx >>= vy
                    break;
                case 0x0007:
                    //8xy7 vx = vy - vx
                    break;
                case 0x000E:
                    //8xyE vx <<= 1
                    break;
            }
            break;
        case 0x9000:
            //9xy0 if vx != vy
            break;
        case 0xA000:
            I = opcode & 0x0FFF;
            break;
        case 0xB000:
            pc = V[0] + (opcode & 0x0FFF);
            break;
        case 0xC000:
            //cxnn vx = rand() & NN
            break;
        case 0xD000: {
            //dxyn draw(vx,vy,n)
            const char x = ((opcode & 0x0F00) >> 8) & 63;
            const char y = ((opcode & 0x00F0) >> 4) & 31;
            const char height = opcode & 0x000F;
            unsigned short pixel;
            V[0xF] = 0;

            for(int yLine = 0; yLine < height; yLine++){
                pixel = memory[I + yLine];
                for(int xLine = 0;xLine < 8; xLine++){
                    if(gfx[(x + xLine + ((y + yLine) * 64))] == 1) V[0xF] = 1; 
                                                                                                   
                    gfx[x + xLine + ((y + yLine) * 64)] ^= 1;
                }
            }

            drawFlag = true;
            break;
        }
            

        case 0xE000:
            switch (opcode & 0x000F) {
                case 0x000E:
                    std::cout << "Handle case 0x009E" << std::endl;
                    break;
                case 0x0001:
                    std::cout << "Handle case 0x00A1" << std::endl;
                    break;
                default:
                    std::cout << "Unhandled case in inner switch" << std::endl;
                    break;
            }
            break;

        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    // Set Vx to delay timer value
                    break;
                case 0x000A:
                    // Wait for key press, store key in Vx
                    break;
                case 0x0015:
                    // Set delay timer to Vx
                    break;
                case 0x0018:
                    // Set sound timer to Vx
                    break;
                case 0x001E:
                    // Add Vx to I
                    break;
                case 0x0029:
                    // Set I to location of sprite for digit Vx
                    break;
                case 0x0033:
                    // Store BCD representation of Vx in memory locations I, I+1, I+2
                    break;
                case 0x0055:
                    // Store registers V0 to Vx in memory starting at I
                    break;
                case 0x0065:
                    // Fill registers V0 to Vx with values from memory starting at I
                    break;
                default:
                    std::cout << "Unhandled case in inner switch" << std::endl;
                    break;
            }
            break;

            default:
                std::cout << "Unhandled case in inner switch" << std::endl;
            break;
    }
}

void chip8::loadGame(char const* fileName){
    std::ifstream gameRom(fileName, std::ios::binary | std::ios::ate);

    if(gameRom.is_open()){
        std::streampos size = gameRom.tellg();
        char* buffer = new char[size];

        gameRom.seekg(0, std::ios::beg);
        gameRom.read(buffer,size);
        gameRom.close();
        for(int i = 0; i < size; i++){
            memory[0x200 + i] = buffer[i];
        }

        delete[] buffer;
    }
}

void chip8::setKeys(){

}