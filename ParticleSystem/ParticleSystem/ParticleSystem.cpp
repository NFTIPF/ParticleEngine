#include "ParticleSystem.h"
#include <iostream>

float Clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}
	if (value > max)
	{
		return max;
	}
	if(min <= value || max >= value)
	{
	    return value;
	}

	return value; // default return
}

ParticleSystem::ParticleSystem(sf::Vector2f position)
{
	origin = position;
	emmitanceRate = 25;
	numParticles = 5000;
	currentIndex = 0;
	systemForce = sf::Vector2f(-.00f, -.03f);
	particle.setRadius(2);
	
	init();
}

void ParticleSystem::init()
{
	for (unsigned int ii = 0; ii < numParticles; ii++)
	{
		addParticle();
	}
}
void ParticleSystem::addParticle()
{
	particles.push_back(new Particle(origin));
}

void ParticleSystem::update()
{
	if (particles.size() - currentIndex+1 < emmitanceRate) //if the emmitance rate would attempt to call out of bounds thing, reset currentIndex
	{
		currentIndex = 0;
	}

	for (unsigned int ii = 0; ii < emmitanceRate; ii++) //iterate through particles and activate them
	{
		particles[ii + currentIndex]->reset();
		particles[ii + currentIndex]->activate(255);
		particles[ii + currentIndex]->setPosition(origin);
	}
	sf::Vector2f particleForce;
	for (unsigned int ii = 0; ii < particles.size(); ii++)
	{
		if (!particles[ii]->isDead()) //if its not dead
		{
			particles[ii]->applyForce(systemForce);
			particleForce.x = particles[ii]->getPosition().x - origin.x;
			//if (particleForce.x < 0)
			//	particleForce.x *= .*-particleForce.x;
			//else
			//	particleForce.x *= particleForce.x;
			particleForce.x /= -3000;
			particleForce.x = Clamp(particleForce.x, -.5f, 0.5f);
			particleForce.y = 0;
			particles[ii]->applyForce(particleForce);
			particles[ii]->update();
		}
	}
	currentIndex += emmitanceRate;
}

void ParticleSystem::draw(sf::RenderTexture& window)
{
	for (unsigned int ii = particles.size() - 1; ii > 0; ii--)
	{
		if (!particles[ii]->isDead())
		{
			particle.setPosition(particles[ii]->getPosition());
			float randomR = 210 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 40));
			float randomG = 90 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 20));
			float randomB = 35 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));
			particle.setFillColor(sf::Color(randomR, randomG, randomB, particles[ii]->getOpacity()));
			window.draw(particle);
		}
	}
}

ParticleSystem::~ParticleSystem()
{
	for (int ii = 0; ii < particles.size(); ii++)
	{
		delete particles[ii];
	}
}

void ParticleSystem::doFrame(sf::RenderWindow& window) //function for threading
{
	update();
	//draw();
}