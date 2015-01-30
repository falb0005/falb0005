#include "MathUtils.h"
#include <math.h>

float MathUtils::ToDegrees(float radians)
{
	float radiansToDegrees = 180.0f / 3.1415926535f;
	return radians * radiansToDegrees;
}

float MathUtils::ToRadians(float degrees)
{
	float degreesToRadians = 3.1415926535f / 180.0f;
	return degrees * degreesToRadians;
}

float MathUtils::CalculateShipSlope(int posX, int posY, int posXOffset, int posYOffset){
	float m = 0, b = 0;
	m = (float)(posYOffset - posY) / (float)(posXOffset - posX);
	return m;
}

float MathUtils::CalculateShipXVector(int posX, int posXOffset)
{
	float x = 0;
	x = (float)(posXOffset - posX);
	return x;
}

float MathUtils::CalculateShipYVector(int posY, int posYOffset)
{
	float y = 0;
	y = (float)(posYOffset - posY);
	return y;
}

float MathUtils::CalculateDistance(float x1, float x2, float y1, float y2)
{
	return sqrt(pow(x2 - x1, 2)+pow(y2 - y1, 2));
}