#include "Missile.h"
#include <stdio.h>
#include <math.h>
#include <SDL.h>

Missile::Missile() : GameObject()
{
	_transform.position = { 0.0f, 0.0f, 0.0f };
	_transform.rotation = { 0.0f, 0.0f, 0.0f };
	_directionVector = { 0.0f, 0.0f, 0.0f };
	_speed = 250;
	_missileSpeed = 0;
}

Missile::~Missile()
{

}

void Missile::Initialize()
{

}

void Missile::Update(float dt)
{
	_transform.position.y += (_speed * (_directionVector.y*0.1f)) * (1 * dt);
	_transform.rotation.y += (_speed * (_directionVector.y*0.1f)) * (1 * dt);
	_transform.position.x += (_speed * (_directionVector.x*0.1f)) * (1 * dt);
	_transform.rotation.x += (_speed * (_directionVector.x*0.1f)) * (1 * dt);
	if (_transform.position.y < 0){
		int ydif = 0;
		ydif = _transform.position.y - _transform.rotation.y;
		_transform.position.y = 480;
		_transform.rotation.y = _transform.position.y - ydif;
	}
	else if (_transform.position.y > _screenHeight){
		int ydif = 0;
		ydif = _transform.position.y - _transform.rotation.y;
		_transform.position.y = 0;
		_transform.rotation.y = _transform.position.y - ydif;
	}
	else if (_transform.position.x < 0){
		int xdif = 0;
		xdif = _transform.position.x - _transform.rotation.x;
		_transform.position.x = 640;
		_transform.rotation.x = _transform.position.x - xdif;
	}
	else if (_transform.position.x > _screenWidth){
		int xdif = 0;
		xdif = _transform.position.x - _transform.rotation.x;
		_transform.position.x = 0;
		_transform.rotation.x = _transform.position.x - xdif;
	}
}

void Missile::Draw(SDL_Renderer *renderer, float dt)
{
	SDL_RenderDrawLine(renderer, _transform.position.x, _transform.position.y, _transform.rotation.x, _transform.rotation.y);
}

void Missile::Set_Position(Vector3 position)
{
	_transform.position = position;
}

Vector3 Missile::Get_Position()
{
	return this->_transform.position;
}

void Missile::Set_MissileSpeed(int missileSpeed)
{
	_missileSpeed = missileSpeed;
}

int Missile::Get_MissileSpeed()
{
	return _missileSpeed;
}


void Missile::Set_DirectionVector(Vector3 directionVector)
{
	_directionVector = directionVector;
}

Vector3 Missile::Get_DirectionVector()
{
	return _directionVector;
}

Vector3 Missile::Get_MissileRotation()
{
	return _transform.rotation;
}

void Missile::Set_MissileRotation(Vector3 rotation)
{
	_transform.rotation = rotation;
}