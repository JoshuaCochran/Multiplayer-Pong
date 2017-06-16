#include "Engine.h"

Engine::Engine()
{
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pong");
	_mainWindow.setFramerateLimit(60);

	_view.reset(sf::FloatRect(24, 24, 256, 192));
	_view.setViewport(sf::FloatRect(0.f, 0.f, 0.75, 1.f));

	_mainMenu = new Menu(_mainWindow, MenuType::Main);
	_mpMenu = new Menu(_mainWindow, MenuType::Multiplayer);

	isExiting = false;

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
		break;
	case Menu::Join:
		break;
	case Menu::MpCancel:
		_gameState = ShowingMainMenu;
		break;
	}
}

bool Engine::getExitState()
{
	return isExiting;
}

GameState Engine::getGameState()
{
	return _gameState;
}

void Engine::setGameState(GameState gameState)
{
	_gameState = gameState;
}

void Engine::exit()
{
	isExiting = true;
}