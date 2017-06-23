#include "Engine.h"
#include "Ball.h"
#include "Server.h"

int main(int argc, char* argv[])
{
	Engine game;
	sf::Event event;
	//Server server;
	sf::Time frameTime;

	//Game loop
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

		case ShowingHostMenu:
			game.ShowHostMenu();
			break;

		case ShowingJoinMenu:
			game.ShowJoinMenu();
			break;

		case Singleplayer:
			game.GetMainWindow().pollEvent(event);
			if (!game.Playing())
			{
				game.GetServer()->Initialize("127.0.0.1", 9000, true);
				game.StartSingleplayer();
			}
			else
			{
				game.GetServer()->receivePacket();
				game.GetServer()->receivePacket();
				game.GetServer()->receivePacket();

				frameTime = game.GetFrameTime();

				game.GetEnemyPaddle()->Update(frameTime, game.GetServer()->getPaddlePacket());
				game.GetServer()->sendPaddlePacket(game.GetGameTime().asSeconds(), game.GetEnemyPaddle()->GetVelocity(), true);

				game.GetPlayerPaddle()->Update(frameTime, event);
				game.GetServer()->sendPaddlePacket(game.GetGameTime().asSeconds(), game.GetPlayerPaddle()->GetVelocity(), false);

				game.GetBall()->Update(frameTime, game.GetServer()->getBallPacket(), game.GetPlayerPaddle());
				game.GetServer()->sendBallPacket(game.GetGameTime().asSeconds(), game.GetBall()->GetVelocity(), game.GetBall()->GetAngle());

				game.GetMainWindow().clear();
				game.GetGameObjectManager()->DrawAll(game.GetMainWindow());
				game.GetMainWindow().display();
			}
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


