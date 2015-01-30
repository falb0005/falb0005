/**
* \class Asteroid.h
* \brief A class that represents a single Asteroid that can
* be placed and manipulated in the world.
* \author Johnathan Falbo
* \date January 29, 2014
*/

#pragma once// Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

#include "GameObject.h"

class Asteroid : GameObject 
{
public:
	/**
	* \fn void Asteroid::Asteroid()
	* \brief Asteroid Constructor
	*/
	Asteroid();
	/**
	* \fn void Asteroid::~Asteroid()
	* \brief Asteroid destructor
	*/
	~Asteroid();

	/**
	* \fn void Asteroid::Initialize()
	* \brief A function that is used to initialize default asteroid values
	*/
	void Initialize();
	/**
	* \fn void Asteroid::Draw(SDL_Renderer *renderer, float dt)
	* \brief A function that is used to update asteroid values
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Update(float dt);
	/**
	* \fn void Asteroid::Draw(SDL_Renderer *renderer, float dt)
	* \brief A function that is used to draw the asteroids based on their position
	* \param renderer The SDL renderer used to draw the object.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Draw(SDL_Renderer *renderer, float dt);
	/**
	* \fn void Asteroid::Draw(SDL_Renderer *renderer, float dt)
	* \brief A function that is used to draw the asteroids based on their position
	* \return Vector3 containing the position of the Asteroid
	*/
	Vector3 GetPosition();
	/**
	* \fn void Asteroid::SetKillFlag(bool isKilled)
	* \brief A function that is used to draw the asteroids based on their position
	* \param isKilled wether or not asteroid has been killed and should be displayed
	*/
	void SetKillFlag(bool isKilled);
	/**
	* \fn void Asteroid::GetKillFlag(SDL_Renderer *renderer, float dt)
	* \brief A function that is used to draw the asteroids based on their position
	* \return bool wether or not the asteroid has been killed and should be displayed
	*/
	bool GetKillFlag();
protected:
	bool _killFlag = false;
	float _speedY = 100.0f;
	float _speedX = 33.0f;
	Vector4 _color;
};