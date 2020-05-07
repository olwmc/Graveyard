// Build with　gcc -o snake main.c -lSDL2

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

void drawNode(SDL_Renderer *r, int x, int y, bool isFruit, bool darkMode);

int main(int argc, char **argv) {
	// Init everything
	SDL_Event e;
	SDL_Renderer *renderer;
	SDL_Window *window;
	
	SDL_Init(SDL_INIT_VIDEO);
	
	bool quit = false;
	
	struct point{
		int x;
		int y;
	};

	struct point snakeBody[500];
	
	// Snake Head X and Y
	int playerX = 0,
	    playerY = 0;
	
	// Snake momentum
	int nextX = 0,
	    nextY = 0;

	int tailSize = 3;

	// Apple coordinates
	int appleX,
	    appleY;
	
	bool isEaten = true;

	bool darkMode; 
	if(argc >= 2){
		if(strcmp(argv[1], "-d") == 0) {
			darkMode = true;
		} else {
			printf("Available commands: \n-d : dark mode\n");
			exit(0);
		}
	} else {
		darkMode = false;
	}


	// Set up window
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH,
	    	    		WINDOW_WIDTH,
	    			0,
	    			&window,
	    			&renderer);
	
	while(!quit) {	
		// Set up background
		if(darkMode){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		} else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		for(int i = 0; i < WINDOW_WIDTH; i++)
		    for(int j = 0; j < WINDOW_HEIGHT; j++)
		        	SDL_RenderDrawPoint(renderer, i, j);


		// Check if Quit
		if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
			quit = true;

		// Get keycode
		SDL_PollEvent(&e);
		switch(e.key.keysym.sym){
                	case SDLK_LEFT:
				nextX = -30;
				nextY = 0;
			break;

			case SDLK_RIGHT:
				nextX = 30;
				nextY = 0;
			break;

			case SDLK_UP:
				nextX = 0;
				nextY = -30;
			break;

			case SDLK_DOWN:
				nextX = 0;
				nextY = 30;
			break;
		}

		playerX += nextX;
		playerY += nextY;

		// Check bounds
		if(playerX >= 600) { playerX = 0; }
		if(playerX < 0) { playerX = 570; }

		if(playerY >= 600) { playerY = 0; }
		if(playerY < 0) { playerY = 570; }

		// Set snake head to current position
		snakeBody[0].x = playerX;
		snakeBody[0].y = playerY;


		// Shift all tail values back
		for(int i = 0; i <= tailSize; i++) {
			int tempVal,
			    prevX,
			    prevY;

			if(i != 0) {
				tempVal = snakeBody[i].x; 
				snakeBody[i].x = prevX;
				prevX = tempVal;

				tempVal = snakeBody[i].y; 
				snakeBody[i].y = prevY;
				prevY = tempVal;
			} else {
				prevX = snakeBody[0].x;
				prevY = snakeBody[0].y;
			}
		}
		
		// Set Apple coords and check if eaten
		if(isEaten) {
			srand(time(0));
			appleX = 30 * (rand() % 20);

			srand(time(0));
			appleY = 30 * (rand() % 20);

			isEaten = false;
		}

		if(snakeBody[0].x == appleX && snakeBody[0].y == appleY) {
			tailSize++;
			isEaten = true;
		}


		for(int i = 2; i <= tailSize; i++) {
			if((playerX == snakeBody[i].x) &&  (playerY == snakeBody[i].y)) {
				tailSize = 3;
				for(int i = 1; i < 500; i++) {
					snakeBody[i].x = -99;
					snakeBody[i].y = -99;
				}
				break;
			}
		}



		// Draw apple
		drawNode(renderer, appleX, appleY, true, darkMode);

		// Draw tail
		for(int i = 0; i <= tailSize; i++) {
			drawNode(renderer, snakeBody[i].x, snakeBody[i].y, false, darkMode);
		}
		
		// Render 
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void drawNode(SDL_Renderer *r, int x, int y, bool isFruit, bool darkMode) {
	if(isFruit) {
		if(darkMode) {
			SDL_SetRenderDrawColor(r,
					0, 255, 255,
					255);
		} else {
			SDL_SetRenderDrawColor(r,
					255, 0, 0,
				        255);		       
		}
	}
	else {
    		if(darkMode) {
			SDL_SetRenderDrawColor(r,
					255, 0, 255,
					255);
		} else { 
			SDL_SetRenderDrawColor(r,
					0, 255, 0,
					255);
		}			
	}
	
	int scale = 30;

	for(int i = x; i < x + scale; i++)
		for(int j = y; j < y + scale; j++)
			if(x != -99 && y != -99)
		    		SDL_RenderDrawPoint(r, i, j);
}