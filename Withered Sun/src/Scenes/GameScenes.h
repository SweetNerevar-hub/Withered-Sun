#pragma once

#include <Apollo.h>

class Scene_Menu : public Apollo::Scene::Scene
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
