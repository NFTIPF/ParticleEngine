#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>

class Particle
{
public:
	Particle(sf::Vector2f l);
	~Particle();
	void update();
	void draw(sf::RenderWindow& window);
	void applyForce(const sf::Vector2f& force);
	void activate(const int& amound);
	void reset();


	void revive(const sf::Vector2f& l);
	bool isDead();

	void setPosition(const sf::Vector2f& newPos);
	sf::Vector2f getPosition();
	float getOpacity();

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float lifeSpan;
};