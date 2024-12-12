#include "pch.h"
#include "GameScenes.h"

#include "../Systems/Systems.h"
#include "../Components/Components.h"

void Scene_Game::start()
{
	std::cout << "Started Game Scene" << std::endl;

	ApolloECS::registerComponent<MoveSpeed>();	
	ApolloECS::registerComponent<Health>();
	ApolloECS::registerComponent<Spawner>();
	ApolloECS::registerComponent<World>();

	AssetManager::loadTextures("assets/scene_game/images/characters");
	AssetManager::loadTextures("assets/scene_game/images/enemies");

	m_world.add<World>();
	worldComponent = m_world.get<World>();

	m_spawner.add<Spawner>(3.f);
	spawnComponent = m_spawner.get<Spawner>();

	m_player = ApolloECS::createEntity("Player");
	m_player.add<ECS::Position>(200.f, 300.f);
	m_player.add<ECS::Scale>();
	m_player.add<ECS::Velocity>(1.f, 1.f);
	m_player.add<ECS::SpriteRenderer>(9.f, 23.f);
	m_player.add<ECS::Animator>();
	m_player.add<ECS::BoxCollider>(sf::Vector2f{ 0, 0 }, 9, 23);
	m_player.add<MoveSpeed>(3.f);
	m_player.add<Health>(20.f);
}

void Scene_Game::handleInputs(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			ECS::TransformSystem::setScale(m_player, { 4.f, 4.f });
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			handleRaycastHit(m_raycastHit);
		}
		break;
	}
}

void Scene_Game::fixedUpdate()
{
	PlayerMovementSystem::updateVelocity(m_player);
	MovementSystem::update();
	ECS::CollisionSystem::update();
}

void Scene_Game::update()
{
	sendRaycast();
	SpawnSystem::update(worldComponent, spawnComponent);
	DeathSystem::update();

	setSpritePositions();

	m_player.get<ECS::SpriteRenderer>().sprite.setDirty();
	worldComponent.enemyVA.setDirty();
}

void Scene_Game::render(sf::RenderWindow& window)
{
	m_player.get<ECS::SpriteRenderer>().sprite.updateBuffer();
	worldComponent.enemyVA.updateBuffer();

	window.draw(m_line.data(), 2, sf::Lines);
	window.draw(m_player.get<ECS::SpriteRenderer>().sprite, &AssetManager::getTexture("atlas_protagonist"));
	window.draw(worldComponent.enemyVA, &AssetManager::getTexture("enemy_eyen"));
}

void Scene_Game::shutdown()
{
	AssetManager::clearAssets();

	for (ECS::Entity e : ApolloECS::getEntities())
	{
		ApolloECS::destroyEntity(e);
	}

	ApolloECS::getEntities().clear();
}

void Scene_Game::setSpritePositions()
{
	for (ECS::Entity e : ApolloECS::getEntities())
	{
		if (!e.has<ECS::SpriteRenderer>())
			continue;

		ECS::SpriteRenderer& spriteRenderer = e.get<ECS::SpriteRenderer>();

		if (e.getTag() == "Enemy")
		{
			ECS::TransformSystem::setPosition(e, worldComponent.enemyVA);
		}

		ECS::TransformSystem::setPosition(e);
	}
}

void Scene_Game::sendRaycast()
{
	sf::Vector2f playerPos = ECS::TransformSystem::getPositionCentre(m_player);
	sf::Vector2f mousePos = Window::window()->mapPixelToCoords(sf::Mouse::getPosition(*Window::window()));

	m_raycastHit = ECS::RaycastSystem::cast(m_player, Math::direction(playerPos, mousePos), k_rayDistance);
	m_line = LineSystem::castToPosition(playerPos, m_raycastHit.pos, sf::Color::Red);
}

void Scene_Game::handleRaycastHit(ECS::Intersect hit)
{
	if (!hit.result)
		return;

	if (hit.hit.getTag() == "Enemy")
	{
		std::cout << "Hit Enemy" << std::endl;
		hit.hit.get<Health>().health -= 5.f;
	}
}