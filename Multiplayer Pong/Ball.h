#ifndef _BALL_H
#define _BALL_H

#include "VisualGameObject.h"

class Ball :
	public VisibleGameObject
{
public:
	Ball();
	virtual ~Ball();
	void Update(float);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
};

#endif