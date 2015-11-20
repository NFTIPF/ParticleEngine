#pragma once
#include "Particle.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Algorithms.h"

class ParticleSystem
{
public:
	ParticleSystem(sf::Vector2f pos,sf::Vector2f systemS, std::string texturePath);
	~ParticleSystem();
	void addParticle();
	//void draw(sf::RenderWindow& window);
	void draw(sf::RenderTexture& texture);
	void update();
	void init();
	void setMousePos(const sf::Vector2i& mP);
	void doFrame(sf::RenderTexture& window); //function for threading
	sf::Vector2f getPosition();
	void setMouseGravity(const float& newGravity);
	float getMouseGravity();
	
private:
	std::vector <Particle*> particles;
	sf::CircleShape particle; 
	std::vector<sf::Vertex> vertices;
	sf::Vector2f origin;
	int emmitanceRate;
	int numParticles;
	int currentIndex;
	sf::Vector2f systemForce;
	sf::Vector2i mousePos;
	sf::Texture texture;
	sf::Vertex tmp;
	sf::Vector2f systemSize;
	float mouseGravity;

};