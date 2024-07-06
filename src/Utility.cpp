#include "Headers/Utility.h"

float Utility::lerp (float start, float end, float speed) {
	return start + speed * (end - start);
}

sf::Vector2f Utility::lerp (const sf::Vector2f& start, const sf::Vector2f& end, float speed) {
	return sf::Vector2f(lerp(start.x, end.x, speed), lerp(start.y, end.y, speed));
}
 
float Utility::getVectorMagnitude (const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
	sf::Vector2f difference = vec1 - vec2;
	return std::sqrt(difference.x * difference.x + difference.y * difference.y);
}