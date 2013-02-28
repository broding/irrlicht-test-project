#include "NetworkBoy.h"
#include <iostream>;

NetworkBoy::NetworkBoy()
{
}

NetworkBoy::NetworkBoy(GameScreen* gameScreen)
{
	this->gameScreen = gameScreen;
	socket = new sf::UdpSocket();
	port = 56000;
}

NetworkBoy::~NetworkBoy()
{
	socket->unbind();
	delete socket;
}

void NetworkBoy::connect(sf::IpAddress &server)
{
	std::cout << "Try connecting to server with ip: " << server;

	serverIp = server;
	
	if(socket->bind(port) == sf::Socket::Done)
	{
		std::cout << "Connection succeeded";
	}
	else
	{
		std::cout << "Connection failed";
	}

	sf::Packet packet;
	packet << "hello";

	if(socket->send(packet, serverIp, port) != sf::Socket::Done)
	{
		// error
	}
}

void NetworkBoy::setupServer()
{
	isServer = true;

	if(socket->bind(port) == sf::Socket::Done)
	{
		std::cout << "Server made on ip: " << sf::IpAddress::getLocalAddress();
	}
	else
	{
		std::cout << "Failed to bind port";
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

	if (socket->receive(receivedPacket, sender, port) == sf::Socket::Done)
	{
		// Error...
	}
	else
	{

	}
}