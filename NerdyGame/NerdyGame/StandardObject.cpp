
#include "StandardObject.h"


	ISceneManager* StandardObject::smgr;
	IVideoDriver* StandardObject::driver;

	//default constructor
	StandardObject::StandardObject()
	{
		//is empty 
	}
	//default constructor where you need to set the filename for mesh and texture
	StandardObject::StandardObject(const io::path & meshFilename,const io::path & textureFilename)
	{
	
		setMesh(meshFilename);
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
			setTexture(textureFilename);
		}

	}
	// constructor with position and other atributes
	StandardObject::StandardObject(vector3df position)
	{
	
		setMesh("../Assets/r_flag.md3");
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
			setTexture("../Assets/r_flag2.tga");
			node->setPosition(position);
			
		}

	}
	// constructor with position and other atributes + filename of mesh and texture
	StandardObject::StandardObject(vector3df position,const io::path & meshFilename,const io::path & textureFilename)
	{
	
		setMesh(meshFilename);
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
			setTexture(textureFilename);
			node->setPosition(position);
		}

	}
	/*Update function
	*/
	void StandardObject::Update()
	{
		vector3df tempPosition = node->getPosition();
		velocity += acceleration;
		tempPosition += velocity;
		node->setPosition(tempPosition);
	}

	// A setter so that the programmer has the ability to set the mesh after constructor
	void StandardObject::setMesh(const io::path & filename)
	{
		mesh = smgr->getMesh(filename);
	}
	// A setter so that the programmer has the ability to set the texture after constructor
	void StandardObject::setTexture(const io::path & filename)
	{
		node->setMaterialTexture(0, driver->getTexture(filename) );
	}
	// a getter that returns the mesh of this object
	IAnimatedMesh* StandardObject::getMesh()
	{
		return mesh;
	}
	// a getter that returns the node of this object, usefull for changing position and stuff
	IAnimatedMeshSceneNode* StandardObject::getNode()
	{
		return node;
	}
	//obsolete
	void StandardObject::drawall()
	{

	}