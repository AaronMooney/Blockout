#ifndef BALL_HPP
#define BALL_HPP

#include <core.hpp>

struct Ball : public Circle {
	sf::Vector2f velocity{ -BALL_VELOCITY,-BALL_VELOCITY };
	Ball(float x, float y, bool isActive = false);
	void update(sf::Time deltaTime);
	bool isActive;
};
#endif