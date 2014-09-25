#include "ResultScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
#include "PlayerSkill.h"
USING_NS_CC;

Scene* ResultScene::createScene(){
    INIT_SCENE(ResultScene);
}
bool ResultScene::init(){
    if (!Layer::init()){
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto bgimage = Sprite::create("background/dimension-light.png");
    this->addChild(bgimage, Z_BACK);
    bgimage->setPosition(visibleSize / 2);
    bgimage->setScale(1.3);

    auto bgimage2 = Sprite::create("background/water.png");
    this->addChild(bgimage2, Z_BACK);
    bgimage2->setPosition(0, visibleSize.height / 2);
    bgimage2->setAnchorPoint(Vec2(0, 0.5));
    bgimage2->setScale(3, 1.3);
    bgimage2->setBlendFunc(GL_BLEND_SCREENMODE);
    bgimage2->setOpacity(200);
    bgimage2->setTag(100);

    auto tempText = LabelTTF::create("Total money you get: ", "Segoe UI", 36);
    tempText->setPosition(100, visibleSize.height - 300);
    tempText->setHorizontalAlignment(TextHAlignment::LEFT);
    tempText->setVerticalAlignment(TextVAlignment::CENTER);
    tempText->setAnchorPoint(Vec2(0, 0.5));
    tempText->setTag(101);
    this->addChild(tempText, Z_UI);

    auto amountPla = LabelTTF::create("Amount of planaria you make: ", "Segoe UI", 36);
    amountPla->setPosition(tempText->getPositionX(), tempText->getPositionY() - 60);
    amountPla->setHorizontalAlignment(TextHAlignment::LEFT);
    amountPla->setVerticalAlignment(TextVAlignment::CENTER);
    amountPla->setAnchorPoint(Vec2(0, 0.5));
    amountPla->setTag(102);
    this->addChild(amountPla, Z_UI);

    auto amountDead = LabelTTF::create("Amount of planaria you cut: ", "Segoe UI", 36);
    amountDead->setPosition(amountPla->getPositionX(), amountPla->getPositionY() - 60);
    amountDead->setHorizontalAlignment(TextHAlignment::LEFT);
    amountDead->setVerticalAlignment(TextVAlignment::CENTER);
    amountDead->setAnchorPoint(Vec2(0, 0.5));
    amountDead->setTag(103);
    this->addChild(amountDead, Z_UI);

    this->schedule(schedule_selector(ResultScene::Mainloop));

    b2Aquarium = Sprite::create("retry.png"); \
    b2Aquarium->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM); \
    b2Aquarium->setPosition(visibleSize.width / 2, 0); \
    this->addChild(b2Aquarium);

    return true;
}

void ResultScene::Mainloop(float t) {
    Sprite *bgimage2 = (Sprite *)getChildByTag(100);

    bgimage2->setPositionX(bgimage2->getPositionX() - 1);

    if (bgimage2->getPositionX() < -bgimage2->getContentSize().width / 1.5){
        bgimage2->setPositionX(0);
    }
}

bool ResultScene::onTouchBegan(Touch* touch, Event* event){
    Mouse::onTouchBegan(touch, event);

    auto touchPt = touch->getLocation();
    auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
    if (bTouch){
        HelloWorld::Initialize();
        Director::getInstance()->popScene();
    }
    return true;
}

void ResultScene::onTouchMoved(Touch* touch, Event* event) {
    Mouse::onTouchMoved(touch, event);
}

void ResultScene::onTouchEnded(Touch* touch, Event* event) {
    Mouse::onTouchEnded(touch, event);
}

void ResultScene::onTouchCancelled(Touch* touch, Event* event) {
    Mouse::onTouchCancelled(touch, event);
}

void ResultScene::onEnter(){
    INIT_LISTENER(ResultScene);

    auto lMoney = (LabelTTF *)getChildByTag(101);
    auto lDeadPla = (LabelTTF *)getChildByTag(102);
    auto lCutPla = (LabelTTF *)getChildByTag(103);

    lMoney->setString("Money you got: " + std::to_string((int)Area::humanCoin));
    lDeadPla->setString("Amount of dead planaria: " + std::to_string((int)Area::deadPlas));
    lCutPla->setString("Amount of planaria you cut: " + std::to_string((int)Area::cutPlas));
}

void ResultScene::onExit() {
    _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

    Mouse::Initialize();

    Layer::onExit();
}
