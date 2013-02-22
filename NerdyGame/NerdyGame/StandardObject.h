#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#ifndef STANDARDOBJECT_H
#define STANDARDOBJECT_H

class StandardObject {
    public:
		//variables
		static ISceneManager* smgr;
		static IVideoDriver* driver;
		//functions
		StandardObject();  // parameterless default constructor
		StandardObject(vector3df position);  // position constructor
		StandardObject(const io::path & meshFilename,const io::path & textureFilename);  // mesh & texture constructor
		StandardObject(vector3df position, const io::path & meshFilename,const io::path & textureFilename);  // position & mesh & texture constructor
		void setMesh(const io::path & filename);
		void setTexture(const io::path & filename);
		void drawall();
		IAnimatedMesh* getMesh();
		IAnimatedMeshSceneNode* getNode();
    private:
		//variables
		IAnimatedMesh* mesh;
		IAnimatedMeshSceneNode* node;
};
#endif