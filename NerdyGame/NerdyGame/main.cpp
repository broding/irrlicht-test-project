#include <irrlicht.h>
#include "StandardObject.h"
#include "GameScreen.h"
#include "MainEventReceiver.cpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


int main()
{
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, 0);

	if (!device)
		return 1;

	device->setWindowCaption(L"Multiplayer Prototype");
	device->getCursorControl()->setVisible(true);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	irr::gui::IGUIButton* connectButton = guienv->addButton(rect<s32>(10, 120, 110, 120+32), 0, GUI_ID_CONNECT_BUTTON, L"Connect");
	irr::gui::IGUIButton* makeButton = guienv->addButton(rect<s32>(150, 120, 250, 120+32), 0, GUI_ID_MAKESERVER_BUTTON, L"Make server");
	irr::gui::IGUIEditBox* ipBox = guienv->addEditBox(L"", rect<s32>(10, 80, 200, 100));

	
	StandardObject::smgr = smgr;
	StandardObject::driver = driver;

	GameScreen::smgr = smgr;
	GameScreen::driver = driver;
	GameScreen::guienv = guienv;
	GameScreen gameScreen = GameScreen();

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.networkBoy = new NetworkBoy(&gameScreen);
	context.ipBox = ipBox;
	context.connect = connectButton;
	context.makeserver = makeButton;

	// Then create the event receiver, giving it that context structure.
	MainEventReceiver receiver(context);

	device->setEventReceiver(&receiver);

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
