#include "Asteroid.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <SDL.h>

Asteroid::Asteroid() : GameObject()
{

}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialize()
{
	float number;
	int number1;

	number1 = rand() % 10 + 1;
	_transform.scale.x = 20;
	_transform.scale.y = 20;
	number1 = (rand() / 100);
	//printf("x: %d\n", number1);
	color.w = number1;//red
	number1 = (rand() / 100);
	//printf("x: %d\n", number1);
	color.x = number1;//blue
	number1 = (rand() / 100);
	//printf("x: %d\n", number1);
	color.y = number1;//green
	color.z = 255;//a

	/*Initiliaze position speed and driection to random values*/
	number = (float)((rand() % 100) * 0.9789687f - 50);
	number = number * 2;
	//printf("x: %f\n", number);
	_transform.position.x = number;
	number = (float)((rand() % 100) * 0.9789687f - 50);
	number = number * 2;
	//printf("y: %f\n", number);
	_transform.position.y = number;
	_transform.position.z = 0.0f;
	number = (float)((rand() % 400) * 0.9789687f - 250);
	number = number / 180;
	if (number > 0){
		number += 0.2;
	}
	else{
		number -= 0.2;
	}
	//printf("y: %f\n", number);
	_transform.rotation.x = number;
	number = (float)((rand() % 300) * 0.9789687f - 150);
	number = number / 180;
	if (number > 0){
		number += 0.7;
	}
	else{
		number -= 0.7;
	}
	//printf("y: %f\n", number);
	_transform.rotation.y = number;
	number = (float)((rand() % 300) * 0.9789687f - 150);
	_transform.rotation.z = number;

}

void Asteroid::Update(float dt)
{
	_transform.position.x += _transform.rotation.x * (dt * _speedX);
	if (_transform.position.x < 0)
	{
		_transform.position.x = 640;
	}
	else if (_transform.position.x > 640){
		_transform.position.x = 0;
	}
	_transform.position.y += _transform.rotation.y * (dt * _speedY);
	if (_transform.position.y < 0)
	{
		_transform.position.y = 480;
	}
	else if (_transform.position.y > 480){
		_transform.position.y = 0;
	}
}

void Asteroid::Draw(SDL_Renderer *renderer, float dt)
{
		SDL_SetRenderDrawColor(renderer, (int)color.w, (int)color.y, (int)color.x, (int)color.z);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 5, _transform.position.y + 5);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y + 5);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 4, _transform.position.y + 4);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y + 4);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 3, _transform.position.y + 3);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y + 3);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 2, _transform.position.y + 2);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y + 2);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 1, _transform.position.y + 1);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y + 1);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 5, _transform.position.y + 5);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 5, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 4, _transform.position.y + 4);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 4, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 3, _transform.position.y + 3);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 3, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 2, _transform.position.y + 2);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 2, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 1, _transform.position.y + 1);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 1, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 1, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 1, _transform.position.y - 1);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 2, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 2, _transform.position.y - 2);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 3, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 3, _transform.position.y - 3);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 4, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 4, _transform.position.y - 4);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 5, _transform.position.y);
		SDL_RenderDrawPoint(renderer, _transform.position.x - 5, _transform.position.y - 5);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y - 1);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 1, _transform.position.y - 1);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y - 2);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 2, _transform.position.y - 2);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y - 3);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 3, _transform.position.y - 3);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y - 4);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 4, _transform.position.y - 4);
		SDL_RenderDrawPoint(renderer, _transform.position.x, _transform.position.y - 5);
		SDL_RenderDrawPoint(renderer, _transform.position.x + 5, _transform.position.y - 5);
}