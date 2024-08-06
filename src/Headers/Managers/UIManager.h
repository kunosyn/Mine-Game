#pragma once

#include <SFML/Graphics.hpp>


class UIManager {
public:
	UIManager(void);

	void drawUI (sf::RenderWindow* window) const;
};
