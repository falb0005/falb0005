#pragma once

#include "GameObject.h"

class Missile : public GameObject
{
public:
	Missile();
	~Missile();

	void Initialize();

	void Update(float);
	void Draw(SDL_Renderer *, float);
	void Set_Position(Vector3);
	Vector3 Get_Position();
	void Set_MissileSpeed(int);
	int Get_MissileSpeed();
	Vector3 Get_DirectionVector();
	void Set_DirectionVector(Vector3);
	Vector3 Get_MissileRotation();
	void Set_MissileRotation(Vector3);


protected:
	Vector3 _directionVector;
	int _missileSpeed;
	float _speed;
	int _screenWidth = 640;
	int _screenHeight = 480;
};