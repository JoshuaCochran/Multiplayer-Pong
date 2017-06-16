#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML/Network.hpp>
#include "Server.h"
#include "Menu.h"
#include "Ball.h"

enum GameState {
	ShowingSplash, Paused, ShowingMainMenu, ShowingMultiplayerMenu, ShowingHostMenu, ShowingJoinMenu, 
	Playing, Singleplayer, Exiting
};

class Engine {
public:
	Engine();
	~Engine();

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

	GameState GetGameState();
	void SetGameState(GameState gameState);

	bool GetExitState();
	void Exit();

	bool Playing();
	
	void ShowMainMenu();
	void ShowMultiplayerMenu();
	
	//bool IsHost;
	
	void StartSingleplayer();

	sf::RenderWindow& GetMainWindow();

private:
	GameState _gameState;

	sf::RenderWindow _mainWindow;
	sf::View _view;

	Menu* _mainMenu;
	Menu* _mpMenu;

	bool isExiting;
	bool isPlaying;

	Ball* ball;

};

#endif
