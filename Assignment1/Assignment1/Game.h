#pragma once

#include "GameEngine.h"
#include "Missile.h"

class Game : public GameEngine
{
	friend class GameEngine;
protected:
	Game();
	~Game();
	void InitializeImpl();
	void UpdateImpl(float, SDL_Window*);
	void DrawImpl(SDL_Renderer*, float);
	int Check_Player_Asteroid_Collissions();
	int _screenWidth = 640;
	int _screenHeight = 480;
	int _gameScore = 0;
	int _lifes = 3;
	Player _player;
	char* title;
	Asteroid _asteroids[10];
	float _speed;
	float _rotationSpeed;
	Vector2 _endPointOffset;
	Missile _missiles[3];
	// Using the default member-wise initializer for our new struct.
};