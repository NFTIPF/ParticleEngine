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
	//sf::Shader smokeShader;
	shader.loadFromFile("blur.frag", sf::Shader::Fragment);
	//smokeShader.loadFromFile("smoke.frag", sf::Shader::Fragment);
	srand(static_cast <unsigned> (time(0)));

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Partic-LE");
	window.setFramerateLimit(60);
	
	ParticleSystem ps2(sf::Vector2f(200, 700), (sf::Vector2f)window.getSize(), "smoke.png");
	ParticleSystem ps(sf::Vector2f(600, 700), (sf::Vector2f)window.getSize(), "fire.png");

	sf::Clock clock;
	sf::Time lastTime;
	sf::Time currentTime;
	sf::Font myfont;
	myfont.loadFromFile("arial.ttf");

	sf::Text fpsText("", myfont);
	fpsText.setCharacterSize(20);
	fpsText.setStyle(sf::Text::Bold);
	fpsText.setPosition(0, 0);
	fpsText.setColor(sf::Color::Blue);
	

	sf::RenderTexture destination; //drawing target
	sf::RenderTexture destination2;
	sf::Texture source;
	sf::Texture source2;
	//sf::RenderTexture source;	//source for shader
	//sf::RenderTexture source2; //swapable source for shader
	if (!destination.create(window.getSize().x, window.getSize().y))
		return -1;
	if (!destination2.create(window.getSize().x, window.getSize().y))
		return -1;

	shader.setParameter("resolution", destination.getSize().x, destination.getSize().y);
	//smokeShader.setParameter("resolution", destination2.getSize().x, destination2.getSize().y);
	std::thread t1, t2;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		destination.clear(sf::Color(0, 0, 0, 0));
		destination2.clear(sf::Color(0, 0, 0, 0));

		
		//t1 = std::thread(&ParticleSystem::update, &ps);
		//t2 = std::thread(&ParticleSystem::update, &ps2);
		//t1.detach();
		//t2.detach();
		//auto t1 = std::async(&ParticleSystem::update, ps);
		//auto t2 = std::async(&ParticleSystem::update, ps2);
		/*
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
		
		ps.setMousePos(sf::Mouse::getPosition(window));

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				ps.setMouseGravity(ps.getMouseGravity()*-1);
			}
		}
		//ps2.setMousePos(sf::Mouse::getPosition(window));
		shader.setParameter("mousePosition", (float)ps.getPosition().x, (float)ps.getPosition().y);
		//smokeShader.setParameter("mousePosition", (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
		ps.update();
		//ps2.update();

		ps.draw(destination);
		//ps2.draw(destination2);

		destination.display(); 

		source = destination.getTexture();
		//source2 = destination2.getTexture();
		
		sf::Sprite mySprite(destination.getTexture());
		//sf::Sprite mySprite2(destination2.getTexture());
		shader.setParameter("texture", source); 
		//smokeShader.setParameter("texture", source2);
		//window.draw(mySprite2, &smokeShader);
		window.draw(mySprite, &shader);
		
		
		currentTime = clock.getElapsedTime();
		float fps = 1.f / (currentTime.asSeconds()-lastTime.asSeconds());
		lastTime = currentTime;
		fpsText.setString(intToString(fps));
		window.draw(fpsText);

		window.display();
	}



	return 0;
}