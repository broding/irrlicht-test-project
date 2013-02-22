#include "GameScreen.h"
#include "StandardObject.h"

ISceneManager* GameScreen::smgr;
IVideoDriver* GameScreen::driver;
IGUIEnvironment* GameScreen::guienv;

GameScreen::GameScreen()
{
	StandardObject flag(vector3df(0,0,0));
	
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("../Assets/skydome.jpg"),64,48,0.999f,5.0f,1000.0f);
	
	/*
	To look at the mesh, we place a camera into 3d space at the position
	(0, 30, -40). The camera looks from there to (0,5,0), which is
	approximately the place where our md2 model is.
	*/
	smgr->addCameraSceneNodeFPS();
}

void GameScreen::Update()
{
	
}