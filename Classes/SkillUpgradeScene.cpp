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

	middleCircle = DrawNode::create();
	midPoint = Vec2(visibleSize.width/2, visibleSize.height/2);
	middleCircle->drawDot(midPoint, circleRadius, circleColor);
	this->addChild(middleCircle);

	equipmentText = LabelTTF::create("Equipment", "Segoe UI", 36);
	equipmentText->setPosition(visibleSize.width * 3 / 4, visibleSize.height * 3 / 4);
	equipmentText->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(equipmentText);

	collectionText = LabelTTF::create("Collection", "Segoe UI", 36);
	collectionText->setPosition(visibleSize.width / 4, visibleSize.height * 3 / 4);
	equipmentText->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(collectionText);

	constructText = LabelTTF::create("Construction", "Segoe UI", 36);
	constructText->setPosition(visibleSize.width * 3 / 4, visibleSize.height / 4);
	constructText->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(constructText);

	valueText = LabelTTF::create("Value", "Segoe UI", 36);
	valueText->setPosition(visibleSize.width / 4, visibleSize.height / 4);
	valueText->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(valueText);
	return true;
}


bool SkillUpgradeScene::onTouchBegan(Touch* touch, Event* event){
	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
	if (bTouch){ 
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