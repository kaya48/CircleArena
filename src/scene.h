#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "ofxJSON.h"
#include "ofxUICanvas.h"


using std::unique_ptr;

class Scene
{
public:

    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void exit();

    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void networkRecieved(string message);

    void add(GameObject &object);
    void add(ofxUICanvas &gui);

    Camera camera;
    vector<reference_wrapper<GameObject>> objects;
    vector<reference_wrapper<GameObject>> destroyObjects;
    vector<reference_wrapper<ofxUICanvas>> guis;
};

#endif // SCENE_H
