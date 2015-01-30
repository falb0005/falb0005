/**
* \class Game.h
* \brief A class that represents the game implementation
* \author Johnathan Falbo
* \date January 29, 2014
*/
#pragma once// Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

#include "GameEngine.h"
#include "Missile.h"

#define NUM_MISSILES 5
#define NUM_ASTEROIDS 12

class Game : public GameEngine
{
	friend class GameEngine;
protected:
	/**
	* \fn void Game::Game()
	* \brief Default Game Constructor
	*/
	Game();
	/**
	* \fn void Gane::~Game()
	* \brief Game destructor
	*/
	~Game();

	/**
	* \fn void Game::InitializeImpl()
	* \brief A function that is used to initialize the game to default values
	*/
	void InitializeImpl();
	/**
	* \fn void Game::UpdateImpl(float, SDL_Window*)
	* \brief A function that is used to update the game each tick
	* \param dt The time in fractions of a second since the last pass.
	* \param renderer The SDL renderer used to draw the object.
	*/
	void UpdateImpl(float dt, SDL_Window* window);
	/**
	* \fn void Game::DrawImpl(SDL_Renderer* renderer, float dt)
	* \brief A function that is used to draw the game objects each tick
	* \param renderer The SDL renderer used to draw the object.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void DrawImpl(SDL_Renderer* renderer, float dt);
	/**
	* \fn void GameObject::CheckPlayerAsteroidCollissions()
	* \brief A function that used to check if the player has collided with an Asteroid
	* \return returns 1 if the player has collided with an Asteroid
	*/
	int CheckPlayerAsteroidCollissions();
	/**
	* \fn void Game::CheckMissileAsteroidCollissions()
	* \brief A function that used to check if the missiles have collided with an Asteroid
	* \return returns 1 if the missile has collided with an Asteroid 0 if it hastnt collided and -1 if
	* there are no Asteroids left
	*/
	int CheckMissileAsteroidCollissions();

	int _screenWidth = 640;
	int _screenHeight = 480;
	int _gameScore = 0;
	int _lifes = 3;
	Player _player;
	char* _title;
	Asteroid _asteroids[NUM_ASTEROIDS];
	float _speed;
	float _rotationSpeed;
	Vector2 _endPointOffset;
	Missile _missiles[NUM_MISSILES];
};