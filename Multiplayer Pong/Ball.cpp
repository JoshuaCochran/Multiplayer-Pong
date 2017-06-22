#include "Ball.h"
#include "Engine.h"

Ball::Ball() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f),
	gen(rd()),
	distrubution(0.0f, 360.0f)
{
	Load("data/images/objects/ball.png");

	GetSprite().setPosition(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

	std::uniform_real_distribution<float> distrubution(0.0f, 360.0f);
	_angle = distrubution(gen);
	distrubution.reset();

	lastPacketTime = -1;
}

Ball::~Ball()
{
}

void Ball::Update(sf::Time elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime.asSeconds();

	float moveAmount = _velocity * elapsedTime.asSeconds();

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

	if (GetSprite().getPosition().y >= Engine::SCREEN_HEIGHT || GetSprite().getPosition().y <= 0)
	{
		GetSprite().setPosition(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

		_angle = distrubution(gen);
		distrubution.reset();

		_velocity = 220.0f;
		_elapsedTimeSinceStart = 0.0f;
	}
	else
		GetSprite().move(moveByX, moveByY);
}

void Ball::Update(sf::Time elapsedTime, ObjectPacket packet)
{
	if (lastPacketTime < packet.timeStamp || packet.type == ObjectType::empty)
		Update(elapsedTime);
	else
	{
		_elapsedTimeSinceStart += elapsedTime.asSeconds();

		if (packet.connectionType == ConnectionType::host)
		{
			_elapsedTimeSinceStart = packet.timeStamp;
			_velocity = packet.velocity;
			_angle = packet.angle;
		}

		/*if (_elapsedTimeSinceStart < 3.0f)
			return;*/

		float moveAmount = _velocity * elapsedTime.asSeconds();

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

		if (GetSprite().getPosition().y >= Engine::SCREEN_HEIGHT || GetSprite().getPosition().y <= 0)
		{
			GetSprite().setPosition(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2);

			_angle = distrubution(gen);
			distrubution.reset();

			_velocity = 220.0f;
			_elapsedTimeSinceStart = 0.0f;
		}
		else
			GetSprite().move(moveByX, moveByY);

		lastPacketTime = packet.timeStamp;
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

float Ball::GetAngle() const
{
	return _angle;
}

float Ball::GetVelocity() const
{
	return _velocity;
}