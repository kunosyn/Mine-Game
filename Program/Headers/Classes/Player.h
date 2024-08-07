#pragma once

#include <SFML/Graphics.hpp>

enum class PlayerState {
	Idle,
	Walking,
	Jumping
};

enum class PlayerMoveAxis {
	X,
	Y
};


class Player {
public:
	int m_health, m_maxHealth;
	float m_walkspeed;

	bool m_isGrounded;
	sf::Vector2f m_acceleration, m_velocity, m_position;
	PlayerState m_state;

	sf::View m_view;

	Player(int id, const float& delta);
	~Player(void);

	void move(PlayerMoveAxis axis, float translateBy);
	bool eligibleForGeneration(void);

	void draw(sf::RenderWindow* renderWindow);
	void applyPhysics(void);

	int getId(void) const;
	sf::FloatRect getViewBounds(void) const;

private:
	void updateState(void);
	void checkCollisions (const sf::Vector2f& requestedLocation);

	int m_id;
	const float& m_deltaTime;
	sf::RectangleShape m_character;
	sf::Vector2f m_lastRenderPosition;
};
