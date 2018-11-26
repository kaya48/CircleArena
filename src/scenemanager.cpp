#include "scenemanager.h"

unique_ptr<Scene> SceneManager::prevScene;
vector<unique_ptr<Scene>> SceneManager::scenes;
string SceneManager::ip;
int SceneManager::port;
bool SceneManager::isConnect = false;
ofxUDPManager SceneManager::udp;

void SceneManager::setup(Scene *&&scene)
{
    scenes.push_back(unique_ptr<Scene>(scene));
    ip = ofxIPAddress::getPrivate();
    port = 53548;
    udp.Create();
    udp.Bind(port);
    udp.SetNonBlocking(true);
    scenes.back()->setup();
}

void SceneManager::update()
{
    if (prevScene) {
        prevScene.release();
    }
    char message[4888];
    if (udp.Receive(message, 4888) > 0) {
        scenes.back()->networkRecieved(message);
    }
    scenes.back()->update();
}

void SceneManager::draw()
{
    scenes.back()->draw();
}

void SceneManager::exit()
{
    scenes.back()->exit();
    udp.Close();
}

void SceneManager::keyPressed(int key)
{
    scenes.back()->keyPressed(key);
}

void SceneManager::keyReleased(int key)
{
    scenes.back()->keyReleased(key);
}

void SceneManager::mouseDragged(int x, int y, int button)
{
    scenes.back()->mouseDragged(x, y, button);
}

void SceneManager::mousePressed(int x, int y, int button)
{
    scenes.back()->mousePressed(x, y, button);
}

void SceneManager::mouseReleased(int x, int y, int button)
{
    scenes.back()->mouseReleased(x, y, button);
}

void SceneManager::setNext(Scene *&&nest, bool clear)
{
    scenes.back()->exit();
    nest->setup();
    if (clear) {
        prevScene = std::move(scenes.back());
        scenes.clear();
    }
    scenes.push_back(unique_ptr<Scene>(nest));
}

void SceneManager::setPrev()
{
    prevScene = std::move(scenes.back());
    scenes.pop_back();
}

void SceneManager::networkConnect(std::string ip)
{
    udp.Connect(ip.c_str(), port);
    isConnect = true;
}

void SceneManager::networkSend(std::string message)
{
    if (isConnect) {
        udp.Send(message.c_str(), message.size());
    }
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
    return scenes.back()->camera.worldPositionFrom(getScreenMouse());
}

Camera &SceneManager::getCamera()
{
    return scenes.back()->camera;
}

void SceneManager::instance(GameObject &object)
{
    scenes.back()->add(object);
}

