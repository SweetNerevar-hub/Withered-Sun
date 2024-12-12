#include "pch.h"
#include "Systems.h"

void MovementSystem::update()
{
	for (ECS::Entity e : ApolloECS::getEntities())
	{
		if (!e.has<ECS::Velocity>())
			return;

		ECS::Position& position = e.get<ECS::Position>();
		ECS::Velocity& velocity = e.get<ECS::Velocity>();

		position.x += velocity.vx;
		position.y += velocity.vy;
	}
}