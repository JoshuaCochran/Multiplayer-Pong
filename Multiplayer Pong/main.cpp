#include "SFML/Network.hpp"
#include "Menu.h"
#include <iostream>
#include "Server.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine game;

	//Game loop
	while (!game.getExitState())
	{
		switch (game.getGameState())
		{
		case ShowingSplash:
			break;

		case Paused:
			break;

		case ShowingMainMenu:
			game.ShowMainMenu();
			break;

		case ShowingMultiplayerMenu:
			game.ShowMultiplayerMenu();
			break;

		case Playing:
			break;
		
		case Exiting:
			game.exit();
			break;
		}
	}


	return 0;
}


