#include "pch.h"
#include "GameScenes.h"

#include "../Systems/Systems.h"
#include "../Components/Components.h"

void Scene_Game::start()
{
	std::cout << "Started Game Scene" << std::endl;

	ApolloECS::registerComponent<MoveSpeed>();	
	AssetManager::loadTextures("assets/scene_game/images/characters");
	AssetManager::loadTextures("assets/scene_game/images/enemies");

	m_player = ApolloECS::createEntity("Player");
	m_player.add<ECS::Position>(200.f, 300.f);
	m_player.add<ECS::Scale>();
	m_player.add<ECS::Velocity>(1.f, 1.f);
	m_player.add<ECS::SpriteRenderer>(9.f, 23.f);
	m_player.add<ECS::Animator>();
	m_player.add<MoveSpeed>(3.f);

	sf::Vector2f origin{ m_player.get<ECS::Position>().x, m_player.get<ECS::Position>().y };
	m_player.add<ECS::BoxCollider>(origin, 9, 23);
}

void Scene_Game::handleInputs(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			ECS::TransformSystem::setScale(m_player, {3.f, 3.f});
		}

		break;
	}
}

void Scene_Game::fixedUpdate()
{
	PlayerMovementSystem::updateVelocity(m_player);
	MovementSystem::update(ApolloECS::getEntities());
	ECS::CollisionSystem::update(ApolloECS::getEntities());
}

void Scene_Game::update()
{
	ECS::TransformSystem::setPosition(m_player);
	m_player.get<ECS::SpriteRenderer>().sprite.setDirty();
}

void Scene_Game::render(sf::RenderWindow& window)
{
	m_player.get<ECS::SpriteRenderer>().sprite.updateBuffer();
	window.draw(m_player.get<ECS::SpriteRenderer>().sprite, &AssetManager::getTexture("atlas_protagonist"));
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