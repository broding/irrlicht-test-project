#ifndef STANDARDOBJECT_H
#define STANDARDOBJECT_H
class StandardObject {
    public:
        StandardObject();  // parameterless default constructor
        int getX();
        int getY();
		void drawall();
    private:
        int x;
        int y;
};
#endif