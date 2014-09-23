#include "ConstructionScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
#include "CollectionScene.h"
#include "EquipmentScene.h"
#include "ValueScene.h"
USING_NS_CC;
Scene* ConstructionScene::createScene(){
	INIT_SCENE(ConstructionScene);
}
bool ConstructionScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bgimage = Sprite::create("background/dimension.png");
	bgimage->setPosition(visibleSize / 2);
	bgimage->setScale(1.3f);
	this->addChild(bgimage);

	auto tempText = LabelTTF::create("ConstructionScene", "Segoe UI", 36);
	tempText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	tempText->setPosition(visibleSize.width / 2, visibleSize.height);
	this->addChild(tempText);

	ADD_RETURN_BUTTON();
	return true;
}
bool ConstructionScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	ADD_RETURN_LISTENER(touchPt);
	return true;
}
void ConstructionScene::onEnter(){
	INIT_LISTENER(ConstructionScene);
}
void ConstructionScene::onExit() {
    _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
    Mouse::Initialize();

	Layer::onExit();
}
