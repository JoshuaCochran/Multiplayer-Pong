#include "MainMenu.h"
#include <iostream>

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	//Load menu image from file
	sf::Texture image;
	if (!image.loadFromFile("Data/Images/Menus/mainmenu.png"))
		std::cout << "ERROR: Cannot load mainmenu.png" << std::endl;
	else
		std::cout << "Successfully loaded mainmenu.png" << std::endl;
	
	sf::Sprite sprite(image);

	//Setup clickable regions


	//Singleplayer menu item coordinates
	MenuItem spButton;
	spButton.rect.top = 50;
	spButton.rect.height = 105;
	spButton.rect.left = 148;
	spButton.rect.width = 530;
	spButton.action = SinglePlayer;


	//Multiplayer menu item coordinates
	MenuItem mpButton;
	mpButton.rect.top = 220;
	mpButton.rect.height = 105;
	mpButton.rect.left = 148;
	mpButton.rect.width = 530;
	mpButton.action = Multiplayer;


	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 395;
	exitButton.rect.height = 105;
	exitButton.rect.left = 148;
	exitButton.rect.width = 530;
	exitButton.action = Exit;

	_menuItems.push_back(spButton);
	_menuItems.push_back(mpButton);
	_menuItems.push_back(exitButton);

	window.clear();
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list <MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (x > menuItemRect.left
			&& x < menuItemRect.left + menuItemRect.width
			&& y > menuItemRect.top
			&& y < menuItemRect.height + menuItemRect.top
			)
			return (*it).action;
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			else if (menuEvent.type == sf::Event::Closed)
				return Exit;
		}
	}
}