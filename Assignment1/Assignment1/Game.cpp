#include "Game.h"
#include "InputManager.h"
#include <SDL.h>
#include <stdio.h>
#include <string.h>
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
	_speed = 80;
	_rotationSpeed = 200;
	_endPointOffset = { 0, 10 };
}

Game::~Game()
{
	free(title);
}

void Game::InitializeImpl()
{
	// Using the default member-wise initializer for our new struct.
	for (int i = 0; i < 10; i++)
	{
		_asteroids[i].Initialize();
	}
	title = (char*)malloc(sizeof(char)* 50);

}

void Game::UpdateImpl(float dt, SDL_Window* window)
{
	int collision = 0;
	Vector3 pos = { 0, 0, 0 };
	Vector3 posEndPoint = { 0, 0, 0 };
	static float rotationDegrees = 0.0f;
	InputManager *im = InputManager::GetInstance();
	sprintf_s(title, 50, "Asteroid Mania   Lives: %d   Score: %d", _lifes, _gameScore);
	SDL_SetWindowTitle(window, title);
	im->Update(dt);
	// Check for user input.
	if (im->IsKeyDown(SDLK_UP) == true)
	{
		float xVector = 0, yVector = 0;

		//get player position and end point position.
		pos = _player.Get_Position();
		posEndPoint = _player.Get_PlayerRotation();

		//calculate players trajectory.
		xVector = MathUtils::Calculate_Ship_X_Vector(pos.x, posEndPoint.x);
		yVector = MathUtils::Calculate_Ship_Y_Vector(pos.y, posEndPoint.y);

		//set player tajectory.
		_player.Set_DirectionVector({xVector, yVector, 0.0f});

		//boost player in direction of trajectory.
		pos.y += (_speed * (yVector*0.1f)) * (1 * dt);
		posEndPoint.y += (_speed * (yVector*0.1f)) * (1 * dt);
		pos.x += (_speed * (xVector*0.1f)) * (1 * dt);
		posEndPoint.x += (_speed * (xVector*0.1f)) * (1 * dt);

		//set player position and end point position.
		_player.Set_Position(pos);
		_player.Set_PlayerRotation(posEndPoint);
	}
	else if (im->IsKeyDown(SDLK_RIGHT) == true)
	{
		//rotate players ship right.
		rotationDegrees += (_rotationSpeed * dt);
		rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

		float rotationRadians = MathUtils::ToRadians(rotationDegrees);

		Vector2 rotatedOffset =
		{
			_endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
			_endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
		};

		_player.Set_PlayerRotation({ _player.Get_Position().x + rotatedOffset.x, _player.Get_Position().y + rotatedOffset.y, 0 });
	}
	else if (im->IsKeyDown(SDLK_LEFT) == true)
	{
		//rotate players ship left
		rotationDegrees -= (_rotationSpeed * dt);
		rotationDegrees += (rotationDegrees <= 0.0f ? +360.0f : 0);

		float rotationRadians = MathUtils::ToRadians(rotationDegrees);

		Vector2 rotatedOffset =
		{
			_endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
			_endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
		};

		_player.Set_PlayerRotation({ _player.Get_Position().x + rotatedOffset.x, _player.Get_Position().y + rotatedOffset.y, 0 });
	}
	else if (im->IsKeyDown(SDLK_SPACE) == true)
	{
		float xVector = 0, yVector = 0;
		
		//get player position and end point position.
		pos = _player.Get_Position();
		posEndPoint = _player.Get_PlayerRotation();

		//calculate players trajectory.
		xVector = MathUtils::Calculate_Ship_X_Vector(pos.x, posEndPoint.x);
		yVector = MathUtils::Calculate_Ship_Y_Vector(pos.y, posEndPoint.y);

		_missiles[0].Set_DirectionVector({ xVector, yVector, 0.0f });
		_missiles[0].Set_Position(_player.Get_Position());
		_missiles[0].Set_MissileRotation(_player.Get_PlayerRotation());
	}
	//printf("%f\n", dt);

	//update player missiles and asteroids.
	_player.Update(dt);
	_missiles[0].Update(dt);
	for (int i = 0; i < 10; i++)
	{
		_asteroids[i].Update(dt);
	}

	//check for collissions
	collision = Check_Player_Asteroid_Collissions();
	//printf("%d\n", collision);
	if (collision == 1)
	{
		_lifes -= 1;
		_player.Set_Position({ _screenWidth / 2, _screenHeight / 2, 0.0f });
		_player.Set_PlayerRotation({ _screenWidth / 2, _screenHeight / 2 - 10, 0.0f });
		_player.Set_DirectionVector({ 0.0f, 0.0f, 0.0f });
		rotationDegrees = 0.0f;
		_missiles[0].Set_DirectionVector({ 0.0f, 0.0f, 0.0f });
		_missiles[0].Set_Position({ -1.0f, -1.0f, -1.0f });
		_missiles[0].Set_MissileRotation({ -1.0f, -1.0f, -1.0f });
		if (_lifes < 0)
		{
			_lifes = 3;
			_gameScore = 0;
			// Using the default member-wise initializer for our new struct.
			for (int i = 0; i < 10; i++)
			{
				_asteroids[i].Initialize();
			}
		}
	}
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	// Set the draw colour for our point.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Draw the points.
	_player.Draw(renderer, dt);
	_missiles[0].Draw(renderer, dt);
	for (int i = 0; i < 10; i++)
	{
		_asteroids[i].Draw(renderer, dt);
	}
}

int Game::Check_Player_Asteroid_Collissions()
{
	float distance = 0.0f;
	for (int i = 0; i < 10; i++)
	{
		if (_asteroids[i]._killedFlag == false)
		{
			distance = MathUtils::Calculate_Distance(_player.Get_Position().x, _asteroids[i].Get_Position().x, _player.Get_Position().y, _asteroids[i].Get_Position().y);
			//printf("%f\n", distance);
			if (distance < 10){
				return 1;
			}
		}
	}
	return 0;
}