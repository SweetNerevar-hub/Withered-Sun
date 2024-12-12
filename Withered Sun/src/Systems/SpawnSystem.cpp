#include "pch.h"
#include "Systems.h"

void SpawnSystem::update(World& world, Spawner& spawner)
{
	spawner.timer -= Time::deltaTime();

	if (spawner.timer <= 0.f)
	{
		spawnEnemy(world, spawner);
		spawner.timer = spawner.maxTimer;
	}
}

void SpawnSystem::spawnEnemy(World& world, Spawner& spawner)
{
	ECS::Entity enemy = ApolloECS::createEntity("Enemy");
	enemy.add<ECS::Position>(spawner.spawnPosition.x, spawner.spawnPosition.y);
	enemy.add<ECS::Scale>();
	enemy.add<ECS::Velocity>();
	enemy.add<ECS::SpriteRenderer>(9.f, 24.f);
	enemy.add<ECS::BoxCollider>(sf::Vector2f{ 0.f, 0.f }, 9, 24);
	enemy.add<ECS::Animator>();
	enemy.add<MoveSpeed>(2.f);
	enemy.add<Health>(10.f);

	world.enemyVA.addArray(enemy.get<ECS::SpriteRenderer>().sprite);
	enemy.get<ECS::SpriteRenderer>().vaIndex = (world.enemyVA.length() / 6) - 1;
}