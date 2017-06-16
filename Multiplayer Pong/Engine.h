#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML/Network.hpp>
#include "Menu.h"

enum GameState {
	ShowingSplash, Paused, ShowingMainMenu, ShowingMultiplayerMenu, ShowingHostMenu, ShowingJoinMenu, Playing, Exiting
};

class Engine {
public:
	Engine();
	~Engine();


	GameState getGameState();
	void setGameState(GameState gameState);

	bool getExitState();
	void exit();

	void ShowMainMenu();
	void ShowMultiplayerMenu();

private:
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	GameState _gameState;

	sf::RenderWindow _mainWindow;
	sf::View _view;

	Menu* _mainMenu;
	Menu* _mpMenu;

	bool isExiting;

};

#endif