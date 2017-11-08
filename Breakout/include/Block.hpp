#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "core.hpp"

struct Block : public Rectangle {
	bool destroyed{ false };
	int health;
	float regen{ REGEN_TIME };
	int blockType;

	Block(float x, float y, int type = 0);
	void update(sf::Time deltaTime);
};
#endif