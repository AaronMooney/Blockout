#include "Ball.hpp"

Ball::Ball(float x, float y,bool active):
	isActive{ active } {
	shape.setPosition({ x,y });
	shape.setRadius(BALL_RADIUS);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin({ BALL_RADIUS,BALL_RADIUS });
}

void Ball::update(sf::Time deltaTime) {
	shape.move(velocity*deltaTime.asSeconds());

	if (left() < 0) {
		velocity.x = BALL_VELOCITY;
	}
	else if (right() > WINDOW_WIDTH) {
		velocity.x = -BALL_VELOCITY;
	}

	if (top() < 0) {
		velocity.y = BALL_VELOCITY;
	}
	else if (bottom() > WINDOW_HEIGHT) {
		velocity.y = -BALL_VELOCITY;
	}
	if (y() > WINDOW_HEIGHT / 2) isActive = true;
}