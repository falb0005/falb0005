/**
* \class GameObject.h
* \brief A class that represents a single abstracted object that can
* be placed and manipulated in the world.
* \author Justin Wilkinson
* \date January 29, 2014
*/
#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

#include "MathUtils.h"

struct SDL_Renderer;

class GameObject
{
public:
	/**
	* \fn void GameObject::Initialize() = 0
	* \brief A virtual function that we’ll use as to define how our
	* object is initialized.
	*/
	virtual void Initialize() = 0;
	/**
	* \fn void GameObject::Update(float dt) = 0
	* \brief A virtual function that we’ll use as to define how our
	* object updated.
	* \param dt The time in fractions of a second since the last pass.
	*/
	virtual void Update(float dt) = 0;
	/**
	* \fn void GameObject::Draw(SDL_Renderer *renderer, float dt)
	* \brief A virtual function that we’ll use as to define how our
	* object is drawn to the screen.
	* \param renderer The SDL renderer used to draw the object.
	* \param dt The time in fractions of a second since the last pass.
	*/
	virtual void Draw(SDL_Renderer *renderer, float dt) = 0;

	/**
	* \fn void GameObject::~GameObject()
	* \brief GameObject Deconstructor
	*/
	~GameObject();

protected:
	/**
	* \fn void GameObject::~GameObject()
	* \brief GameObject Default Constructor
	*/
	GameObject();

	Transform _transform;
};