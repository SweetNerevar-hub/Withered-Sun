#pragma once

#include <Apollo.h>

using namespace Apollo;

struct World : public ECS::Component
{
	VertexArray enemyVA;

	World() = default;
};

struct MoveSpeed : public ECS::Component
{
	float speed = 0.f;

	MoveSpeed() = default;
	MoveSpeed(float speed) : speed(speed) {}
}; 

struct Health : public ECS::Component
{
	float health = 0.f;

	Health() = default;
	Health(float health) : health(health) {}
};

struct Spawner : public ECS::Component
{
	// Add the enemy vertex array here so it can be gotten from anywhere
	VertexArray enemyVA;

	float maxTimer = Math::infinity();
	float timer = 0.f;
	sf::Vector2f spawnPosition{ 600.f, 400.f };

	Spawner() = default;
	Spawner(float maxTimer) : maxTimer(maxTimer), timer(maxTimer) {}
};