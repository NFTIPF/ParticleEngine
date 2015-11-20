#pragma once
#include <SFML\Graphics.hpp>

inline void normalize(sf::Vector2f& toDo)
{
	float mag = sqrt(toDo.x*toDo.x + toDo.y*toDo.y);
	toDo /= mag;
};

inline void mag(sf::Vector2f& p1, float& res)
{
	res = sqrt(p1.x*p1.x + p1.y*p1.y);
};

inline void mag2(sf::Vector2f& p1, float& res)
{
	res = p1.x*p1.x + p1.y*p1.y;
};

inline void clamp(float& in, const float& min, const float& max)
{
	if (in < min)
	{
		in = min;
	} 
	else if (in > max)
	{
		in = max;
	}
};