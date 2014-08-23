#include "SkillUpgradeScene.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Scene* SkillUpgradeScene::createScene(){
	auto scene = Scene::create();

	auto layer = SkillUpgradeScene::create();

	scene->addChild(layer);
	
	return scene;

}
void SkillUpgradeScene::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SkillUpgradeScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SkillUpgradeScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SkillUpgradeScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void SkillUpgradeScene::onExit(){
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool SkillUpgradeScene::init(){
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	b2Aquarium = Sprite::create("b2aquarium.png");
	b2Aquarium->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	b2Aquarium->setPosition(visibleSize.width/2, 0);
	this->addChild(b2Aquarium);
	/*
	auto b2Aquarium = MenuItemImage::create("b2aquarium.png", "b2aquarium.png", CC_CALLBACK_1(SkillUpgradeScene::returnToAquarium, this));
	b2Aquarium->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	auto *menu = Menu::create(b2Aquarium, NULL);
	menu->setPosition(visibleSize.width/2, 0);
	this->addChild(menu, 1);*/

	return true;
}
void SkillUpgradeScene::returnToAquarium(Ref* pSender){
	log("clicked");
}

bool SkillUpgradeScene::onTouchBegan(Touch* touch, Event* event){
	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);
	if (bTouch){ 
		log("clicked"); 
		Director::getInstance()->popScene();
	}
	return true;
}
void SkillUpgradeScene::onTouchMoved(Touch* touch, Event* event){

}
void SkillUpgradeScene::onTouchEnded(Touch* touch, Event* event){

}
void SkillUpgradeScene::onTouchCancelled(Touch* touch, Event* event){

}