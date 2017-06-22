#include "Engine.h"
#include "Ball.h"
#include "Server.h"

int main(int argc, char* argv[])
{
	Engine game;
	// Test
	//Game loop
	sf::Event event;
	Server server;
	sf::Time frameTime;
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
			game.GetMainWindow().pollEvent(event);
			if (!game.Playing())
			{
				server.Initialize("127.0.0.1", 9000, true);
				game.StartSingleplayer();
			}
			else
			{
				server.receivePacket();

				frameTime = game.GetFrameTime();

				game.GetBall()->Update(frameTime, server.getBallPacket());
				server.sendBallPacket(game.GetGameTime().asSeconds(), game.GetBall()->GetVelocity(), game.GetBall()->GetAngle());
				
				game.GetPlayerPaddle()->Update(frameTime, event);
				server.sendPaddlePacket(game.GetGameTime().asSeconds(), game.GetPlayerPaddle()->GetVelocity());

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


