#include "ConstructionScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* ConstructionScene::createScene(){
	auto scene = Scene::create();
	auto layer = ConstructionScene::create();
	scene->addChild(layer);
	return scene;
}
bool ConstructionScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto tempText = LabelTTF::create("ConstructionScene", "Segoe UI", 36);
	tempText->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(tempText);

	b2Aquarium = Sprite::create("b2aquarium.png");
	b2Aquarium->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	b2Aquarium->setPosition(visibleSize.width / 2, 0);
	this->addChild(b2Aquarium);
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
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ConstructionScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseBinder = EventListenerMouse::create();
}
void ConstructionScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
