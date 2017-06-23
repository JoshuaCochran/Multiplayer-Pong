#ifndef _BALL_H
#define _BALL_H

#include "PlayderPaddle.h"
#include <random>

class Ball :
	public VisibleGameObject
{
public:
	Ball();
	virtual ~Ball();
	void Update(sf::Time elapsedTime);
	void Update(sf::Time elapsedTime, PlayerPaddle* player1);
	void Update(sf::Time elapsedTime, ObjectPacket& packet, PlayerPaddle* player1);

	float GetVelocity() const;
	float GetAngle() const;

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> distrubution;

	float lastPacketTime;
};

#endif