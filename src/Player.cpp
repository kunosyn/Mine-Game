#include "Headers/Player.h"
#include "Headers/Utility.h"
#include "Headers/Constants.h"

#include <iostream>


// Public Functions
Player::Player (int id)
	: m_maxHealth(100), m_health(100), 
	m_walkspeed(5.0f),
	m_id(id), 
	m_state(PlayerState::Idle), m_isGrounded(true),
	m_position(sf::Vector2f(0, 0)),
	m_view(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT))
{
	std::cout << "[PlayerManager]: Player " << m_id << " created." << std::endl;

	m_character = sf::RectangleShape(sf::Vector2f(15.f, 20.f));

	m_character.setFillColor(sf::Color::Cyan);
	m_character.setPosition(m_position);

	m_view.zoom(4.f);
}

Player::~Player (void) {
	std::cout << "[PlayerManager]: Player " << m_id << " destroyed." << std::endl;
}


void Player::move (PlayerMoveAxis axis, float translateBy) {
	if (axis == PlayerMoveAxis::X) {
		m_position.x += translateBy;
	} 
	else if (axis == PlayerMoveAxis::Y) {
		m_position.y += translateBy;
	}
}

bool Player::isMoving (void) const {
	sf::Vector2f characterPos = m_character.getPosition();
	return std::fabs(m_position.x - characterPos.x) > 10 || std::fabs(m_position.y - characterPos.y) > 10;
}

void Player::draw (sf::RenderWindow* render_window) {
	m_character.setPosition(Utility::lerp(m_character.getPosition(), m_position, .1));
	m_view.setCenter(Utility::lerp(m_view.getCenter(), m_position, .1));

	render_window->setView(m_view);
	render_window->draw(m_character);
}

int Player::getId (void) const {
	return m_id;
}

void Player::applyPhysics (void) {
	if (m_acceleration.x > 0 || m_acceleration.y > 0) {
		m_velocity += m_acceleration;
	}
	else {
		m_acceleration = Utility::lerp(m_acceleration, sf::Vector2f(0, 0), .1f); // Apply wind resistance
	}


	if (m_velocity.x > 0 || m_velocity.y > 0) {
		m_position += m_velocity;
	}
	else {
		m_velocity = Utility::lerp(m_velocity, sf::Vector2f(0, 0), .1f); // Apply friction
	}

	if (m_state != PlayerState::Jumping) {
		m_acceleration += sf::Vector2f(0, GRAVITY);
	}


	if (m_isGrounded) {
		if (m_velocity.y > 0)
			m_velocity.y = 0;

		if (m_acceleration.y > 0)
			m_acceleration.y = 0;
	}
}

sf::FloatRect Player::getViewBounds (void) const {
	sf::Vector2f center = m_view.getCenter();
	sf::Vector2f size = m_view.getSize();

	return sf::FloatRect(center.x - size.x / 2.f, center.y - size.y / 2.f, size.x, size.y);
}



// Private Functions
void Player::updateState (void) {

}

void Player::checkCollisions (const sf::Vector2f& requested_location) {

}
