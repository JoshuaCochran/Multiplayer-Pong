#include "PlayderPaddle.h"
#include "Engine.h"

PlayerPaddle::PlayerPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	Load("data/images/objects/paddle.png");
	GetSprite().setPosition(Engine::SCREEN_WIDTH / 2, 0);
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow& window)
{
	VisibleGameObject::Draw(window);
}

float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}

void PlayerPaddle::Update(sf::Time elapsedTime, sf::Event input)
{
	if (input.type == sf::Event::KeyPressed || input.type == sf::Event::KeyReleased)
	{
		if (input.key.code == sf::Keyboard::Left)
			_velocity -= 5.0f;
		else if (input.key.code == sf::Keyboard::Right)
			_velocity += 5.0f;
		else if (input.key.code == sf::Keyboard::Down)
			_velocity = 0.0f;
	}

	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = GetPosition();

	if (pos.x <= 0
		|| pos.x >= Engine::SCREEN_WIDTH - GetSprite().getGlobalBounds().width)
		_velocity = -_velocity;

	GetSprite().move(_velocity * elapsedTime.asSeconds(), 0);
}