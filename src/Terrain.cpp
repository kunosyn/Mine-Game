#include "Headers/Terrain.h"
#include <algorithm>


Terrain::Terrain (void) {
	m_vertices.setPrimitiveType(sf::Triangles);
}

void Terrain::push (const TerrainBlock& block) {
	sf::Vertex tri[6];

	tri[0].position = block.position;
	tri[1].position = block.position + sf::Vector2f(BLOCK_WIDTH, 0);
	tri[2].position = block.position + sf::Vector2f(BLOCK_WIDTH, BLOCK_WIDTH);

	tri[3].position = block.position;
	tri[4].position = block.position + sf::Vector2f(BLOCK_WIDTH, BLOCK_WIDTH);
	tri[5].position = block.position + sf::Vector2f(0, BLOCK_WIDTH);

	sf::Vector2f texCoords = getTextureCoordinates(block.type);

	tri[0].texCoords = texCoords;
	tri[1].texCoords = texCoords + sf::Vector2f(16, 0);
	tri[2].texCoords = texCoords + sf::Vector2f(16, 16);

	tri[3].texCoords = texCoords;
	tri[4].texCoords = texCoords + sf::Vector2f(16, 16);
	tri[5].texCoords = texCoords + sf::Vector2f(0, 16);

	for (int i = 0; i < 6; ++i) {
		m_vertices.append(tri[i]);
	}
}

const sf::VertexArray& Terrain::getVertices (void) const {
	return m_vertices;
}

// Private Functions
sf::Vector2f Terrain::getTextureCoordinates (BlockType type) {
	switch (type) {
		case BlockType::Stone: return sf::Vector2f(1, 37);
		case BlockType::Dirt: return sf::Vector2f(1, 19);
		case BlockType::Grass: return sf::Vector2f(37, 1);
		default: return sf::Vector2f(19, 37);
	}
}
