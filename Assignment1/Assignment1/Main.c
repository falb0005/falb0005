#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) > 0){
		printf("Video Initilization Error:\n%s", SDL_GetError());
	}
	else{
		window = SDL_CreateWindow("Asteroids Mania", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == NULL){
			printf("Window Initilization Error:\n%s", SDL_GetError());
		}
		else{
			char isRunning = 1;
			SDL_Event evt;
			int posX = 100, posY = 100;
			while (isRunning){
				while (SDL_PollEvent(&evt) != 0){
					if (evt.type == SDL_QUIT)
						isRunning = 0;
				}
				//set the draw colour so background is white
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				//clear screen
				SDL_RenderClear(renderer);
				//set the draw colour for our point
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				//render point
				SDL_RenderDrawPoint(renderer, posX, posY);
				//present point
				SDL_RenderPresent(renderer);

				posY++;
				if (posY > 640){ posY = 0; }
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}