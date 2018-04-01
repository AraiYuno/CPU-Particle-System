#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;
using namespace std;

float lerp(const float & a, const float & b, const float & t);
float lerpFast(const float & a, const float & b, const float & t);
float getNorm(const Vector2f & v);
float getDistance(const Vector2f& v1, const Vector2f& v2);
float clamp(const float& value, const float& min, const float& max);
