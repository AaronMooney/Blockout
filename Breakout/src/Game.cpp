#include <iostream>

#include "Game.hpp"

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Blockout"),
	paddle(WINDOW_WIDTH/2, WINDOW_HEIGHT-50),
	level{ 1 }{

    
    window.setFramerateLimit(60);
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	getLetterboxView(view, WINDOW_WIDTH, WINDOW_HEIGHT);
	init(level);
}

void Game::init(int lvl) {
	balls.clear();
	blocks.clear();

	level = lvl;
	balls.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, true);
	paddle.shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);

	build(level);
}

void Game::build(int level) {
	//normal wall
	if (level == 1 || level == 2) {
		for (int c{ 0 }; c < BLOCK_COLUMNS; ++c)
			for (int r{ 0 }; r < BLOCK_ROWS; ++r) {
				blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
			}
	}
	//multiple balls spwan in wall
	if (level == 3) {
		for (int c{ 0 }; c < BLOCK_COLUMNS; ++c)
			for (int r{ 0 }; r < BLOCK_ROWS + 4; ++r) {
				if ( (c == 3 && r==2)||(c==8 && r==2) && r > 0 && r < (BLOCK_ROWS+4) - 1 && c > 0 && c < BLOCK_COLUMNS - 1) {
					balls.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
				}
				blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5));
				//erase blocks that balls spawn in
				if ((c == 3 && r == 2)) {
					blocks.erase(blocks.begin() + 26);
				}
				else if ((c == 8 && r == 2)) {
					blocks.erase(blocks.end() - 1);
				}
			}
	}
	//different types of blocks
	if (level == 4) {
		for (int c{ 0 }; c < BLOCK_COLUMNS; ++c)
			for (int r{ 0 }; r < BLOCK_ROWS + 4; ++r) {
				int type;
				switch (rand() % 12) {
				case(1):
				{
					type = 1;
					break;
				}
				case(2):
				{
					type = 2;
					break;
				}
				case(3):
				{
					type = 2;
					break;
				}
				case(4):
				{
					type = 2;
					break;
				}
				case(5):
				{
					type = 1;
					break;
				}
				default:
					type = 0;
					break;
				}
				blocks.emplace_back((c + 1)*(BLOCK_WIDTH + 3) + 22, (r + 2)*(BLOCK_HEIGHT + 5), type);
			}
	}
}


void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        if (!processEvents()) break;
        update(clock.restart());
        render();
    }
}


bool Game::processEvents() {
    
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
            break;
        }
    }

	if (event.type == sf::Event::Resized)  getLetterboxView(view, event.size.width, event.size.height);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) init(1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) init(2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) init(3);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) init(4);

	if (level == 2) return true;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) return false;
    
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		paddle.velocity.x = -PADDLE_VELOCITY;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		paddle.velocity.x = PADDLE_VELOCITY;
	else
		paddle.velocity.x = 0;

    return true;
}

void Game::update(sf::Time deltaTime) {

	if (level == 2) {
		paddle.automatic(deltaTime, balls[0].x());
	} else paddle.update(deltaTime);


	for (auto& ball : balls) {
		ball.update(deltaTime);
		testCollision(paddle, ball);
		for (auto& block : blocks) {
			testCollision(block, ball);
			block.update(deltaTime);
		}
	}

	blocks.erase(std::remove_if(std::begin(blocks), std::end(blocks), [](const Block& block) {
		return block.destroyed;
	}),
		std::end(blocks)
		);

}

void Game::getLetterboxView(sf::View &view, int windowWidth, int windowHeight) {
	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio) horizontalSpacing = false;

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void Game::render() {
    
    window.clear(sf::Color::Black);
	window.setView(view);
   
	for (auto& ball : balls) window.draw(ball.shape);
	window.draw(paddle.shape);
	for (auto& block : blocks) window.draw(block.shape);
    window.display();
}


