#pragma once

#include <Apollo.h>
#include <Apollo/Core/Entry.h>

#include "Systems/Systems.h"
#include "Components/Components.h"

#include "GameEvents/GameEvents.h"
#include "Scenes/GameScenes.h"

class Game : public Apollo::IGame
{
public:
	void start() override;
	void handleInput(sf::Event& event) override;
	void fixedUpdate() override;
	void update() override;
	void render(sf::RenderWindow& window) override;

	Game(Apollo::u32 entityArraySize) : Apollo::IGame(entityArraySize) {}
};