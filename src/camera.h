#ifndef CAMERA_H
#define CAMERA_H

#include "gameobject.h"
#include "ofGraphics.h"

class Camera
{
public:
    Camera();

    void draw(GameObject &object);
    void draw(vector<reference_wrapper<GameObject> > &objects);
    void draw(vector<unique_ptr<GameObject> > &objects);

    ofVec2f screenPositionFrom(ofVec2f world);
    ofVec2f worldPositionFrom(ofVec2f screen);

    float width;
    float height;
    ofVec2f position;
};

#endif // CAMERA_H
