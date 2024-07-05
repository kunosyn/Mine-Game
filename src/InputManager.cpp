#include "Headers/InputManager.h"

InputManager::InputManager (sf::RenderWindow* window, Player* player) 
	: m_window(window), m_player(player)
{ }


void InputManager::continuousInputChecks (void) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_player->move(PlayerMoveAxis::Y, -m_player->m_walkspeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_player->move(PlayerMoveAxis::X, -m_player->m_walkspeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_player->move(PlayerMoveAxis::Y, m_player->m_walkspeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_player->move(PlayerMoveAxis::X, m_player->m_walkspeed);
}

void InputManager::handleInput (const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		onKeyDown(event.key);
	} 
	else if (event.type == sf::Event::KeyReleased) {
		onKeyUp(event.key);
	}
}

void InputManager::onKeyDown (const sf::Event::KeyEvent& event) { }
void InputManager::onKeyUp (const sf::Event::KeyEvent& event) { }
