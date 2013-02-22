#include "GameScreen.h"
#include "StandardObject.h"

ISceneManager* GameScreen::smgr;
IVideoDriver* GameScreen::driver;
IGUIEnvironment* GameScreen::guienv;

GameScreen::GameScreen()
{
	StandardObject flag(vector3df(0,0,0));
	
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("../Assets/skydome2.jpg"),64,48,0.999f,5.0f,1000.0f);
	
	smgr->addCameraSceneNodeFPS();
}

void GameScreen::Update()
{
	
}