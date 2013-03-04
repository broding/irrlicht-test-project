#include <irrlicht.h>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <enet/enet.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifndef NETWORKBOY_H
#define NETWORKBOY_H

class NetworkBoy {
    public:
		NetworkBoy();
		~NetworkBoy();
		void connect(const char* ipString);
		void setupServer();
		void sendPacket(sf::Packet* packet);
		void flush();
		void receivePackets();

		unsigned short port;
    private:
		void addPlayer(sf::IpAddress &address);
		void handlePacket(sf::Packet packet, sf::IpAddress address);

		ENetHost* host;
		ENetPeer* serverPeer;

		sf::UdpSocket *socket;
		bool isServer;
		ENetAddress serverAddress;
		std::vector<sf::Packet*> buffer;
		std::vector<sf::IpAddress*> players;
};
#endif