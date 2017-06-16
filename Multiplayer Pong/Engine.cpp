#include "Engine.h"

Engine::Engine()
{
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pong");
	_mainWindow.setFramerateLimit(60);

	_view.reset(sf::FloatRect(24, 24, 256, 192));
	_view.setViewport(sf::FloatRect(0.f, 0.f, 0.75, 1.f));

	_mainMenu = new Menu(_mainWindow, MenuType::Main);
	_mpMenu = new Menu(_mainWindow, MenuType::Multiplayer);
	
	//isConnected = false;
	//int playerID;
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
		// Start server, then do everything else as if we are the client.
		// The server should establish TCP connections for sending
		// important information like player ID and changes in score.
		break;
	case Menu::Join:
		// OPen 
		break;
	case Menu::MpCancel:
		_gameState = ShowingMainMenu;
		break;
	}
}

void Engine::StartSingleplayer()
{
	Server server("127.0.0.1", 9000);
	isPlaying = true;
	ball = new Ball();
}

void Engine::StartMultiplayer()
{
	// Get player ID
	// 
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
