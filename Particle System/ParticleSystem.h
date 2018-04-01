#pragma once
#include "Particle.h"

using namespace sf;
using namespace std;


class ParticleSystem : public Drawable, Transformable
{
private:
	virtual void draw(RenderTarget& target, RenderStates states) const;
	vector<Particle> mParticles;
	VertexArray	mVerticies;
	int	winX;
	int winY;
	int	mNumParticles;
	bool bIsDirectlyInteracting;
	bool bIsWrappingParticlesOnScreen;
	bool bParticleDrag;

public:
	ParticleSystem(unsigned int numParticles, float width, float height);
	void update(Time& dt);
	void resetParticles();
};