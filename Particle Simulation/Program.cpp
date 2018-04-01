#include "Program.h"
#include <algorithm>
#include <functional>
#include "Helper.h"


const Time Program::TimePerFrame = seconds(1.0f/60.f);
Program* Program::s_pInstance = nullptr;

Program::Program(): window(VideoMode(1000, 1000), "Kyle Ahn - Particle System"), mFont(), mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0),
					  mWorldView(Vector2f(0.f, 0.f), Vector2f(1000, 1000)), mUIView(Vector2f(500, 500), Vector2f(1000, 1000)), camPos(0, 0),
					  windowInFocus(true), buttonCooldown(seconds(0.1f)), buttonTimer(), bDirectInteraction(true),
					  particleNumberOptions({ { 10 * 10, 100 * 100, 200 * 200, 300 * 300, 400 * 400, 600 * 600 } }), particleNumberSelector(2)
{
	this->window.setKeyRepeatEnabled(false);

	cout << "Real-Time User Interaction" << endl;
	cout << "===============================" << endl;
	cout << "||    Program Instruction    ||" << endl;
	cout << "===============================" << endl;
	cout << "1. Click left cursor to attract particles." << endl;
	cout << "2. Click right cursor to push away particles." << endl;
	cout << "3. Press R to reset." << endl;
	cout << "4. Right arrow key button to increase the number of particles." << endl;
	cout << "5. Left arrow key button to decrease the number of particles." << endl;

	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
	mTextBackground.setSize(Vector2f(125.f, 35.f));
	mTextBackground.setFillColor(Color(110, 110, 110, 80));
	this->particleSystem = new ParticleSystem(particleNumberOptions.at(this->particleNumberSelector), 1000, 1000);				///< Initialize particle system with the desired number of particles and window size
}

void Program::initiate()
{
	Clock clock;
	Time timeUnit = Time::Zero;
	while (this->window.isOpen())
	{
		Time elapsedTime = clock.restart();
		timeUnit += elapsedTime;
		while (timeUnit > TimePerFrame)
		{
			timeUnit -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
	this->window.close();
}

void Program::processEvents()
{

	Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			this->window.close();
		if (event.type == Event::GainedFocus)
			this->windowInFocus = true;
		else if (event.type == Event::LostFocus)
			this->windowInFocus = false;
	}

	// User Interaction
	if (this->buttonTimer.getElapsedTime().asSeconds() >= buttonCooldown.asSeconds())
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (this->particleNumberSelector > 0)
				this->particleNumberSelector--;
			delete this->particleSystem;
			this->particleSystem = new ParticleSystem(particleNumberOptions.at(this->particleNumberSelector), 1000, 1000);
			cout << "Number of Particles: " << particleNumberOptions.at(this->particleNumberSelector) << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (this->particleNumberSelector < particleNumberOptions.size() -1)
				this->particleNumberSelector++;
			delete this->particleSystem;
			this->particleSystem = new ParticleSystem(particleNumberOptions.at(this->particleNumberSelector), 1000, 1000);
			cout << "Number of Particles: " << particleNumberOptions.at(this->particleNumberSelector) << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			cout << "Particles are reset" << endl;
			this->particleSystem->resetParticles();
		}

		this->buttonTimer.restart();
	}
}

void Program::update(Time dTime)
{
	if (this->windowInFocus)
		this->particleSystem->update(dTime);
}

void Program::render()
{
	this->window.clear();
	this->window.setView(mWorldView);
	this->window.draw(*this->particleSystem);
	this->window.setView(mWorldView);
	this->window.display();
}