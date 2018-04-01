#include "Helper.h"

float lerp(const float & a, const float & b, const float & t) { return (1 - t)*a + t * b; }
float getNorm(const sf::Vector2f & v) { return sqrt(pow(v.x, 2) + pow(v.y, 2)); }
float getDistance(const sf::Vector2f& v1, const sf::Vector2f& v2) { return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2)); }
float lerpFast(const float & a, const float & b, const float & t) { return a + t*(b - a); }
float clamp(const float& value, const float& min, const float& max)
{
	float result;
	if (value > max)
		result = max;
	else if (value < min)
		result = min;
	else
		result = value;
	return result;
}