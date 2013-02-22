
#include "StandardObject.h"


	ISceneManager* StandardObject::smgr;
	IVideoDriver* StandardObject::driver;

	StandardObject::StandardObject()
	{
		
	}
	StandardObject::StandardObject(vector3df position)
	{
	
		mesh = smgr->getMesh("../Assets/r_flag.md3");
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		node = smgr->addAnimatedMeshSceneNode( mesh );
	
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture(0, driver->getTexture("../Assets/r_flag2.tga") );
		}

	}
	IAnimatedMesh* StandardObject::getMesh()
	{
		return mesh;
	}
	IAnimatedMeshSceneNode* StandardObject::getNode()
	{
		return node;
	}
	void StandardObject::drawall()
	{

	}