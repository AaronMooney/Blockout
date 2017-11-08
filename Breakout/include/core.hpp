#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>

constexpr int WINDOW_WIDTH{800}, WINDOW_HEIGHT{600};
constexpr float BALL_RADIUS{10.0f }, BALL_VELOCITY{ 180.0f };
constexpr float PADDLE_WIDTH{ 120.0f }, PADDLE_HEIGHT{ 20.0f };
constexpr float PADDLE_VELOCITY{ 1000.0f };
constexpr float BLOCK_WIDTH{ 60.0f }, BLOCK_HEIGHT{ 20.0f };
constexpr int BLOCK_COLUMNS{ 11 }, BLOCK_ROWS{ 4 };
constexpr float REGEN_TIME{ 5.0f };

struct Circle {
	sf::CircleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getRadius(); }
	float right() const noexcept { return x() + shape.getRadius(); }
	float top() const noexcept { return y() - shape.getRadius(); }
	float bottom() const noexcept { return y() + shape.getRadius(); }
};

struct Rectangle {
	sf::RectangleShape shape;
	float x() const noexcept { return shape.getPosition().x; }
	float y() const noexcept { return shape.getPosition().y; }
	float left() const noexcept { return x() - shape.getSize().x / 2.f; }
	float right() const noexcept { return x() + shape.getSize().x / 2.f; }
	float top() const noexcept { return y() - shape.getSize().y / 2.f; }
	float bottom() const noexcept { return y() - shape.getSize().y / 2.f; }
};

#endif

