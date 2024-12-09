#include "pch.h"
#include "Systems.h"

void DeathSystem::update()
{
	for (ECS::Entity e : ApolloECS::getEntities())
	{
		if (!e.has<Health>())
			continue;

		if (e.get<Health>().health <= 0.f)
		{
			ApolloECS::destroyEntity(e);
		}
	}
}