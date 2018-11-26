#ifndef FLASH_H
#define FLASH_H

#include "skill.h"
#include "unit.h"
#include "ofSoundPlayer.h"

class Flash : public Skill
{
public:
    Flash(float _key, Unit &_unit);
    void keyReleased(int key, int x, int y);

private:
    float range;

    ofSoundPlayer sound;
};

#endif // FLASH_H
