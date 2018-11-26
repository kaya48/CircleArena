#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "scenemanager.h"
#include "editorscene.h"
#include "ofTrueTypeFont.h"
#include "ofSoundPlayer.h"

class TitleScene : public Scene
{
public:
    TitleScene();

    void update();
    void draw();
    void exit();
    void mouseReleased(int x, int y, int button);

    ofTrueTypeFont largeFont;
    ofTrueTypeFont smallFont;

    string titleString;
    string tapToTheScreenString;

    ofVec2f titlePosition;
    ofVec2f tapToTheScreenPosition;

    float time;

    ofSoundPlayer bgm;
};

#endif // TITLESCENE_H
