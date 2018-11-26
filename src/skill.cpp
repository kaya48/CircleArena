#include "skill.h"

#include "unit.h"

void Skill::instance(GameObject &object)
{
    SceneManager::instance(object);
}

Skill::Skill(int _key, float _cost, float _coolTime, Unit &_unit)
    : key(_key)
    , cost(_cost)
    , coolTime(_coolTime)
    , time(0.f)
    , unit(_unit)
{

}
