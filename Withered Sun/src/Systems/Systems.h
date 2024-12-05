#pragma once

#include <Apollo.h>

class MovementSystem
{
public:
	static void update(Apollo::ECS::Entities& entities);
	static void updatePlayerVelocity(Apollo::ECS::Entity player);
};