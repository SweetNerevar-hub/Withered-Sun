#pragma once

#include <Apollo.h>

using namespace Apollo;

class MovementSystem
{
public:
	static void update(ECS::Entities& entities);
};

class PlayerMovementSystem
{
public:
	static void updateVelocity(ECS::Entity player);
};

class LineSystem
{
public:
	static void castToDistance(sf::Vector2f origin, sf::Vector2f dest, float distance, sf::Color colour);
	static void castToScalar(sf::Vector2f origin, sf::Vector2f dest, float scalar, sf::Color colour);
	static void castToPosition(sf::Vector2f origin, sf::Vector2f dest, sf::Color colour);

private:
	static sf::Vector2f getLineDirection(sf::Vector2f origin, sf::Vector2f dest);
};