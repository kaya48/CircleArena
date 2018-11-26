#include "shot.h"

#include "scenemanager.h"

Shot::Shot(int _key, Unit &_unit)
    : Skill(_key, 10, 0.2f, _unit)
    , range(480 * 4)
    , speed(480 * 4)
{
    sound.load("sound/shot.mp3");
}

void Shot::keyReleased(int key, int x, int y)
{
    sound.play();

    ofVec2f world(x, y);
    ofVec2f direction;
    if (world != unit.position) {
        direction = (world - unit.position).getNormalized();
    } else {
        float theta = ofRandom(2 * PI);
        direction = ofVec2f(cos(theta), sin(theta));
    }

    for (int i = 0; i < bullets.size(); i++) {

        if (!bullets[i]->isActive()) {
            bullets[i]->init(unit.ip, unit.radius / 3.f, unit.attack, range, speed, unit.position, direction);
            bullets[i]->setActive(true);
            return;
        }
    }

    unique_ptr<Bullet> newBullet (new Bullet(unit.ip, unit.radius / 3.f, unit.attack, range, speed, unit.position, direction));
    instance(*newBullet);
    bullets.push_back(std::move(newBullet));
}
