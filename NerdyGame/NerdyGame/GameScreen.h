#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <irrlicht.h>
#include <iostream>
#include <vector>
#include "StandardObject.h"
#include "NetworkBoy.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GameScreen {
public:
	GameScreen();
	GameScreen(NetworkBoy* networkBoy);
	static ISceneManager* smgr;
	static IVideoDriver* driver;
	static IGUIEnvironment* guienv;
	void Update();
	void Add(StandardObject* object);

	NetworkBoy* networkBoy;

private:
	std::vector<StandardObject*> objects;	
};
#endif