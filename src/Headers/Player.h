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

	Player(int id);
	~Player(void);

	void move(PlayerMoveAxis axis, float translateBy);
	bool isMoving(void) const;

	void draw(sf::RenderWindow* renderWindow);
	void applyPhysics(void);

	int getId(void) const;
	sf::FloatRect getViewBounds(void) const;

private:
	void updateState(void);
	void checkCollisions (const sf::Vector2f& requestedLocation);

	int m_id;
	sf::RectangleShape m_character;
};
