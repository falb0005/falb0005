#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Initialize();

	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);
	void Set_Position(float x, float y);
	Vector3 Get_Position();

protected:
	Vector2 _endPointOffset;
	float _speed;
	float _rotationSpeed;
};