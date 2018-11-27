#include "scenemanager.h"

#define SCENE_MANAGER_UDP_MESSAGE_SIZE 4888

string SceneManager::name;
unordered_map<string, unique_ptr<Scene>> SceneManager::scenes;
string SceneManager::ip;
int SceneManager::port;
bool SceneManager::isConnect = false;
ofxUDPManager SceneManager::udp;

void SceneManager::setup(string _name, Scene *&&scene)
{
    name = _name;
    scenes[name] = unique_ptr<Scene>(scene);
    scenes[name]->setup();


    ip = ofxIPAddress::getPrivate();
    port = 53548;
    udp.Create();
    udp.Bind(port);
    udp.SetNonBlocking(true);
}

void SceneManager::update()
{
    char message[SCENE_MANAGER_UDP_MESSAGE_SIZE];
    if (udp.Receive(message, SCENE_MANAGER_UDP_MESSAGE_SIZE) > 0) {
        scenes[name]->networkRecieved(message);
    }
    scenes[name]->update();
}

void SceneManager::draw()
{
    scenes[name]->draw();
}

void SceneManager::exit()
{
    scenes[name]->exit();
    udp.Close();
}

void SceneManager::keyPressed(int key)
{
    scenes[name]->keyPressed(key);
}

void SceneManager::keyReleased(int key)
{
    scenes[name]->keyReleased(key);
}

void SceneManager::mouseDragged(int x, int y, int button)
{
    scenes[name]->mouseDragged(x, y, button);
}

void SceneManager::mousePressed(int x, int y, int button)
{
    scenes[name]->mousePressed(x, y, button);
}

void SceneManager::mouseReleased(int x, int y, int button)
{
    scenes[name]->mouseReleased(x, y, button);
}

void SceneManager::setNext(string _name, Scene *&&scene)
{
    if (scene != nullptr) {
        scenes[_name] = unique_ptr<Scene>(scene);
    }

    if (scenes[_name]) {
        scenes[name]->exit();
        name = _name;
        scenes[name]->setup();
    }
}

void SceneManager::networkConnect(std::string ip)
{
    udp.Connect(ip.c_str(), port);
    setConnect(true);
}

void SceneManager::networkSend(std::string message)
{
    if (isConnect) {
        udp.Send(message.c_str(), message.size());
    }
}

void SceneManager::networkReset()
{
    udp.Close();
    udp.Create();
    udp.Bind(port);
    udp.SetNonBlocking(true);
    setConnect(false);
}

string SceneManager::getIP()
{
    return ip;
}

void SceneManager::setConnect(bool connect)
{
    isConnect = connect;
}

ofVec2f SceneManager::getScreenMouse()
{
    return ofVec2f(ofGetMouseX(), ofGetMouseY());
}

ofVec2f SceneManager::getWorldMouse()
{
    return scenes[name]->camera.worldPositionFrom(getScreenMouse());
}

Camera &SceneManager::getCamera()
{
    return scenes[name]->camera;
}

void SceneManager::instance(GameObject &object)
{
    scenes[name]->add(object);
}

