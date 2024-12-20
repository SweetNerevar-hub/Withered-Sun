#pragma once

#include <Apollo.h>

class World
{
public:
	Apollo::VertexArray enemyVA;
	std::vector<Apollo::u32> enemyVAFreeIndices;

	World() = default;
};