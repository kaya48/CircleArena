#include "unit.h"

#include "scenemanager.h"

Unit::Unit()
    : GameObject()
    , targetPosition(position)
    , time(0.f)
{
    tag = "Unit";

    gui.setVisible(false);
    gui.setInput(false);

    damageSound.load("sound/damage.mp3");
}

void Unit::setup()
{
    hp = maxHP;
    mp = maxMP;
    targetPosition = position;
    for (int i = 0; i < skills.size(); i++) {
        skills[i]->setup();
    }
    gui.setVisible(true);
    gui.addMinimalSlider("HP", 0.f, maxHP, &hp)->setColorFill(ofColor::green);
    gui.addMinimalSlider("MP", 0.f, maxMP, &mp)->setColorFill(ofColor::blueViolet);
    gui.autoSizeToFitWidgets();
}



void Unit::update()
{
    float movement = speed * ofGetLastFrameTime();
    ofVec2f direction = targetPosition - position;

    if ((direction.length() * 2) > movement) {
        position += direction.getNormalized() * movement;
    } else {
        position = targetPosition;
    }

    time += ofGetLastFrameTime();
    if (time >= 3.f) {
        time = 0.f;
        hp = std::min(100.f, std::max(hp + hpr, 0.f));
        mp = std::min(100.f, std::max(mp + mpr, 0.f));
    }

    for (vector<unique_ptr<Skill>>::iterator
         begin = skills.begin(),
         end = skills.end();
         begin != end;
         begin++) {

        (*begin)->update();
        if ((*begin)->time < (*begin)->coolTime) {
            (*begin)->time += ofGetLastFrameTime();
        } else {
            (*begin)->time = (*begin)->coolTime;
        }
    }

    Camera &camera = SceneManager::getCamera();
    ofVec2f screenPosition = camera.screenPositionFrom(position);
    gui.getRect()->setX(screenPosition.x - gui.getRect()->getHalfWidth());
    gui.getRect()->setY(screenPosition.y + radius * ofGetHeight() / camera.height + gui.getRect()->getHalfHeight());
}

void Unit::exit()
{
    for (int i = 0; i < skills.size(); i++) {
        skills[i]->exit();
    }
    gui.setVisible(false);
    gui.disable();
    gui.removeWidgets();
}

void Unit::keyPressed(int key, int x, int y)
{
    for (int i = 0; i < skills.size(); i++) {
        if (skills[i]->key == key) {
            skills[i]->keyPressed(key, x, y);
        }
    }
}

void Unit::keyReleased(int key, int x, int y)
{
    for (int i = 0; i < skills.size(); i++) {
        if (skills[i]->key == key) {
            if (skills[i]->time >= skills[i]->coolTime) {
                skills[i]->time = 0.f;
                if (mp >= skills[i]->cost) {
                    skills[i]->keyReleased(key, x, y);
                    mp -= skills[i]->cost;
                }
            }
        }

    }
}

void Unit::mouseDragged(int x, int y, int button)
{
    setTargetPosition(ofVec2f(x, y));
    for (int i = 0; i < skills.size(); i++) {
        skills[i]->mouseDragged(x, y, button);
    }
}

void Unit::mousePressed(int x, int y, int button)
{
    setTargetPosition(ofVec2f(x, y));
    for (int i = 0; i < skills.size(); i++) {
        skills[i]->mousePressed(x, y, button);
    }
}

void Unit::mouseReleased(int x, int y, int button)
{
    for (int i = 0; i < skills.size(); i++) {
        skills[i]->mouseReleased(x, y, button);
    }
}

void Unit::setTargetPosition(ofVec2f position)
{
    targetPosition = position;
}

void Unit::addSkill(Skill *&&skill)
{
    skills.push_back(unique_ptr<Skill>(skill));
}

void Unit::damage(float amount)
{
    damageSound.play();
    hp = std::min(100.f, std::max(hp - amount, 0.f));
}

bool Unit::isDead()
{
    return hp <= 0;
}
