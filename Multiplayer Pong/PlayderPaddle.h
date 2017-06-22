#ifndef _PLAYERPADDLE_H
#define _PLAYERPADDLE_H

#include "VisualGameObject.h"

class PlayerPaddle :
	public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(sf::Time elapsedTime, sf::Event input);
	void Draw(sf::RenderWindow& window);

	float GetVelocity() const;

private:
	float _velocity; // -- left ++ right
	float _maxVelocity;

};

#endif