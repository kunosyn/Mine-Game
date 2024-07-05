#pragma once

#include "Terrain.h"
#include "FastNoiseLite.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_set>


class TerrainGenerator {
public:
	TerrainGenerator(sf::RenderWindow* window);

	void generateTerrain(const sf::Vector2f& position, const sf::FloatRect viewBounds);
	void renderTerrain(void) const;

	BlockType getBlockTypeFromHeight(int y, int height);
	void selectSeed(void);

	sf::Vector2f findSpawnLocation(void) const;

private:
	sf::RenderWindow* m_window;
	Terrain m_terrain;

	FastNoiseLite m_noise;
	uint32_t m_seed;

	sf::Texture m_textureAtlas;
};

