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

ParticleSystem::ParticleSystem(sf::Vector2f position, sf::Vector2f systemS)
{
	origin = position;
	emmitanceRate = 100;
	numParticles = 10000;
	currentIndex = 0;
	systemForce = sf::Vector2f(-.00f, .00f);
	particle.setRadius(2);
	circleShader.loadFromFile("circleShader.frag", sf::Shader::Fragment);
	texture.loadFromFile("fire.png");
	systemSize = systemS;
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		origin = (sf::Vector2f)mousePos;
		if (particles.size() - currentIndex + 1 < emmitanceRate) //if the emmitance rate would attempt to call out of bounds thing, reset currentIndex
		{
			currentIndex = 0;
		}

		for (unsigned int ii = 0; ii < emmitanceRate; ii++) //iterate through particles and activate them
		{
			particles[ii + currentIndex]->reset();
			particles[ii + currentIndex]->activate(255);
			particles[ii + currentIndex]->setPosition(origin);
		}
		currentIndex += emmitanceRate;
		
	}
	sf::Vector2f particleForce; 
	for (unsigned int ii = 0; ii < particles.size(); ii++)
	{
		if (!particles[ii]->isDead()) //if its not dead
		{
			if (particles[ii]->getPosition().y > systemSize.y)
			{
				particles[ii]->activate(0); //activate as dead
			}
			particles[ii]->applyForce(systemForce);
			particleForce.x = particles[ii]->getPosition().x - origin.x;
			//if (particleForce.x < 0)
			//	particleForce.x *= .*-particleForce.x;
			//else
			//	particleForce.x *= particleForce.x;
			particleForce.x /= -3000;
			particleForce.x = Clamp(particleForce.x, -.5f, 0.5f);
			particleForce.y = 0;
			//particles[ii]->applyForce(particleForce);
			//particles[ii]->applyForce(sf::Vector2f(0, -.06));
			particles[ii]->update();
		}
	}
	
}

void makeCircle(const sf::Vertex& v, std::vector<sf::Vertex>& va)
{
	
	std::vector<sf::Vertex> verts;
	sf::Vertex tmp[4];
	int halfsquareSize = 32;
	tmp[0].position = sf::Vector2f(halfsquareSize + v.position.x, halfsquareSize + v.position.y);
	tmp[1].position = sf::Vector2f(-halfsquareSize + v.position.x, halfsquareSize + v.position.y);
	tmp[2].position = sf::Vector2f(halfsquareSize + v.position.x, -halfsquareSize + v.position.y);
	tmp[3].position = sf::Vector2f(-halfsquareSize + v.position.x, -halfsquareSize + v.position.y);

	tmp[0].texCoords = sf::Vector2f(64, 64);
	tmp[1].texCoords = sf::Vector2f(0, 64);
	tmp[2].texCoords = sf::Vector2f(64, 0);
	tmp[3].texCoords = sf::Vector2f(0, 0);

	va.push_back(tmp[0]);
	va.push_back(tmp[1]);
	va.push_back(tmp[3]);
	va.push_back(tmp[2]);
	/*
	for (int ii = 0; ii < 10; ii++)
	{
		tmp.position.x = cos((2 * PI * ii) / 10) * 3 + v.position.x;
		tmp.position.y = sin((2 * PI * ii) / 10) * 3 + v.position.y;
		tmp.color = v.color;
		va.push_back(tmp);
	}
	*/
	
}

void ParticleSystem::setMousePos(const sf::Vector2i& mP)
{
	mousePos = mP;
	mousePos.y = systemSize.y - mousePos.y;
}
void ParticleSystem::draw(sf::RenderTexture& window)
{
	//sf::Color colors[30000];
	//float Xpositions[30000];
	//float Ypositions[30000];
	
	for (unsigned int ii = particles.size() - 1; ii > 0; ii--)
	{
		if (!particles[ii]->isDead())
		{
			//float randomR = 210 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 40));
			//float randomG = 90 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 20));
			//float randomB = 35 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));
			//Xpositions[ii] = particles[ii]->getPosition().x;
			//Ypositions[ii] = particles[ii]->getPosition().y;
			//colors[ii] = sf::Color(randomR, randomG, randomB, particles[ii]->getOpacity());
			tmp.position = particles[ii]->getPosition();
			//tmp.color = sf::Color(randomR, randomG, randomB, particles[ii]->getOpacity());
			makeCircle(tmp, vertices);
			//vertices.push_back(tmp);
		}
	}
	if (vertices.size() > 1)
	{
		window.draw(&vertices[0], vertices.size(), sf::Quads, &texture);
		vertices.clear();
	}

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