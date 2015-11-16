#pragma once
#include "Particle.h"
#include <vector>
#include <SFML/Graphics.hpp>

class ParticleSystem
{
public:
	ParticleSystem(sf::Vector2f);
	~ParticleSystem();
	void addParticle();
	//void draw(sf::RenderWindow& window);
	void draw(sf::RenderTexture& texture);
	void update();
	void init();

	void doFrame(sf::RenderWindow& window); //function for threading
	
private:
	std::vector <Particle*> particles;
	sf::CircleShape particle;
	sf::Vector2f origin;
	int emmitanceRate;
	int numParticles;
	int currentIndex;
	sf::Vector2f systemForce;

};