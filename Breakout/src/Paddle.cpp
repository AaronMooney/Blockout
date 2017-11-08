#include "Paddle.hpp"

Paddle::Paddle(float x, float y) {
	shape.setPosition({ x,y });
	shape.setSize({ PADDLE_WIDTH,PADDLE_HEIGHT });
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin({ PADDLE_WIDTH / 2,PADDLE_HEIGHT / 2 });
}

void Paddle::update(sf::Time deltaTime) {
	shape.move(velocity*deltaTime.asSeconds());

	if (left() < 0) shape.move(-left(), 0);
	if (right() > WINDOW_WIDTH) shape.move(-right() + WINDOW_WIDTH, 0);
}

void Paddle::automatic(sf::Time deltaTime, float ballX) {
	update(deltaTime);
	if (x() < ballX) velocity.x = 200.0f;
	else if(x() > ballX) velocity.x = -200.0f;
	else velocity.x = 0;

}