#include "flash.h"

Flash::Flash(float _key, Unit &_unit)
    : Skill(_key, 50, 1.f, _unit)
    , range(480)
{
    sound.load("sound/flash.mp3");
}

void Flash::keyReleased(int key, int x, int y)
{
    sound.play();

    ofVec2f world(x, y);
    ofVec2f difference = world - unit.position;
    if (difference.length() > range) {
        unit.position += difference.getNormalized() * range;
    } else {
        unit.position.set(world);
    }
    unit.setTargetPosition(unit.position);
}
