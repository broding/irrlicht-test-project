#include "NetworkBoy.h"
#include <iostream>;

NetworkBoy::NetworkBoy()
{
}

NetworkBoy::NetworkBoy(GameScreen* gameScreen)
{
	this->gameScreen = gameScreen;
	socket = new sf::UdpSocket();
	port = 12345;

}

NetworkBoy::~NetworkBoy()
{
	delete socket;
}

void NetworkBoy::connect(sf::IpAddress &server)
{
	printf("The text you want to write goes here.");

	serverIp = server;
	
	if(socket->bind(port))
	{
		std::cout << "COnnection succeeded";
	}
	else
	{
		std::cout << "Connection failed";
	}

}

void NetworkBoy::setupServer()
{
	isServer = true;

	if(socket->bind(port))
	{
	}
	else
	{
		// error
	}
}

void NetworkBoy::sendPackage(sf::Packet* packet)
{
	buffer.push_back(packet);
}

void NetworkBoy::flush()
{
	for(unsigned int i = 0; i < buffer.size(); i++)
	{
		socket->send(*buffer[i], serverIp, port);
	}
}

void NetworkBoy::receivePackages()
{
	sf::Packet receivedPacket;
	sf::IpAddress sender;
	unsigned short port;

	if (socket->receive(receivedPacket, sender, port) != sf::Socket::Done)
	{
		// Error...
	}
	else
	{

	}
}