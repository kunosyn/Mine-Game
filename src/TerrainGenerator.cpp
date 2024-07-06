#include "Headers/TerrainGenerator.h"
#include "Headers/Constants.h"
#include "Headers/Utility.h"

#include <iostream>
#include <vector>
#include <chrono>

using std::chrono::duration_cast;

TerrainGenerator::TerrainGenerator (sf::RenderWindow* window)
	: m_window(window), m_seed(0)
{
	if (!m_textureAtlas.loadFromFile("Textures/block_textures.png")) {
		throw std::runtime_error("An error occurred while loading the block texture atlas.");
	}

	this->selectSeed();
}

void TerrainGenerator::selectSeed (void) {
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

void TerrainGenerator::generateTerrain (const sf::Vector2f& position, const sf::FloatRect viewBounds) {
	for (auto it = m_terrain.begin(); it != m_terrain.end();) {
		if (!it->intersects(viewBounds)) {
   			it = m_terrain.erase(it);
			std::cout << "# of Chunks: " <<  m_terrain.size() << std::endl;
		}
		else {
			++it;
		}
	}

	int posX = std::clamp(static_cast<int>(position.x) - (CHUNK_WIDTH * BLOCK_WIDTH) * 2, 0, MAP_WIDTH * BLOCK_WIDTH);
	int posY = std::clamp(static_cast<int>(position.y) - (CHUNK_HEIGHT * BLOCK_WIDTH) * 2, 0, MAP_HEIGHT * BLOCK_WIDTH);

	for (int chunkX = posX; (chunkX * BLOCK_WIDTH) < position.x + (CHUNK_WIDTH * BLOCK_WIDTH) * 2; chunkX += CHUNK_WIDTH) {
		for (int chunkY = posY; (chunkY * BLOCK_WIDTH) < position.y + (CHUNK_WIDTH * BLOCK_WIDTH) * 2; chunkY += CHUNK_HEIGHT) {
			Chunk chunk(chunkX / CHUNK_WIDTH, chunkY / CHUNK_HEIGHT);

			if (m_terrain.find(chunk) != m_terrain.end()) {
				std::cout << "# of Chunks" << m_terrain.size() << std::endl;
				continue;
			}


			for (int x = chunkX; x < (chunkX + CHUNK_WIDTH); ++x) {
				float noiseValue = m_noise.GetNoise(x * TERRAIN_FREQUENCY, m_seed * TERRAIN_FREQUENCY);
				int height = static_cast<int>(noiseValue * HEIGHT_MULTIPLIER + HEIGHT_ADDITION);

				for (int y = 0; y < height; ++y) {
					
					BlockType type = getBlockTypeFromHeight(y, height);
					chunk.push(TerrainBlock { type, sf::Vector2f(x * BLOCK_WIDTH, -y * BLOCK_WIDTH) });
				}
			}

			m_terrain.insert(chunk);
			std::cout << "# of Chunks: " << m_terrain.size() << std::endl;
		}
	}
}

void TerrainGenerator::renderTerrain (void) const {
	for (const Chunk& chunk : m_terrain) {
		m_window->draw(chunk.getVertices(), &m_textureAtlas);
	}
}

BlockType TerrainGenerator::getBlockTypeFromHeight (int y, int height) {
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
