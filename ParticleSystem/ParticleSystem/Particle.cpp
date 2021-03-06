#include "Particle.h"
#include <stdlib.h>
#include <iostream>


Particle::Particle(sf::Vector2f l)
{
	reset();
	position = l;
	originalPosition = position;
	lifeSpan = 255;
	dying = false;
	float randomX = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1920));            //"random" floats
	float randomY = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1080));
	position = sf::Vector2f(randomX, randomY);
}

Particle::~Particle()
{
}


void Particle::reset()
{
	float randomX = -8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 16));            //"random" floats
	float randomY = -8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 16));
	float angle = atan(randomY / randomX)*2;
	float speed = 3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));
	sf::Vector2f velVector = sf::Vector2f(cos(angle)*speed, sin(angle)*speed);
	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	//velocity = velVector;
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
	if (dying)
	{
		lifeSpan -= 1;
	}
	clamp(velocity.x, -10, 10);
	clamp(velocity.y, -10, 10);

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

sf::Vector2f Particle::getOrigin(){
	return originalPosition;
}

float Particle::getOpacity()
{
	return lifeSpan;
}



