#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include "Server.h"
#include "Menu.h"
#include "Ball.h"
#include "PlayderPaddle.h"
#include "GameObjectManager.h"
#include "EnemyPaddle.h"
#include "GUI.h"

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
	void ShowHostMenu();
	void ShowJoinMenu();


	void StartSingleplayer();

	sf::Time GetFrameTime();
	sf::Time GetGameTime();
	sf::Time ResetFrameTime();

	sf::RenderWindow& GetMainWindow();

	GameObjectManager* GetGameObjectManager();

	Ball* GetBall();
	PlayerPaddle* GetPlayerPaddle();
	EnemyPaddle* GetEnemyPaddle();

	Server* GetServer();

private:
	GameState _gameState;

	sf::RenderWindow _mainWindow;
	sf::View _view;

	Menu* _mainMenu;
	Menu* _mpMenu;

	GameObjectManager* _gameObjectManager;

	Server* _server;

	bool isExiting;
	bool isPlaying;

	Ball* ball;
	PlayerPaddle* playerPaddle;
	EnemyPaddle* enemyPaddle;

	sf::Clock frameTime;
	sf::Clock gameTime;

	GUI* _hostGui;
	GUI* _joinGui;

};

#endif