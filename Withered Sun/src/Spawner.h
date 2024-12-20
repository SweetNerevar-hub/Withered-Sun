#pragma once

#include <Apollo.h>

using namespace Apollo;

class Spawner
{
public:
	float maxTimer = Math::infinity();
	float timer = 0.f;
	sf::Vector2f spawnPosition{ 600.f, 500.f };

	Spawner() = default;
	Spawner(float maxTimer) : maxTimer(maxTimer), timer(maxTimer) {}
};