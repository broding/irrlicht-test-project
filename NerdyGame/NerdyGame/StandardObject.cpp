
#include "StandardObject.h"


	ISceneManager* StandardObject::smgr;
	IVideoDriver* StandardObject::driver;

	StandardObject::StandardObject()
	{
		
	}
	StandardObject::StandardObject(vector3df position)
	{
		/*
	To show something interesting, we load a Quake 2 model and display it.
	We only have to get the Mesh from the Scene Manager with getMesh() and add
	a SceneNode to display the mesh with addAnimatedMeshSceneNode(). We
	check the return value of getMesh() to become aware of loading problems
	and other errors.

	Instead of writing the filename sydney.md2, it would also be possible
	to load a Maya object file (.obj), a complete Quake3 map (.bsp) or any
	other supported file format. By the way, that cool Quake 2 model
	called sydney was modelled by Brian Collins.
	*/
		IAnimatedMesh* mesh = smgr->getMesh("../Assets/r_flag.md3");
		if (!mesh)
		{
			//device->drop();
			//return 1;
		}
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
		
	/*
	To let the mesh look a little bit nicer, we change its material. We
	disable lighting because we do not have a dynamic light in here, and
	the mesh would be totally black otherwise. Then we set the frame loop,
	such that the predefined STAND animation is used. And last, we apply a
	texture to the mesh. Without it the mesh would be drawn using only a
	color.
	*/
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("../Assets/r_flag2.tga") );
	}

	}

	void StandardObject::drawall()
	{

	}