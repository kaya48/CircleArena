#ifndef NETWORKSCENE_H
#define NETWORKSCENE_H

#include "world.h"
#include "scenemanager.h"
#include "ofxUI.h"
#include "ofxJSON.h"
#include "ofxipaddress.h"
#include "ofSoundPlayer.h"

class NetworkScene : public Scene
{
public:
    NetworkScene();

    void setup();
    void update();
    void exit();

    void networkRecieved(string message);

private:
    void uiEvent(ofxUIEventArgs &e);
    void selectEvent(ofxUIEventArgs &e);
    void serverEvent(ofxUIEventArgs &e);
    void clientEvent(ofxUIEventArgs &e);

    void setUIFont(ofxUICanvas &ui);
    void setUICenter(ofxUICanvas &ui);
    ofxUICanvas selectUI;
    ofxUICanvas serverUI;
    ofxUICanvas clientUI;
    ofxUICanvas connectUI;


    float time;
    bool sended;

    ofSoundPlayer bgm;
};

#endif // NETWORKSCENE_H
