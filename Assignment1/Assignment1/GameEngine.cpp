#include "GameEngine.h"
#include <SDL.h>
#include <math.h>
#include "MathUtils.h"
#include <stdio.h>

GameEngine::GameEngine()
{
	
}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = SDL_CreateWindow("CST8237 Lab",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player.Initialize();
	

	/* Get the time at the beginning of our game loop so that we can track the
	* elapsed difference. */
	oldTime = SDL_GetTicks();
	currentTime = oldTime;
}

void GameEngine::Shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GameEngine::Update()
{
	SDL_Event evt;
	SDL_PollEvent(&evt);

	// Calculating the time difference since our last loop.
	oldTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - oldTime) / 1000;
	//printf("%f\n", deltaTime);
	// Check for user input.
	if (evt.type == SDL_KEYDOWN)
	{
		SDL_KeyboardEvent &keyboardEvt = evt.key;
		SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
		switch (keyCode)
		{
		case SDLK_UP:
			//pos.y -= (speed * deltaTime);
			break;
		case SDLK_DOWN:
			//pos.y += (speed * deltaTime);
			break;
		default:
			break;
		}
	}

	//update player
	player.Update(deltaTime);
}

void GameEngine::Draw()
{
	// Set the draw colour for screen clearing.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	// Clear the renderer with the current draw colour.
	SDL_RenderClear(renderer);

	// Set the draw colour for our point.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// draw player
	player.Draw(renderer, deltaTime);

	// Present what is in our renderer to our window.
	SDL_RenderPresent(renderer);
}