#include <stdint.h>
#include <SDL2/SDL.h>

class Chip8 {
    private:
        uint8_t V[16];              // Registers

        uint16_t I;                 // I register
        
        uint8_t sound_timer,        // Sound register
                delay_timer;        // Delay register

        uint8_t sp;                 // Stack pointer
        uint16_t stack[16];         // Stack


        uint16_t opcode;

        unsigned short nnn,
                       n,
                       x,
                       y,
                       kk;

        uint16_t currentKey;
        
        bool keyboard[16];

        uint16_t pc;                // Program counter
        uint8_t memory[4096];       // Main memory
        uint8_t screen[64][32];    // Screen memory

    public:
        SDL_Event event;

        Chip8();
        ~Chip8();

        void printMem();
        void startUp();
        void drawScreen(SDL_Renderer *r);
        void emu_cycle(SDL_Renderer *r);
        
        void drawSprite(SDL_Renderer *r);

        bool exit = false;

        void captureKeys();
        bool loadFile(char *file_path);
        
        void drawPixel(SDL_Renderer *r, unsigned short x, unsigned short y);

        uint8_t fontset[80] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, //0
            0x20, 0x60, 0x20, 0x20, 0x70, //1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
            0x90, 0x90, 0xF0, 0x10, 0x10, //4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
            0xF0, 0x10, 0x20, 0x40, 0x40, //7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
            0xF0, 0x90, 0xF0, 0x90, 0x90, //A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
            0xF0, 0x80, 0x80, 0x80, 0xF0, //C
            0xE0, 0x90, 0x90, 0x90, 0xE0, //D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
            0xF0, 0x80, 0xF0, 0x80, 0x80  //F        
        };
};