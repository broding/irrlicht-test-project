#include <irrlicht.h>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

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
		void connect(sf::IpAddress &server);
		void setupServer();
		void sendPacket(sf::Packet* packet);
		void flush();
		void receivePackets();

		unsigned short port;
    private:
		void addPlayer(sf::IpAddress &address);
		void handlePacket(sf::Packet packet, sf::IpAddress address);

		sf::UdpSocket *socket;
		bool isServer;
		sf::IpAddress serverIp;
		std::vector<sf::Packet*> buffer;
		std::vector<sf::IpAddress*> players;
};
#endif