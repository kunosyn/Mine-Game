#include "../Headers/Managers/InputManager.h"

InputManager::InputManager (
	sf::RenderWindow* window, 
	Player*& player, 
	bool& isGamePaused
) 
	: m_window(window), m_player(player), m_isGamePaused(isGamePaused)
{
	m_heldKeys.reserve(MAX_KEYS_HELD);
}


void InputManager::update (void) {
	if (isKeyDown(sf::Keyboard::W)) {
		m_player->move(PlayerMoveAxis::Y, -m_player->m_walkspeed);
	}
	
	if (isKeyDown(sf::Keyboard::A)) {
		m_player->move(PlayerMoveAxis::X, -m_player->m_walkspeed);
	}
	
	if (isKeyDown(sf::Keyboard::S)) {
		m_player->move(PlayerMoveAxis::Y, m_player->m_walkspeed);
	}
	
	if (isKeyDown(sf::Keyboard::D)) {
		m_player->move(PlayerMoveAxis::X, m_player->m_walkspeed);
	}
}

void InputManager::handleInput (const sf::Event& event) {
	if (event.type == sf::Event::EventType::KeyPressed) {
		m_heldKeys.insert(event.key.code);
		onKeyInput(event.key);
	}
	else if (event.type == sf::Event::EventType::KeyReleased) {
		m_heldKeys.erase(event.key.code);
	}
}

void InputManager::onKeyInput (const sf::Event::KeyEvent& event) {
	switch (event.code) {
		case sf::Keyboard::Escape:
			m_isGamePaused = !m_isGamePaused;
		break;
	}
}

bool InputManager::isKeyDown (sf::Keyboard::Key key) const {
	return std::find(m_heldKeys.begin(), m_heldKeys.end(), key) != m_heldKeys.end();
}
