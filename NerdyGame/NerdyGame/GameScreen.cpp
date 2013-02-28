#include "GameScreen.h"
#include "StandardObject.h"

ISceneManager* GameScreen::smgr;
IVideoDriver* GameScreen::driver;
IGUIEnvironment* GameScreen::guienv;

GameScreen::GameScreen(NetworkBoy* networkBoy)
{
	this->networkBoy = networkBoy;

	//StandardObject* flag = new StandardObject(vector3df(0,0,0));
	//Add(flag);
	//flag->AddForce(vector3df(0.0001f, 0.0001f, 0.0001f));
	
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("../Assets/skydome2.jpg"),64,48,0.999f,5.0f,1000.0f);
	
	smgr->addCameraSceneNode();
}

void GameScreen::Update()
{
	//networkBoy->receivePackets();

	for(std::vector<int>::size_type i = 0; i != objects.size(); i++) 
	{
		objects[i]->Update();
	}

	networkBoy->flush();
}

void GameScreen::Add(StandardObject* object)
{
	objects.push_back(object);
}