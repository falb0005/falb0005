#include "Player.h"
#include <math.h>
#include <SDL.h>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void Player::Initialize()
{
	// Using the default member-wise initializer for our new struct.
	pos = { 100.0f, 100.0f };
	endPointOffset = { 10.0f, 0.0f };
	speed = 10.0f;
	rotationSpeed = 360.0f;
}

void Player::Update(float dt)
{
	// Draw the point.
	//SDL_RenderDrawPoint(renderer, posX, posY);

	static float rotationDegrees = 10.0f;
	rotationDegrees += (rotationSpeed * dt);
	rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

	float rotationRadians = MathUtils::ToRadians(rotationDegrees);

	Vector2 rotatedOffset =
	{
		endPointOffset.x * cosf(rotationRadians) + endPointOffset.y * sinf(rotationRadians),
		endPointOffset.x * sinf(rotationRadians) - endPointOffset.y * cosf(rotationRadians)
	};

	transformedEndPoint = { pos.x + rotatedOffset.x, pos.y + rotatedOffset.y };

	
}

void Player::Draw(SDL_Renderer *renderer, float dt)
{
	SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);
}