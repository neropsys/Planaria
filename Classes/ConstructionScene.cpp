#include "ConstructionScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
USING_NS_CC;
Scene* ConstructionScene::createScene(){
	INIT_SCENE(ConstructionScene);
}
bool ConstructionScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto tempText = LabelTTF::create("ConstructionScene", "Segoe UI", 36);
	tempText->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(tempText);

	ADD_RETURN_BUTTON();
	return true;
}
bool ConstructionScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
	if (bTouch){
		Director::getInstance()->popScene();
	}
	return true;
}
void ConstructionScene::onEnter(){
	INIT_LISTENER(ConstructionScene);
}
void ConstructionScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
