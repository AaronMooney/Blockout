#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "core.hpp"

struct Paddle : Rectangle {
	sf::Vector2f velocity;

	Paddle(float x, float y);
	
	void update(sf::Time deltaTime);
	void automatic(sf::Time deltaTime, float ballX);
};
#endif
