#include "pch.h"
#include "Systems.h"
#include "../Components/Components.h"

void PlayerMovementSystem::updateVelocity(ECS::Entity player)
{
	sf::Vector2f velocity{ 0.f, 0.f };
	ECS::Velocity& vel = player.get<ECS::Velocity>();
	ECS::SpriteRenderer& spriteRenderer = player.get<ECS::SpriteRenderer>();
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

		if (!spriteRenderer.flipX)
		{
			ECS::SpriteSystem::flipX(player);
			spriteRenderer.flipX = true;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed.speed;

		if (spriteRenderer.flipX)
		{
			ECS::SpriteSystem::flipX(player);
			spriteRenderer.flipX = false;
		}
	}

	vel.vx = velocity.x;
	vel.vy = velocity.y;
}