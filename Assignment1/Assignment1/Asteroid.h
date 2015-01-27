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

protected:
	float _speedY = 50.0f;
	float _speedX = 25.0f;
	Vector4 color;
};