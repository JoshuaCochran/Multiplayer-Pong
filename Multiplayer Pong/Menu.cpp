#include "Menu.h"
#include <iostream>


Menu::Menu(sf::RenderWindow& window, MenuType _menuType)
{
	menuType = _menuType;

	if (menuType == MenuType::Main)
	{
		//Load menu image from file
		if (!image.loadFromFile("Data/Images/Menus/mainmenu.png"))
			std::cout << "ERROR: Cannot load mainmenu.png" << std::endl;
		else
			std::cout << "Successfully loaded mainmenu.png" << std::endl;

		sprite.setTexture(image);

		//Setup clickable regions

		//Singleplayer menu item coordinates
		MenuItem spButton;
		spButton.rect.top = 64;
		spButton.rect.height = 136;
		spButton.rect.left = 190;
		spButton.rect.width = 678;
		spButton.action = SinglePlayer;


		//Multiplayer menu item coordinates
		MenuItem mpButton;
		mpButton.rect.top = 282;
		mpButton.rect.height = 136;
		mpButton.rect.left = 190;
		mpButton.rect.width = 678;
		mpButton.action = Multiplayer;


		//Exit menu item coordinates
		MenuItem exitButton;
		exitButton.rect.top = 506;
		exitButton.rect.height = 136;
		exitButton.rect.left = 190;
		exitButton.rect.width = 678;
		exitButton.action = Exit;

		_menuItems.push_back(spButton);
		_menuItems.push_back(mpButton);
		_menuItems.push_back(exitButton);
	}
	else if (menuType == MenuType::Multiplayer)
	{
		//Load menu image from file
		if (!image.loadFromFile("Data/Images/Menus/multiplayermenu.png"))
			std::cout << "ERROR: Cannot load multiplayermenu.png" << std::endl;
		else
			std::cout << "Successfully loaded multiplayermenu.png" << std::endl;

		sprite.setTexture(image);

		//Setup clickable regions

		//Host menu item coordinates
		MenuItem hostButton;
		hostButton.rect.top = 64;
		hostButton.rect.height = 136;
		hostButton.rect.left = 189;
		hostButton.rect.width = 678;
		hostButton.action = Host;

		//Join menu item coordinates
		MenuItem joinButton;
		joinButton.rect.top = 282;
		joinButton.rect.height = 136;
		joinButton.rect.left = 190;
		joinButton.rect.width = 678;
		joinButton.action = Join;

		//Cancel menu item coordinates
		MenuItem cancelButton;
		cancelButton.rect.top = 506;
		cancelButton.rect.height = 136;
		cancelButton.rect.left = 190;
		cancelButton.rect.width = 678;
		cancelButton.action = MpCancel;

		_menuItems.push_back(hostButton);
		_menuItems.push_back(joinButton);
		_menuItems.push_back(cancelButton);
	}
}

Menu::MenuResult Menu::Show(sf::RenderWindow& window)
{
	//Clear window, draw sprite, and display the sprite to the window
	window.clear();
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

/*
	Iterates through menu items and if the click was in the bounds of a menu item returns button action
	Otherwise returns nothing
*/
Menu::MenuResult Menu::HandleClick(int x, int y)
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

/*
	Handles user input with the main menu
*/
Menu::MenuResult Menu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	
	//Polls for user input
	while (window.pollEvent(menuEvent))
	{
		//If user clicked then handle the input
		if (menuEvent.type == sf::Event::MouseButtonPressed)
			return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		//If user clicked exit window button then close window
		else if (menuEvent.type == sf::Event::Closed)
			return Exit;
		//Otherwise do nothing
		else
			return Nothing;
	}
	return Nothing;
}