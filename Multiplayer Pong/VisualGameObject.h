#ifndef _VISIBLEGAMEOBJECT_H
#define _VISIBLEGAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Server.h"

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(sf::Time elapsedTime);
	virtual void Update(sf::Time elapsedTime, ObjectPacket packet);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual bool IsLoaded() const;
	virtual sf::Rect<float> GetBoundingRect() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};

#endif