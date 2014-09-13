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
	

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("techtreeicons.plist");
	

	auto roseKnife = Sprite::createWithSpriteFrameName("roseknife.png");
	roseKnife->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(roseKnife);

	auto bioSystem = Sprite::createWithSpriteFrameName("biosystem.png");
	bioSystem->setPosition(visibleSize.width / 3, visibleSize.width / 3);
	this->addChild(bioSystem);

	


	
	
	/*auto roseKnife = Sprite::createWithSpriteFrameName("roseknife.png"); 

	iconBatch->setPosition(0, 0);
	iconBatch->addChild(roseKnife);
	roseKnife->setPosition(visibleSize.width, visibleSize.height);*/
	//this->addChild(iconBatch);

	ADD_RETURN_BUTTON();
	return true;
}
bool CollectionScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
	if (b2Aquarium->getBoundingBox().containsPoint(touchPt)){
		Director::getInstance()->popScene();
		return true;
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

void CollectionScene::Mainloop(float){

}