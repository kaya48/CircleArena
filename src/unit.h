#ifndef UNIT_H
#define UNIT_H

#include "gameobject.h"
#include "skill.h"
#include <vector>
#include <memory>
#include "ofxUI.h"
#include "ofSoundPlayer.h"

using std::vector;
using std::unique_ptr;

class Unit : public GameObject
{
public:
    Unit();

    void setup();
    void update();
    void exit();

    void keyPressed(int key, int x, int y);
    void keyReleased(int key, int x, int y);

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    void setTargetPosition(ofVec2f position);
    void addSkill(Skill *&&skill);
    void damage(float amount);
    bool isDead();

    float maxHP;
    float maxMP;
    float hpr;
    float mpr;
    float speed;
    float attack;

private:
    float hp;
    float mp;
    float time;
    ofVec2f targetPosition;
    vector<unique_ptr<Skill>> skills;

    ofxUICanvas gui;

    ofSoundPlayer damageSound;
};

#endif // UNIT_H
