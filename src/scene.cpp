#include "scene.h"
#include "scenemanager.h"

void Scene::setup()
{
    for (GameObject &object : objects) {
        object.setup();
    }
}

void Scene::update()
{
    for (GameObject &object : objects) {
        object.collision.clear();
        object.collision.judge(objects);
        object.update();
    }
}

void Scene::draw()
{
    camera.draw(objects);
}

void Scene::exit()
{
    for (GameObject &object : objects) {
        object.exit();
    }
}

void Scene::keyPressed(int key)
{
    for (GameObject &object : objects) {
        if (object.ip == "") {
            ofVec2f world = SceneManager::getWorldMouse();
            ofxJSON json;
            json["ip"] = SceneManager::getIP();
            json["keyPressed"] = true;
            json["key"] = key;
            json["x"] = world.x;
            json["y"] = world.y;
            SceneManager::networkSend(json.getRawString(false));
            object.keyPressed(key, world.x, world.y);
        }
    }
}

void Scene::keyReleased(int key)
{
    for (GameObject &object : objects) {
        if (object.ip == "") {
            ofVec2f world = SceneManager::getWorldMouse();
            ofxJSON json;
            json["ip"] = SceneManager::getIP();
            json["keyReleased"] = true;
            json["key"] = key;
            json["x"] = world.x;
            json["y"] = world.y;
            SceneManager::networkSend(json.getRawString(false));
            object.keyReleased(key, world.x, world.y);
        }
    }
}

void Scene::mouseDragged(int x, int y, int button)
{
    for (ofxUICanvas &gui : guis) {
        if (gui.getRect()->inside(x, y) && gui.isVisible()) {
            return;
        }
    }

    ofVec2f world = SceneManager::getWorldMouse();
    for (GameObject &object : objects) {
        if (object.ip == "") {
            ofxJSON json;
            json["ip"] = SceneManager::getIP();
            json["mouseDragged"] = true;
            json["x"] = world.x;
            json["y"] = world.y;
            json["button"] = button;
            SceneManager::networkSend(json.getRawString(false));
            object.mouseDragged(world.x, world.y, button);
        }
    }
}

void Scene::mousePressed(int x, int y, int button)
{
    for (ofxUICanvas &gui : guis) {
        if (gui.getRect()->inside(x, y) && gui.isVisible()) {
            return;
        }
    }

    ofVec2f world = camera.worldPositionFrom(ofVec2f(x, y));
    for (GameObject &object : objects) {
        if (object.ip == "") {
            ofxJSON json;
            json["ip"] = SceneManager::getIP();
            json["mousePressed"] = true;
            json["x"] = world.x;
            json["y"] = world.y;
            json["button"] = button;
            SceneManager::networkSend(json.getRawString(false));
            object.mousePressed(world.x, world.y, button);
        }
    }
}

void Scene::mouseReleased(int x, int y, int button)
{
    for (ofxUICanvas &gui : guis) {
        if (gui.getRect()->inside(x, y) && gui.isVisible()) {
            return;
        }
    }

    ofVec2f world = camera.worldPositionFrom(ofVec2f(x, y));
    for (GameObject &object : objects) {
        if (object.ip == "") {
            ofxJSON json;
            json["ip"] = SceneManager::getIP();
            json["mouseReleased"] = true;
            json["x"] = world.x;
            json["y"] = world.y;
            json["button"] = button;
            SceneManager::networkSend(json.getRawString(false));
            object.mouseReleased(world.x, world.y, button);
        }
    }
}

void Scene::networkRecieved(std::string message)
{
    ofxJSON json(message);
    string ip = json["ip"].asString();
    int key = json["key"].asInt();
    int x = json["x"].asFloat();
    int y = json["y"].asFloat();
    int button = json["button"].asInt();

    if (json["keyPressed"].asBool()) {
        for (GameObject &object : objects) {
            if (object.ip == ip) {
                object.keyPressed(key, x, y);
            }
        }
    }
    if (json["keyReleased"].asBool()) {
        for (GameObject &object : objects) {
            if (object.ip == ip) {
                object.keyReleased(key, x, y);
            }
        }
    }
    if (json["mouseDragged"].asBool()) {
        for (GameObject &object : objects) {
            if (object.ip == ip) {
                object.mouseDragged(x, y, button);
            }
        }
    }
    if (json["mousePressed"].asBool()) {
        for (GameObject &object : objects) {
            if (object.ip == ip) {
                object.mousePressed(x, y, button);
            }
        }
    }
    if (json["mouseReleased"].asBool()) {
        for (GameObject &object : objects) {
            if (object.ip == ip) {
                object.mouseReleased(x, y, button);
            }
        }
    }

    for (GameObject &object : objects) {
        object.networkRecieved(message);
    }
}

void Scene::add(GameObject &object)
{
    objects.push_back(object);
}

void Scene::add(ofxUICanvas &gui)
{
    guis.push_back(gui);
}
