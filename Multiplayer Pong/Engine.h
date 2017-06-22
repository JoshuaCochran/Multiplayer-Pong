#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include "Server.h"
#include "Menu.h"
#include "Ball.h"
#include "PlayderPaddle.h"
#include "GameObjectManager.h"


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

	void StartSingleplayer();

	sf::Time GetFrameTime();
	sf::Time GetGameTime();
	sf::Time ResetFrameTime();

	sf::RenderWindow& GetMainWindow();

	GameObjectManager* GetGameObjectManager();

	Ball* GetBall();
	PlayerPaddle* GetPlayerPaddle();

private:
	GameState _gameState;

	sf::RenderWindow _mainWindow;
	sf::View _view;

	Menu* _mainMenu;
	Menu* _mpMenu;

	GameObjectManager* _gameObjectManager;

	bool isExiting;
	bool isPlaying;

	Ball* ball;
	PlayerPaddle* playerPaddle;

	sf::Clock frameTime;
	sf::Clock gameTime;

};

#endif