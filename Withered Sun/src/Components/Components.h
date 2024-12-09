#pragma once

#include <Apollo.h>

using namespace Apollo;

struct MoveSpeed : public ECS::Component
{
	float speed = 0.f;

	MoveSpeed() = default;
	MoveSpeed(float speed) : speed(speed) {}
}; 