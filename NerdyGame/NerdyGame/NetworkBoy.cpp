#include "NetworkBoy.h"
#include <iostream>
#include <enet/enet.h>

enum PACKET_TYPE : sf::Int8
{
	CLIENT_HANDSHAKE,
	SERVER_CONNECTION_ACCEPT
};

NetworkBoy::NetworkBoy()
{
	enet_initialize();
	socket = new sf::UdpSocket();
	socket->setBlocking(false);
	port = 56000;
}

NetworkBoy::~NetworkBoy()
{
	enet_deinitialize();
	socket->unbind();
	delete socket;
}

void NetworkBoy::connect(const char* ipString)
{
	std::cout << "Try connecting to server with ip: " << ipString;

	host = enet_host_create(NULL, 1, 2, 0, 0);

	if(host == NULL)
		std::cout << "Error while creating ENet client host";
	else
		std::cout << "Created ENet client host";

	enet_address_set_host(&serverAddress, ipString);
	serverAddress.port = 51234;
	serverPeer = enet_host_connect(host, &serverAddress, 2, 0);

	if(serverPeer == NULL)
		std::cout << "Error creating peer";
	else
		std::cout << "Created peer with server";

	sf::Packet* packet = new sf::Packet();
	sf::Int8 s = 1;
	*packet << s;

	sendPacket(packet);
}

void NetworkBoy::setupServer()
{
	isServer = true;

	serverAddress.host = ENET_HOST_ANY;
	serverAddress.port = 51234;
	host = enet_host_create(&serverAddress, 32, 2, 0, 0);

	if(host == NULL)
		std::cout << "Error while creating ENet server host";
	else
		std::cout << "Created ENet server host";
}

void NetworkBoy::sendPacket(sf::Packet* packet)
{
	buffer.push_back(packet);
}

void NetworkBoy::flush()
{
	for(unsigned int i = 0; i < buffer.size(); i++)
	{
		//socket->send(*buffer[i], serverIp, port);
		ENetPacket* packet = enet_packet_create(
			buffer[i]->getData(), 
			buffer[i]->getDataSize(), 
			ENET_PACKET_FLAG_RELIABLE
			);

		enet_peer_send(serverPeer, 0, packet);

		//delete buffer[i];
	}

	if(buffer.size() > 0)
		enet_host_flush(host);

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
	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service (host, & event, 10) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf ("A new client connected from %x:%u.\n", 
					event.peer -> address.host,
					event.peer -> address.port);
			/* Store any relevant client information here. */
			event.peer -> data = "Client information";
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
					event.packet -> dataLength,
					event.packet -> data,
					event.peer -> data,
					event.channelID);
			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy (event.packet);
        
			break;
       
		case ENET_EVENT_TYPE_DISCONNECT:
			printf ("%s disconected.\n", event.peer -> data);
			/* Reset the peer's client information. */
			event.peer -> data = NULL;
		}
	}
}

void NetworkBoy::addPlayer(sf::IpAddress &address)
{
	players.push_back(&address);
}