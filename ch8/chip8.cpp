#include <random>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "chip8.h"

#define HEIGHT 320
#define WIDTH 640

Chip8::Chip8() {}
Chip8::~Chip8() {}

uint8_t reverseBits(uint8_t num);

void Chip8::startUp() {    
    for(int i = 0; i < 4096; i++)       { memory[i] = 0; }
    for(int i = 0; i <= 0xF; i++)       { V[i] = 0; }
    for(int i = 0; i < 16; i++)         { stack[i] = 0; }
    for(int x = 0; x < 64; x++) {
        for(int y = 0; y < 32; y++) {
            screen[x][y] = 0;
        }
    }

    pc = 512;
    I = 0;

    sound_timer = 0;
    delay_timer = 0;
    
    nnn = 0;
    n = 0;
    x = 0;
    y = 0;
    kk = 0;
    sp = 0;

    // currentKey = 0xFF;

    for(int i = 0; i < 80; i++) { memory[i] = fontset[i]; }
}


void Chip8::emu_cycle(SDL_Renderer *r) {
    // eat opcode
    // draw new screen
    // opcode = (memory[pc] << 8) | memory[pc 
    opcode = memory[pc] << 8 | memory[pc + 1];

    nnn = opcode & 0x0FFF;
    n = opcode & 0x000F;
    x = (opcode & 0x0F00) >> 8;
    y = (opcode & 0x00F0) >> 4;
    kk = opcode & 0x000FF; 

    // // printf("%X  %X\n",pc, opcode);

    switch(opcode & 0xF000) {
        //cls ret
        case 0x0000:
            switch(opcode & 0x000F) {
                // 00E0 - CLS
                case 0x0000:
                    // printf("Clear screen!\n");
                    for(int x = 0; x <= 64; x++) {
                        for(int y = 0; y <= 32; y++) {
                            screen[x][y] = 0;
		                    drawPixel(r, x, y);
                        }
                    }
                break;

                // 00EE - RET
                case 0x000E:
                    pc = stack[sp];
                    sp--;
                    // printf("Return!\n");
                break;
            }
        break;

        case 0x1000:
            // 1nnn - JP addr
            pc = nnn - 2;
            // printf("Jump: %X\n", nnn);
        break;

        case 0x2000:
            // 2nnn - CALL addr
            sp++;
            stack[sp] = pc;
            pc = nnn - 2;

            // printf("Call: %X\n", nnn);
        break;

        case 0x3000:
            // 3xkk - SE Vx, byte
            if(V[x] == kk) {
                pc += 2;
                // printf("Skipped because V[%d] == %X\n", x, kk);
            }
            
        break;

        case 0x4000:
            // 4xkk - SNE Vx, byte
            if(V[x] != kk) {
                pc += 2;
                // printf("Skipped because V[%d] != %X\n", x, kk);
            }
        break;

        case 0x5000:
            // 5xy0 - SE Vx, Vy
            if(V[x] == V[y]){
                pc += 2;
                // printf("Skipped because V[%d] == V[%d]\n", x, y);
            }
        break;

        case 0x6000:
            // 6xkk - LD Vx, byte
            V[x] = kk;
            // printf("Load V[%d] with %X", x, kk);
        break;

        case 0x7000:
            // 7xkk - ADD Vx, byte
            V[x] += kk;
            // printf("V[%d] += %X\n", x, kk);
        break;

        case 0x8000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    // 8xy0 - LD Vx, Vy
                    V[x] = V[y];
                break;

                case 0x0001:
                    // 8xy1 - OR Vx, Vy
                    V[x] |= V[y];
                break;

                case 0x0002:
                    // 8xy2 - AND Vx, Vy
                    V[x] &= V[y];
                break;

                case 0x0003:
                    // 8xy3 - XOR Vx, Vy
                    V[x] ^= V[y];
                break;

                case 0x0004:
                    // 8xy4 - ADD Vx, Vy
                    V[x] += V[y];

                    if(V[x] > 255) {
                        V[0xF] = 1;
                    } else {
                        V[0xF] = 0;
                        V[x] &= 0xFF;
                    }
                break;

                case 0x0005:
                    // 8xy5 - SUB Vx, Vy
                    if(V[x] > V[y]){
                        V[0xF] = 1;  
                    } else{
                        V[0xF] = 0;
                    }

                    V[x] -= V[y];
                
                break;

                case 0x0006:
                    // 8xy6 - SHR Vx {, Vy}
                    V[0xF] = V[x] & 0x1;
                    V[x] >>= 1;
                break;

                case 0x0007:
                    // 8xy7 - SUBN Vx, Vy
                    if(V[y] > V[x]) {
                        V[0xF] = 1;
                    } else{
                        V[0xF] = 0;
                    }
                    
                    V[x] = V[y] - V[x];
                break;

                case 0x000E:
                    // 8xyE - SHL Vx {, Vy}
                    V[0xF] = V[x] >> 7;
                    V[x] <<= 1;
                break;
            }
        break;

        case 0x9000:
            // 9xy0 - SNE Vx, Vy
            if(V[x] != V[y]) {
                pc += 2;
            }
        break;

        case 0xA000:
            // Annn - LD I, addr
            I = nnn;
            // printf("LOADED I WITH %X\n", nnn);
        break;
        
        case 0xB000:
            //  Bnnn - JP V0, addr
            pc = nnn + V[0] - 2;
        break;
        
        case 0xC000:
            // Cxkk - RND Vx, byte
            V[x] = (rand () % 256) & kk;
            // printf("SET V[%X] to %X\n", x, V[x]);
        break;

        case 0xD000:
            // Dxyn - DRW Vx, Vy, nibble
            drawSprite(r);

            // // printf("DRAW A %X BYTE SPRITE STARTING AT %X AT (%X, %X)\n",
            //         n, I, V[x], V[y]);
        break;
        
        case 0xE000:
            switch(opcode & 0x00FF) {
                case 0x009E:
                    // Ex9E - SKP Vx
                    /*

                        Come back to later
                        poll sdl event check if key etc etc.
                    */
                    if(currentKey == V[x]) {
                        pc += 2;
                    }
                break;

                case 0x00A1:
                    // ExA1 - SKNP Vx
                    /*

                        Come back to later
                        poll sdl event check if key etc etc.
                    */
                    if(currentKey != V[x]) {
                        pc += 2;
                    }
                break;
            }
        break;

        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007:
                    // Fx07 - LD Vx, DT
                    V[x] = delay_timer;
                break;

                case 0x000A:
                    // Fx0A - LD Vx, K
                    // more keypress shit
                    while(currentKey == 0xFF) {
                        captureKeys();
                    }

                    V[x] = currentKey;
                break;

                case 0x0015:
                    // Fx15 - LD DT, Vx
                    delay_timer = V[x];
                break;

                case 0x0018:
                    // Fx18 - LD ST, Vx
                    sound_timer = V[x];
                break;

                case 0x001E:
                    // Fx1E - ADD I, Vx
                    I += V[x];
                break;

                case 0x0029:
                    // Fx29 - LD F, Vx
                    // Come back to this
                    I = V[x] * 0x5;
                break;

                case 0x0033:
                    // Fx33 - LD B, Vx
                    // Come back
                    memory[I]       = V[x] / 100;
                    memory[I + 1]   = (V[x] / 10) % 10;
                    memory[I + 2]   = V[x] % 10;
                break;

                case 0x0055:
                    // Fx55 - LD [I], Vx
                    //
                    for(int i = 0; i <= x; ++i) {
                        memory[I+i] = V[i];
                    }
                break;

                case 0x0065:
                    // Fx65 - LD Vx, [I]
                    for (int i = 0; i <= x; ++i){
                        V[i] = memory[I + i];
                    }
                break;
            }
        break;
        
    }
    if(delay_timer > 0) {  delay_timer--; } 
    if(sound_timer > 0) {  sound_timer--; } 

    pc += 2;

}

bool Chip8::loadFile(char *file_path) {
    FILE* gameFile = fopen(file_path, "rb");

    /* REFACTOR TO AVOID COPYING */

    fseek(gameFile, 0, SEEK_END);
    long gameSize = ftell(gameFile);
    rewind(gameFile);

    char* buffer = (char*)malloc (sizeof(char)* gameSize);
    
    size_t result = fread(buffer, sizeof(char), (size_t)gameSize, gameFile);

    for(int i = 0 ; i < gameSize; ++i) {
        memory[i + 512] = (uint8_t)buffer[i];
    }

    //check if null

    fclose (gameFile);
    free (buffer);

    return true;
}

void Chip8::drawPixel(SDL_Renderer *r, unsigned short x, unsigned short y){
	// MAKE A PART OF CH8 CLASS
    if(screen[x][y] == 1) {
        SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    } else {
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    }
    
    x *= 10;
    y *= 10;

    for(int i = x; i < x + 10; i++) {
        for(int j = y; j < y + 10; j++) {
            SDL_RenderDrawPoint(r, i, j);
        }
    }
}

void Chip8::drawSprite(SDL_Renderer *r) {
    uint8_t bytes[n];
    // // printf("Drawing:");

    int j = 0;

    for(int i = I; i < (I+n); i++) {
        bytes[j] = memory[i];
        j++;
    }

    uint8_t byte;

    for(int i = 0; i < n; i++) {
        // printf("Printing: ");
        //printf("MEM[%d]: %X     ", i, bytes[i]);
        bytes[i] = reverseBits(bytes[i]);

        V[0xF] = 0;

        for(int j = 8; j >= 0; j--) {
            byte = (bytes[i] >> j) & 1;
            
            if(byte == 1) {
                if(screen[V[x] + j][V[y] + i] == 1) {
                    V[0xF] = 1;
                }

                screen[V[x] + j][V[y] + i] ^= 1;

                drawPixel(r, (V[x] + j), (V[y] + i));
            } else {
                screen[V[x]+j][V[y]+i] ^= 0;
                
                drawPixel(r, V[x] + j, V[y] + i);
            }
        }
    //  printf("\n");
    }
    SDL_RenderPresent(r);
    SDL_Delay(16);
}

uint8_t reverseBits(uint8_t num) { 
    uint8_t NO_OF_BITS = sizeof(num) * 8; 
    uint8_t reverse_num = 0, i, temp; 
  
    for (i = 0; i < NO_OF_BITS; i++) 
    { 
        temp = (num & (1 << i)); 
        if(temp) 
            reverse_num |= (1 << ((NO_OF_BITS - 1) - i)); 
    } 
   
    return reverse_num; 
} 

void Chip8::captureKeys(){
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			exit = true;

    if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_1:    currentKey = 0x1;   break;
            case SDLK_2:    currentKey = 0x2;   break;
            case SDLK_3:    currentKey = 0x3;   break;
            case SDLK_4:    currentKey = 0xC;   break;

            case SDLK_q:    currentKey = 0x4;   break;
            case SDLK_w:    currentKey = 0x5;   break;
            case SDLK_e:    currentKey = 0x6;   break;
            case SDLK_r:    currentKey = 0xD;   break;

            case SDLK_a:    currentKey = 0x7;   break;
            case SDLK_s:    currentKey = 0x8;   break;
            case SDLK_d:    currentKey = 0x9;   break;
            case SDLK_f:    currentKey = 0xE;   break;

            case SDLK_z:    currentKey = 0xA;   break;
            case SDLK_x:    currentKey = 0x0;   break;
            case SDLK_c:    currentKey = 0xB;   break;
            case SDLK_v:    currentKey = 0xF;   break;
            
            default:        currentKey = 0xFF;  break;
        }
    } else if(event.type == SDL_KEYUP){
        currentKey = 0xFF;
    }
}

int main(int argc, char** argv) {
    srand (time(0));
    
    SDL_Renderer *renderer;
    SDL_Window *window;

    Chip8 chip8 = Chip8();

    chip8.startUp();

    if(argc == 2) {
	printf("Loading rom: %s\n", argv[1]);
    	chip8.loadFile((char*)argv[1]);
    } else {
    	printf("No rom selected\n");
    	return EXIT_FAILURE;
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 320, 0, &window, &renderer);

    while(!chip8.exit) {
        chip8.emu_cycle(renderer);
        chip8.captureKeys();
    }

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
