#include "CollectionScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
USING_NS_CC;
Scene* CollectionScene::createScene(){
	INIT_SCENE(CollectionScene);
}
bool CollectionScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto tempText = LabelTTF::create("CollectionScene", "Segoe UI", 36);
	tempText->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(tempText);

	ADD_RETURN_BUTTON();
	return true;
}
bool CollectionScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
	if (bTouch){
		Director::getInstance()->popScene();
	}
	return true;
}
void CollectionScene::onEnter(){
	INIT_LISTENER(CollectionScene);
}
void CollectionScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
