#include "Game.h"
#include <SDL.h>
#include <stdio.h>
#include <math.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}
	return _instance;
}

Game::Game() : GameEngine()
{
	_speed = 2000;
}

void Game::InitializeImpl()
{
	// Using the default member-wise initializer for our new struct.
	for (int i = 0; i < 10; i++)
	{
		_asteroids[i].Initialize();
	}

}

void Game::UpdateImpl(float dt)
{
	Vector3 pos = { 0, 0, 0 };
	SDL_Event evt;
	SDL_PollEvent(&evt);
	// Check for user input.
	if (evt.type == SDL_KEYDOWN)
	{
		SDL_KeyboardEvent &keyboardEvt = evt.key;
		SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
		printf("%f\n", dt);
		switch (keyCode)
		{
		case SDLK_UP:
			pos = _player.Get_Position();
			pos.y -= _speed * (1 * dt);
			_player.Set_Position(pos.x, pos.y);
			break;
		case SDLK_DOWN:
			pos = _player.Get_Position();
			pos.y += _speed * (1 * dt);
			_player.Set_Position(pos.x, pos.y);
			break;
		default:
			break;
		}
	}
	_player.Update(dt);
	for (int i = 0; i < 10; i++)
	{
		_asteroids[i].Update(dt);
	}
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	// Set the draw colour for our point.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Draw the point.
	//SDL_RenderDrawPoint(renderer, posX, posY);
	_player.Draw(renderer, dt);
	for (int i = 0; i < 10; i++)
	{
		_asteroids[i].Draw(renderer, dt);
	}
//	SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);
}