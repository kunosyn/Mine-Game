#pragma once

#include "Constants.h"

#include <SFML/Graphics.hpp>


enum class BlockType {
	Grass,
	Dirt,
	Stone
};


struct TerrainBlock {
	BlockType type;
	sf::Vector2f position;
};

class Chunk {
public:
	Chunk(int x, int y);

	void push(const TerrainBlock& block);
	void clear(void);

	const sf::VertexArray& getVertices(void) const;
	const sf::Vector2f& getPosition(void) const;

	bool intersects(const sf::FloatRect& other) const;
	bool operator == (const Chunk& other) const;
	
	struct Hash {
		std::size_t operator()(const Chunk& chunk) const;
	};
private:
	std::vector<TerrainBlock> m_blocks;
	sf::VertexArray m_vertices;
	sf::Vector2f m_position;

	sf::Vector2f getTextureCoordinates(BlockType type);
};