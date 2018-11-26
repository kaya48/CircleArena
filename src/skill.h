#ifndef SKILL_H
#define SKILL_H

#include "gameobject.h"
#include <vector>
#include <memory>
#include "ofxJSON.h"
#include "scenemanager.h"

using std::vector;
using std::reference_wrapper;

class Unit;

class Skill : public Object
{
public:
    static void instance(GameObject &object);

    Skill(int _key, float _cost, float _coolTime, Unit &_unit);

    int key;
    float cost;
    float coolTime;
    float time;
    Unit &unit;
};

#endif // SKILL_H
