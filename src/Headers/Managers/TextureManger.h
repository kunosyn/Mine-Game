#pragma once

#include <SFML/Graphics.hpp>


class TextureManager {
public:
		TextureManager(void);

		const sf::Texture& getBlockAtlas(void) const;

private:
		sf::Texture m_blockAtlas;
};