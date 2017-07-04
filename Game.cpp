#include "Game.hpp"

Game::Game() : window(sf::VideoMode(1500, 1000), "Sorta Flappy Bird!"), floor(sf::Vector2f(1500, 100)), 
			   bground(sf::Vector2f(1500, 1000)), pipeColor(26, 255, 26) {
	
	init();

}

std::pair<sf::RectangleShape, sf::RectangleShape> makePipePair() {
	sf::RectangleShape top(sf::Vector2f(200, 200 + rand() % 300));
	sf::RectangleShape bot(sf::Vector2f);
}

void Game::init() {
	
	floor.setPosition(0, 900);
	floor.setFillColor(sf::Color(0, 102, 0));
	
	bground.setPosition(0, 0);
	bground.setFillColor(sf::Color(204, 245, 255));

	birdTexture.loadFromFile("birdie.png");
	birdie.setTexture(birdTexture);
	birdie.setPosition(0, 400);
	birdie.setScale(sf::Vector2f(.75, .75));

	deathTxt.setCharacterSize(50);
	deathTxt.setFillColor(sf::Color::Red);
	deathTxt.setString("You died!");
	deathTxt.setCharacterSize(150);
	deathTxt.setPosition(550, 400);

	winTxt.setCharacterSize(150);
	winTxt.setFillColor(sf::Color::Blue);
	winTxt.setString("You Win!");
	winTxt.setPosition(550, 400);

	if (!font.loadFromFile("tnr.ttf")) {
		std::cout << "Unable to load font";
	}

	deathTxt.setFont(font);
	winTxt.setFont(font);

	

	dx = 0;
	dy = 0;
	d2y = 0;
	cdTime = 0;
	isJumping = 0;
	started = 0;
	birdieAlive = 1;
	win = 0;
}

void Game::loop() {
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();

		jmpCD = jumpCooldownTimer.getElapsedTime();
		if (jmpCD.asMilliseconds() > 300) {
			isJumping = false;
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space && !isJumping) {
					if (!started) {
						started = 1;
						d2y = .005;
					              
					}
					isJumping = true;
					dy = -1.5;
					jmpCD = jumpCooldownTimer.restart();
				}
			}
		}

		//collision detection:  if birdie's position = floor position crash!


		if (birdie.getPosition().y > 1000 || birdie.getPosition().y < 0) {
			d2y = 0;
			dy = .5;
			dx = 0;
			birdieAlive = false;

		}
		if (birdie.getPosition().x > 1400) {
			win = true;
		}
		dy += d2y * elapsed.asMilliseconds();
		birdie.move(elapsed.asMilliseconds() * dx, elapsed.asMilliseconds() * dy);

		window.clear();
		window.draw(bground);
		for (sf::RectangleShape pipe : pipes) {
			if (birdie.getGlobalBounds().intersects(pipe.getGlobalBounds())) {
				d2y = 0;
				dy = .5;
				dx = 0;
				birdie.rotate(180);
				birdieAlive = false;
			}
			window.draw(pipe);
		}

		window.draw(floor);
		window.draw(birdie);

		if (!birdieAlive) {
			window.draw(deathTxt);
		}
		if (win) {
			d2y = 0;
			dx = 0;
			dy = 0;
			window.draw(winTxt);
		}

		window.display();

	}
}