#pragma once

#include <Apollo.h>

struct MoveSpeed : public Apollo::ECS::Component
{
	float speed = 0.f;

	MoveSpeed() = default;
	MoveSpeed(float speed) : speed(speed) {}
}; 