#pragma once

#include <SFML/Graphics.hpp>


namespace Utility {
	float lerp(float start, float end, float speed);
	sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float speed);

	float getVectorMagnitude(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
	float getWorldSpaceMagnitude(int blockUnit);
}
