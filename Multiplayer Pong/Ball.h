#ifndef _BALL_H
#define _BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::Vector2f position;

	sf::RectangleShape ballShape;

	float xVelocity = .2f;
	float yVelocity = .2f;

public:
	Ball(float startX, float startY);
	
	sf::FloatRect getPosition();

	sf::RectangleShape getShape();

	float getXVelocity();

	void reboundSides();

	void reboundBotOrTop();

	void hitBottom();

	void update();

};

#endif