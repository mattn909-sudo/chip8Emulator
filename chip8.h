#include <string>

class chip8{
    public:
        void initialize();
        void loadGame(std::string);
        void emulateCycle();
    private:
        unsigned short opcode;
        unsigned char memory[4096];
        unsigned char V[16];
        unsigned short I;
        unsigned short pc;
        unsigned char gfx[64 * 32];
        unsigned char delay_timer;
        unsigned char sound_timer; 
}