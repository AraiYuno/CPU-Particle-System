#include "ParticleSystem.h"
#include "Program.h"
#include "Helper.h"
#include <cmath>


ParticleSystem::ParticleSystem(unsigned int numParticles, float width, float height) :
mParticles(),mVerticies(Points, numParticles), winX(width), winY(height), mNumParticles(numParticles),
bIsDirectlyInteracting(true), bIsWrappingParticlesOnScreen(true), bParticleDrag(false)
{
	float spacing = 1.0;
	int sqrtParticles = sqrt(mNumParticles);
	for (int i = 0; i < sqrtParticles; i++)
	{
		for (int j = 0; j < sqrtParticles; j++)
		{
			Particle newParticle;
			newParticle.setPosition(Vector2f(i*spacing, j*spacing) - Vector2f(sqrtParticles / 2 * spacing, sqrtParticles / 2 * spacing));
			mParticles.push_back(newParticle);
		}
	}
}

void ParticleSystem::update(Time& dt)
{
	Vector2f mousePosition = Program::Instance()->getMousePosition();
	bool mouseLeftClick = Program::Instance()->getMouseButtonState(Mouse::Left);
	bool mouseRightClick = Program::Instance()->getMouseButtonState(Mouse::Right);

	for (unsigned int i = 0; i < mParticles.size(); i++)
	{
		Particle& pParticle = mParticles.at(i);

		if (bIsDirectlyInteracting)	
		{
			if (mouseLeftClick)
				pParticle.addForce((mousePosition - pParticle.getPosition())* (float)(500000) / (pow(getDistance(mousePosition, pParticle.getPosition()) + 10, 2)));
			else if (mouseRightClick)
				pParticle.addForce((pParticle.getPosition() - mousePosition)* (float)(500000) / (pow(getDistance(mousePosition, pParticle.getPosition()) + 10, 2)));
		}

		if (bParticleDrag)
			pParticle.addForce(-pParticle.getVelocity() * (float)10);		
		pParticle.update(dt);												

		if (bIsWrappingParticlesOnScreen)
		{
			Vector2f pPos = pParticle.getPosition();
			Vector2f winPos = Program::Instance()->getWorldView()->getCenter();

			if (pPos.x < winPos.x - (winX / 2.0))
				pParticle.setPosition(Vector2f(winPos.x + winX / 2.0, pPos.y));
			else if (pPos.x > winPos.x + (winX / 2.0))
				pParticle.setPosition(Vector2f(winPos.x - winX / 2.0, pPos.y));

			if (pPos.y < winPos.y - (winY / 2.0))
				pParticle.setPosition(Vector2f(pPos.x, winPos.y + winY / 2.0));
			else if (pPos.y > winPos.y + (winY / 2.0))
				pParticle.setPosition(Vector2f(pPos.x, winPos.y - winY / 2.0));
		}

		mVerticies[i].position = pParticle.getPosition();	
		int red = 50;  // Change the colours based on the velocity of the particles
		int green = 0; 
		int blue = clamp(255 - getNorm(pParticle.getVelocity()), 0, 255);;
		mVerticies[i].color = Color(red, green, blue);
		pParticle.clearForces();									
	}
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();	
	states.texture = nullptr;				
	target.draw(mVerticies, states);

}


void ParticleSystem::resetParticles()
{
	float spacing = 1;
	int sqrtParticles = sqrt(mNumParticles);
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles.at(i).setPosition(Vector2f((i%sqrtParticles)*spacing, (i/sqrtParticles)*spacing) - Vector2f(sqrtParticles / 2 * spacing, sqrtParticles / 2 * spacing));
		mParticles.at(i).setVelocity(Vector2f(0, 0));
	}
}