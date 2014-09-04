#include "CollectionScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
#include "UI.h"
USING_NS_CC;
Scene* CollectionScene::createScene(){
	INIT_SCENE(CollectionScene);
}
bool CollectionScene::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	

	auto roseKnifeBatch = SpriteBatchNode::create("sprite.png");
	auto roseKnife = new Icon();
	roseKnife->create("border-circle.png", "knife.png", &roseKnifeBatch);
	roseKnifeBatch->setPosition(100, visibleSize.height-100);
	this->addChild(roseKnifeBatch);

	auto roseKnifeLogo = LabelTTF::create("Rose\nKnife", UI_FONT, 14.f);
	roseKnifeLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	roseKnifeLogo->setPosition(100,visibleSize.height - 125);
	this->addChild(roseKnifeLogo);

	auto fishTankBatch = SpriteBatchNode::create("sprite.png");
	auto fishTank = new Icon();
	fishTank->create("border-circle.png", "gear.png", &fishTankBatch);
	fishTankBatch->setPosition(200, visibleSize.height- 100);
	this->addChild(fishTankBatch);

	auto fishTankLogo = LabelTTF::create("Expand\nFish Tank", UI_FONT, 14.f);
	fishTankLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	fishTankLogo->setPosition(200, visibleSize.height - 125);
	this->addChild(fishTankLogo);

	auto filterBatch = SpriteBatchNode::create("sprite.png");
	auto filter = new Icon();
	filter->create("border-circle.png", "gear.png", &filterBatch);
	filterBatch->setPosition(300, visibleSize.height - 100);
	this->addChild(filterBatch);

	auto filterLogo = LabelTTF::create("Upgrade\nFilter", UI_FONT, 14.f);
	filterLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	filterLogo->setPosition(300, visibleSize.height - 125);
	this->addChild(filterLogo);

	auto novaBatch = SpriteBatchNode::create("sprite.png");
	auto nova = new Icon();
	nova->create("border-polygon.png", "nova.png", &novaBatch);
	novaBatch->setPosition(400, visibleSize.height - 100);
	this->addChild(novaBatch);

	auto novaLogo = LabelTTF::create("Nova", UI_FONT, 14.f);
	novaLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	novaLogo->setPosition(400, visibleSize.height - 125);
	this->addChild(novaLogo);

	auto pureBatch = SpriteBatchNode::create("sprite.png");
	auto pure = new Icon();
	pure->create("border-polygon.png", "pure.png", &pureBatch);
	pureBatch->setPosition(500, visibleSize.height - 100);
	this->addChild(pureBatch);

	auto pureLogo = LabelTTF::create("Pure", UI_FONT, 14.f);
	pureLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	pureLogo->setPosition(500, visibleSize.height - 125);
	this->addChild(pureLogo);

	auto platonicBatch = SpriteBatchNode::create("sprite.png");
	auto platonic = new Icon();
	platonic->create("border-polygon.png", "pure.png", &platonicBatch);
	platonicBatch->setPosition(600, visibleSize.height - 100);
	this->addChild(platonicBatch);

	auto platonicLogo = LabelTTF::create("Pla\nTonic", UI_FONT, 14.f);
	platonicLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	platonicLogo->setPosition(600, visibleSize.height - 125);
	this->addChild(platonicLogo);


	/*auto iconLogo = LabelTTF::create("test", UI_FONT, 14.f);
	iconLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	iconLogo->setPosition(icon->locationForLogo());
	log("%f %f", icon->locationForLogo().x, icon->locationForLogo().y);
	this->addChild(iconLogo); stub for inserting logo*/
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
