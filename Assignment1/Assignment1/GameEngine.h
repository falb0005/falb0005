/**
* \class Asteroid.h
* \brief A class that represents an abstracted game engine
* \author Justin Wilkinson
* \date January 29, 2014
*/
#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

// Preprocessor directive to ensure that this header will only be included once. -- Generally used for all environments.
/*#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#endif // _GAME_ENGINE_H_*/

#include "MathUtils.h"
#include "Player.h"
#include "Asteroid.h"
#include "Timer.h"

// Forward declaring our renderer and window.
// Because we're using them as pointers, we don't need to know their size
// at compile time to define this class.
struct SDL_Renderer;
struct SDL_Window;

class GameEngine
{
public:
	static GameEngine* CreateInstance();

	/**
	* \fn void GameEngine::Initialize()
	* \brief A function that is used to initialize the game
	*/
	void Initialize();
	/**
	* \fn void GameEngine::Shutdown()
	* \brief A function that is used to shutdown the game
	*/
	void Shutdown();
	/**
	* \fn void GameEngine::Update()
	* \brief A function that is used to update the game
	*/
	void Update();
	/**
	* \fn void GameEngine::Draw()
	* \brief A function that is used to draw the game
	*/
	void Draw();

	/**
	* \fn void GameEngine::~GameEngine()
	* \brief GameEngine Deconstructor
	*/
	~GameEngine();

protected:
	/**
	* \fn void GameEngine::GameEngine()
	* \brief GameEngine Default Constructor
	*/
	GameEngine();

	/**
	* \fn void GameEngine::InitializeImpl() = 0
	* \brief A virtual function that is used to initialize the game
	*/
	virtual void InitializeImpl() = 0;
	/**
	* \fn void GameEngine::UpdateImpl(float dt, SDL_Window*) = 0
	* \brief A virtual function that we’ll use as to define how our
	* game is updated.
	* \param dt The time in fractions of a second since the last pass.
	* \param renderer The SDL renderer used to draw the object.
	*/
	virtual void UpdateImpl(float dt, SDL_Window*) = 0;
	/**
	* \fn void GameEngine::DrawImpl(SDL_Renderer *renderer, float dt) = 0
	* \brief A virtual function that we’ll use as to define how our
	* game is drawn to the screen.
	* \param renderer The SDL renderer used to draw the object.
	* \param dt The time in fractions of a second since the last pass.
	*/
	virtual void DrawImpl(SDL_Renderer *renderer, float dt) = 0;

	static GameEngine *_instance;

	SDL_Window *_window;
	SDL_Renderer *_renderer;
	Timer _engineTimer;

	float _oldTime, _currentTime, _deltaTime;
};