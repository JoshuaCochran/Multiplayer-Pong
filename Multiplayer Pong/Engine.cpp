#include "Engine.h"

Engine::Engine()
{
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pong");
	_mainWindow.setFramerateLimit(60);

	_view.reset(sf::FloatRect(24, 24, 256, 192));
	_view.setViewport(sf::FloatRect(0.f, 0.f, 0.75, 1.f));

	_mainMenu = new Menu(_mainWindow, MenuType::Main);
	_mpMenu = new Menu(_mainWindow, MenuType::Multiplayer);

	_gameObjectManager = new GameObjectManager();

	_server = new Server;

	_hostGui = new GUI(_mainWindow, _server, GUIType::hostMenu);
	_joinGui = new GUI(_mainWindow, _server, GUIType::joinMenu);
	
	frameTime.restart();

	isExiting = false;
	isPlaying = false;

	_gameState = GameState::ShowingMainMenu;
}

Engine::~Engine()
{
	delete _mainMenu;
	delete _mpMenu;
}

void Engine::ShowMainMenu()
{
	Menu::MenuResult result = _mainMenu->Show(_mainWindow);
	switch (result)
	{
	case Menu::Exit:
		_gameState = Exiting;
		break;
	case Menu::SinglePlayer:
		_gameState = GameState::Singleplayer;
		break;
	case Menu::Multiplayer:
		_gameState = ShowingMultiplayerMenu;
		break;
	case Menu::Nothing:
		break;
	}
}

void Engine::ShowMultiplayerMenu()
{
	Menu::MenuResult result = _mpMenu->Show(_mainWindow);
	switch (result)
	{
	case Menu::Exit:
		_gameState = GameState::Exiting;
		break;
	case Menu::Host:
		_gameState = GameState::ShowingHostMenu;
		break;
	case Menu::Join:
		_gameState = GameState::ShowingJoinMenu;
		break;
	case Menu::MpCancel:
		_gameState = ShowingMainMenu;
		break;
	}
}

void Engine::ShowHostMenu()
{
	sf::Event event;
	_mainWindow.pollEvent(event);
	/*if (event.type == sf::Event::Resized)
	{
		_mainWindow.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		_hostGui->setView(_mainWindow.getView());
		_mainWindow.setView(_mainWindow.getDefaultView());
	}*/
	_hostGui->HandleEvent(event);

	_mainWindow.clear();
	_hostGui->Draw();
	_mainWindow.display();
}

void Engine::ShowJoinMenu()
{
	sf::Event event;
	_mainWindow.pollEvent(event);

	_joinGui->HandleEvent(event);

	_mainWindow.clear();
	_joinGui->Draw();
	_mainWindow.display();
}

void Engine::StartSingleplayer()
{
	//Server server("127.0.0.1", 9000, true);
	isPlaying = true;
	
	ball = new Ball();
	playerPaddle = new PlayerPaddle();
	enemyPaddle = new EnemyPaddle();

	_gameObjectManager->Add("ball", ball);
	_gameObjectManager->Add("player paddle", playerPaddle);
	_gameObjectManager->Add("enemy paddle", enemyPaddle);

	gameTime.restart();
}

bool Engine::GetExitState()
{
	return isExiting;
}

GameState Engine::GetGameState()
{
	return _gameState;
}

void Engine::SetGameState(GameState gameState)
{
	_gameState = gameState;
}

void Engine::Exit()
{
	isExiting = true;
}

sf::RenderWindow& Engine::GetMainWindow()
{
	return _mainWindow;
}

bool Engine::Playing()
{
	return isPlaying;
}

sf::Time Engine::GetFrameTime()
{
	return frameTime.restart();//.getElapsedTime();
}

sf::Time Engine::ResetFrameTime()
{
	return frameTime.restart();
}

sf::Time Engine::GetGameTime()
{
	return gameTime.getElapsedTime();
}

GameObjectManager* Engine::GetGameObjectManager()
{
	return _gameObjectManager;
}

Ball* Engine::GetBall()
{
	return ball;
}

PlayerPaddle* Engine::GetPlayerPaddle()
{
	return playerPaddle;
}

EnemyPaddle* Engine::GetEnemyPaddle()
{
	return enemyPaddle;
}

Server* Engine::GetServer()
{
	return _server;
}