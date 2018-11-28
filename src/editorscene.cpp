#include "editorscene.h"

EditorScene::EditorScene()
{
    hue = ofColor::green.getHue();
    saturation = ofColor::green.getSaturation();
    brightness = ofColor::green.getBrightness();

    Camera camera = SceneManager::getCamera();

    unit.reset(new Unit());
    unit->radius = 48;
    unit->position = ofVec2f(camera.width*2.f/4.f, camera.height/2.f);
    unit->color = ofColor::green;
    unit->maxHP = 100;
    unit->maxMP = 100;
    unit->hpr = 10.f;
    unit->mpr = 30.f;
    unit->speed = 480;
    unit->attack = 10;
    unit->addSkill(new Shot('q', *unit));
    unit->addSkill(new Flash('e', *unit));
    add(*unit);

    enemy.reset(new Unit());
    enemy->ip = "enemy";
    enemy->radius = 48;
    enemy->position = ofVec2f(camera.width*3.f/4.f, camera.height/2.f);
    enemy->color = ofColor::red;
    enemy->maxHP = 100;
    enemy->maxMP = 100;
    enemy->hpr = 10.f;
    enemy->mpr = 30.f;
    enemy->speed = 480;
    enemy->attack = 10;
    enemy->addSkill(new Shot('q', *enemy));
    enemy->addSkill(new Flash('e', *enemy));
    add(*enemy);

    setUIFont(editor);
    editor.addLabel("Unit", OFX_UI_FONT_LARGE);
    editor.setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    editor.addLabelButton("ready ok", false, 280, 72);
    editor.setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

    editor.addLabel("");
    editor.addSpacer();
    editor.addLabel("status");
    editor.setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    editor.addLabelButton("Point", false, 160, 40);
    editor.addLabel("point", "0");
    editor.setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    editor.addSpacer();
    statuss.push_back("MaxHP");
    statuss.push_back("HPR");
    statuss.push_back("MaxMP");
    statuss.push_back("MPR");
    statuss.push_back("Speed");
    statuss.push_back("Attack");

    for (string &status : statuss) {
        addStatus(status);
    }

    editor.addLabel("");
    editor.addSpacer();
    editor.addLabel("color");
    editor.addSpacer();
    editor.addMinimalSlider("hue", 0.f, 255.f, &hue, 500, 80);
    editor.addMinimalSlider("saturation", 0.f, 255.f, &saturation, 500, 80);
    editor.addMinimalSlider("brightness", 0.f, 255.f, &brightness, 500, 80);

    editor.addLabel("");
    editor.addSpacer();
    editor.addLabel("skill");
    editor.addSpacer();
    editor.addLabelButton("", false, 500, 80);
    editor.addLabelButton("", false, 500, 80);
    editor.addLabelButton("", false, 500, 80);

    editor.autoSizeToFitWidgets();
    editor.getRect()->setHeight(ofGetHeight());

    add(editor);

    ofAddListener(editor.newGUIEvent, this, &EditorScene::uiEvent);

    bgm.load("sound/editor_bgm.mp3");
    bgm.setLoop(true);
    bgm.play();
}

void EditorScene::update()
{
    unit->color.setHsb(hue, saturation, brightness);

    Scene::update();
}

void EditorScene::exit()
{
    editor.setVisible(false);
    unit->exit();
    enemy->exit();

    bgm.stop();
}

void EditorScene::setUIFont(ofxUICanvas &ui)
{
    ui.setFont("type/mono.ttf");
    ui.setFontSize(OFX_UI_FONT_LARGE, 48);
    ui.setFontSize(OFX_UI_FONT_MEDIUM, 24);
    ui.setFontSize(OFX_UI_FONT_SMALL, 16);
}

void EditorScene::addStatus(string status)
{
    editor.addLabelButton(status, false, 240, 80);
    editor.setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    editor.addLabelButton("<", false, 80, 80)->setName(status + "<");
    editor.addLabel(status + "point", "100");
    editor.addLabelButton(">", false, 80, 80)->setName(status + ">");
    editor.setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
}

void EditorScene::uiEvent(ofxUIEventArgs &e)
{
    if (e.widget->getState() == OFX_UI_STATE_OVER) {

        if (e.isName("ready ok")) {
            SceneManager::setNext("NetworkScene", new NetworkScene());
        } else {

            for (string &status : statuss) {

                if (e.isName(status + "<")) {
                    ofxUILabel *statusInput = (ofxUILabel *)editor.getWidget(status + "point");
                    ofxUILabel *pointInput = (ofxUILabel *)editor.getWidget("point");
                    int statusValue = std::stoi(statusInput->getLabel());
                    int pointValue = std::stoi(pointInput->getLabel());
                    if (statusValue > 1) {
                        statusInput->setLabel(std::to_string(--statusValue));
                        pointInput->setLabel(std::to_string(++pointValue));
                    }

                } else if (e.isName(status + ">")) {

                    ofxUILabel *statusInput = (ofxUILabel *)editor.getWidget(status + "point");
                    ofxUILabel *pointInput = (ofxUILabel *)editor.getWidget("point");
                    int statusValue = std::stoi(statusInput->getLabel());
                    int pointValue = std::stoi(pointInput->getLabel());
                    if (pointValue > 0) {
                        pointInput->setLabel(std::to_string(--pointValue));
                        statusInput->setLabel(std::to_string(++statusValue));
                    }
                }
            }
        }
    }
}
