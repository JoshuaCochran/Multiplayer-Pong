#include <SFML/Network.hpp>
#include <iostream>

#include "Server.h"


sf::Packet& operator <<(sf::Packet& packet, const ObjectPacket& objPacket)
{
	return packet << objPacket.packetNum << objPacket.timeStamp << objPacket.type << objPacket.connectionType << objPacket.velocity
		<< objPacket.angle << objPacket.singlePlayer;
}

sf::Packet& operator >>(sf::Packet& packet, ObjectPacket& objPacket)
{
	return packet >> objPacket.packetNum >> objPacket.timeStamp >> objPacket.type >> objPacket.connectionType >> objPacket.velocity
		>> objPacket.angle >> objPacket.singlePlayer;
}


Server::Server()
{
	socket.setBlocking(false);
}

Server::Server(sf::IpAddress _ipAddress, unsigned int _port, bool _host)
{
	socket.setBlocking(false);
	std::cout << "Initializing server. . ." << std::endl;
	if (socket.bind(_port) != sf::Socket::Done)
		std::cout << "Binding to port " << _port << " was unsuccessful!" << std::endl;
	else
		std::cout << "Binding to port " << _port << " was successful!" << std::endl;

	port = _port;

	host = _host;

	handShake = false;
	sentHandShake = false;

	packetsSent = 0;
}

void Server::Initialize(sf::IpAddress _ipAddress, unsigned int _port, bool _host)
{
	host = _host;

	if (host)
		port = _port;
	else
		port = _port + 1;


	std::cout << "Initializing server. . ." << std::endl;
	if (socket.bind(port) != sf::Socket::Done)
		std::cout << "Binding to port " << port << " was unsuccessful!" << std::endl;
	else
		std::cout << "Binding to port " << port << " was successful!" << std::endl;

	if (!host)
	{
		player2 = _ipAddress;
		port2 = _port;
	}

	handShake = false;
	sentHandShake = false;
	handShakeReceived = false;

	connected = false;

	packetsSent = 0;
}

void Server::sendBallPacket(float timeStamp, float velocity, float angle)
{
	ObjectPacket pack;

	pack.packetNum = packetsSent;
	pack.timeStamp = timeStamp;
	pack.type = ObjectType::ball;

	if (host)
		pack.connectionType = ConnectionType::host;
	else
		pack.connectionType = ConnectionType::client;

	pack.velocity = velocity;
	pack.angle = angle;

	sf::Packet packet;

	packet << pack;
	socket.send(packet, player2, port2);

	packetsSent++;
}

void Server::sendPaddlePacket(float timeStamp, float velocity, bool singlePlayer)
{
	ObjectPacket pack;
	pack.packetNum = packetsSent;
	pack.timeStamp = timeStamp;
	pack.type = ObjectType::paddle;

	if (host)
		pack.connectionType = ConnectionType::host;
	else
	{
		pack.connectionType = ConnectionType::client;
		std::cout << "Sent Client Paddle Packet!\n";
	}

	if (singlePlayer)
		pack.singlePlayer = 1;
	else
		pack.singlePlayer = 0;

	pack.velocity = velocity;

	sf::Packet packet;

	packet << pack;
	socket.send(packet, player2, port2);

	packetsSent++;
}

void Server::receivePacket()
{
	sf::IpAddress sender;
	unsigned short senderPort;
	sf::Packet receivedPacket;
	ObjectPacket pack;


	socket.receive(receivedPacket, sender, senderPort);
	receivedPacket >> pack;

	/*if (pack.connectionType == ConnectionType::host)
		serverIp = sender;
	else
	{
		player2 = sender;
		port2 = senderPort;
	}*/

	if (pack.type == ObjectType::handShake)
	{
		handShake = true;
		player2 = sender;
		port2 = senderPort;
	}
	else if (pack.type == ObjectType::ackHandShake && pack.connectionType == ConnectionType::host)
	{
		handShakeReceived = true;
	}
	else if (pack.type == ObjectType::ball)
		ballPackets2.push(pack);
	else if (pack.type == ObjectType::paddle)
	{
		if (pack.singlePlayer == 1)
			paddlePackets2.push(pack);
		else if (isHost() && pack.connectionType == ConnectionType::client)
			paddlePackets2.push(pack);
		else if (!isHost() && pack.connectionType == ConnectionType::host)
			paddlePackets2.push(pack);
	}


	if (isHost() && pack.connectionType == ConnectionType::client && !connected)
		connected = true;
}

ObjectPacket Server::getBallPacket()
{
	if (!ballPackets2.empty())
	{
		ObjectPacket packet = ballPackets2.front();
		ballPackets2.pop();
		return packet;
	}
	else
	{
		ObjectPacket packet;
		packet.type = ObjectType::empty;
		return packet;
	}
}

ObjectPacket Server::getPaddlePacket()
{
	ObjectPacket packet;
	if (!paddlePackets2.empty())
	{
		packet = paddlePackets2.front();
		paddlePackets2.pop();
	}
	else
	{
		packet.type = ObjectType::empty;
	}

	return packet;
}

bool Server::isHost() {
	return host;
}

bool Server::hasHandShake()
{
	return handShake;
}

void Server::ShakeHands()
{
	handShake = true;
}

void Server::sendHandShake()
{
	ObjectPacket pack;
	pack.type = ObjectType::handShake;
	pack.connectionType = ConnectionType::client;

	sf::Packet packet;

	packet << pack;
	socket.send(packet, player2, port2);
	
	sentHandShake = true;

	packetsSent++;
}

void Server::ackHandShake()
{
	ObjectPacket pack;
	pack.type = ObjectType::ackHandShake;
	pack.connectionType = ConnectionType::host;

	sf::Packet packet;
	packet << pack;
	socket.send(packet, player2, port2);

	packetsSent++;
}

bool Server::hasSentHandShake()
{
	return sentHandShake;
}

bool Server::handShakeAcknowledged()
{
	return handShakeReceived;
}

bool Server::isConnected()
{
	return connected;
}

void Server::Connected()
{
	connected = true;
}

/*
Packet Structure

struct Packet {

int32 packet number;
float timeStamp;
float type; // 0 ball, 1 paddle
if (type == 0)
	//send angle and velocity
else
	//send velocity



}


*/


/*
Network Test
*/
/*sf::UdpSocket socket;
socket.setBlocking(false);

sf::IpAddress recipient = "127.0.0.1";
unsigned short port = 9000;

if (socket.bind(port) != sf::Socket::Done)
std::cout << "Server failed to start!" << std::endl;
else
std::cout << "Server started..." << std::endl;

std::string test = "This is a UDP socket test";
sf::Packet packet;
packet << test;

if (socket.send(packet, recipient, port) != sf::Socket::Done)
std::cout << "DGram failed to send!" << std::endl;
else
std::cout << "DGram sent!" << std::endl;

sf::Packet packetReceive;
unsigned short senderPort;
sf::IpAddress sender;
socket.receive(packetReceive, sender, senderPort);

std::string test2;
if (packetReceive >> test2)
{
	std::cout << "Received " << sizeof(test2) << " bytes from " << sender << " on port " << senderPort << std::endl;
	std::cout << "Packet text: " << test2 << std::endl;
}
else
std::cout << "Packet not received!" << std::endl;*/
