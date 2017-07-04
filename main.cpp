#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "Sorta Flappy Bird!");
	sf::RectangleShape floor(sf::Vector2f(1500, 100));
	floor.setPosition(0, 900);
	floor.setFillColor(sf::Color(0, 102, 0));
	sf::RectangleShape bground(sf::Vector2f(1500, 1000));
	bground.setPosition(0, 0);
	bground.setFillColor(sf::Color(204, 245, 255));
	sf::Texture birdTexture;
	birdTexture.loadFromFile("birdie.png");
	sf::Sprite birdie;
	birdie.setTexture(birdTexture);
	birdie.setPosition(0, 400);
	birdie.setScale(sf::Vector2f(.75, .75));
	sf::Text deathTxt;
	deathTxt.setCharacterSize(50);
	deathTxt.setFillColor(sf::Color::Red);
	deathTxt.setString("You died!");
	sf::Text winTxt;
	deathTxt.setCharacterSize(150);
	winTxt.setCharacterSize(150);
	winTxt.setFillColor(sf::Color::Blue);
	winTxt.setString("You Win!");
	deathTxt.setPosition(550, 400);
	winTxt.setPosition(550, 400);
	sf::Font font;
	if (!font.loadFromFile("tnr.ttf")) {
		std::cout << "Unable to load font";
	}
	deathTxt.setFont(font);
	winTxt.setFont(font);



	std::vector<sf::RectangleShape> pipes;
	sf::RectangleShape pipebot1(sf::Vector2f(100, 200));
	pipebot1.setPosition(300, 700);
	sf::RectangleShape pipetop1(sf::Vector2f(100, 175));
	pipetop1.setPosition(300, 000);
	sf::RectangleShape pipebot2(sf::Vector2f(100, 325));
	pipebot2.setPosition(800, 575);
	sf::RectangleShape pipetop2(sf::Vector2f(100, 100));
	pipetop2.setPosition(800, 000);
	sf::RectangleShape pipebot3(sf::Vector2f(100, 250));
	pipebot3.setPosition(1300, 750);
	sf::RectangleShape pipetop3(sf::Vector2f(100, 350));
	pipetop3.setPosition(1300, 000);

	pipes.push_back(pipebot1);
	pipes.push_back(pipebot2);
	pipes.push_back(pipetop1);
	pipes.push_back(pipetop2);
	pipes.push_back(pipebot3);
	pipes.push_back(pipetop3);

	//text to desplay if birdie hits pipe or floor

	sf::Color pipeColor(26, 255, 26);
	for (auto it = pipes.begin(); it != pipes.end(); ++it) {
		(*it).setFillColor(pipeColor);
	}
	float dx = 0;
	float dy = 0;
	float d2y = 0;
	sf::Clock clock;
	sf::Clock jumpCooldownTimer;
	sf::Time jmpCD;
	int cdTime = 0;
	bool isJumping = 0;
	bool started = 0;
	bool birdieAlive = true;
	bool win = false;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();

		jmpCD = jumpCooldownTimer.getElapsedTime();
		if (jmpCD.asMilliseconds() > 300) {
			//dy = .85;
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
						dx = .3;
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

	return 0;
} 