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
	free(_title);
}

void Game::InitializeImpl()
{
	// Using the default member-wise initializer for our new struct.
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		_asteroids[i].Initialize();
	}
	_title = (char*)malloc(sizeof(char)* 50);
	_gameScore = 0;
}

void Game::UpdateImpl(float dt, SDL_Window* window)
{
	int collision = 0;
	Vector3 pos = { 0, 0, 0 };
	Vector3 posEndPoint = { 0, 0, 0 };
	static float rotationDegrees = 0.0f;
	InputManager *im = InputManager::GetInstance();
	sprintf_s(_title, 50, "Asteroid Mania   Lives: %d   Score: %d", _lifes, _gameScore);
	SDL_SetWindowTitle(window, _title);
	im->Update(dt);
	// Check for user input.
	if (im->IsKeyDown(SDLK_UP) == true)
	{
		float xVector = 0, yVector = 0;

		//get player position and end point position.
		pos = _player.GetPosition();
		posEndPoint = _player.GetPlayerRotation();

		//calculate players trajectory.
		xVector = MathUtils::CalculateShipXVector(pos.x, posEndPoint.x);
		yVector = MathUtils::CalculateShipYVector(pos.y, posEndPoint.y);

		//set player tajectory.
		_player.SetDirectionVector({xVector, yVector, 0.0f});

		//boost player in direction of trajectory.
		pos.y += (_speed * (yVector*0.1f)) * (1 * dt);
		posEndPoint.y += (_speed * (yVector*0.1f)) * (1 * dt);
		pos.x += (_speed * (xVector*0.1f)) * (1 * dt);
		posEndPoint.x += (_speed * (xVector*0.1f)) * (1 * dt);

		//set player position and end point position.
		_player.SetPosition(pos);
		_player.SetPlayerRotation(posEndPoint);
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

		_player.SetPlayerRotation({ _player.GetPosition().x + rotatedOffset.x, _player.GetPosition().y + rotatedOffset.y, 0 });
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

		_player.SetPlayerRotation({ _player.GetPosition().x + rotatedOffset.x, _player.GetPosition().y + rotatedOffset.y, 0 });
	}
	else if (im->IsKeyDown(SDLK_SPACE) == true)
	{
		float xVector = 0, yVector = 0;
		
		//get player position and end point position.
		pos = _player.GetPosition();
		posEndPoint = _player.GetPlayerRotation();

		//calculate players trajectory.
		xVector = MathUtils::CalculateShipXVector(pos.x, posEndPoint.x);
		yVector = MathUtils::CalculateShipYVector(pos.y, posEndPoint.y);

		for (int i = 0; i < NUM_MISSILES; i++)
		{
			if (_missiles[i].GetKillFlag() == true)
			{
				static float time_Elapsed = 0.0f;
				time_Elapsed += dt;
				if (time_Elapsed > 0.5){
					time_Elapsed = 0.0f;
					_missiles[i].SetDirectionVector({ xVector, yVector, 0.0f });
					_missiles[i].SetPosition(_player.GetPosition());
					_missiles[i].SetMissileRotation(_player.GetPlayerRotation());
					_missiles[i].SetKillFlag(false);
					break;
				}
			}
		}

	}
	//printf("%f\n", dt);

	//update player missiles and asteroids.
	_player.Update(dt);
	for (int i = 0; i < NUM_MISSILES; i++)
	{
		_missiles[i].Update(dt);
	}
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		_asteroids[i].Update(dt);
	}

	//reset collision to no collisions state
	collision = 0;

	//check for collissions
	collision = CheckPlayerAsteroidCollissions();

	//if player collides with and Asteroid
	if (collision == 1)
	{
		_lifes -= 1;

		//reset player attributes to default
		_player.SetPosition({ _screenWidth / 2, _screenHeight / 2, 0.0f });
		_player.SetPlayerRotation({ _screenWidth / 2, _screenHeight / 2 - 10, 0.0f });
		_player.SetDirectionVector({ 0.0f, 0.0f, 0.0f });
		rotationDegrees = 0.0f;

		//reset missile values to un-shot
		for (int i = 0; i < NUM_MISSILES; i++)
		{
			_missiles[i].SetDirectionVector({ 0.0f, 0.0f, 0.0f });
			_missiles[i].SetPosition({ -1000.0f, -1000.0f, -1000.0f });
			_missiles[i].SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
			_missiles[i].SetKillFlag(true);
		}

		//if player is out of lives
		if (_lifes < 0)
		{
			_lifes = 3;
			_gameScore = 0;
			for (int i = 0; i < NUM_ASTEROIDS; i++)
			{
				_asteroids[i].Initialize();
				_asteroids[i].SetKillFlag(false);
			}
		}
	}

	//reset collission indicator too no collisions
	collision = 0;

	//poll asteroids to check if any missiles have collided
	collision = CheckMissileAsteroidCollissions();

	if (collision == 1)
	{
		_gameScore = _gameScore + 50;

		//reset missile values to un-shot
		for (int i = 0; i < NUM_MISSILES; i++)
		{
			_missiles[i].SetDirectionVector({ 0.0f, 0.0f, 0.0f });
			_missiles[i].SetPosition({ -1000.0f, -1000.0f, -1000.0f });
			_missiles[i].SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
			_missiles[i].SetKillFlag(true);
		}
	}
	else if (collision == -1)
	{
		for (int i = 0; i < NUM_ASTEROIDS; i++)
		{
			//re-initialize asteroids to random values
			_asteroids[i].Initialize();
			_asteroids[i].SetKillFlag(false);
		}
	}
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	// Draw the points.
	_player.Draw(renderer, dt);
	for (int i = 0; i < NUM_MISSILES; i++)
	{
		_missiles[i].Draw(renderer, dt);
	}
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		_asteroids[i].Draw(renderer, dt);
	}
}

int Game::CheckPlayerAsteroidCollissions()
{
	float distance = 0.0f;
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		if (_asteroids[i].GetKillFlag() == false)
		{
			distance = MathUtils::CalculateDistance(_player.GetPosition().x, _asteroids[i].GetPosition().x, _player.GetPosition().y, _asteroids[i].GetPosition().y);
			//printf("%f\n", distance);
			if (distance < 10){
				_asteroids[i].SetKillFlag(true);
				return 1;
			}
		}
	}
	distance = 0.0f;
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		if (_asteroids[i].GetKillFlag() == false)
		{
			distance = MathUtils::CalculateDistance(_player.GetPlayerRotation().x, _asteroids[i].GetPosition().x, _player.GetPlayerRotation().y, _asteroids[i].GetPosition().y);
			//printf("%f\n", distance);
			if (distance < 10){
				_asteroids[i].SetKillFlag(true);
				return 1;
			}
		}
	}
	return 0;
}

int Game::CheckMissileAsteroidCollissions()
{
	float distance = 0.0f;
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		for (int j = 0; j < NUM_MISSILES; j++)
		{
			if (_missiles[j].GetKillFlag() == false && _asteroids[i].GetKillFlag() == false)
			{
				distance = MathUtils::CalculateDistance(_missiles[j].GetMissileRotation().x, _asteroids[i].GetPosition().x, _missiles[j].GetMissileRotation().y, _asteroids[i].GetPosition().y);
				//printf("%f\n", distance);
				if (distance < 10){
					_asteroids[i].SetKillFlag(true);
					return 1;
				}
			}
		}
	}
	distance = 0.0f;
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		for (int j = 0; j < NUM_MISSILES; j++)
		{
			if (_missiles[j].GetKillFlag() == false && _asteroids[i].GetKillFlag() == false)
			{
				distance = MathUtils::CalculateDistance(_missiles[j].GetPosition().x, _asteroids[i].GetPosition().x, _missiles[j].GetPosition().y, _asteroids[i].GetPosition().y);
				//printf("%f\n", distance);
				if (distance < 10){
					_asteroids[i].SetKillFlag(true);
					return 1;
				}
			}
		}
	}
	int check = -1;
	for (int i = 0; i < 10; i++)
	{
		if (_asteroids[i].GetKillFlag() == false){
			check = 0;
		}
	}
	return check;
}