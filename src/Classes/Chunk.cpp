#include "../Headers/Classes/Chunk.h"
#include <algorithm>


Chunk::Chunk (int x, int y) 
	: m_vertices(sf::Triangles), m_position(x, y) 
{ } 

void Chunk::push (const TerrainBlock& block) {
	sf::Vertex tri[6];

	// Draw two triangles to form a quad
	tri[0].position = block.position;
	tri[1].position = block.position + sf::Vector2f(BLOCK_WIDTH, 0);
	tri[2].position = block.position + sf::Vector2f(BLOCK_WIDTH, BLOCK_WIDTH);

	tri[3].position = block.position;
	tri[4].position = block.position + sf::Vector2f(BLOCK_WIDTH, BLOCK_WIDTH);
	tri[5].position = block.position + sf::Vector2f(0, BLOCK_WIDTH);

	
	// Apply textures to both halves of the quad
	sf::Vector2f texCoords = getTextureCoordinates(block.type);

	tri[0].texCoords = texCoords;
	tri[1].texCoords = texCoords + sf::Vector2f(16, 0);
	tri[2].texCoords = texCoords + sf::Vector2f(16, 16);

	tri[3].texCoords = texCoords;
	tri[4].texCoords = texCoords + sf::Vector2f(16, 16);
	tri[5].texCoords = texCoords + sf::Vector2f(0, 16);

	for (int i = 0; i < 6; ++i)
		m_vertices.append(tri[i]);
}

void Chunk::clear (void) {
	m_vertices.clear();
}

const sf::VertexArray& Chunk::getVertices (void) const {
	return m_vertices;
}

const sf::Vector2f& Chunk::getPosition (void) const {
	return m_position;
}

const std::size_t Chunk::getVertexCount (void) const {
	return getVertices().getVertexCount();
}

bool Chunk::intersects (const sf::FloatRect& bounds) const {
	return m_vertices.getBounds().intersects(bounds);
}

bool Chunk::operator == (const Chunk& other) const {
	return m_position.x == other.m_position.x && m_position.y == other.m_position.y;
}

size_t Chunk::Hash::operator () (const Chunk& other) const {
	std::size_t hx = std::hash<float>()(other.m_position.x);
	std::size_t hy = std::hash<float>()(other.m_position.y);

	return hx ^ (hy << 1);
}


// Private Functions
sf::Vector2f Chunk::getTextureCoordinates (BlockType type) {
	switch (type) {
		case BlockType::Bedrock: return sf::Vector2f(2, 2);
		case BlockType::Stone: return sf::Vector2f(62, 2);
		case BlockType::Dirt: return sf::Vector2f(42, 22);
		case BlockType::Grass: return sf::Vector2f(22, 42);
		default: return sf::Vector2f(22, 22);
	}
}
