#include "pch.h"
#include "GameScenes.h"

#include "../Systems/Systems.h"
#include "../Components/Components.h"

void Scene_Game::start()
{
	std::cout << "Started Game Scene" << std::endl;

	ApolloECS::registerComponent<MoveSpeed>();	
	ApolloECS::registerComponent<Health>();

	AssetManager::loadTextures("assets/scene_game/images/characters");
	AssetManager::loadTextures("assets/scene_game/images/enemies");

	m_player = ApolloECS::createEntity("Player");
	m_player.add<ECS::Position>(200.f, 300.f);
	m_player.add<ECS::Scale>();
	m_player.add<ECS::Velocity>(1.f, 1.f);
	m_player.add<ECS::SpriteRenderer>(9.f, 23.f);
	m_player.add<ECS::Animator>();
	m_player.add<MoveSpeed>(3.f);
	m_player.add<Health>(20.f);

	sf::Vector2f origin{ m_player.get<ECS::Position>().x, m_player.get<ECS::Position>().y };
	m_player.add<ECS::BoxCollider>(origin, 9, 23);


	m_enemy = ApolloECS::createEntity("Enemy");
	m_enemy.add<ECS::Position>(400.f, 600.f);
	m_enemy.add<ECS::Scale>();
	m_enemy.add<ECS::Velocity>();
	m_enemy.add<ECS::SpriteRenderer>(9.f, 24.f);
	m_enemy.add<ECS::Animator>();
	m_enemy.add<MoveSpeed>();
	m_enemy.add<Health>(10.f);

	sf::Vector2f _origin{ m_enemy.get<ECS::Position>().x, m_enemy.get<ECS::Position>().y };
	m_enemy.add<ECS::BoxCollider>(_origin, 9, 24);
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

	case sf::Event::MouseButtonPressed:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			handleRaycastHit(raycastHit);
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
	sf::Vector2f playerPos = ECS::TransformSystem::getPositionCentre(m_player);
	sf::Vector2f mousePos = Window::window()->mapPixelToCoords(sf::Mouse::getPosition(*Window::window()));

	raycastHit = ECS::RaycastSystem::cast(m_player, Math::direction(playerPos, mousePos), k_rayDistance);
	m_line = LineSystem::castToPosition(playerPos, raycastHit.pos, sf::Color::Red);

	DeathSystem::update();
}

void Scene_Game::render(sf::RenderWindow& window)
{
	for (ECS::Entity e : ApolloECS::getEntities())
	{
		if (!e.has<ECS::SpriteRenderer>())
			continue;

		ECS::TransformSystem::setPosition(e);
		e.get<ECS::SpriteRenderer>().sprite.setDirty();
		e.get<ECS::SpriteRenderer>().sprite.updateBuffer();
	}

	window.draw(m_line.data(), 2, sf::Lines);
	window.draw(m_player.get<ECS::SpriteRenderer>().sprite, &AssetManager::getTexture("atlas_protagonist"));

	if (m_enemy.has<ECS::SpriteRenderer>())
	{
		window.draw(m_enemy.get<ECS::SpriteRenderer>().sprite, &AssetManager::getTexture("enemy_eyen"));
	}
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