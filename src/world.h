#ifndef WORLD_H
#define WORLD_H

#include "unit.h"
#include "shot.h"
#include "flash.h"
#include "scenemanager.h"
#include "ofxNetwork.h"
#include "ofxJSON.h"
#include "resultscene.h"
#include "ofSoundPlayer.h"

#include <memory>

using std::unique_ptr;

class World : public Scene
{
public:
    World(string ip, bool server);

    void update();
    void exit();

    unique_ptr<Unit> unit;
    unique_ptr<Unit> enemy;

    ofSoundPlayer bgm;
};

#endif // WORLD_H
