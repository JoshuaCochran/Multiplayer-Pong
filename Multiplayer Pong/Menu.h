#ifndef _MENU_H
#define _MENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

enum MenuType{
	Main, Multiplayer, Host, Join
};

class Menu
{
public:
	enum MenuResult {
		Nothing, Exit, SinglePlayer, Multiplayer, Host, Join, MpCancel
	};

	Menu(sf::RenderWindow& window, MenuType _menuType);

	MenuResult Show(sf::RenderWindow& window);
	MenuType menuType;

private:

	struct MenuItem
	{
		sf::Rect<int> rect;
		MenuResult action;
	};

	sf::Texture image;
	sf::Sprite sprite;
	std::list<MenuItem> _menuItems;

	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);

};

#endif