#include "pch.h"
#include "Systems.h"
#include "../Components/Components.h"

void MovementSystem::update(Apollo::ECS::Entities& entities)
{
	for (Apollo::ECS::Entity e : entities)
	{
		if (!e.has<Apollo::ECS::Velocity>())
			return;

		Apollo::ECS::Position& position = e.get<Apollo::ECS::Position>();
		Apollo::ECS::Velocity& velocity = e.get<Apollo::ECS::Velocity>();

		position.x += velocity.vx;
		position.y += velocity.vy;
	}
}

void MovementSystem::updatePlayerVelocity(Apollo::ECS::Entity player)
{
	sf::Vector2f velocity{ 0.f, 0.f };
	Apollo::ECS::Velocity& vel = player.get<Apollo::ECS::Velocity>();
	MoveSpeed& speed = player.get<MoveSpeed>();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= speed.speed;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += speed.speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed.speed;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed.speed;
	}

	vel.vx = velocity.x;
	vel.vy = velocity.y;
}