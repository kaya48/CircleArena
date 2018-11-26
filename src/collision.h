#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
using std::reference_wrapper;

class GameObject;

class Collision
{
public:
    Collision(GameObject &_object);

    void clear();
    void judge(GameObject &target);
    void judge(vector<reference_wrapper<GameObject>> &targets);
    void judge(vector<unique_ptr<GameObject> > &targets);
    GameObject &getObject();

    vector<reference_wrapper<GameObject>> objects;
private:
    GameObject &object;
};

#endif // COLLISION_H
