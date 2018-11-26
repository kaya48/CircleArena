#ifndef SHOT_H
#define SHOT_H

#include "skill.h"
#include "unit.h"
#include "bullet.h"
#include "ofMath.h"
#include <vector>
#include <memory>
#include "ofSoundPlayer.h"

using std::vector;
using std::unique_ptr;

using std::reference_wrapper;

class Shot : public Skill
{
public:
    Shot(int _key, Unit &_unit);

    void keyReleased(int key, int x, int y);

private:

    float speed;
    float range;
    vector<unique_ptr<Bullet>> bullets;

    ofSoundPlayer sound;
};

#endif // SHOT_H
