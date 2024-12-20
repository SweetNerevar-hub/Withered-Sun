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

	addSpriteToVertexArray(world, world.enemyVA, enemy);
}

void SpawnSystem::addSpriteToVertexArray(World& world, VertexArray& array, ECS::Entity entity)
{
	ECS::SpriteRenderer& spriteRenderer = entity.get<ECS::SpriteRenderer>();

	/* If there are no empty slots in the vertex array, append a new sprite */
	if (world.enemyVAFreeIndices.empty())
	{
		array.appendArray(spriteRenderer.sprite);
		spriteRenderer.vaIndex = (array.length() / 6) - 1;
		return;
	}

	/* If there is an empty slot, then get its position in the vertex array and override it with a new sprite */
	spriteRenderer.vaIndex = getFirstFreeIndex(world);
	array.slotArray(spriteRenderer.vaIndex, spriteRenderer.sprite);
}

u32 SpawnSystem::getFirstFreeIndex(World& world)
{
	std::sort(world.enemyVAFreeIndices.begin(), world.enemyVAFreeIndices.end(), std::greater<u32>());
	u32 firstIndex = world.enemyVAFreeIndices.back();
	world.enemyVAFreeIndices.pop_back();

	std::cout << "First Index: " << firstIndex << std::endl;

	return firstIndex;
}