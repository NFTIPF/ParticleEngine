#include "ParticleSystem.h"
#include <iostream>
#define PI 3.1415
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
	emmitanceRate = 50;
	numParticles = 30000;
	currentIndex = 0;
	systemForce = sf::Vector2f(-.00f, -.03f);
	particle.setRadius(2);
	circleShader.loadFromFile("circleShader.frag", sf::Shader::Fragment);
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
	origin =(sf::Vector2f)mousePos;
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
		if (particles[ii]->getPosition().y > 700)
		{
			particles[ii]->activate(0); //activate as dead
		}
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

void makeCircle(const sf::Vertex& v, std::vector<sf::Vertex>& va)
{
	
	std::vector<sf::Vertex> verts;
	sf::Vertex tmp;
	for (int ii = 0; ii < 10; ii++)
	{
		tmp.position.x = cos((2 * PI * ii) / 10) * 3 + v.position.x;
		tmp.position.y = sin((2 * PI * ii) / 10) * 3 + v.position.y;
		tmp.color = v.color;
		va.push_back(tmp);
	}
	
}

void ParticleSystem::setMousePos(const sf::Vector2i& mP)
{
	mousePos = mP;
	mousePos.y
}
void ParticleSystem::draw(sf::RenderTexture& window)
{
	//sf::Color colors[30000];
	//float Xpositions[30000];
	//float Ypositions[30000];
	sf::VertexArray v(sf::Points, 10);
	sf::Vertex tmp;
	for (unsigned int ii = particles.size() - 1; ii > 0; ii--)
	{
		if (!particles[ii]->isDead())
		{
			float randomR = 210 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 40));
			float randomG = 90 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 20));
			float randomB = 35 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));
			//Xpositions[ii] = particles[ii]->getPosition().x;
			//Ypositions[ii] = particles[ii]->getPosition().y;
			//colors[ii] = sf::Color(randomR, randomG, randomB, particles[ii]->getOpacity());
			tmp.position = particles[ii]->getPosition();
			tmp.color = sf::Color(randomR, randomG, randomB, particles[ii]->getOpacity());
			//makeCircle(tmp, vertices);
			vertices.push_back(tmp);
		}
	}
	
	window.draw(&vertices[0], vertices.size(), sf::Points);
	vertices.clear();
}

ParticleSystem::~ParticleSystem()
{
	for (int ii = 0; ii < particles.size(); ii++)
	{
		//delete particles[ii];
	}
}

void ParticleSystem::doFrame(sf::RenderTexture& window) //function for threading
{
	//std::thread t1(&ParticleSystem::update, this);
	//t1.detach();
	draw(window);
}