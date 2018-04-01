#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;


class Program : private NonCopyable
{
private:
	void processEvents();
	void update(Time dtTime);
	void render();

	static Program* s_pInstance;
	static const Time TimePerFrame;
	RenderWindow window;
	Font mFont;
	Text mStatisticsText;
	Time mStatisticsUpdateTime;
	size_t mStatisticsNumFrames;
	RectangleShape mTextBackground;
	View mUIView;
	View mWorldView;
	Vector2f camPos;
	ParticleSystem* particleSystem;
	bool windowInFocus;
	Clock buttonTimer;
	Time buttonCooldown;
	bool bDirectInteraction;
	vector<int> particleNumberOptions;
	int	particleNumberSelector;

public:
	static Program* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new Program();
		return s_pInstance;
	}
	Program();
	void initiate();
	RenderWindow* getWindow() { return &this->window; }
	View* getWorldView() { return &mWorldView; }
	bool getMouseButtonState(Mouse::Button button) { return Mouse::isButtonPressed(button); }
	Vector2f getMousePosition() { return this->window.mapPixelToCoords((Mouse::getPosition(this->window))); }
};
typedef Program;
