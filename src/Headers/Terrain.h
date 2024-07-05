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

class Terrain {
public:
	Terrain(void);

	void push(const TerrainBlock& block);
	void remove(int x, int y);

	const sf::VertexArray& getVertices(void) const;

private:
	sf::VertexArray m_vertices;
	sf::Vector2f getTextureCoordinates(BlockType type);
};