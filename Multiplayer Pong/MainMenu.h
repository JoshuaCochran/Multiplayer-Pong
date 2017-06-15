#ifndef _MAINMENU_H
#define _MAINMENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class MainMenu
{
public:
	enum MenuResult {
		Nothing, Exit, SinglePlayer, Multiplayer
	};

	struct MenuItem
	{
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};

#endif