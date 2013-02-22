#include <irrlicht.h>
#include "StandardObject.h"
#include "GameScreen.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


int main()
{
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(1680, 1050), 16,
			true, false, false, 0);

	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	device->getCursorControl()->setVisible(false);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	StandardObject::smgr = smgr;
	StandardObject::driver = driver;

	GameScreen::smgr = smgr;
	GameScreen::driver = driver;
	GameScreen::guienv = guienv;
	GameScreen gameScreen = GameScreen();

	while(device->run())
	{
		gameScreen.Update();

		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	device->drop();

	return 0;
}
