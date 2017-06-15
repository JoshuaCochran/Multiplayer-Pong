#include "SFML/Network.hpp"

int main(int argc, char* argv[])
{

	enum GameState {
		ShowingSplash, Paused, ShowingMenu, Playing, Exiting
	};

	bool IsExiting = false;

	GameState _gameState = ShowingSplash;

	while (!IsExiting)
	{
		switch (_gameState)
		{
		case ShowingSplash:
			break;

		case Paused:
			break;

		case ShowingMenu:
			break;

		case Playing:
			break;
		
		case Exiting:
			IsExiting = true;
			break;
		}
	}


	return 0;
}