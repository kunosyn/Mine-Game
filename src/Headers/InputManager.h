#pragma once

#include "Player.h"

#include <SFML/Graphics.hpp>
#include <memory>


class InputManager {
public:
	InputManager(sf::RenderWindow* window, Player* player);

	void handleInput(const sf::Event& event);
	void onKeyDown(const sf::Event::KeyEvent& key);
	void onKeyUp(const::sf::Event::KeyEvent& key);

	void continuousInputChecks(void);

private:
	sf::RenderWindow* m_window;
	Player* m_player;
};
