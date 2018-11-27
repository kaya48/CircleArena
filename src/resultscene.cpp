#include "resultscene.h"

ResultScene::ResultScene(bool win)
{
    ui.setFont("type/mono.ttf");
    ui.setFontSize(OFX_UI_FONT_LARGE, 48);
    ui.setFontSize(OFX_UI_FONT_MEDIUM, 24);
    ui.setFontSize(OFX_UI_FONT_SMALL, 16);

    if (win) {
        ui.addLabel("Win", OFX_UI_FONT_LARGE);
    } else {
        ui.addLabel("Lose", OFX_UI_FONT_LARGE);
    }

    ui.addLabelButton("ok", false);

    ui.autoSizeToFitWidgets();
    ui.getRect()->setX(ofGetWidth() / 2.f - ui.getRect()->getHalfWidth());
    ui.getRect()->setY(ofGetHeight() / 2.f - ui.getRect()->getHalfHeight());

    ofAddListener(ui.newGUIEvent, this, &ResultScene::uiEvent);
}

void ResultScene::exit()
{
    ui.setVisible(false);
}

void ResultScene::uiEvent(ofxUIEventArgs &e)
{
    if (e.isName("ok")) {
        if (e.widget->getState() == OFX_UI_STATE_OVER) {
            SceneManager::setNext("EditorScene", new EditorScene());
        }
    }
}
