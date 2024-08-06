#pragma once

#include "../Classes/Chunk.h"
#include <FastNoiseLite.h>
#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_set>

struct BlockTypeRange {
	int maxHeight;
	BlockType type;
};

class TerrainManager {
public:
	TerrainManager(sf::RenderWindow* window);

	void generateTerrain(const sf::Vector2f& position, const sf::FloatRect viewBounds);
	void renderTerrain(const sf::FloatRect viewBounds) const;

	BlockType getBlockTypeFromHeight(int y, int height);
	void selectSeed(void);

	sf::Vector2f findSpawnLocation(void) const;

private:
	sf::RenderWindow* m_window;
	std::unordered_set<Chunk, Chunk::Hash> m_terrain;

	FastNoiseLite m_noise;
	uint32_t m_seed;

	sf::Texture m_textureAtlas;

	std::vector<BlockTypeRange> m_blockTypeRanges { 
		{DIRT_LAYER_HEIGHT, BlockType::Stone},
		{1, BlockType::Dirt},
		{0, BlockType::Grass}
	};
};

