#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <ctime> 

#define PI 3.14159265358979323846

inline double distance(sf::Vector2f v1, sf::Vector2f v2)
{
	return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

inline double mag(sf::Vector2f v)
{
	return std::sqrt((v.x * v.x + v.y * v.y));
}

inline double magSq(sf::Vector2f v)
{
	return (v.x * v.x + v.y * v.y);
}

inline sf::Vector2f normalize(sf::Vector2f v)
{
	sf::Vector2f normal = sf::Vector2f(0, 0);

	if (mag(v) > 0)
	{
		normal = sf::Vector2f(v.x / mag(v), v.y / mag(v));
	}

	return normal;
}

inline sf::Vector2f directionVector(float angle)
{
	float radians = (PI / 180) * angle;
	return sf::Vector2f(cos(radians), sin(radians));
}

inline sf::Vector2f limitForce(sf::Vector2f v, float max)
{
	sf::Vector2f limit = v;
	if (magSq(v) > max * max)
	{
		limit = normalize(limit);
		limit *= max;
	}
	return limit;
}

inline float dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

#endif // !MATHHELPER_H
