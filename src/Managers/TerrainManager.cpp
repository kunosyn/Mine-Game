#include "../Headers/Managers/TerrainManager.h"
#include "../Headers/Constants.h"
#include "../Headers/Utility.h"

#include <FastNoiseLite.h>

#include <iostream>
#include <vector>
#include <chrono>

using std::chrono::duration_cast;

TerrainManager::TerrainManager(sf::RenderWindow* window)
	: m_window(window), m_seed(0)
{
	if (!m_textureAtlas.loadFromFile("Textures/block_textures.png")) {
		throw std::runtime_error("An error occurred while loading the block texture atlas.");
	}

	this->selectSeed();
}

void TerrainManager::selectSeed (void) {
	auto currentTime = std::chrono::system_clock::now();
	auto duration = currentTime.time_since_epoch();

	m_seed = static_cast<uint32_t>(duration_cast<std::chrono::milliseconds>(duration).count());

	m_noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	m_noise.SetSeed(m_seed);


	std::cout << "Seed: " << m_seed << std::endl;
	std::cout << "Frequency: " << TERRAIN_FREQUENCY << std::endl;
	std::cout << "Height Addition: " << HEIGHT_ADDITION << std::endl;
	std::cout << "Height Multiplier: " << HEIGHT_MULTIPLIER << std::endl;
}

void TerrainManager::generateTerrain(const sf::Vector2f& position, const sf::FloatRect viewBounds) {
	// Erase chunks that are not in the view bounds
	for (auto it = m_terrain.begin(); it != m_terrain.end();) {
		if (!it->intersects(viewBounds)) {
			it = m_terrain.erase(it);
		}
		else {
			++it;
		}
	}

	int startX = static_cast<int>(position.x) / (CHUNK_WIDTH * BLOCK_WIDTH) - 2;
	int startY = static_cast<int>(position.y) / (CHUNK_HEIGHT * BLOCK_WIDTH) - 2;

	for (int chunkX = startX; chunkX < startX + 4; ++chunkX) {
		for (int chunkY = startY; chunkY <= startY + 4; ++chunkY) {
			Chunk chunk(chunkX, chunkY);


			if (m_terrain.find(chunk) != m_terrain.end())
				continue;
			

			for (int x = chunkX * CHUNK_WIDTH; x < (chunkX + 1) * CHUNK_WIDTH; ++x) {
				float noiseValue = m_noise.GetNoise(x * TERRAIN_FREQUENCY, m_seed * TERRAIN_FREQUENCY);
				int height = static_cast<int>(noiseValue * HEIGHT_MULTIPLIER + HEIGHT_ADDITION);

				for (int y = chunkY * CHUNK_WIDTH; y < (chunkY + 3) * CHUNK_WIDTH && y < height; ++y) {
					BlockType type = getBlockTypeFromHeight(y, height);
					chunk.push(TerrainBlock{ type, sf::Vector2f(x * BLOCK_WIDTH, -y * BLOCK_WIDTH) });
				}

				/*for (int y = 0; y < height; ++y) {
					BlockType type = getBlockTypeFromHeight(y, height);
					chunk.push(TerrainBlock{ type, sf::Vector2f(x * BLOCK_WIDTH, -y * BLOCK_WIDTH) });
				}*/
			}

			if (chunk.getVertexCount() > 0) 
				m_terrain.insert(chunk);
		}
	}
}




void TerrainManager::renderTerrain (const sf::FloatRect viewBounds) const {
	for (const Chunk& chunk : m_terrain) {
		m_window->draw(chunk.getVertices(), &m_textureAtlas);
	}
}

BlockType TerrainManager::getBlockTypeFromHeight (int y, int height) {
	/*if (y <= 15) {
		return BlockType::Bedrock;
	}

	for (const auto& range : m_blockTypeRanges) {
		if (y <= height - range.maxHeight) {
			return range.type;
		}
	}*/

	BlockType type;

	if (y < (height - DIRT_LAYER_HEIGHT)) {
		type = BlockType::Stone;
	}
	else if (y < (height - 1)) {
		type = BlockType::Dirt;
	}
	else {
		type = BlockType::Grass;
	}

	return type;
}
