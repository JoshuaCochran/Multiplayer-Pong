#ifndef _SERVER_H
#define _SERVER_H

#include <SFML/Network.hpp>
#include <vector>
#include <queue>

enum ConnectionType {
	host, client
};

enum ObjectType {
	ball, paddle, handShake, ackHandShake, empty
};

struct ObjectPacket {
	float packetNum;
	float timeStamp;
	float type; //= ObjectType::empty;
	float connectionType; //0 for host, 1 for client
	float velocity;
	float angle;
	float singlePlayer;
};

struct GamePacket {
	std::string type;
	ObjectPacket objPacket;
};


class Server
{
public:
	Server();
	Server(sf::IpAddress ipAddress, unsigned int port, bool host);

	void Initialize(sf::IpAddress ipAddress, unsigned int port, bool host);

	void sendBallPacket(float timeStamp, float velocity, float angle);
	void sendPaddlePacket(float timeStamp, float velocity, bool singlePlayer);

	void receivePacket();

	ObjectPacket getBallPacket();
	ObjectPacket getPaddlePacket();

	bool isHost();
	bool hasHandShake();
	
	void sendHandShake();
	void ackHandShake();

	bool hasSentHandShake();
	bool handShakeAcknowledged();

	bool isConnected();
	void Connected();

	void ShakeHands();

private:

	sf::UdpSocket socket;
	unsigned int port;
	sf::IpAddress serverIp;

	bool host;
	bool handShake;
	bool sentHandShake;
	bool handShakeReceived;
	bool connected;


	sf::IpAddress player2 = "127.0.0.1";
	unsigned int port2 = 9000;

	float packetsSent;

	//std::vector<ObjectPacket> ballPackets;
	//std::vector<ObjectPacket> paddlePackets;
	
	std::queue<ObjectPacket> ballPackets2;
	std::queue<ObjectPacket> paddlePackets2;
};

#endif