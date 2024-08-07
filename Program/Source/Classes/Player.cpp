#include <Classes/Player.h>
#include <Utility.h>
#include <Constants.h>

#include <iostream>


// Public Functions
Player::Player (int id, const float& delta)
	: m_maxHealth(100), m_health(100), 
	m_walkspeed(100.0f),
	m_id(id), 
	m_state(PlayerState::Idle), m_isGrounded(true),
	m_position(sf::Vector2f(0, 0)),
	m_view(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)),
	m_deltaTime(delta),
	m_lastRenderPosition(sf::Vector2f(0, 0))
{
	std::cout << "[PlayerManager]: Player " << m_id << " created." << std::endl;

	m_character = sf::RectangleShape(sf::Vector2f(15.f, 20.f));

	m_character.setFillColor(sf::Color::Cyan);
	m_character.setPosition(m_position);
}

Player::~Player (void) {
	std::cout << "[PlayerManager]: Player " << m_id << " destroyed." << std::endl;
}


void Player::move (PlayerMoveAxis axis, float translateBy) {
	if (axis == PlayerMoveAxis::X) {
		m_position.x += translateBy * m_deltaTime;
	} 
	else if (axis == PlayerMoveAxis::Y) {
		m_position.y += translateBy * m_deltaTime;
	}
}

bool Player::eligibleForGeneration(void) {
	if (Utility::getVectorMagnitude(m_position, m_lastRenderPosition) > 50) {
		m_lastRenderPosition = m_position;

		return true;
	}

	return false;
}

void Player::draw (sf::RenderWindow* render_window) {
	m_character.setPosition(Utility::lerp(m_character.getPosition(), m_position, .1));
	m_view.setCenter(Utility::lerp(m_view.getCenter(), m_position, .1));

	render_window->draw(m_character);
}

int Player::getId (void) const {
	return m_id;
}

void Player::applyPhysics (void) {
	if (m_acceleration.x > 0 || m_acceleration.y > 0) {
		m_velocity += m_acceleration * m_deltaTime;
	}
	else {
		m_acceleration = Utility::lerp(m_acceleration, sf::Vector2f(0, 0), .1f * m_deltaTime); // Apply wind resistance
	}


	if (m_velocity.x > 0 || m_velocity.y > 0) {
		m_position += m_velocity * m_deltaTime;
	}
	else {
		m_velocity = Utility::lerp(m_velocity, sf::Vector2f(0, 0), .1f * m_deltaTime); // Apply friction
	}

	if (m_state != PlayerState::Jumping) {
		m_acceleration += sf::Vector2f(0, GRAVITY * m_deltaTime);
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
