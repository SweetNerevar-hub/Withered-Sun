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
			Apollo::Scene::SceneManager::addScene<Scene_Game>(false);
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
	AssetManager::clearAssets();

	for (ECS::Entity e : ApolloECS::getEntities())
	{
		ApolloECS::destroyEntity(e);
	}

	ApolloECS::getEntities().clear();
}