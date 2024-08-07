#include <Managers/TextureManger.h>

TextureManager::TextureManager (void) 
	: m_blockAtlas()
{
	if (!m_blockAtlas.loadFromFile("Textures/block_textures.png")) {
		throw std::runtime_error("An error occurred while loading the block texture atlas.");
	}
}


const sf::Texture& TextureManager::getBlockAtlas () const {
	return m_blockAtlas;
}
