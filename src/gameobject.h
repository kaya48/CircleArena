#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "object.h"
#include "ofAppRunner.h"
#include "ofVec2f.h"
#include "ofColor.h"
#include "collision.h"
#include <string>
#include <vector>
#include <memory>

using std::vector;
using std::reference_wrapper;

using std::string;

class GameObject : public Object
{
public:
    static void instance(GameObject &object);


    GameObject();

    bool isCollision(GameObject &object);

    void setActive(bool _active);
    bool isActive();

    bool fill;
    float radius;
    ofVec2f position;
    ofColor color;
    string tag;
    Collision collision;
    string ip;
    bool active;
};

#endif // GAMEOBJECT_H
