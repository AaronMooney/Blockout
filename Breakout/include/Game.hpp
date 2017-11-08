#ifndef GAME_HPP
#define GAME_HPP

#include "core.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "physics.hpp"
#include <vector>

class Game {
public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    Game();
	void init(int level);
	void build(int level);
    void run();
    
private:
    bool processEvents();
    void update(sf::Time deltaTime);
    void render();
	void getLetterboxView(sf::View &view, int windowWidth, int windowHeight);
    
    sf::RenderWindow window;
	int level;
    
    // game specific code
	Paddle paddle;
	sf::View view;
	std::vector<Block> blocks;
	std::vector<Ball> balls;

};
#endif