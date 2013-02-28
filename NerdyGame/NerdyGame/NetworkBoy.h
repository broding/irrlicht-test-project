#include <irrlicht.h>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "GameScreen.h"
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
		NetworkBoy(GameScreen* screen);
		~NetworkBoy();
		void connect(sf::IpAddress &server);
		void setupServer();
		void sendPacket(sf::Packet* packet);
		void flush();
		void receivePackets();

		unsigned short port;
    private:
		sf::UdpSocket *socket;
		bool isServer;
		sf::IpAddress serverIp;
		GameScreen* gameScreen;
		std::vector<sf::Packet*> buffer;
};
#endif