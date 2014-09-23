#include "ValueScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
#include "EquipmentScene.h"
#include "CollectionScene.h"
#include "ConstructionScene.h"
USING_NS_CC;
Scene* ValueScene::createScene(){
	INIT_SCENE(ValueScene);
}
bool ValueScene::init(){
	if (!Layer::init()){
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	auto bgimage = Sprite::create("background/dimension.png");
	bgimage->setPosition(visibleSize / 2);
	bgimage->setScale(1.3f);
	this->addChild(bgimage);

	auto tempText = LabelTTF::create("ValueScene", "Segoe UI", 36);
	tempText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	tempText->setPosition(visibleSize.width/2, visibleSize.height);
	this->addChild(tempText);

	ADD_RETURN_BUTTON();
	return true;
}
bool ValueScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	ADD_RETURN_LISTENER(touchPt);

	return true;
}
void ValueScene::onEnter(){
	INIT_LISTENER(ValueScene);
}
void ValueScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
