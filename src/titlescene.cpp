#include "titlescene.h"

TitleScene::TitleScene()   
{
    largeFont.load("type/mono.ttf", 80);
    smallFont.load("type/mono.ttf", 24);

    titleString = "Circle Arena";
    tapToTheScreenString = "tap to the screen";

    titlePosition.x = (ofGetWidth() - largeFont.stringWidth(titleString)) / 2.f;
    titlePosition.y = (ofGetHeight()- largeFont.stringHeight(titleString))/ 2.f;

    tapToTheScreenPosition.x = (ofGetWidth() - smallFont.stringWidth(tapToTheScreenString)) / 2.f;
    tapToTheScreenPosition.y = ofGetHeight() * 2.f / 3.f - smallFont.stringHeight(tapToTheScreenString) / 2.f;

    time = 0.f;

    bgm.load("sound/title_bgm.mp3");
    bgm.setLoop(true);
    bgm.play();
}

void TitleScene::update()
{
    if (time < 1.f) {
        time += ofGetLastFrameTime();
    } else {
        time = 0.f;
        if (tapToTheScreenString == "") {
            tapToTheScreenString = "tap to the screen";
        } else {
            tapToTheScreenString = "";
        }
    }
}

void TitleScene::draw()
{
    largeFont.drawString(titleString, titlePosition.x, titlePosition.y);
    smallFont.drawString(tapToTheScreenString, tapToTheScreenPosition.x, tapToTheScreenPosition.y);
}

void TitleScene::exit()
{
    bgm.stop();
}

void TitleScene::mouseReleased(int x, int y, int button)
{
    SceneManager::setNext("EditorScene", new EditorScene());
}
