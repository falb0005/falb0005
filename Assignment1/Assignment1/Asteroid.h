#pragma once

#include "GameObject.h"

class Asteroid : GameObject 
{
public:
	Asteroid();
	~Asteroid();

	void Initialize();
	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);
	Vector3 Get_Position();
	bool _killedFlag = false;
protected:
	float _speedY = 50.0f;
	float _speedX = 25.0f;
	Vector4 color;
};