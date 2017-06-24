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
		case GameState::ShowingSplash:
			break;

		case Paused:
			break;

		case GameState::ShowingMainMenu:
			game.ShowMainMenu();
			break;

		case GameState::ShowingMultiplayerMenu:             
			game.ShowMultiplayerMenu();
			break;

		case GameState::ShowingHostMenu:
			while (game.GetMainWindow().pollEvent(event))
			{
				game.ShowHostMenu(event);
				if (event.type == sf::Event::Closed)
					game.SetGameState(GameState::Exiting);
			}
			break;

		case GameState::ShowingJoinMenu:
			while (game.GetMainWindow().pollEvent(event))
			{
				game.ShowJoinMenu(event);
				if (event.type == sf::Event::Closed)
					game.SetGameState(GameState::Exiting);
			}
			break;

		case GameState::Singleplayer:
			while (game.GetMainWindow().pollEvent(event))
			{
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
			}
			break;

		case GameState::Multiplayer:
			while (game.GetMainWindow().pollEvent(event))
			{
				if (game.GetServer()->isHost() && !game.GetServer()->hasHandShake())
					game.GetServer()->receivePacket();
				else if (game.GetServer()->isHost() && game.GetServer()->hasHandShake() && !game.GetServer()->isConnected())
				{
					game.GetServer()->ackHandShake();
					std::cout << "Sent ack!\n";
				}
				else if (!game.GetServer()->isHost() && !game.GetServer()->handShakeAcknowledged())
				{
					game.GetServer()->sendHandShake();
					game.GetServer()->receivePacket();
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
			}
			break;
		
		case GameState::Exiting:
			game.Exit();
			break;
		}
	}


	return 0;
}


