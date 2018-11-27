#include "networkscene.h"

NetworkScene::NetworkScene()
{
    setUIFont(selectUI);
    selectUI.addLabelButton("Server", false, 560, 240);
    selectUI.addLabelButton("Client", false, 560, 240);
    setUICenter(selectUI);

    setUIFont(serverUI);
    serverUI.addLabel("Server");
    serverUI.addSpacer();
    serverUI.addLabel("it's private ip.", OFX_UI_FONT_SMALL);
    serverUI.addLabel(ofxIPAddress::getPrivate());
    serverUI.addLabelButton("return", false, 560, 80);
    setUICenter(serverUI);
    serverUI.setVisible(false);

    setUIFont(clientUI);
    clientUI.addLabel("Client");
    clientUI.addSpacer();
    clientUI.addLabel("Please enter private ip.", OFX_UI_FONT_SMALL);
    clientUI.addTextInput("ipInput", "", 560, 80)->setAutoClear(false);
    clientUI.addLabelButton("connect", false, 560, 240);
    clientUI.addLabelButton("return", false, 560, 80);
    setUICenter(clientUI);
    clientUI.setVisible(false);

    setUIFont(connectUI);
    connectUI.addLabel("Connect");
    connectUI.addSpacer();
    connectUI.addMinimalSlider("Loading", 0.f, 1.f, &time)->setColorFill(ofColor::green);
    setUICenter(connectUI);
    connectUI.setVisible(false);

    ofAddListener(selectUI.newGUIEvent, this, &NetworkScene::selectEvent);
    ofAddListener(serverUI.newGUIEvent, this, &NetworkScene::serverEvent);
    ofAddListener(clientUI.newGUIEvent, this, &NetworkScene::clientEvent);

    bgm.load("sound/editor_bgm.mp3");
    bgm.setLoop(true);
    bgm.play();
}

void NetworkScene::setup()
{
    time = 0.f;
    sended = false;
}

void NetworkScene::update()
{
    time += ofGetLastFrameTime();
    if (time > 1.0) {
        time = 0;
    }
}

void NetworkScene::exit()
{
    ofRemoveListener(selectUI.newGUIEvent, this, &NetworkScene::selectEvent);
    ofRemoveListener(serverUI.newGUIEvent, this, &NetworkScene::serverEvent);
    ofRemoveListener(clientUI.newGUIEvent, this, &NetworkScene::clientEvent);
    connectUI.setVisible(false);
    serverUI.setVisible(false);

    bgm.stop();
}

void NetworkScene::networkRecieved(string message)
{
    bool server = false;
    if (!sended) {
        SceneManager::setConnect(true);
        SceneManager::networkSend(SceneManager::getIP());
        sended = true;
        server = true;
    }

    connectUI.removeWidgets();
    SceneManager::setNext("world", new World(message, server));

}



void NetworkScene::selectEvent(ofxUIEventArgs &e)
{
    if (e.isName("Server")) {
        if (e.widget->getState() == OFX_UI_STATE_OVER) {
            selectUI.setVisible(false);
            serverUI.setVisible(true);
        }
    }

    if (e.isName("Client")) {
        if (e.widget->getState() == OFX_UI_STATE_OVER) {
            selectUI.setVisible(false);
            clientUI.setVisible(true);
            ofxUITextInput *input = (ofxUITextInput *)clientUI.getWidget("ipInput");
            input->setFocus(true);
        }
    }
}

void NetworkScene::serverEvent(ofxUIEventArgs &e)
{
    if (e.isName("return")) {
        if (e.widget->getState() == OFX_UI_STATE_OVER) {
            serverUI.setVisible(false);
            selectUI.setVisible(true);
        }
    }
}

void NetworkScene::clientEvent(ofxUIEventArgs &e)
{
    if (e.isName("return")) {
        if (e.widget->getState() == OFX_UI_STATE_OVER) {
            clientUI.setVisible(false);
            selectUI.setVisible(true);
        }
    }

    if (e.isName("connect")) {
        if (e.widget->getState() == OFX_UI_STATE_OVER) {
            clientUI.setVisible(false);
            connectUI.setVisible(true);
            ofxUITextInput *input = (ofxUITextInput *)clientUI.getWidget("ipInput");
            SceneManager::networkConnect(input->getTextString());
            SceneManager::networkSend(SceneManager::getIP());
            sended = true;
        }
    }
}

void NetworkScene::setUIFont(ofxUICanvas &ui)
{
    ui.setFont("type/mono.ttf");
    ui.setFontSize(OFX_UI_FONT_LARGE, 48);
    ui.setFontSize(OFX_UI_FONT_MEDIUM, 24);
    ui.setFontSize(OFX_UI_FONT_SMALL, 16);
}

void NetworkScene::setUICenter(ofxUICanvas &ui)
{
    ui.autoSizeToFitWidgets();
    ui.getRect()->setX(ofGetWidth() / 2.f - ui.getRect()->getHalfWidth());
    ui.getRect()->setY(ofGetHeight() / 2.f - ui.getRect()->getHalfHeight());
}
