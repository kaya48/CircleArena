#include "bullet.h"

Bullet::Bullet(string _ip, float _radius, float _attack, float _range, float _speed, ofVec2f _position, ofVec2f _direction)
    : attack(_attack)
    , range(_range)
    , speed(_speed)
    , direction(_direction)
    , startPosition(_position)
{
    ip = _ip;
    radius = _radius;
    position = _position;
}

void Bullet::init(string _ip, float _radius, float _attack, float _range, float _speed, ofVec2f _position, ofVec2f _direction)
{
    attack = _attack;
    range = _range;
    speed = _speed;
    direction = _direction;
    startPosition = _position;

    ip = _ip;
    radius = _radius;
    position = _position;
}

void Bullet::update()
{
    if (isActive()) {
        position += direction * speed * ofGetLastFrameTime();
        if (startPosition.distance(position) >= range) {
            setActive(false);
        }

        for (GameObject &collisionObject : collision.objects) {
            if (collisionObject.tag == "Unit") {
                if (ip != collisionObject.ip) {
                    Unit &collisionUnit = (Unit&)collisionObject;
                    collisionUnit.damage(attack);
                    setActive(false);
                }
            }
        }
    }

}
