#include <SDL.h>
#include <stdio.h>
#include "Asteroids.h"
void render_asteroids();

struct Asteroid * asteroid_head = NULL;
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;



int main(int argc, char* argv[]){
	int temp = 0;
	int i = 0;
	float old_Time = 0.0f;
	float current_Time = 0.0f;
	float delta_Time = 0.0f;
	float speed = 2000.0f;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) > 0){
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
			float posX = 100.0f, posY = 100.0f, posX2 = 200.0f, posY2 = 100.0f;
			temp = 0;
			while (temp < 10){
				asteroid_add(&asteroid_head);
				temp++;
			}
			temp = 0;
			old_Time = (float)SDL_GetTicks();
			current_Time = old_Time;

			while (isRunning){
				//calculating the time difference since our last loop.
				old_Time = current_Time;
				current_Time = (float)SDL_GetTicks();
				delta_Time = (current_Time - old_Time) / 1000.0f;

				//event loop
				while (SDL_PollEvent(&evt) != 0){
					if (evt.type == SDL_QUIT){
						isRunning = 0;
						break;
					}
					else if (evt.type == SDL_KEYDOWN){
						SDL_KeyboardEvent &keyboardEvt = evt.key;
						SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
						if (keyCode == SDLK_UP){
							posY -= (1 * delta_Time) * speed;
							posY2 -= (1 * delta_Time) * speed;
						}
						if (keyCode == SDLK_DOWN){
							posY += (1 * delta_Time) * speed;
							posY2 += (1 * delta_Time) * speed;
						}
						if (keyCode == SDLK_RIGHT){
							posX += (1 * delta_Time) * speed;
							posX2 += (1 * delta_Time) * speed;
						}
						if (keyCode == SDLK_LEFT){
							posX -= (1 * delta_Time) * speed;
							posX2 -= (1 * delta_Time) * speed;
						}
					}
				}
				//set the draw colour so background is black
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				//clear screen
				SDL_RenderClear(renderer);
				//set the draw colour for our points
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawLine(renderer, posX, posY, posX2, posY2);
				//render asteroids
				render_asteroids();
				//present point
				SDL_RenderPresent(renderer);
			}
		}
	}
	asteroid_destroy(&asteroid_head);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void render_asteroids(){
	int temp = 0;
	int i = 0;
	struct Asteroid * a;
	asteroid_update(&asteroid_head);
	while (temp < 10){
		a = asteroid_head;
		while (i != temp){
			a = a->next;
			i++;
		}
		i = 0;
		temp++;
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y);
	}
}