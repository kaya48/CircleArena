#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"
#include "ofxNetwork.h"
#include "ofVec2f.h"
#include "ofAppRunner.h"
#include "ofxipaddress.h"

using std::unique_ptr;
using std::unordered_map;

class SceneManager
{
public:
    static void setup(string name, Scene *&&scene);
    static void update();
    static void draw();
    static void exit();

    static void keyPressed(int key);
    static void keyReleased(int key);
    static void mouseDragged(int x, int y, int button);
    static void mousePressed(int x, int y, int button);
    static void mouseReleased(int x, int y, int button);

    static void setNext(string name, Scene *&&nest);

    static void networkConnect(string ip);
    static void networkSend(string message);
    static void networkReset();

    static string getIP();
    static void setConnect(bool connect);

    static ofVec2f getScreenMouse();
    static ofVec2f getWorldMouse();

    static Camera &getCamera();

    static void instance(GameObject &object);
private:
    static string name;
    static unordered_map<string, unique_ptr<Scene>> scenes;

    static string ip;
    static int port;
    static bool isConnect;
    static ofxUDPManager udp;
};

#endif // SCENEMANAGER_H
