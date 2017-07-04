#pragma once
#ifndef GAME2_GAME_HPP
#define GAME2_GAME_HPP

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <queue>
#include <random>

class Game {
private:
	sf::RenderWindow window;
	sf::RectangleShape floor;
	sf::RectangleShape bground;
	sf::Texture birdTexture;
	sf::Sprite birdie;
	sf::Text deathTxt;
	sf::Text winTxt;
	sf::Font font;
	std::queue<std::pair<sf::RectangleShape, sf::RectangleShape>> pipes;
	sf::Color pipeColor;
	sf::Clock clock;
	sf::Clock jumpCooldownTimer;
	sf::Time jmpCD;
	int cdTime;
	bool isJumping;
	bool started;
	bool birdieAlive;
	bool win;
	float dx;
	float dy;
	float d2y;
	
	std::pair<sf::RectangleShape, sf::RectangleShape> makePipePair();


public:
	Game();
	void update(int timePassed);
	void init();
	void loop();
};


#endif

