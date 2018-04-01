#include "Particle.h"
#include <cmath>
#include <iostream>

Particle::Particle() :
mPosition(Vector2f(0.0f, 0.0f)),
mMass(10.0f){}

Particle::Particle(const Vector2f& position, const float& mass) :
mPosition(position),
mMass(mass){}

void Particle::update(const Time& dt)
{
	Vector2f prevPosition = mPosition;
	mPosition += mVelocity*dt.asSeconds() + 0.45f*(getTotalForce() / mMass) * (float)pow(dt.asSeconds(), 2.0f); 
	mVelocity = (mPosition - prevPosition) / dt.asSeconds();
}

Vector2f Particle::getTotalForce() const
{
	Vector2f totalForce(0,0);
	for (const Vector2f & force : mForces)
		totalForce += force;
	return totalForce;
}

vector<Vector2f> Particle::getForces() const { return mForces; }
void Particle::addForce(const Vector2f & force) { mForces.push_back(force); }
void Particle::clearForces() { mForces.clear(); }
void Particle::setPosition(const Vector2f& pos) { this->mPosition = pos; }
const Vector2f& Particle::getPosition() { return this->mPosition; }
void Particle::setVelocity(const Vector2f& vel) { mVelocity = vel; }
const Vector2f& Particle::getVelocity() { return mVelocity; }