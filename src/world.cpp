#include "world.h"

World::World(string ip, bool server)
{
    Camera camera = SceneManager::getCamera();
    float unitPoint = 3.f;
    float enemyPoint = 1.f;
    if (server) {
        unitPoint = 1.f;
        enemyPoint = 3.f;
    }

    unit.reset(new Unit());
    unit->radius = 48;
    unit->position = ofVec2f(camera.width*unitPoint/4.f, camera.height/2.f);
    unit->color = ofColor::green;
    unit->maxHP = 100;
    unit->maxMP = 100;
    unit->hpr = 0.f;
    unit->mpr = 30.f;
    unit->speed = 248;
    unit->attack = 10;
    unit->addSkill(new Shot('q', *unit));
    unit->addSkill(new Flash('e', *unit));
    add(*unit);

    enemy.reset(new Unit());
    enemy->radius = 48;
    enemy->position = ofVec2f(camera.width*enemyPoint/4.f, camera.height/2.f);
    enemy->color = ofColor::red;
    enemy->maxHP = 100;
    enemy->maxMP = 100;
    enemy->hpr = 0.f;
    enemy->mpr = 30.f;
    enemy->speed = 248;
    enemy->attack = 10;
    enemy->ip = ip;
    enemy->addSkill(new Shot('q', *enemy));
    enemy->addSkill(new Flash('e', *enemy));
    add(*enemy);

    bgm.load("sound/world_bgm.mp3");
    bgm.setLoop(true);
    bgm.play();
}

void World::update()
{
    if (unit->isDead()) {
        SceneManager::setNext(new ResultScene(false));
    } else if (enemy->isDead()) {
        SceneManager::setNext(new ResultScene(true));
    }

    Scene::update();
}

void World::exit()
{
    bgm.stop();

    Scene::exit();
}
