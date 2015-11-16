#include "Particle.h"
#include <stdlib.h>
#include <iostream>


Particle::Particle(sf::Vector2f l)
{
	reset();
	position = l;
	lifeSpan = 0;
}

Particle::~Particle()
{
}

void Particle::reset()
{
	float randomX = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));            //"random" floats
	float randomY = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(randomX, randomY);
}

void Particle::activate(const int& amount)
{
	lifeSpan = amount;
}
void Particle::applyForce(const sf::Vector2f& force) 
{
	velocity += force;
}

void Particle::update()
{
	velocity += acceleration;
	position += velocity;
	lifeSpan -= 1;
}

void Particle::draw(sf::RenderWindow& window){

	//p.setOutlineThickness(1);
	//p.setOutlineColor(sf::Color(0, 0, 0, lifeSpan));
	//std::cout << velocity.y << std::endl;

	//window.draw(p);
}




bool Particle::isDead(){
	if (lifeSpan < 1)
		return true;
	else
		return false;
}

void Particle::setPosition(const sf::Vector2f& newPos)
{
	position = newPos;
}

sf::Vector2f Particle::getPosition()
{
	return position;
}

float Particle::getOpacity()
{
	return lifeSpan;
}

