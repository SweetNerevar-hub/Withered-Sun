#include "pch.h"
#include "Game.h"

void Game::start()
{
	Apollo::ApolloECS::registerComponent<Apollo::ECS::Position>();
	Apollo::ApolloECS::registerComponent<Apollo::ECS::Velocity>();
	Apollo::ApolloECS::registerComponent<Apollo::ECS::SpriteRenderer>();
	Apollo::ApolloECS::registerComponent<Apollo::ECS::BoxCollider>();
	Apollo::ApolloECS::registerComponent<Apollo::ECS::Animator>();
	Apollo::ApolloECS::registerComponent<Apollo::ECS::Camera>();

	Apollo::Scene::SceneManager::addScene<Scene_Menu>(false);
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
	return new Game(5000);
}