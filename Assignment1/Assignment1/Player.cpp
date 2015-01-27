#include "Player.h"
#include <stdio.h>
#include <math.h>
#include <SDL.h>

Player::Player() : GameObject()
{
	_transform.position = { 320.0f, 240.0f, 0.0f };
	_endPointOffset = { 0, 10 };
	_speed = 10000;
	_rotationSpeed = 100;
}

Player::~Player()
{
}

void Player::Initialize()
{

}

void Player::Update(float dt)
{
	static float rotationDegrees = 10.0f;
	rotationDegrees += (_rotationSpeed * dt);
	rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

	float rotationRadians = MathUtils::ToRadians(rotationDegrees);

	Vector2 rotatedOffset =
	{
		_endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
		_endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
	};
	
	_transform.rotation = { this->_transform.position.x + rotatedOffset.x, this->_transform.position.y + rotatedOffset.y, 0 };
}

void Player::Draw(SDL_Renderer *renderer, float dt)
{
	SDL_RenderDrawLine(renderer, _transform.position.x, _transform.position.y, _transform.rotation.x, _transform.rotation.y);
}

void Player::Set_Position(float x, float y){
	_transform.position.x = x;
	_transform.position.y = y;
}

Vector3 Player::Get_Position(){
	return this->_transform.position;
}