#include "pch.h"
#include "Systems.h"

void LineSystem::castToDistance(sf::Vector2f origin, sf::Vector2f dest, float distance, sf::Color colour)
{
	sf::Vertex line[2];
	line[0].position = origin;
	line[0].color = colour;
	line[1].position = origin + getLineDirection(origin, dest) * distance;
	line[1].color = colour;

	Window::window()->draw(line, 2, sf::Lines);
}

void LineSystem::castToScalar(sf::Vector2f origin, sf::Vector2f dest, float scalar, sf::Color colour)
{
	sf::Vertex line[2];
	float distance = Math::distance(origin, dest) * scalar;
	
	line[0].position = origin;
	line[0].color = colour;
	line[1].position = origin + getLineDirection(origin, dest) * distance;
	line[1].color = colour;

	Window::window()->draw(line, 2, sf::Lines);
}

void LineSystem::castToPosition(sf::Vector2f origin, sf::Vector2f dest, sf::Color colour)
{
	sf::Vertex line[2];
	line[0].position = origin;
	line[0].color = colour;
	line[1].position = dest;
	line[1].color = colour;

	Window::window()->draw(line, 2, sf::Lines);
}

sf::Vector2f LineSystem::getLineDirection(sf::Vector2f origin, sf::Vector2f dest)
{
	sf::Vector2f dir = Math::normalise(dest - origin);
	return dir;
}