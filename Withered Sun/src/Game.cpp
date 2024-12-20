#include "pch.h"
#include "Game.h"

void Game::start()
{
	ApolloECS::registerComponent<ECS::Position>();
	ApolloECS::registerComponent<ECS::Scale>();
	ApolloECS::registerComponent<ECS::Velocity>();
	ApolloECS::registerComponent<ECS::SpriteRenderer>();
	ApolloECS::registerComponent<ECS::BoxCollider>();
	ApolloECS::registerComponent<ECS::Animator>();
	ApolloECS::registerComponent<ECS::Camera>();

	Scene::SceneManager::addScene<Scene_Menu>(false);
}

void Game::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			Apollo::Scene::SceneManager::removeScene();
		}

		break;
	}

	Apollo::Scene::SceneManager::getActiveScene()->handleInputs(event);
}

void Game::fixedUpdate()
{
	Apollo::Scene::SceneManager::getActiveScene()->fixedUpdate();
}

void Game::update()
{
	Apollo::Scene::SceneManager::getActiveScene()->update();
}

void Game::render(sf::RenderWindow& window)
{
	Apollo::Scene::SceneManager::getActiveScene()->render(window);
}

Apollo::IGame* Apollo::createGame()
{
	return new Game(10000);
}