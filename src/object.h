#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::reference_wrapper;

class Object
{
public:

    virtual void setup() {}
    virtual void update() {}
    virtual void draw() {}
    virtual void exit() {}

    virtual void keyPressed(int key, int x, int y) {}
    virtual void keyReleased(int key, int x, int y) {}
    virtual void mouseDragged(int x, int y, int button) {}
    virtual void mousePressed(int x, int y, int button) {}
    virtual void mouseReleased(int x, int y, int button) {}
    virtual void networkRecieved(string message) {}
};

#endif // OBJECT_H
