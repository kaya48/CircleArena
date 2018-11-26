#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include "scenemanager.h"
#include "ofxUI.h"
#include "ofxJSON.h"
#include "unit.h"
#include "shot.h"
#include "flash.h"
#include "networkscene.h"
#include "ofSoundPlayer.h"

class EditorScene : public Scene
{
public:
    EditorScene();

    void update();
    void exit();

    void setUIFont(ofxUICanvas &ui);
    void setStatus(ofxUISlider *slider);

private:
    void addStatus(string status);
    void uiEvent(ofxUIEventArgs &e);

    ofxUICanvas editor;

    float hue;
    float saturation;
    float brightness;

    vector<string> statuss;

    unique_ptr<Unit> unit;
    unique_ptr<Unit> enemy;

    ofSoundPlayer bgm;
};

#endif // EDITORSCENE_H
