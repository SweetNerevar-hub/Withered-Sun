#pragma once

#include <Apollo.h>

#include "../Components/Components.h"

using namespace Apollo;

class MovementSystem
{
public:
	static void update();
};

class PlayerMovementSystem
{
public:
	static void updateVelocity(ECS::Entity player);
};

class LineSystem
{
public:
	static std::array<sf::Vertex, 2> castToDistance(sf::Vector2f origin, sf::Vector2f dest, float distance, sf::Color colour);
	static std::array<sf::Vertex, 2> castToScalar(sf::Vector2f origin, sf::Vector2f dest, float scalar, sf::Color colour);
	static std::array<sf::Vertex, 2> castToPosition(sf::Vector2f origin, sf::Vector2f dest, sf::Color colour);

private:
	static sf::Vector2f getLineDirection(sf::Vector2f origin, sf::Vector2f dest);
};

class DeathSystem
{
public:
	static void update();
};