#pragma once

#include <Apollo.h>

#include "../Systems/Systems.h"

using namespace Apollo;

class Scene_Menu : public Scene::Scene
{
public:
	void start() override;
	void handleInputs(sf::Event& event) override;
	void fixedUpdate() override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	void shutdown() override;

	void pause() override {}
	void resume() override {}

private:

};

class Scene_Game : public Scene::Scene
{
public:
	void start() override;
	void handleInputs(sf::Event& event) override;
	void fixedUpdate() override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	void shutdown() override;

	void pause() override {}
	void resume() override {}

private:
	ECS::Entity m_world;
	ECS::Entity m_player;
	ECS::Entity m_spawner;

	std::array<sf::Vertex, 2> m_line;
	const float k_rayDistance = 1000.f;
	ECS::Intersect m_raycastHit;

	Spawner spawnComponent;
	World worldComponent;

private:
	void setSpritePositions();
	void sendRaycast();
	void handleRaycastHit(ECS::Intersect hit);
};
