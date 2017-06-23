#ifndef _ENEMYPADDLE_H
#define _ENEMYPADDLE_H

#include "Ball.h"

class EnemyPaddle :
	public VisibleGameObject
{
public:
	EnemyPaddle();
	~EnemyPaddle();

	void Update(sf::Time elapsedTime);
	void Update(sf::Time elapsedTime, ObjectPacket packet);
	
	void Draw(sf::RenderWindow& window);

	float GetVelocity() const;

private:
	float _velocity; // -- left ++ right
	float _maxVelocity;

	float lastPacketTime;

	Ball* ball;
};


#endif
