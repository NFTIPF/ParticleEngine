#include "SFML/Graphics.hpp"
#include "Particle.h"
#include "ParticleSystem.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <time.h>
#include <thread>
#include <future>
#include <chrono>

std::string intToString(int toConvert)
{
	std::stringstream ss;
	ss << toConvert;
	return ss.str();
}


int main()
{
	sf::Shader shader;
	shader.loadFromFile("blur.frag", sf::Shader::Fragment);
	srand(static_cast <unsigned> (time(0)));

	sf::RenderWindow window(sf::VideoMode(800, 800), "Partic-LE");
	window.setFramerateLimit(60);
	
	ParticleSystem ps2(sf::Vector2f(200, 700));
	ParticleSystem ps(sf::Vector2f(600, 700));

	sf::Clock clock;
	sf::Font myfont;
	myfont.loadFromFile("arial.ttf");
	float lastTime = 0;
	sf::Text fpsText("", myfont);
	fpsText.setCharacterSize(20);
	fpsText.setStyle(sf::Text::Bold);
	fpsText.setPosition(0, 0);
	fpsText.setColor(sf::Color::Blue);
	

	sf::RenderTexture destination; //drawing target
	sf::RenderTexture source;	//source for shader
	if (!destination.create(800, 800))
		return -1;

	shader.setParameter("resolution", destination.getSize().x, destination.getSize().y);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		destination.clear(sf::Color::White);

		/*
		auto t1 = std::async(&ParticleSystem::update, ps);
		auto t2 = std::async(&ParticleSystem::update, ps2);

		while (true)
		{
			auto s1 = t1.wait_for(std::chrono::seconds(0));
			auto s2 = t2.wait_for(std::chrono::seconds(0));

			if (s1 == std::future_status::ready)
			{
				ps2.draw(window);
			}
			if (s2 == std::future_status::ready)
			{
				ps2.draw(window);
			}
			if (s2 == std::future_status::ready && s1 == std::future_status::ready)
			{
				break;
			}
		}
		*/


	
		//t1.join();
		//t2.join();
		ps.update();
		ps2.update();
		ps.draw(destination);
		ps2.draw(destination);

		destination.display(); 

		sf::Texture source = destination.getTexture();
		shader.setParameter("blur_radius", 3.0f);
		shader.setParameter("texture", source);
		sf::Sprite mySprite(destination.getTexture());
		window.draw(mySprite, &shader);
		
		
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / (currentTime - lastTime);
		lastTime = currentTime;
		fpsText.setString(intToString(fps));
		window.draw(fpsText);

		window.display();
	}



	return 0;
}