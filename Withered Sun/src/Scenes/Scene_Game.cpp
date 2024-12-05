#include "pch.h"
#include "GameScenes.h"

#include "../Systems/Systems.h"
#include "../Components/Components.h"

void Scene_Game::start()
{
	std::cout << "Started Game Scene" << std::endl;

	Apollo::ApolloECS::registerComponent<MoveSpeed>();
	Apollo::AssetManager::loadTextures("assets/scene_game/images/characters");

	m_player = Apollo::ApolloECS::createEntity("Player");
	m_player.add<Apollo::ECS::Position>(200.f, 300.f);
	m_player.add<Apollo::ECS::Velocity>(1.f, 1.f);
	m_player.add<Apollo::ECS::SpriteRenderer>(sf::FloatRect(0.f, 0.f, 9.f, 23.f));
	m_player.add<Apollo::ECS::Animator>();
	m_player.add<MoveSpeed>(3.f);

	sf::Vector2f origin{ m_player.get<Apollo::ECS::Position>().x, m_player.get<Apollo::ECS::Position>().y };
	m_player.add<Apollo::ECS::BoxCollider>(origin, 9, 23);

	m_playerTexture = Apollo::AssetManager::getTexture("atlas_protagonist");
}

void Scene_Game::handleInputs(sf::Event& event)
{

}

void Scene_Game::fixedUpdate()
{
	MovementSystem::updatePlayerVelocity(m_player);
	MovementSystem::update(Apollo::ApolloECS::getEntities());
}

void Scene_Game::update()
{
	setPosition(m_player);
	m_player.get<Apollo::ECS::SpriteRenderer>().sprite.setDirty();
}

void Scene_Game::render(sf::RenderWindow& window)
{
	m_player.get<Apollo::ECS::SpriteRenderer>().sprite.updateBuffer();
	window.draw(m_player.get<Apollo::ECS::SpriteRenderer>().sprite, &m_playerTexture);
}

void Scene_Game::shutdown()
{
	Apollo::AssetManager::clearAssets();

	for (Apollo::ECS::Entity e : Apollo::ApolloECS::getEntities())
	{
		Apollo::ApolloECS::destroyEntity(e);
	}

	Apollo::ApolloECS::getEntities().clear();
}

// TODO: Move to a SpriteSystem class, where there can also be logic like setting sprite scale and flipping
void Scene_Game::setPosition(Apollo::ECS::Entity entity)
{
	Apollo::ECS::Position& position = entity.get<Apollo::ECS::Position>();
	Apollo::ECS::SpriteRenderer& spriteRenderer = entity.get<Apollo::ECS::SpriteRenderer>();
	float width = spriteRenderer.textureRect.width;
	float height = spriteRenderer.textureRect.height;

	/* Update the sprite's visual position */
	spriteRenderer.sprite[0].position = sf::Vector2f{ position.x, position.y };
	spriteRenderer.sprite[1].position = sf::Vector2f{ position.x + width, position.y };
	spriteRenderer.sprite[2].position = sf::Vector2f{ position.x, position.y + height };
	spriteRenderer.sprite[3].position = sf::Vector2f{ position.x, position.y + height };
	spriteRenderer.sprite[4].position = sf::Vector2f{ position.x + width, position.y };
	spriteRenderer.sprite[5].position = sf::Vector2f{ position.x + width, position.y + height };
}