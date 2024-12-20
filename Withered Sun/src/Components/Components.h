#pragma once

#include <Apollo.h>

using namespace Apollo;

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