#include "gameobject.h"

#include "scenemanager.h"

void GameObject::instance(GameObject &object)
{
    SceneManager::instance(object);
}

GameObject::GameObject()
    : fill(true)
    , radius(48)
    , position(ofVec2f::zero())
    , color(ofColor::green)
    , tag("")
    , collision(*this)
    , ip("")
    , active(true)
{

}

bool GameObject::isCollision(GameObject &object)
{
    float distance = position.distance(object.position);
    float radiusSum = radius + object.radius;
    return distance < radiusSum;
}

void GameObject::setActive(bool _active)
{
    active = _active;
}

bool GameObject::isActive()
{
    return active;
}
