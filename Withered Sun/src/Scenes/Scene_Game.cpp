#include "pch.h"
#include "GameScenes.h"

void Scene_Game::start()
{
	std::cout << "Started Game Scene" << std::endl;

	ApolloECS::registerComponent<ECS::Cell>();
	ApolloECS::registerComponent<MoveSpeed>();	
	ApolloECS::registerComponent<Health>();

	AssetManager::loadTextures("assets/scene_game/images/characters");
	AssetManager::loadTextures("assets/scene_game/images/enemies");
	AssetManager::loadTextures("assets/scene_game/images/environment");

	m_player = ApolloECS::createEntity("Player");
	m_player.add<ECS::Position>(200.f, 100.f);
	m_player.add<ECS::Scale>();
	m_player.add<ECS::Velocity>();
	m_player.add<ECS::SpriteRenderer>(9.f, 23.f);
	m_player.add<ECS::Animator>();
	m_player.add<ECS::BoxCollider>(sf::Vector2f{ 0, 0 }, 9, 23);
	m_player.add<MoveSpeed>(2.f);
	m_player.add<Health>(20.f);

	m_cellMap = new Map(AssetManager::getTexture("atlas_environment"), 16, true);
	m_cellMap->addPixelData(sf::Color::White, { 0, 0, 16, 16 }, false, 3);
	m_cellMap->addPixelData(sf::Color::Black, { 0, 0, 16, 16 }, true, 3);
	m_cellMap->load("assets/scene_game/map/cellmap_test.png");

	m_spriteMap = new Map(AssetManager::getTexture("atlas_environment"), 16, false);
	m_spriteMap->addPixelData({ 34, 32, 52 }, { 0, 16, 16, 16 }, false, 3);
	m_spriteMap->addPixelData({ 138, 111, 48 }, { 0, 32, 16, 16 });
	m_spriteMap->addPixelData({ 223, 113, 38 }, { 32, 32, 16, 16 });
	m_spriteMap->addPixelData({ 82, 75, 36 }, { 16, 32, 16, 16 });
	m_spriteMap->addPixelData({ 143, 86, 59 }, { 48, 32, 16, 16 });
	m_spriteMap->load("assets/scene_game/map/spritemap_test.png");
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
	SpawnSystem::update(world, spawner);
	DeathSystem::update(world);

	setSpritePositions();

	m_player.get<ECS::SpriteRenderer>().sprite.setDirty();
	world.enemyVA.setDirty();
}

void Scene_Game::render(sf::RenderWindow& window)
{
	m_player.get<ECS::SpriteRenderer>().sprite.updateBuffer();
	world.enemyVA.updateBuffer();

	m_cellMap->draw(window);
	m_spriteMap->draw(window);

	window.draw(m_line.data(), 2, sf::Lines);
	window.draw(m_player.get<ECS::SpriteRenderer>().sprite, &AssetManager::getTexture("atlas_protagonist"));
	window.draw(world.enemyVA, &AssetManager::getTexture("enemy_eyen"));
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
			ECS::TransformSystem::setPosition(e, world.enemyVA);
			continue;
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