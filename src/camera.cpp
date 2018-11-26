#include "camera.h"

Camera::Camera()
    : width(2560)
    , height(1440)
    , position(ofVec2f::zero())
{

}

void Camera::draw(GameObject &object)
{
    if (object.isActive()) {
        ofPushMatrix();
        ofPushStyle();
        if (object.fill) {
            ofFill();
        } else {
            ofNoFill();
        }
        ofSetColor(object.color);
        ofTranslate(screenPositionFrom(object.position));
        ofScale(ofGetWidth() / width, ofGetHeight() / height);
        ofDrawCircle(0.f, 0.f, object.radius);
        ofPopStyle();
        ofPopMatrix();
    }
}

void Camera::draw(vector<reference_wrapper<GameObject> > &objects)
{
    for (GameObject &object : objects) {
        draw(object);
    }
}

void Camera::draw(vector<unique_ptr<GameObject> > &objects)
{
    for (int i = 0; i < objects.size(); i++) {
        draw(*objects[i]);
    }
}

ofVec2f Camera::screenPositionFrom(ofVec2f world)
{
    ofVec2f cameraPosition = world - position;
    ofVec2f screenPosition;
    screenPosition.x = ofGetWidth()  * cameraPosition.x / width;
    screenPosition.y = ofGetHeight() * cameraPosition.y / height;
    return screenPosition;
}

ofVec2f Camera::worldPositionFrom(ofVec2f screen)
{
    ofVec2f position = this->position;
    position.x += width  * screen.x / ofGetWidth();
    position.y += height * screen.y / ofGetHeight();
    return position;
}
