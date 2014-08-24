#include "ValueScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
USING_NS_CC;
Scene* ValueScene::createScene(){
	auto scene = Scene::create();
	auto layer = ValueScene::create();
	scene->addChild(layer);
	return scene;
}
bool ValueScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto tempText = LabelTTF::create("ValueScene", "Segoe UI", 36);
	tempText->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(tempText);

	ADD_RETURN_BUTTON();
	return true;
}
bool ValueScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
	if (bTouch){
		Director::getInstance()->popScene();
	}
	return true;
}
void ValueScene::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ValueScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseBinder = EventListenerMouse::create();
}
void ValueScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
