#include "collision.h"

#include "gameobject.h"

Collision::Collision(GameObject &_object)
    : object(_object)
{

}

void Collision::clear()
{
    objects.clear();
}

void Collision::judge(GameObject &target)
{
    if (target.isActive()) {
        if (object.isCollision(target)) {
            if (&object != &target) {
                objects.push_back(target);
            }
        }
    }
}

void Collision::judge(vector<reference_wrapper<GameObject> > &targets)
{
    for (GameObject &target : targets) {
        judge(target);
    }
}

void Collision::judge(vector<unique_ptr<GameObject> > &targets)
{
    for (int i = 0; i < targets.size(); i++) {
        judge(*targets[i]);
    }
}
