#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include "scenemanager.h"
#include "ofxUI.h"
#include "editorscene.h"

class ResultScene : public Scene
{
public:
    ResultScene(bool win);
    void exit();
    void uiEvent(ofxUIEventArgs &e);
    ofxUICanvas ui;
};

#endif // RESULTSCENE_H
