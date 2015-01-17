#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "Asteroids.h"

struct Vector2D
{
	float x;
	float y;
};

void draw_asteroids();
void draw_ship(int, int, int, int);

struct Asteroid * asteroid_head = NULL;
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;



int main(int argc, char* argv[]){
	int temp = 0;
	int i = 0;
	float old_Time = 0.0f;
	float current_Time = 0.0f;
	float delta_Time = 0.0f;
	float speed = 100.0f;
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
			Vector2D pos = { 315.0f, 240.0f };
			Vector2D posOffSet{ 10.f, 0.0f };
			float rotationSpeed = 360.0f;
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

				SDL_PollEvent(&evt);
				if (evt.type == SDL_QUIT){
					isRunning = 0;
					break;
				}
				else if (evt.type == SDL_KEYDOWN){
					SDL_KeyboardEvent &keyboardEvt = evt.key;
					SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
					if (keyCode == SDLK_UP){
						if (pos.y > 0){
							pos.y -= (1 * delta_Time) * speed;
						}
						else{
							pos.y = 480;
						}
					}
					if (keyCode == SDLK_DOWN){
						if (pos.y < 480){
							pos.y += (1 * delta_Time) * speed;
						}
						else{
							pos.y = 0;
						}
					}
					if (keyCode == SDLK_RIGHT){
						if (pos.x + posOffSet.x < 640){
							pos.x += (1 * delta_Time) * speed;

						}
						else{
							pos.x = 0;
						}
					}
					if (keyCode == SDLK_LEFT){
						if (pos.x > 0){
							pos.x -= (1 * delta_Time) * speed;
						}
						else{
							pos.x = 630;
						}
					}
				}
				//set the draw colour so background is black
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				//clear screen
				SDL_RenderClear(renderer);
				//set the draw colour for our points
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				
				
				
				//draw asteroids
				draw_asteroids();


				/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				static float rotationDegrees = 10.0f;
				rotationDegrees += (rotationSpeed * delta_Time);
				rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

				float degreesToRadians = 3.1415926535f / 180.0f;
				float radiansToDegrees = 180.0f / 3.1415926535f;
				float rotationRadians = rotationDegrees * degreesToRadians;

				Vector2D rotatedOffset =
				{
					posOffSet.x * cosf(rotationRadians) + posOffSet.y * sinf(rotationRadians),
					posOffSet.x * sinf(rotationRadians) - posOffSet.y * cosf(rotationRadians)
				};

				Vector2D transformedEndPoint = { pos.x + rotatedOffset.x, pos.y + rotatedOffset.y };

				SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);*/

				//draw ship
				draw_ship(pos.x, pos.y, posOffSet.x, posOffSet.y);

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

void draw_asteroids(){
	int temp = 0;
	int i = 0;
	int j = 0;
	struct Asteroid * a;
	a = asteroid_head;
	asteroid_update(&asteroid_head);
	while (temp < 10){
		SDL_SetRenderDrawColor(renderer, a->color.r, a->color.g, a->color.b, a->color.a);
		SDL_RenderDrawPoint(renderer, a->pos.x - 5, a->pos.y + 5);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y + 5);
		SDL_RenderDrawPoint(renderer, a->pos.x - 4, a->pos.y + 4);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y + 4);
		SDL_RenderDrawPoint(renderer, a->pos.x - 3, a->pos.y + 3);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y + 3);
		SDL_RenderDrawPoint(renderer, a->pos.x - 2, a->pos.y + 2);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y + 2);
		SDL_RenderDrawPoint(renderer, a->pos.x - 1, a->pos.y + 1);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y + 1);
		SDL_RenderDrawPoint(renderer, a->pos.x + 5, a->pos.y + 5);
		SDL_RenderDrawPoint(renderer, a->pos.x + 5, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x + 4, a->pos.y + 4);
		SDL_RenderDrawPoint(renderer, a->pos.x + 4, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x + 3, a->pos.y + 3);
		SDL_RenderDrawPoint(renderer, a->pos.x + 3, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x + 2, a->pos.y + 2);
		SDL_RenderDrawPoint(renderer, a->pos.x + 2, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x + 1, a->pos.y + 1);
		SDL_RenderDrawPoint(renderer, a->pos.x + 1, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x - 1, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x - 1, a->pos.y - 1);
		SDL_RenderDrawPoint(renderer, a->pos.x - 2, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x - 2, a->pos.y - 2);
		SDL_RenderDrawPoint(renderer, a->pos.x - 3, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x - 3, a->pos.y - 3);
		SDL_RenderDrawPoint(renderer, a->pos.x - 4, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x - 4, a->pos.y - 4);
		SDL_RenderDrawPoint(renderer, a->pos.x - 5, a->pos.y);
		SDL_RenderDrawPoint(renderer, a->pos.x - 5, a->pos.y - 5);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y - 1);
		SDL_RenderDrawPoint(renderer, a->pos.x + 1, a->pos.y - 1);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y - 2);
		SDL_RenderDrawPoint(renderer, a->pos.x + 2, a->pos.y - 2);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y - 3);
		SDL_RenderDrawPoint(renderer, a->pos.x + 3, a->pos.y - 3);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y - 4);
		SDL_RenderDrawPoint(renderer, a->pos.x + 4, a->pos.y - 4);
		SDL_RenderDrawPoint(renderer, a->pos.x, a->pos.y - 5);
		SDL_RenderDrawPoint(renderer, a->pos.x + 5, a->pos.y - 5);
		a = a->next;
		temp++;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void draw_ship(int posX, int posY, int posX2, int posY2){
	//draw ship
	SDL_RenderDrawLine(renderer, posX + 5, posY - 5, posX + posX2 - 5, posY + posY2 - 5);
	SDL_RenderDrawLine(renderer, posX + 4, posY - 4, posX + posX2 - 4, posY + posY2 - 4);
	SDL_RenderDrawLine(renderer, posX + 3, posY - 3, posX + posX2 - 3, posY + posY2 - 3);
	SDL_RenderDrawLine(renderer, posX + 2, posY - 2, posX + posX2 - 2, posY + posY2 - 2);
	SDL_RenderDrawLine(renderer, posX + 1, posY - 1, posX + posX2 - 1, posY + posY2 - 1);
	SDL_RenderDrawLine(renderer, posX, posY, posX + posX2, posY + posY2);
	SDL_RenderDrawLine(renderer, posX - 1, posY + 1, posX + posX2 + 1, posY + posY2 + 1);
	SDL_RenderDrawLine(renderer, posX - 2, posY + 2, posX + posX2 + 2, posY + posY2 + 2);
	SDL_RenderDrawLine(renderer, posX - 3, posY + 3, posX + posX2 + 3, posY + posY2 + 3);
	SDL_RenderDrawLine(renderer, posX - 4, posY + 4, posX + posX2 + 4, posY + posY2 + 4);
	SDL_RenderDrawLine(renderer, posX - 5, posY + 5, posX + posX2 + 5, posY + posY2 + 5);
}