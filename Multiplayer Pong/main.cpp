#include "SFML/Network.hpp"
#include "MainMenu.h"

enum GameState {
	ShowingSplash, Paused, ShowingMenu, Playing, Exiting
};

void ShowMenu(GameState& gameState, sf::RenderWindow& mainWindow)
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		gameState = Exiting;
		break;
	case MainMenu::SinglePlayer:
		break;
	case MainMenu::Multiplayer:
		break;
	case MainMenu::Nothing:
		break;
	}
}

int main(int argc, char* argv[])
{
	bool isExiting = false;

	GameState _gameState = ShowingMenu;
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	
	sf::RenderWindow _mainWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pong");
	_mainWindow.setFramerateLimit(60);

	sf::View view;
	view.reset(sf::FloatRect(24, 24, 256, 192));
	view.setViewport(sf::FloatRect(0.f, 0.f, 0.75, 1.f));

	while (!isExiting)
	{
		switch (_gameState)
		{
		case ShowingSplash:
			break;

		case Paused:
			break;

		case ShowingMenu:
			ShowMenu(_gameState, _mainWindow);
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

