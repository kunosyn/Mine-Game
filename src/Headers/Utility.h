#pragma once

#include <SFML/Graphics.hpp>


namespace Utility {
	float lerp(float start, float end, float speed);
	sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float speed);
}
