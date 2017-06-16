#include <SFML/Network.hpp>
#include <iostream>

#include "Server.h"

Server::Server(sf::IpAddress _ipAddress, unsigned int _port)
{
	std::cout << "Initializing server. . ." << std::endl;
	if (socket.bind(_port) != sf::Socket::Done)
		std::cout << "Binding to port " << _port << " was unsuccessful!" << std::endl;
	else
		std::cout << "Binding to port " << _port << " was successful!" << std::endl;

	port = _port;
}

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
