#include "Block.hpp"
#include "core.hpp"

Block::Block(float x, float y, int type) {
	shape.setPosition({ x,y });
	shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin({ BLOCK_WIDTH / 2.0f,BLOCK_HEIGHT / 2.0f });
	blockType = type;
	switch (type) {
	//regenerating
	case (1):
	{
		shape.setFillColor(sf::Color::Cyan);
		health = (2);
		break;
	}
	//armored
	case (2):
	{
		health = 3;
		shape.setFillColor(sf::Color::Yellow);
		break;
	}
	default:
	{
		health = 1;
		break;
	}
	}

}

void Block::update(sf::Time deltaTime)
{
	if (health <= 0) {
		destroyed = true;
		return;
	}
	switch (blockType) {
	//regenerating
	case (1):
	{
		if (health == 1) {
			regen -= deltaTime.asSeconds();
			shape.setFillColor(sf::Color::White);

			if (regen <= 0) {
				health++;
				if (health >= 2) health = 2;
				shape.setFillColor(sf::Color::Cyan);
				regen = REGEN_TIME;
			}
		}
		break;
	}
	//armored
	case (2):
	{
		if (health == 2) shape.setFillColor(sf::Color::Magenta);
		if (health == 1) shape.setFillColor(sf::Color::Green);
		break;
	}
	}
}
