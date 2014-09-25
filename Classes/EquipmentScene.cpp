#include "EquipmentScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
#include "ValueScene.h"
#include "CollectionScene.h"
#include "ConstructionScene.h"
USING_NS_CC;
Scene* EquipmentScene::createScene(){
	INIT_SCENE(EquipmentScene);
}
bool EquipmentScene::init(){
	if (!Layer::init()){
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	
	auto bgimage = Sprite::create("background/dimension.png");
	bgimage->setPosition(visibleSize / 2);
	bgimage->setScale(1.3f);
	this->addChild(bgimage);

	auto tempText = LabelTTF::create("EquipmentScene", "Segoe UI", 36);
	tempText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	tempText->setPosition(visibleSize.width / 2, visibleSize.height);
	this->addChild(tempText);

	

	ADD_RETURN_BUTTON();
	return true;
}
bool EquipmentScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	ADD_RETURN_LISTENER(touchPt);
	return true;
}

void EquipmentScene::onTouchMoved(Touch* touch, Event* event) {
    Mouse::onTouchMoved(touch, event);
}

void EquipmentScene::onTouchEnded(Touch* touch, Event* event) {
    Mouse::onTouchEnded(touch, event);
}

void EquipmentScene::onTouchCancelled(Touch* touch, Event* event) {
    Mouse::onTouchCancelled(touch, event);
}

void EquipmentScene::onEnter(){
	INIT_LISTENER(EquipmentScene);
}
void EquipmentScene::onExit() {
    _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

    Mouse::Initialize();

	Layer::onExit();
}
