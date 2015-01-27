#pragma once

#include "GameEngine.h"


class Game : public GameEngine
{
	friend class GameEngine;

protected:
	Game();

	void InitializeImpl();
	void UpdateImpl(float dt);
	void DrawImpl(SDL_Renderer *renderer, float dt);

	Player _player;
	Asteroid _asteroids[10];
	float _speed;
	// Using the default member-wise initializer for our new struct.
};