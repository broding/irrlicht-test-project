#include "NetworkBoy.h"
#include <iostream>;

enum PACKET_TYPE
{
	CLIENT_HANDSHAKE,
	SERVER_CONNECTION_ACCEPT
};

NetworkBoy::NetworkBoy()
{
	socket = new sf::UdpSocket();
	socket->setBlocking(false);
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

	sf::Packet* packet = new sf::Packet();
	*packet << CLIENT_HANDSHAKE;

	sendPacket(packet);
}

void NetworkBoy::setupServer()
{
	isServer = true;

	if(socket->bind(port) == sf::Socket::Done)
	{
		std::cout << "Server made on ip: " << sf::IpAddress::getLocalAddress << "\n";
	}
	else
	{
		std::cout << "Failed to bind port\n";
	}
}

void NetworkBoy::sendPacket(sf::Packet* packet)
{
	buffer.push_back(packet);
}

void NetworkBoy::flush()
{
	for(unsigned int i = 0; i < buffer.size(); i++)
	{
		socket->send(*buffer[i], serverIp, port);

		//delete buffer[i];
	}

	buffer.clear();
}

void NetworkBoy::receivePackets()
{
	sf::Packet receivedPacket;
	sf::IpAddress sender;
	unsigned short port;

	if (socket->receive(receivedPacket, sender, port) == sf::Socket::Done && port == this->port)
	{
		std::cout << "Received packet from: " << sender;

		handlePacket(receivedPacket, sender);
	}
}

void NetworkBoy::handlePacket(sf::Packet packet, sf::IpAddress address)
{
	unsigned char type;

	packet >> type;

	std::cout << "Received packet with type: " << packet;

	switch(type)
	{
		case CLIENT_HANDSHAKE:
			if(isServer)
			{
				addPlayer(address);
				std::cout << "Added player to player list";

				sf::Packet* packet = new sf::Packet();
				*packet << SERVER_CONNECTION_ACCEPT;
				sendPacket(packet);
			}
			
			break;

		case SERVER_CONNECTION_ACCEPT:
			std::cout << "Client got accepted by server";
			break;
	}
}

void NetworkBoy::addPlayer(sf::IpAddress &address)
{
	players.push_back(&address);
}