#pragma once

#include <Apollo.h>

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
	ECS::Entity m_player;
	ECS::Entity m_enemy;

	std::array<sf::Vertex, 2> m_line;
	const float k_rayDistance = 1000.f;
	ECS::Intersect raycastHit;

private:
	void handleRaycastHit(ECS::Intersect hit);
};
