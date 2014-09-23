#include "CollectionScene.h"
#include "HelloWorldScene.h"
#include "ConstructionScene.h"
#include "EquipmentScene.h"
#include "ValueScene.h"
#include "ConstructionScene.h"
#include "CollectionScene.h"
USING_NS_CC;
Scene* CollectionScene::createScene(){
	INIT_SCENE(CollectionScene);
}
bool CollectionScene::init(){
	if (!Layer::init()){
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	auto bgimage = Sprite::create("background/dimension.png");
	bgimage->setPosition(visibleSize / 2);
	bgimage->setScale(1.3f);
	this->addChild(bgimage);

	auto tempText = LabelTTF::create("CollectionScene", "Segoe UI", 36);
	tempText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	tempText->setPosition(visibleSize.width / 2, visibleSize.height);
	this->addChild(tempText);


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("iconspritesheet.plist");
	
	nova = Sprite::createWithSpriteFrameName("nova.png");
	nova->setPosition(visibleSize.width * 3.5 / 13, visibleSize.height * 5.8 / 9);
	this->addChild(nova, Z_UI);

	roseKnife = Sprite::createWithSpriteFrameName("roseknife.png");
	roseKnife->setPosition(visibleSize.width / 13, visibleSize.height * 5.8 / 9);
	this->addChild(roseKnife, Z_UI);

	fishTank = Sprite::createWithSpriteFrameName("fishtank.png");
	fishTank->setPosition(visibleSize.width * 3.5 / 13, visibleSize.height * 7.3 / 9);
	this->addChild(fishTank, Z_UI);

	platonic = Sprite::createWithSpriteFrameName("platonic.png");
	platonic->setPosition(visibleSize.width * 4.5 / 13, visibleSize.height * 4.3 / 9);
	this->addChild(platonic, Z_UI);

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
	if (nova->getBoundingBox().containsPoint(touchPt)){
		log("nova touched");
		//do something that nova does

		Area::ppm = 0.f;
		
		if (Area::humanCoin <= 0){//if there's no money
			//give warning sign
		}

		return true;
	}
	if (fishTank->getBoundingBox().containsPoint(touchPt)){
		if (Area::humanCoin < EXT_AQUARIUM_VALUE) return true;
		Area::humanCoin -= EXT_AQUARIUM_VALUE;
		Area::maxPlanaria = MAXNUMBER;
		log("fishtank touched");
		return true;
	}
	if (roseKnife->getBoundingBox().containsPoint(touchPt)){
		log("roseKnife touched");
		return true;
	}
	if (platonic->getBoundingBox().containsPoint(touchPt)){
		if (Area::humanCoin < PLATONIC_VALUE) return true;
		Area::humanCoin -= PLATONIC_VALUE;
		log("platonic touched");
		for (auto child : Planaria::Plas){
			child->increaseGrowthRate(.1f);
		}
		return true;
	}


	return true;
}
void CollectionScene::onEnter(){
	INIT_LISTENER(CollectionScene);
}
void CollectionScene::onExit() {
    _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
    Mouse::Initialize();
	Layer::onExit();
}

void CollectionScene::Mainloop(float){

}