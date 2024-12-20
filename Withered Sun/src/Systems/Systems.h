#pragma once

#include <Apollo.h>

#include "../Components/Components.h"
#include "../World.h"
#include "../Spawner.h"

using namespace Apollo;

using Line = std::array<sf::Vertex, 2>;

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
	static Line castToDistance(sf::Vector2f origin, sf::Vector2f dest, float distance, sf::Color colour);
	static Line castToScalar(sf::Vector2f origin, sf::Vector2f dest, float scalar, sf::Color colour);
	static Line castToPosition(sf::Vector2f origin, sf::Vector2f dest, sf::Color colour);

private:
	static sf::Vector2f getLineDirection(sf::Vector2f origin, sf::Vector2f dest);
};

class DeathSystem
{
public:
	static void update(World& world);

private:
	static void killEntity(ECS::Entity e, World& world);
};

class SpawnSystem
{
public:
	static void update(World& world, Spawner& spawner);

private:
	static void spawnEnemy(World& world, Spawner& spawner);
	static void addSpriteToVertexArray(World& world, VertexArray& array, ECS::Entity entity);
	static u32 getFirstFreeIndex(World& world);
};