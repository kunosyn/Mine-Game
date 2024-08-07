#pragma once

#include <Classes/Player.h>
#include <Constants.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_set>


class InputManager {
public:
	InputManager(sf::RenderWindow* window, Player*& player, bool& isGamePaused);

	void handleInput(const sf::Event& event);
	void onKeyInput(const sf::Event::KeyEvent& key);
	bool isKeyDown(sf::Keyboard::Key key) const;

	void update(void);

private:
	sf::RenderWindow* m_window;
	Player*& m_player;
	bool& m_isGamePaused;

	std::unordered_set<sf::Keyboard::Key> m_heldKeys;
};
