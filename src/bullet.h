#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"
#include "unit.h"

class Bullet : public GameObject
{
public:
    Bullet(string _ip, float _radius, float _attack, float _range, float _speed, ofVec2f _position, ofVec2f _direction);

    void init(string _ip, float _radius, float _attack, float _range, float _speed, ofVec2f _position, ofVec2f _direction);

    void update();

private:

    float attack;
    float range;
    float speed;
    ofVec2f direction;
    ofVec2f startPosition;
};

#endif // BULLET_H
