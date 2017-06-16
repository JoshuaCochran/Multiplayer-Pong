#include "Ball.h"
#include "Engine.h"

Ball::Ball() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f)
{
	Load("data/images/objects/ball.png");

	GetSprite().setPosition(15, 15);

	srand(std::time(0));
	_angle = static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / 360));
}

Ball::~Ball()
{
}

void Ball::Update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	// Delay game from starting until 3 seconds have passed
	if (_elapsedTimeSinceStart < 3.0f)
		return;

	float moveAmount = _velocity * elapsedTime;

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

	//collide with the left side of the screen
	if (GetPosition().x + moveByX <= 0 + GetWidth() / 2 || GetPosition().x + GetHeight() / 2 + moveByX >= Engine::SCREEN_WIDTH)
	{
		//Ricochet!
		_angle = 360.0f - _angle;
		if (_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveByX = -moveByX;
	}

	
}

float Ball::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float Ball::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}