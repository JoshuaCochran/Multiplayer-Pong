#include "SFML/Network.hpp"
#include "Menu.h"

enum GameState {
	ShowingSplash, Paused, ShowingMainMenu, ShowingMultiplayerMenu, ShowingHostMenu, ShowingJoinMenu, Playing, Exiting
};

void ShowMainMenu(Menu& mainMenu, sf::RenderWindow& mainWindow, GameState& gameState)
{
	Menu::MenuResult result = mainMenu.Show(mainWindow);
	switch (result)
	{
	case Menu::Exit:
		gameState = Exiting;
		break;
	case Menu::SinglePlayer:
		break;
	case Menu::Multiplayer:
		gameState = ShowingMultiplayerMenu;
		break;
	case Menu::Nothing:
		break;
	}
}

void ShowMultiplayerMenu(Menu& mpMenu, sf::RenderWindow& mainWindow, GameState& gameState)
{
	Menu::MenuResult result = mpMenu.Show(mainWindow);
	switch (result)
	{
	case Menu::Exit:
		gameState = Exiting;
		break;
	case Menu::Host:
		break;
	case Menu::Join:
		break;
	case Menu::MpCancel:
		gameState = ShowingMainMenu;
		break;
	}
}

int main(int argc, char* argv[])
{
	GameState _gameState = ShowingMainMenu;
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	
	sf::RenderWindow _mainWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pong");
	_mainWindow.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(24, 24, 256, 192));
	view.setViewport(sf::FloatRect(0.f, 0.f, 0.75, 1.f));

	Menu _mainMenu(_mainWindow, Main);
	Menu _mpMenu(_mainWindow, Multiplayer);

	bool isExiting = false;

	while (!isExiting)
	{
		switch (_gameState)
		{
		case ShowingSplash:
			break;

		case Paused:
			break;

		case ShowingMainMenu:
			ShowMainMenu(_mainMenu, _mainWindow, _gameState);
			break;

		case ShowingMultiplayerMenu:
			ShowMultiplayerMenu(_mpMenu, _mainWindow, _gameState);
			break;

		case Playing:
			break;
		
		case Exiting:
			isExiting = true;
			break;
		}
	}


	return 0;
}

