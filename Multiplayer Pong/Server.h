#ifndef _SERVER_H
#define _SERVER_H

#include <SFML/Network.hpp>

class Server
{
public:
	Server(sf::IpAddress ipAddress, unsigned int port);

private:
	sf::UdpSocket socket;
	unsigned int port;
};

#endif