#include <string>

class chip8{
    public:
        void initialize();
        void loadGame(std::string);
        void emulateCycle();
        void setKeys();
        bool drawFlag = false;
    private:
        unsigned short opcode;
        unsigned char memory[4096];
        unsigned char V[16];
        unsigned short I;
        unsigned short pc = 0x200;
        unsigned short sp;
        unsigned short stack[16];
        unsigned char gfx[64 * 32];
        unsigned char key[16];
        unsigned char delay_timer;
        unsigned char sound_timer; 
};