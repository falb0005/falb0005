#pragma once
#include "GameObject.h"
#include "MathUtils.h"

class Player : public GameObject
{
public:
	void Initialize();
	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);
protected:
	Vector2 pos;
	Vector2 endPointOffset;
	Vector2 transformedEndPoint;
	float speed, rotationSpeed;
};

