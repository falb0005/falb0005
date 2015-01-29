#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Initialize();

	void Update(float);
	void Draw(SDL_Renderer *, float);
	void Set_Position(Vector3);
	Vector3 Get_Position();
	void Set_PlayerSpeed(int);
	int Get_PlayerSpeed();
	Vector3 Get_DirectionVector();
	void Set_DirectionVector(Vector3);
	Vector3 Get_PlayerRotation();
	void Set_PlayerRotation(Vector3);


protected:
	Vector3 _directionVector;
	int _playerSpeed;
	float _speed;
	float _rotationSpeed;
	int _screenWidth = 640;
	int _screenHeight = 480;
};