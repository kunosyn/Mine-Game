#include "../Headers/Managers/TextureManger.h"

TextureManager::TextureManager (void) 
	: m_blockAtlas()
{

}


const sf::Texture& TextureManager::getBlockAtlas () const {
	return m_blockAtlas;
}