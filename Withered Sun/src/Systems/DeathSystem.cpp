#include "pch.h"
#include "Systems.h"

void DeathSystem::update(World& world)
{
	for (ECS::Entity e : ApolloECS::getEntities())
	{
		if (!e.has<Health>())
			continue;

		if (e.get<Health>().health <= 0.f)
		{
			killEntity(e, world);
		}
	}
}

void DeathSystem::killEntity(ECS::Entity e, World& world)
{
	if (e.getTag() == "Enemy")
	{
		world.enemyVAFreeIndices.emplace_back(e.get<ECS::SpriteRenderer>().vaIndex);

		/* Moves the position of the sprite to give the illusion of death */
		/* Very hacky, try to think of something better */
		e.get<ECS::Position>().x = Math::infinity();
		e.get<ECS::Position>().y = Math::infinity();
	}

	ApolloECS::destroyEntity(e);
}