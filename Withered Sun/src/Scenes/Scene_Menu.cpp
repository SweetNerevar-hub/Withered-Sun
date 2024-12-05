#include "pch.h"
#include "GameScenes.h"

void Scene_Menu::start()
{
	std::cout << "Started Menu Scene" << std::endl;
}

void Scene_Menu::handleInputs(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			Apollo::Scene::SceneManager::addScene<Scene_Game>(true);
		}

		break;
	}
}

void Scene_Menu::fixedUpdate()
{

}

void Scene_Menu::update()
{

}

void Scene_Menu::render(sf::RenderWindow& window)
{

}

void Scene_Menu::shutdown()
{
	Apollo::AssetManager::clearAssets();

	for (Apollo::ECS::Entity e : Apollo::ApolloECS::getEntities())
	{
		Apollo::ApolloECS::destroyEntity(e);
	}

	Apollo::ApolloECS::getEntities().clear();
}