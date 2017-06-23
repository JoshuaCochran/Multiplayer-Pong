#include "EnemyPaddle.h"
#include "Engine.h"

EnemyPaddle::EnemyPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	Load("data/images/objects/paddle.png");

	GetSprite().setPosition(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT - GetSprite().getLocalBounds().height);
}

EnemyPaddle::~EnemyPaddle()
{
}

void EnemyPaddle::Draw(sf::RenderWindow& window)
{
	VisibleGameObject::Draw(window);
}

float EnemyPaddle::GetVelocity() const
{
	return _velocity;
}

void EnemyPaddle::Update(sf::Time elapsedTime)
{
	sf::Vector2f pos = GetPosition();

	if (pos.x <= 0
		|| pos.x >= Engine::SCREEN_WIDTH - GetSprite().getGlobalBounds().width)
		_velocity = -_velocity;

	GetSprite().move(_velocity * elapsedTime.asSeconds(), 0);
}

void EnemyPaddle::Update(sf::Time elapsedTime, ObjectPacket packet)
{
	if (lastPacketTime > packet.timeStamp || packet.type == ObjectType::empty)
		Update(elapsedTime);
	else
	{
		_velocity = packet.velocity;

		sf::Vector2f pos = GetPosition();

		if (pos.x <= 0
			|| pos.x >= Engine::SCREEN_WIDTH - GetSprite().getGlobalBounds().width)
			_velocity = -_velocity;

		GetSprite().move(_velocity * elapsedTime.asSeconds(), 0);
	}
}

