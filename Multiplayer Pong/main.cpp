#include "Engine.h"
#include "Ball.h"

int main(int argc, char* argv[])
{
	Engine game;

	//Game loop
	sf::Event event;
	while (!game.GetExitState())
	{
		switch (game.GetGameState())
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

		case Singleplayer:
			if (!game.Playing())
				game.StartSingleplayer();
			else
			{
				game.GetMainWindow().clear();
				game.GetMainWindow().display();
			}
			game.GetMainWindow().pollEvent(event);
			if (event.type == sf::Event::Closed)
				game.SetGameState(GameState::Exiting);
			break;
		
		case Exiting:
			game.Exit();
			break;
		}
	}


	return 0;
}


