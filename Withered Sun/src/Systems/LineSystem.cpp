#include "pch.h"
#include "Systems.h"

std::array<sf::Vertex, 2> LineSystem::castToDistance(sf::Vector2f origin, sf::Vector2f dest, float distance, sf::Color colour)
{
	std::array<sf::Vertex, 2> line;
	line[0].position = origin;
	line[0].color = colour;
	line[1].position = origin + getLineDirection(origin, dest) * distance;
	line[1].color = colour;

	return line;
}

std::array<sf::Vertex, 2> LineSystem::castToScalar(sf::Vector2f origin, sf::Vector2f dest, float scalar, sf::Color colour)
{
	std::array<sf::Vertex, 2> line;
	float distance = Math::distance(origin, dest) * scalar;
	
	line[0].position = origin;
	line[0].color = colour;
	line[1].position = origin + getLineDirection(origin, dest) * distance;
	line[1].color = colour;

	return line;
}

std::array<sf::Vertex, 2> LineSystem::castToPosition(sf::Vector2f origin, sf::Vector2f dest, sf::Color colour)
{
	std::array<sf::Vertex, 2> line;
	line[0].position = origin;
	line[0].color = colour;
	line[1].position = dest;
	line[1].color = colour;

	return line;
}

sf::Vector2f LineSystem::getLineDirection(sf::Vector2f origin, sf::Vector2f dest)
{
	sf::Vector2f dir = Math::normalise(dest - origin);
	return dir;
}