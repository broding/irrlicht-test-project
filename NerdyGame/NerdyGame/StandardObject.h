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
		StandardObject();  // parameterless default constructor
		StandardObject(vector3df position);  // parameterless default constructor
		static ISceneManager* smgr;
		static IVideoDriver* driver;
        int getX();
        int getY();
		void drawall();
    private:
        int x;
        int y;
};
#endif